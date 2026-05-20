#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "eventdialog.h"
#include "categorydialog.h"
#include "colorcelldelegate.h"
#include "categorybadgedelegate.h"
#include "tagchipdelegate.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QSqlRelation>
#include <QSqlRelationalDelegate>
#include <QSqlQuery>
#include <QSqlError>
#include <QHeaderView>
#include <QFile>
#include <QDir>
#include <QHash>
#include <QTime>
#include <QCalendarWidget>
#include <QTextCharFormat>
#include <QBrush>
#include <QStandardItem>
#include <QColor>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_db(new Database(this))
{
    ui->setupUi(this);
    setupDatabase();
    setupModels();
    setupViews();
    connectSignals();

    loadTodayTab();
    loadWishlistTab();
    loadCalendarTab(QDate::currentDate());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupDatabase()
{
    QString path = "calendar.db";
    bool isNew = !QFile::exists(path);

    if (!m_db->init(path)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть базу данных.");
        return;
    }

    ui->statusbar->showMessage("БД: " + path, 3000);

    if (isNew)
        populateSampleData();
}

void MainWindow::setupModels()
{
    m_categoriesModel = new QSqlTableModel(this, m_db->db());
    m_categoriesModel->setTable("categories");
    m_categoriesModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    m_categoriesModel->select();

    m_eventsModel = new QSqlRelationalTableModel(this, m_db->db());
    m_eventsModel->setTable("events");
    m_eventsModel->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    m_eventsModel->select();

    int categoryIdIdx = m_eventsModel->fieldIndex("category_id");
    if (categoryIdIdx >= 0)
        m_eventsModel->setRelation(categoryIdIdx, QSqlRelation("categories", "id", "name"));

    int dateIdx = m_eventsModel->fieldIndex("date");
    if (dateIdx >= 0)
        m_eventsModel->setSort(dateIdx, Qt::AscendingOrder);

    m_eventsModel->select();

    m_tagsModel = new QSqlTableModel(this, m_db->db());
    m_tagsModel->setTable("tags");
    m_tagsModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    m_tagsModel->select();

    m_todayModel = new QStandardItemModel(this);
    m_wishlistModel = new QStandardItemModel(this);
    m_calendarModel = new QStandardItemModel(this);

    int catId = m_categoriesModel->fieldIndex("id");
    int catName = m_categoriesModel->fieldIndex("name");
    int catColor = m_categoriesModel->fieldIndex("color");

    if (catId >= 0)    m_categoriesModel->setHeaderData(catId, Qt::Horizontal, "ID");
    if (catName >= 0)  m_categoriesModel->setHeaderData(catName, Qt::Horizontal, "Название");
    if (catColor >= 0) m_categoriesModel->setHeaderData(catColor, Qt::Horizontal, "Цвет");

    int evId = m_eventsModel->fieldIndex("id");
    int evTitle = m_eventsModel->fieldIndex("title");
    int evDesc = m_eventsModel->fieldIndex("description");
    int evDate = m_eventsModel->fieldIndex("date");
    int evTime = m_eventsModel->fieldIndex("time");
    int evType = m_eventsModel->fieldIndex("type");
    int evDeadline = m_eventsModel->fieldIndex("is_deadline");
    int evCategory = m_eventsModel->fieldIndex("category_id");

    if (evId >= 0)       m_eventsModel->setHeaderData(evId, Qt::Horizontal, "ID");
    if (evTitle >= 0)    m_eventsModel->setHeaderData(evTitle, Qt::Horizontal, "Название");
    if (evDesc >= 0)     m_eventsModel->setHeaderData(evDesc, Qt::Horizontal, "Описание");
    if (evDate >= 0)     m_eventsModel->setHeaderData(evDate, Qt::Horizontal, "Дата");
    if (evTime >= 0)     m_eventsModel->setHeaderData(evTime, Qt::Horizontal, "Время");
    if (evType >= 0)     m_eventsModel->setHeaderData(evType, Qt::Horizontal, "Тип");
    if (evDeadline >= 0) m_eventsModel->setHeaderData(evDeadline, Qt::Horizontal, "Дедлайн");
    if (evCategory >= 0) m_eventsModel->setHeaderData(evCategory, Qt::Horizontal, "Категория");

    int tagId = m_tagsModel->fieldIndex("id");
    int tagName = m_tagsModel->fieldIndex("name");

    if (tagId >= 0)   m_tagsModel->setHeaderData(tagId, Qt::Horizontal, "ID");
    if (tagName >= 0) m_tagsModel->setHeaderData(tagName, Qt::Horizontal, "Тег");
}

void MainWindow::setupViews()
{
    auto setupTable = [](QTableView *v) {
        v->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        v->setSelectionBehavior(QAbstractItemView::SelectRows);
        v->setSelectionMode(QAbstractItemView::SingleSelection);
        v->setEditTriggers(QAbstractItemView::NoEditTriggers);
        v->setAlternatingRowColors(true);
        v->verticalHeader()->setDefaultSectionSize(38);
        v->verticalHeader()->hide();
    };

    ui->todayTableView->setModel(m_todayModel);
    setupTable(ui->todayTableView);

    ui->eventsTableView->setModel(m_eventsModel);
    ui->eventsTableView->setItemDelegate(new QSqlRelationalDelegate(ui->eventsTableView));
    setupTable(ui->eventsTableView);

    int evId = m_eventsModel->fieldIndex("id");
    int evDesc = m_eventsModel->fieldIndex("description");
    int evType = m_eventsModel->fieldIndex("type");
    int evDeadline = m_eventsModel->fieldIndex("is_deadline");
    int evCategory = m_eventsModel->fieldIndex("category_id");

    if (evId >= 0) ui->eventsTableView->hideColumn(evId);
    if (evDesc >= 0) ui->eventsTableView->hideColumn(evDesc);
    if (evType >= 0) ui->eventsTableView->hideColumn(evType);
    if (evDeadline >= 0) ui->eventsTableView->hideColumn(evDeadline);

    ui->categoriesTableView->setModel(m_categoriesModel);
    setupTable(ui->categoriesTableView);

    int catId = m_categoriesModel->fieldIndex("id");
    int catColor = m_categoriesModel->fieldIndex("color");
    int catName = m_categoriesModel->fieldIndex("name");

    if (catId >= 0) ui->categoriesTableView->hideColumn(catId);
    if (catColor >= 0) {
        ui->categoriesTableView->setItemDelegateForColumn(
            catColor, new ColorCellDelegate(ui->categoriesTableView));
    }

    ui->tagsTableView->setModel(m_tagsModel);
    setupTable(ui->tagsTableView);

    int tagId = m_tagsModel->fieldIndex("id");
    if (tagId >= 0) ui->tagsTableView->hideColumn(tagId);

    ui->wishlistTableView->setModel(m_wishlistModel);
    setupTable(ui->wishlistTableView);

    ui->calendarTableView->setModel(m_calendarModel);
    setupTable(ui->calendarTableView);

    if (evCategory >= 0) {
        auto *catBadge = new CategoryBadgeDelegate(ui->eventsTableView);
        QHash<QString, QColor> categoryMap;

        for (int row = 0; row < m_categoriesModel->rowCount(); ++row) {
            QString name = m_categoriesModel->data(m_categoriesModel->index(row, catName)).toString();
            QString color = m_categoriesModel->data(m_categoriesModel->index(row, catColor)).toString();
            categoryMap.insert(name, QColor(color));
        }

        catBadge->setCategoryColors(categoryMap);
        ui->eventsTableView->setItemDelegateForColumn(evCategory, catBadge);
    }

    auto *tagDelegate1 = new TagChipDelegate(ui->wishlistTableView);
    auto *tagDelegate2 = new TagChipDelegate(ui->calendarTableView);

    QHash<QString, QColor> tagColors;
    tagColors["книга"] = QColor("#2ecc71");
    tagColors["фильм"] = QColor("#3498db");
    tagColors["игра"] = QColor("#9b59b6");
    tagColors["важно"] = QColor("#e67e22");
    tagColors["срочно"] = QColor("#e74c3c");
    tagColors["идея"] = QColor("#1abc9c");
    tagColors["задание"] = QColor("#f1c40f");

    tagDelegate1->setTagColors(tagColors);
    tagDelegate2->setTagColors(tagColors);

    ui->wishlistTableView->setItemDelegateForColumn(4, tagDelegate1);
    ui->calendarTableView->setItemDelegateForColumn(4, tagDelegate2);

    ui->calendarWidget->setSelectedDate(QDate::currentDate());
}

void MainWindow::connectSignals()
{
    connect(ui->addCategoryBtn, &QPushButton::clicked, this, &MainWindow::onAddCategory);
    connect(ui->editCategoryBtn, &QPushButton::clicked, this, &MainWindow::onEditCategory);
    connect(ui->deleteCategoryBtn, &QPushButton::clicked, this, &MainWindow::onDeleteCategory);

    connect(ui->addEventBtn, &QPushButton::clicked, this, &MainWindow::onAddEvent);
    connect(ui->editEventBtn, &QPushButton::clicked, this, &MainWindow::onEditEvent);
    connect(ui->deleteEventBtn, &QPushButton::clicked, this, &MainWindow::onDeleteEvent);

    connect(ui->eventsTableView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this, &MainWindow::onEventSelectionChanged);

    connect(ui->addTagBtn, &QPushButton::clicked, this, &MainWindow::onAddTag);
    connect(ui->editTagBtn, &QPushButton::clicked, this, &MainWindow::onEditTag);
    connect(ui->deleteTagBtn, &QPushButton::clicked, this, &MainWindow::onDeleteTag);

    connect(ui->calendarWidget, &QCalendarWidget::selectionChanged,
            this, &MainWindow::onCalendarDateChanged);
}

void MainWindow::populateSampleData()
{
    m_db->addCategory("Работа", "#e74c3c");
    m_db->addCategory("Учёба", "#3498db");
    m_db->addCategory("Личное", "#2ecc71");
    m_db->addCategory("Развлечения", "#9b59b6");

    m_db->addTag("срочно");
    m_db->addTag("важно");
    m_db->addTag("идея");
    m_db->addTag("книга");
    m_db->addTag("фильм");
    m_db->addTag("игра");
    m_db->addTag("задание");

    QDate today = QDate::currentDate();
    m_db->addEvent("Сдать лабораторную", "Qt + SQLite проект",
                   today, QTime(14, 30), "дедлайн", 2, true);
    m_db->addEvent("Встреча с командой", "Обсуждение спринта",
                   today.addDays(1), QTime(11, 0), "событие", 1, false);
    m_db->addEvent("Посмотреть Dune 3", "Когда выйдет в прокат",
                   today.addDays(5), QTime(20, 0), "желание", 4, false);
    m_db->addEvent("Прочитать SICP", "Структура и интерпретация",
                   today.addDays(10), QTime(18, 0), "желание", 2, false);
    m_db->addEvent("Дедлайн по алгебре", "Сдать контрольную",
                   today.addDays(2), QTime(23, 59), "дедлайн", 2, true);

    m_db->assignTagsToEvent(1, {1, 2, 7});
    m_db->assignTagsToEvent(2, {2});
    m_db->assignTagsToEvent(3, {5});
    m_db->assignTagsToEvent(4, {4, 3});
    m_db->assignTagsToEvent(5, {1, 7});

    refreshAll();
}

void MainWindow::refreshAll()
{
    m_categoriesModel->select();
    m_eventsModel->select();
    m_tagsModel->select();

    loadTodayTab();
    loadWishlistTab();
    loadCalendarTab(ui->calendarWidget->selectedDate());

    QTextCharFormat fmt;
    fmt.setBackground(QBrush(QColor("#3d5a80")));
    fmt.setForeground(QBrush(Qt::white));

    ui->calendarWidget->setDateTextFormat(QDate(), QTextCharFormat());

    QSqlQuery q(m_db->db());
    q.prepare("SELECT DISTINCT date FROM events");
    if (q.exec()) {
        while (q.next()) {
            QDate d = QDate::fromString(q.value(0).toString(), "yyyy-MM-dd");
            if (d.isValid())
                ui->calendarWidget->setDateTextFormat(d, fmt);
        }
    }
}

void MainWindow::updateTagsPanel(int eventId)
{
    QString tags = m_db->getTagsStringForEvent(eventId);
    ui->eventTagsLabel->setText(
        tags.isEmpty()
            ? "Теги выбранного события: нет"
            : "Теги выбранного события: " + tags);
}

void MainWindow::loadTodayTab()
{
    m_todayModel->clear();
    m_todayModel->setHorizontalHeaderLabels(
        {"Раздел", "Дата", "Время", "Название", "Категория"});

    QDate today = QDate::currentDate();

    QSqlQuery q(m_db->db());
    q.prepare(
        "SELECT e.id, e.date, e.time, e.title, e.is_deadline, c.name AS category_name "
        "FROM events e "
        "JOIN categories c ON e.category_id = c.id "
        "WHERE e.date >= :today "
        "ORDER BY e.date, e.time "
        "LIMIT 6");
    q.bindValue(":today", today.toString("yyyy-MM-dd"));

    if (!q.exec())
        return;

    while (q.next()) {
        QDate d = QDate::fromString(q.value("date").toString(), "yyyy-MM-dd");
        QTime t = QTime::fromString(q.value("time").toString(), "HH:mm");
        bool isDeadline = q.value("is_deadline").toInt() == 1;

        QString section = "Позже";
        if (d == today)
            section = "Сегодня";
        else if (d == today.addDays(1))
            section = "Завтра";

        auto *sectionItem = new QStandardItem(section);
        auto *dateItem = new QStandardItem(d.isValid() ? d.toString("dd.MM.yyyy") : q.value("date").toString());
        auto *timeItem = new QStandardItem(t.isValid() ? t.toString("HH:mm") : q.value("time").toString());
        auto *titleItem = new QStandardItem(q.value("title").toString());
        auto *catItem = new QStandardItem(q.value("category_name").toString());

        if (isDeadline)
            titleItem->setForeground(QBrush(QColor("#f1c40f")));

        QList<QStandardItem*> row;
        row << sectionItem << dateItem << timeItem << titleItem << catItem;
        m_todayModel->appendRow(row);
    }
}

void MainWindow::loadWishlistTab()
{
    m_wishlistModel->clear();
    m_wishlistModel->setHorizontalHeaderLabels(
        {"Дата", "Время", "Название", "Категория", "Теги"});

    QSqlQuery q(m_db->db());
    q.prepare(
        "SELECT DISTINCT e.id, e.date, e.time, e.title, c.name AS category_name "
        "FROM events e "
        "JOIN categories c ON e.category_id = c.id "
        "JOIN event_tags et ON et.event_id = e.id "
        "JOIN tags t ON t.id = et.tag_id "
        "WHERE e.type = 'желание' AND t.name IN ('книга','фильм','игра') "
        "ORDER BY e.date, e.time, e.title");

    if (!q.exec())
        return;

    while (q.next()) {
        int eventId = q.value("id").toInt();
        QDate d = QDate::fromString(q.value("date").toString(), "yyyy-MM-dd");
        QTime t = QTime::fromString(q.value("time").toString(), "HH:mm");

        QList<QStandardItem*> row;
        row << new QStandardItem(d.isValid() ? d.toString("dd.MM.yyyy") : q.value("date").toString());
        row << new QStandardItem(t.isValid() ? t.toString("HH:mm") : q.value("time").toString());
        row << new QStandardItem(q.value("title").toString());
        row << new QStandardItem(q.value("category_name").toString());
        row << new QStandardItem(m_db->getTagsStringForEvent(eventId));
        m_wishlistModel->appendRow(row);
    }
}

void MainWindow::loadCalendarTab(const QDate &date)
{
    m_calendarModel->clear();
    m_calendarModel->setHorizontalHeaderLabels(
        {"Дата", "Время", "Название", "Категория", "Теги"});

    QSqlQuery q(m_db->db());
    q.prepare(
        "SELECT e.id, e.date, e.time, e.title, e.is_deadline, c.name AS category_name "
        "FROM events e "
        "JOIN categories c ON e.category_id = c.id "
        "WHERE e.date = :d "
        "ORDER BY e.time, e.title");
    q.bindValue(":d", date.toString("yyyy-MM-dd"));

    if (!q.exec())
        return;

    while (q.next()) {
        int eventId = q.value("id").toInt();
        QDate d = QDate::fromString(q.value("date").toString(), "yyyy-MM-dd");
        QTime t = QTime::fromString(q.value("time").toString(), "HH:mm");
        bool isDeadline = q.value("is_deadline").toInt() == 1;

        auto *dateItem = new QStandardItem(d.isValid() ? d.toString("dd.MM.yyyy") : q.value("date").toString());
        auto *timeItem = new QStandardItem(t.isValid() ? t.toString("HH:mm") : q.value("time").toString());
        auto *titleItem = new QStandardItem(q.value("title").toString());
        auto *catItem = new QStandardItem(q.value("category_name").toString());
        auto *tagsItem = new QStandardItem(m_db->getTagsStringForEvent(eventId));

        if (isDeadline)
            titleItem->setForeground(QBrush(QColor("#f1c40f")));

        QList<QStandardItem*> row;
        row << dateItem << timeItem << titleItem << catItem << tagsItem;
        m_calendarModel->appendRow(row);
    }
}

void MainWindow::onCalendarDateChanged()
{
    loadCalendarTab(ui->calendarWidget->selectedDate());
}

void MainWindow::onAddCategory()
{
    CategoryDialog dlg(this);
    dlg.setWindowTitle("Новая категория");
    dlg.setColor(QColor("#3498db"));

    if (dlg.exec() != QDialog::Accepted)
        return;

    QString name = dlg.name();
    if (name.trimmed().isEmpty())
        return;

    if (!m_db->addCategory(name, dlg.color().name()))
        QMessageBox::warning(this, "Ошибка",
                             "Не удалось добавить категорию. Такое название уже существует.");

    m_categoriesModel->select();
    m_eventsModel->select();
    setupViews();
    refreshAll();
}

void MainWindow::onEditCategory()
{
    auto rows = ui->categoriesTableView->selectionModel()->selectedRows();
    if (rows.isEmpty()) {
        QMessageBox::information(this, "Выбор", "Выберите категорию.");
        return;
    }

    int idCol = m_categoriesModel->fieldIndex("id");
    int nameCol = m_categoriesModel->fieldIndex("name");
    int colorCol = m_categoriesModel->fieldIndex("color");

    int row = rows.first().row();
    int id = m_categoriesModel->data(m_categoriesModel->index(row, idCol)).toInt();
    QString curName = m_categoriesModel->data(m_categoriesModel->index(row, nameCol)).toString();
    QString curColor = m_categoriesModel->data(m_categoriesModel->index(row, colorCol)).toString();

    CategoryDialog dlg(this);
    dlg.setWindowTitle("Редактировать категорию");
    dlg.setName(curName);
    dlg.setColor(QColor(curColor));

    if (dlg.exec() != QDialog::Accepted)
        return;

    QString name = dlg.name();
    if (name.trimmed().isEmpty())
        return;

    if (!m_db->updateCategory(id, name, dlg.color().name()))
        QMessageBox::warning(this, "Ошибка", "Не удалось обновить категорию.");

    m_categoriesModel->select();
    m_eventsModel->select();
    setupViews();
    refreshAll();
}

void MainWindow::onDeleteCategory()
{
    auto rows = ui->categoriesTableView->selectionModel()->selectedRows();
    if (rows.isEmpty()) {
        QMessageBox::information(this, "Выбор", "Выберите категорию.");
        return;
    }

    int idCol = m_categoriesModel->fieldIndex("id");
    int nameCol = m_categoriesModel->fieldIndex("name");

    int row = rows.first().row();
    int id = m_categoriesModel->data(m_categoriesModel->index(row, idCol)).toInt();
    QString name = m_categoriesModel->data(m_categoriesModel->index(row, nameCol)).toString();

    if (m_db->categoryHasEvents(id)) {
        QMessageBox::warning(this, "Ошибка",
                             QString("Нельзя удалить категорию «%1»: сначала удалите её события.").arg(name));
        return;
    }

    if (QMessageBox::question(this, "Удаление",
                              QString("Удалить «%1»?").arg(name)) != QMessageBox::Yes)
        return;

    if (!m_db->deleteCategory(id))
        QMessageBox::warning(this, "Ошибка", "Не удалось удалить.");

    m_categoriesModel->select();
    m_eventsModel->select();
    setupViews();
    refreshAll();
}

void MainWindow::onEventSelectionChanged()
{
    auto rows = ui->eventsTableView->selectionModel()->selectedRows();
    if (rows.isEmpty()) {
        ui->eventTagsLabel->setText("Теги выбранного события: —");
        return;
    }

    int idCol = m_eventsModel->fieldIndex("id");
    int id = m_eventsModel->data(m_eventsModel->index(rows.first().row(), idCol)).toInt();
    updateTagsPanel(id);
}

void MainWindow::onAddEvent()
{
    if (m_categoriesModel->rowCount() == 0) {
        QMessageBox::warning(this, "Нет категорий", "Сначала добавьте категорию.");
        return;
    }

    EventDialog dlg(m_db, this);
    dlg.setWindowTitle("Добавить событие");
    if (dlg.exec() != QDialog::Accepted)
        return;

    if (!m_db->addEvent(dlg.title(), dlg.description(), dlg.date(), dlg.time(),
                        dlg.eventType(), dlg.categoryId(), dlg.isDeadline())) {
        QMessageBox::warning(this, "Ошибка", "Не удалось добавить событие.");
        return;
    }

    QSqlQuery q(m_db->db());
    q.exec("SELECT last_insert_rowid()");
    if (q.next())
        m_db->assignTagsToEvent(q.value(0).toInt(), dlg.selectedTagIds());

    m_eventsModel->select();
    refreshAll();
    ui->statusbar->showMessage("Событие добавлено", 2000);
}

void MainWindow::onEditEvent()
{
    auto rows = ui->eventsTableView->selectionModel()->selectedRows();
    if (rows.isEmpty()) {
        QMessageBox::information(this, "Выбор", "Выберите событие.");
        return;
    }

    int idCol = m_eventsModel->fieldIndex("id");
    int eventId = m_eventsModel->data(m_eventsModel->index(rows.first().row(), idCol)).toInt();

    EventDialog dlg(m_db, this);
    dlg.loadEvent(eventId);
    if (dlg.exec() != QDialog::Accepted)
        return;

    if (!m_db->updateEvent(eventId, dlg.title(), dlg.description(), dlg.date(), dlg.time(),
                           dlg.eventType(), dlg.categoryId(), dlg.isDeadline())) {
        QMessageBox::warning(this, "Ошибка", "Не удалось обновить событие.");
        return;
    }

    m_db->assignTagsToEvent(eventId, dlg.selectedTagIds());
    m_eventsModel->select();
    refreshAll();
    updateTagsPanel(eventId);
    ui->statusbar->showMessage("Событие обновлено", 2000);
}

void MainWindow::onDeleteEvent()
{
    auto rows = ui->eventsTableView->selectionModel()->selectedRows();
    if (rows.isEmpty()) {
        QMessageBox::information(this, "Выбор", "Выберите событие.");
        return;
    }

    int idCol = m_eventsModel->fieldIndex("id");
    int titleCol = m_eventsModel->fieldIndex("title");

    int row = rows.first().row();
    int id = m_eventsModel->data(m_eventsModel->index(row, idCol)).toInt();
    QString title = m_eventsModel->data(m_eventsModel->index(row, titleCol)).toString();

    if (QMessageBox::question(this, "Удаление",
                              QString("Удалить «%1»?").arg(title)) != QMessageBox::Yes)
        return;

    if (!m_db->deleteEvent(id))
        QMessageBox::warning(this, "Ошибка", "Не удалось удалить.");

    m_eventsModel->select();
    refreshAll();
    ui->eventTagsLabel->setText("Теги выбранного события: —");
    ui->statusbar->showMessage("Событие удалено", 2000);
}

void MainWindow::onAddTag()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Новый тег", "Название:",
                                         QLineEdit::Normal, "", &ok);
    if (!ok || name.trimmed().isEmpty())
        return;

    if (!m_db->addTag(name.trimmed()))
        QMessageBox::warning(this, "Ошибка",
                             "Не удалось добавить тег. Такой тег уже существует.");

    m_tagsModel->select();
    refreshAll();
}

