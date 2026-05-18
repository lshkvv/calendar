#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "eventdialog.h"
#include "categorydialog.h"
#include "colorcelldelegate.h"
#include "categorybadgedelegate.h"

#include <QInputDialog>
#include <QColorDialog>
#include <QMessageBox>
#include <QSqlRelation>
#include <QSqlQuery>
#include <QHeaderView>
#include <QFile>
#include <QDir>
#include <QHash>

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupDatabase()
{
    QString path = QDir::currentPath() + "/calendar.db";
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
    m_categoriesModel->setHeaderData(0, Qt::Horizontal, "ID");
    m_categoriesModel->setHeaderData(1, Qt::Horizontal, "Название");
    m_categoriesModel->setHeaderData(2, Qt::Horizontal, "Цвет");
    m_categoriesModel->select();

    m_eventsModel = new QSqlRelationalTableModel(this, m_db->db());
    m_eventsModel->setTable("events");
    m_eventsModel->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    m_eventsModel->setRelation(6, QSqlRelation("categories", "id", "name"));
    m_eventsModel->setHeaderData(0, Qt::Horizontal, "ID");
    m_eventsModel->setHeaderData(1, Qt::Horizontal, "Название");
    m_eventsModel->setHeaderData(2, Qt::Horizontal, "Описание");
    m_eventsModel->setHeaderData(3, Qt::Horizontal, "Дата");
    m_eventsModel->setHeaderData(4, Qt::Horizontal, "Тип");
    m_eventsModel->setHeaderData(5, Qt::Horizontal, "Дедлайн");
    m_eventsModel->setHeaderData(6, Qt::Horizontal, "Категория");
    m_eventsModel->setSort(3, Qt::AscendingOrder);
    m_eventsModel->select();

    m_tagsModel = new QSqlTableModel(this, m_db->db());
    m_tagsModel->setTable("tags");
    m_tagsModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    m_tagsModel->setHeaderData(0, Qt::Horizontal, "ID");
    m_tagsModel->setHeaderData(1, Qt::Horizontal, "Тег");
    m_tagsModel->select();
}

void MainWindow::setupViews()
{
    auto setup = [](QTableView *v) {
        v->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        v->setSelectionBehavior(QAbstractItemView::SelectRows);
        v->setSelectionMode(QAbstractItemView::SingleSelection);
        v->setEditTriggers(QAbstractItemView::NoEditTriggers);
        v->setAlternatingRowColors(true);
        v->hideColumn(0);
        v->verticalHeader()->setDefaultSectionSize(34);
        v->verticalHeader()->hide();
    };

    ui->categoriesTableView->setModel(m_categoriesModel);
    setup(ui->categoriesTableView);
    ui->categoriesTableView->setItemDelegateForColumn(
        2, new ColorCellDelegate(ui->categoriesTableView));

    ui->eventsTableView->setModel(m_eventsModel);
    ui->eventsTableView->setItemDelegate(
        new QSqlRelationalDelegate(ui->eventsTableView));
    setup(ui->eventsTableView);

    // badge для категории
    auto *catBadge = new CategoryBadgeDelegate(ui->eventsTableView);
    QHash<QString, QColor> map;
    for (int row = 0; row < m_categoriesModel->rowCount(); ++row) {
        QString name  = m_categoriesModel->data(m_categoriesModel->index(row, 1)).toString();
        QString color = m_categoriesModel->data(m_categoriesModel->index(row, 2)).toString();
        map.insert(name, QColor(color));
    }
    catBadge->setCategoryColors(map);
    ui->eventsTableView->setItemDelegateForColumn(6, catBadge);

    ui->tagsTableView->setModel(m_tagsModel);
    setup(ui->tagsTableView);
}

