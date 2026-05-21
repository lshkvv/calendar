#include "database.h"
#include <QVariant>

Database::Database(QObject *parent) : QObject(parent) {}

Database::~Database()
{
    if (m_db.isOpen())
        m_db.close();
}

bool Database::init(const QString &dbPath)
{
    qDebug() << "DB init path =" << dbPath;
    qDebug() << "Available SQL drivers =" << QSqlDatabase::drivers();
    qDebug() << "QSQLITE available =" << QSqlDatabase::isDriverAvailable("QSQLITE");

    if (QSqlDatabase::contains("qt_sql_default_connection"))
        m_db = QSqlDatabase::database("qt_sql_default_connection");
    else
        m_db = QSqlDatabase::addDatabase("QSQLITE");

    m_db.setDatabaseName(dbPath);

    if (!m_db.open()) {
        qDebug() << "OPEN DATABASE FAILED";
        qDebug() << "Driver valid =" << m_db.isValid();
        qDebug() << "Is open error =" << m_db.isOpenError();
        qDebug() << "Driver text =" << m_db.lastError().driverText();
        qDebug() << "Database text =" << m_db.lastError().databaseText();
        qDebug() << "Full error =" << m_db.lastError().text();
        qDebug() << "Database name =" << m_db.databaseName();
        return false;
    }

    QSqlQuery q(m_db);
    q.exec("PRAGMA foreign_keys = ON;");

    return createTables();
}

bool Database::createTables()
{
    QSqlQuery q(m_db);

    if (!q.exec("CREATE TABLE IF NOT EXISTS categories ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name TEXT NOT NULL UNIQUE,"
                "color TEXT NOT NULL DEFAULT '#3498db');")) {
        qDebug() << q.lastError().text();
        return false;
    }

    if (!q.exec("CREATE TABLE IF NOT EXISTS events ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "title TEXT NOT NULL,"
                "description TEXT DEFAULT '',"
                "date TEXT NOT NULL,"
                "time TEXT NOT NULL DEFAULT '00:00',"
                "type TEXT NOT NULL DEFAULT 'событие',"
                "is_deadline INTEGER NOT NULL DEFAULT 0,"
                "category_id INTEGER NOT NULL,"
                "FOREIGN KEY (category_id) REFERENCES categories(id)"
                " ON DELETE RESTRICT ON UPDATE CASCADE);")) {
        qDebug() << q.lastError().text();
        return false;
    }

    if (!q.exec("CREATE TABLE IF NOT EXISTS tags ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name TEXT NOT NULL UNIQUE);")) {
        qDebug() << q.lastError().text();
        return false;
    }

    if (!q.exec("CREATE TABLE IF NOT EXISTS event_tags ("
                "event_id INTEGER NOT NULL,"
                "tag_id INTEGER NOT NULL,"
                "PRIMARY KEY (event_id, tag_id),"
                "FOREIGN KEY (event_id) REFERENCES events(id) ON DELETE CASCADE,"
                "FOREIGN KEY (tag_id) REFERENCES tags(id) ON DELETE CASCADE);")) {
        qDebug() << q.lastError().text();
        return false;
    }

    return true;
}

bool Database::execQuery(QSqlQuery &q, const QString &where)
{
    if (!q.exec()) {
        qDebug() << where << q.lastError().text();
        return false;
    }
    return true;
}

bool Database::addCategory(const QString &name, const QString &color)
{
    QSqlQuery q(m_db);
    q.prepare("INSERT INTO categories (name, color) VALUES (:n, :c)");
    q.bindValue(":n", name);
    q.bindValue(":c", color);
    return execQuery(q, "addCategory");
}

bool Database::updateCategory(int id, const QString &name, const QString &color)
{
    QSqlQuery q(m_db);
    q.prepare("UPDATE categories SET name=:n, color=:c WHERE id=:id");
    q.bindValue(":n", name);
    q.bindValue(":c", color);
    q.bindValue(":id", id);
    return execQuery(q, "updateCategory");
}

bool Database::deleteCategory(int id)
{
    QSqlQuery q(m_db);
    q.prepare("DELETE FROM categories WHERE id=:id");
    q.bindValue(":id", id);
    return execQuery(q, "deleteCategory");
}

bool Database::categoryHasEvents(int id)
{
    QSqlQuery q(m_db);
    q.prepare("SELECT COUNT(*) FROM events WHERE category_id=:id");
    q.bindValue(":id", id);
    return q.exec() && q.next() && q.value(0).toInt() > 0;
}

