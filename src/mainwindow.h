#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QStandardItemModel>
#include <QDate>

#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddCategory();
    void onEditCategory();
    void onDeleteCategory();

    void onAddEvent();
    void onEditEvent();
    void onDeleteEvent();
    void onEventSelectionChanged();

    void onAddTag();
    void onEditTag();
    void onDeleteTag();

    void onCalendarDateChanged();

private:
    Ui::MainWindow *ui;
    Database *m_db;

    QSqlTableModel *m_categoriesModel = nullptr;
    QSqlRelationalTableModel *m_eventsModel = nullptr;
    QSqlTableModel *m_tagsModel = nullptr;

    QStandardItemModel *m_todayModel = nullptr;
    QStandardItemModel *m_wishlistModel = nullptr;
    QStandardItemModel *m_calendarModel = nullptr;

    void setupDatabase();
    void setupModels();
    void setupViews();
    void connectSignals();

    void populateSampleData();
    void refreshAll();

    void loadTodayTab();
    void loadWishlistTab();
    void loadCalendarTab(const QDate &date);
    void updateTagsPanel(int eventId);
};

#endif // MAINWINDOW_H