void MainWindow::connectSignals()
{
    connect(ui->addCategoryBtn,    &QPushButton::clicked, this, &MainWindow::onAddCategory);
    connect(ui->editCategoryBtn,   &QPushButton::clicked, this, &MainWindow::onEditCategory);
    connect(ui->deleteCategoryBtn, &QPushButton::clicked, this, &MainWindow::onDeleteCategory);

    connect(ui->addEventBtn,    &QPushButton::clicked, this, &MainWindow::onAddEvent);
    connect(ui->editEventBtn,   &QPushButton::clicked, this, &MainWindow::onEditEvent);
    connect(ui->deleteEventBtn, &QPushButton::clicked, this, &MainWindow::onDeleteEvent);

    connect(ui->eventsTableView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this, &MainWindow::onEventSelectionChanged);

    connect(ui->addTagBtn,    &QPushButton::clicked, this, &MainWindow::onAddTag);
    connect(ui->editTagBtn,   &QPushButton::clicked, this, &MainWindow::onEditTag);
    connect(ui->deleteTagBtn, &QPushButton::clicked, this, &MainWindow::onDeleteTag);
}

void MainWindow::populateSampleData()
{
    m_db->addCategory("Работа",      "#e74c3c");
    m_db->addCategory("Учёба",       "#3498db");
    m_db->addCategory("Личное",      "#2ecc71");
    m_db->addCategory("Развлечения", "#9b59b6");

    m_db->addTag("срочно");
    m_db->addTag("важно");
    m_db->addTag("идея");
    m_db->addTag("книга");
    m_db->addTag("фильм");
    m_db->addTag("игра");
    m_db->addTag("задание");

    QDate today = QDate::currentDate();
    m_db->addEvent("Сдать лабораторную", "Qt + SQLite проект",        today,             "дедлайн", 2, true);
    m_db->addEvent("Встреча с командой",  "Обсуждение спринта",        today.addDays(1),  "событие", 1, false);
    m_db->addEvent("Посмотреть Dune 3",   "Когда выйдет в прокат",     today.addDays(5),  "желание", 4, false);
    m_db->addEvent("Прочитать SICP",      "Структура и интерпретация", today.addDays(10), "желание", 2, false);
    m_db->addEvent("Дедлайн по алгебре",  "Сдать контрольную",         today.addDays(2),  "дедлайн", 2, true);

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
}

void MainWindow::updateTagsPanel(int eventId)
{
    QString tags = m_db->getTagsStringForEvent(eventId);
    ui->eventTagsLabel->setText(
        tags.isEmpty()
            ? "Теги выбранного события: нет"
            : "Теги выбранного события: " + tags);
}

// ---------- Категории ----------

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
    setupViews();
}

void MainWindow::onEditCategory()
{
    auto rows = ui->categoriesTableView->selectionModel()->selectedRows();
    if (rows.isEmpty()) {
        QMessageBox::information(this, "Выбор", "Выберите категорию.");
        return;
    }

    int row = rows.first().row();
    int id   = m_categoriesModel->data(m_categoriesModel->index(row, 0)).toInt();
    QString curName  = m_categoriesModel->data(m_categoriesModel->index(row, 1)).toString();
    QString curColor = m_categoriesModel->data(m_categoriesModel->index(row, 2)).toString();

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
}

void MainWindow::onDeleteCategory()
{
    auto rows = ui->categoriesTableView->selectionModel()->selectedRows();
    if (rows.isEmpty()) {
        QMessageBox::information(this, "Выбор", "Выберите категорию.");
        return;
    }

    int row = rows.first().row();
    int id  = m_categoriesModel->data(m_categoriesModel->index(row, 0)).toInt();
    QString name = m_categoriesModel->data(m_categoriesModel->index(row, 1)).toString();

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
    setupViews();
}

// ---------- События ----------

