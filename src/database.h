#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QTime>
#include <QDebug>

class Database : public QObject
{
    Q_OBJECT

public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    bool init(const QString &dbPath);
    QSqlDatabase db() const { return m_db; }

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

    bool assignTagsToEvent(int eventId, const QList<int> &tagIds);
    QList<int> getTagsForEvent(int eventId);
    QString getTagsStringForEvent(int eventId);

private:
    QSqlDatabase m_db;
    bool createTables();
    bool execQuery(QSqlQuery &q, const QString &where);
};

#endif // DATABASE_H