bool Database::addTag(const QString &name)
{
    QSqlQuery q(m_db);
    q.prepare("INSERT INTO tags (name) VALUES (:n)");
    q.bindValue(":n", name);
    return execQuery(q, "addTag");
}

bool Database::updateTag(int id, const QString &name)
{
    QSqlQuery q(m_db);
    q.prepare("UPDATE tags SET name=:n WHERE id=:id");
    q.bindValue(":n", name);
    q.bindValue(":id", id);
    return execQuery(q, "updateTag");
}

bool Database::deleteTag(int id)
{
    QSqlQuery q(m_db);
    q.prepare("DELETE FROM tags WHERE id=:id");
    q.bindValue(":id", id);
    return execQuery(q, "deleteTag");
}

bool Database::tagIsUsed(int id)
{
    QSqlQuery q(m_db);
    q.prepare("SELECT COUNT(*) FROM event_tags WHERE tag_id=:id");
    q.bindValue(":id", id);
    return q.exec() && q.next() && q.value(0).toInt() > 0;
}

bool Database::addEvent(const QString &title, const QString &desc,
                        const QDate &date, const QTime &time,
                        const QString &type, int categoryId, bool isDeadline)
{
    QSqlQuery q(m_db);
    q.prepare("INSERT INTO events (title, description, date, time, type, is_deadline, category_id)"
              " VALUES (:t, :d, :dt, :tm, :tp, :dl, :cat)");
    q.bindValue(":t",   title);
    q.bindValue(":d",   desc);
    q.bindValue(":dt",  date.toString("yyyy-MM-dd"));
    q.bindValue(":tm",  time.toString("HH:mm"));
    q.bindValue(":tp",  type);
    q.bindValue(":dl",  isDeadline ? 1 : 0);
    q.bindValue(":cat", categoryId);
    return execQuery(q, "addEvent");
}

bool Database::updateEvent(int id, const QString &title, const QString &desc,
                           const QDate &date, const QTime &time,
                           const QString &type, int categoryId, bool isDeadline)
{
    QSqlQuery q(m_db);
    q.prepare("UPDATE events SET title=:t, description=:d, date=:dt, time=:tm,"
              " type=:tp, is_deadline=:dl, category_id=:cat WHERE id=:id");
    q.bindValue(":t",   title);
    q.bindValue(":d",   desc);
    q.bindValue(":dt",  date.toString("yyyy-MM-dd"));
    q.bindValue(":tm",  time.toString("HH:mm"));
    q.bindValue(":tp",  type);
    q.bindValue(":dl",  isDeadline ? 1 : 0);
    q.bindValue(":cat", categoryId);
    q.bindValue(":id",  id);
    return execQuery(q, "updateEvent");
}

bool Database::deleteEvent(int id)
{
    QSqlQuery q(m_db);
    q.prepare("DELETE FROM events WHERE id=:id");
    q.bindValue(":id", id);
    return execQuery(q, "deleteEvent");
}

bool Database::assignTagsToEvent(int eventId, const QList<int> &tagIds)
{
    QSqlQuery del(m_db);
    del.prepare("DELETE FROM event_tags WHERE event_id=:eid");
    del.bindValue(":eid", eventId);
    if (!execQuery(del, "assignTags/del"))
        return false;

    for (int tid : tagIds) {
        QSqlQuery ins(m_db);
        ins.prepare("INSERT INTO event_tags (event_id, tag_id) VALUES (:eid, :tid)");
        ins.bindValue(":eid", eventId);
        ins.bindValue(":tid", tid);
        if (!execQuery(ins, "assignTags/ins"))
            return false;
    }
    return true;
}

QList<int> Database::getTagsForEvent(int eventId)
{
    QList<int> ids;
    QSqlQuery q(m_db);
    q.prepare("SELECT tag_id FROM event_tags WHERE event_id=:eid");
    q.bindValue(":eid", eventId);
    if (q.exec())
        while (q.next())
            ids << q.value(0).toInt();
    return ids;
}

QString Database::getTagsStringForEvent(int eventId)
{
    QSqlQuery q(m_db);
    q.prepare("SELECT t.name FROM tags t "
              "JOIN event_tags et ON et.tag_id = t.id "
              "WHERE et.event_id = :eid ORDER BY t.name");
    q.bindValue(":eid", eventId);
    QStringList names;
    if (q.exec())
        while (q.next())
            names << q.value(0).toString();
    return names.join(", ");
}