void MainWindow::onEventSelectionChanged()
{
    auto rows = ui->eventsTableView->selectionModel()->selectedRows();
    if (rows.isEmpty()) {
        ui->eventTagsLabel->setText("Теги выбранного события: —");
        return;
    }
    int id = m_eventsModel->data(m_eventsModel->index(rows.first().row(), 0)).toInt();
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

    if (!m_db->addEvent(dlg.title(), dlg.description(), dlg.date(),
                        dlg.eventType(), dlg.categoryId(), dlg.isDeadline())) {
        QMessageBox::warning(this, "Ошибка", "Не удалось добавить событие.");
        return;
    }

    QSqlQuery q(m_db->db());
    q.exec("SELECT last_insert_rowid()");
    if (q.next())
        m_db->assignTagsToEvent(q.value(0).toInt(), dlg.selectedTagIds());

    m_eventsModel->select();
    ui->statusbar->showMessage("Событие добавлено", 2000);
}

void MainWindow::onEditEvent()
{
    auto rows = ui->eventsTableView->selectionModel()->selectedRows();
    if (rows.isEmpty()) {
        QMessageBox::information(this, "Выбор", "Выберите событие.");
        return;
    }

    int eventId = m_eventsModel->data(m_eventsModel->index(rows.first().row(), 0)).toInt();

    EventDialog dlg(m_db, this);
    dlg.loadEvent(eventId);
    if (dlg.exec() != QDialog::Accepted)
        return;

    if (!m_db->updateEvent(eventId, dlg.title(), dlg.description(), dlg.date(),
                           dlg.eventType(), dlg.categoryId(), dlg.isDeadline())) {
        QMessageBox::warning(this, "Ошибка", "Не удалось обновить событие.");
        return;
    }

    m_db->assignTagsToEvent(eventId, dlg.selectedTagIds());
    m_eventsModel->select();
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

    int row = rows.first().row();
    int id  = m_eventsModel->data(m_eventsModel->index(row, 0)).toInt();
    QString title = m_eventsModel->data(m_eventsModel->index(row, 1)).toString();

    if (QMessageBox::question(this, "Удаление",
                              QString("Удалить «%1»?").arg(title)) != QMessageBox::Yes)
        return;

    if (!m_db->deleteEvent(id))
        QMessageBox::warning(this, "Ошибка", "Не удалось удалить.");

    m_eventsModel->select();
    ui->eventTagsLabel->setText("Теги выбранного события: —");
    ui->statusbar->showMessage("Событие удалено", 2000);
}

// ---------- Теги ----------

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
}

void MainWindow::onEditTag()
{
    auto rows = ui->tagsTableView->selectionModel()->selectedRows();
    if (rows.isEmpty()) {
        QMessageBox::information(this, "Выбор", "Выберите тег.");
        return;
    }

    int row = rows.first().row();
    int id  = m_tagsModel->data(m_tagsModel->index(row, 0)).toInt();
    QString cur = m_tagsModel->data(m_tagsModel->index(row, 1)).toString();

    bool ok;
    QString name = QInputDialog::getText(this, "Редактировать тег", "Название:",
                                         QLineEdit::Normal, cur, &ok);
    if (!ok || name.trimmed().isEmpty())
        return;

    if (!m_db->updateTag(id, name.trimmed()))
        QMessageBox::warning(this, "Ошибка", "Не удалось обновить тег.");

    m_tagsModel->select();
}

void MainWindow::onDeleteTag()
{
    auto rows = ui->tagsTableView->selectionModel()->selectedRows();
    if (rows.isEmpty()) {
        QMessageBox::information(this, "Выбор", "Выберите тег.");
        return;
    }

    int row = rows.first().row();
    int id  = m_tagsModel->data(m_tagsModel->index(row, 0)).toInt();
    QString name = m_tagsModel->data(m_tagsModel->index(row, 1)).toString();

    QString msg = m_db->tagIsUsed(id)
                      ? QString("Тег «%1» используется в событиях. Всё равно удалить?").arg(name)
                      : QString("Удалить тег «%1»?").arg(name);

    if (QMessageBox::question(this, "Удаление", msg) != QMessageBox::Yes)
        return;

    if (!m_db->deleteTag(id))
        QMessageBox::warning(this, "Ошибка", "Не удалось удалить тег.");

    m_tagsModel->select();
}