void MainWindow::onEditTag()
{
    auto rows = ui->tagsTableView->selectionModel()->selectedRows();
    if (rows.isEmpty()) {
        QMessageBox::information(this, "Выбор", "Выберите тег.");
        return;
    }

    int idCol = m_tagsModel->fieldIndex("id");
    int nameCol = m_tagsModel->fieldIndex("name");

    int row = rows.first().row();
    int id = m_tagsModel->data(m_tagsModel->index(row, idCol)).toInt();
    QString cur = m_tagsModel->data(m_tagsModel->index(row, nameCol)).toString();

    bool ok;
    QString name = QInputDialog::getText(this, "Редактировать тег", "Название:",
                                         QLineEdit::Normal, cur, &ok);
    if (!ok || name.trimmed().isEmpty())
        return;

    if (!m_db->updateTag(id, name.trimmed()))
        QMessageBox::warning(this, "Ошибка", "Не удалось обновить тег.");

    m_tagsModel->select();
    refreshAll();
}

void MainWindow::onDeleteTag()
{
    auto rows = ui->tagsTableView->selectionModel()->selectedRows();
    if (rows.isEmpty()) {
        QMessageBox::information(this, "Выбор", "Выберите тег.");
        return;
    }

    int idCol = m_tagsModel->fieldIndex("id");
    int nameCol = m_tagsModel->fieldIndex("name");

    int row = rows.first().row();
    int id = m_tagsModel->data(m_tagsModel->index(row, idCol)).toInt();
    QString name = m_tagsModel->data(m_tagsModel->index(row, nameCol)).toString();

    QString msg = m_db->tagIsUsed(id)
                      ? QString("Тег «%1» используется в событиях. Всё равно удалить?").arg(name)
                      : QString("Удалить тег «%1»?").arg(name);

    if (QMessageBox::question(this, "Удаление", msg) != QMessageBox::Yes)
        return;

    if (!m_db->deleteTag(id))
        QMessageBox::warning(this, "Ошибка", "Не удалось удалить тег.");

    m_tagsModel->select();
    refreshAll();
}
