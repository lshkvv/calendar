#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QDate>
#include <QTime>
#include <QList>
#include <QDebug>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    bool init(const QString &dbPath);
    bool createTables();
    bool ensureEventsSchema();

    bool addCategory(const QString &name, const QString &color);
    bool updateCategory(int id, const QString &name, const QString &color);
    bool deleteCategory(int id);
    bool categoryHasEvents(int id);

    bool addTag(const QString &name);
    bool updateTag(int id, const QString &name);
    bool deleteTag(int id);
    bool tagIsUsed(int id);

    bool addEvent(const QString &title, const QString &desc,
                  const QDate &date, const QTime &time,
                  const QString &type, int categoryId, bool isDeadline);

    bool updateEvent(int id, const QString &title, const QString &desc,
                     const QDate &date, const QTime &time,
                     const QString &type, int categoryId, bool isDeadline);

    bool deleteEvent(int id);
    bool setEventDone(int eventId, bool done);

    bool assignTagsToEvent(int eventId, const QList<int> &tagIds);
    QList<int> getTagsForEvent(int eventId);
    QString getTagsStringForEvent(int eventId);

    QSqlDatabase db() const { return m_db; }

private:
    QSqlDatabase m_db;
    bool execQuery(QSqlQuery &q, const QString &where);
};

#endif // DATABASE_H
