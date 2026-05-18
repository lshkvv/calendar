#include "eventdialog.h"
#include "ui_eventdialog.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QListWidgetItem>

EventDialog::EventDialog(Database *db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EventDialog)
    , m_db(db)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());

    populateCategories();
    populateTags();

    disconnect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EventDialog::onAccept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

EventDialog::~EventDialog()
{
    delete ui;
}

void EventDialog::loadEvent(int eventId)
{
    m_eventId = eventId;
    setWindowTitle("Редактировать событие");
    ui->titleLabel->setText("Редактировать событие");

    QSqlQuery q(m_db->db());
    q.prepare("SELECT title, description, date, type, is_deadline, category_id "
              "FROM events WHERE id = :id");
    q.bindValue(":id", eventId);
    if (!q.exec() || !q.next())
        return;

    ui->titleEdit->setText(q.value("title").toString());
    ui->descriptionEdit->setPlainText(q.value("description").toString());
    ui->dateEdit->setDate(QDate::fromString(q.value("date").toString(), "yyyy-MM-dd"));

    int idx = ui->typeComboBox->findText(q.value("type").toString());
    if (idx >= 0)
        ui->typeComboBox->setCurrentIndex(idx);

    ui->deadlineCheckBox->setChecked(q.value("is_deadline").toInt() == 1);

    int catId = q.value("category_id").toInt();
    for (int i = 0; i < ui->categoryComboBox->count(); ++i) {
        if (ui->categoryComboBox->itemData(i).toInt() == catId) {
            ui->categoryComboBox->setCurrentIndex(i);
            break;
        }
    }

    setCheckedTags(m_db->getTagsForEvent(eventId));
}

void EventDialog::populateCategories()
{
    ui->categoryComboBox->clear();

    QSqlQuery q(m_db->db());
    q.exec("SELECT id, name FROM categories ORDER BY name");
    while (q.next())
        ui->categoryComboBox->addItem(q.value("name").toString(), q.value("id").toInt());
}

void EventDialog::populateTags()
{
    ui->tagsListWidget->clear();

    QSqlQuery q(m_db->db());
    q.exec("SELECT id, name FROM tags ORDER BY name");
    while (q.next()) {
        auto *item = new QListWidgetItem(q.value("name").toString(), ui->tagsListWidget);
        item->setData(Qt::UserRole, q.value("id").toInt());
        item->setCheckState(Qt::Unchecked);
    }
}

void EventDialog::setCheckedTags(const QList<int> &ids)
{
    for (int i = 0; i < ui->tagsListWidget->count(); ++i) {
        auto *item = ui->tagsListWidget->item(i);
        int tid = item->data(Qt::UserRole).toInt();
        item->setCheckState(ids.contains(tid) ? Qt::Checked : Qt::Unchecked);
    }
}

bool EventDialog::validateInput()
{
    if (ui->titleEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Название не может быть пустым.");
        ui->titleEdit->setFocus();
        return false;
    }
    if (ui->categoryComboBox->currentIndex() < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите категорию.");
        return false;
    }
    return true;
}

void EventDialog::onAccept()
{
    if (validateInput())
        accept();
}

QString EventDialog::title() const
{
    return ui->titleEdit->text().trimmed();
}

QString EventDialog::description() const
{
    return ui->descriptionEdit->toPlainText().trimmed();
}

QDate EventDialog::date() const
{
    return ui->dateEdit->date();
}

QString EventDialog::eventType() const
{
    return ui->typeComboBox->currentText();
}

int EventDialog::categoryId() const
{
    return ui->categoryComboBox->currentData().toInt();
}

bool EventDialog::isDeadline() const
{
    return ui->deadlineCheckBox->isChecked();
}

QList<int> EventDialog::selectedTagIds() const
{
    QList<int> ids;
    for (int i = 0; i < ui->tagsListWidget->count(); ++i) {
        auto *item = ui->tagsListWidget->item(i);
        if (item->checkState() == Qt::Checked)
            ids << item->data(Qt::UserRole).toInt();
    }
    return ids;
}
