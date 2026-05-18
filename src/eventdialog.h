#ifndef EVENTDIALOG_H
#define EVENTDIALOG_H

#include <QDialog>
#include <QDate>
#include <QList>
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EventDialog; }
QT_END_NAMESPACE

class EventDialog : public QDialog
{
    Q_OBJECT
public:
    explicit EventDialog(Database *db, QWidget *parent = nullptr);
    ~EventDialog();

    void loadEvent(int eventId);

    QString    title()          const;
    QString    description()    const;
    QDate      date()           const;
    QString    eventType()      const;
    int        categoryId()     const;
    bool       isDeadline()     const;
    QList<int> selectedTagIds() const;
    int        eventId()        const { return m_eventId; }

private slots:
    void onAccept();

private:
    Ui::EventDialog *ui;
    Database *m_db;
    int m_eventId = -1;

    void populateCategories();
    void populateTags();
    void setCheckedTags(const QList<int> &ids);
    bool validateInput();
};

#endif // EVENTDIALOG_H
