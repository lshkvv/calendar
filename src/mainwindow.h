#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
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

private:
    Ui::MainWindow *ui;
    Database *m_db;

    QSqlTableModel           *m_categoriesModel;
    QSqlRelationalTableModel *m_eventsModel;
    QSqlTableModel           *m_tagsModel;

    void setupDatabase();
    void setupModels();
    void setupViews();
    void connectSignals();
    void populateSampleData();
    void refreshAll();
    void updateTagsPanel(int eventId);
};

#endif // MAINWINDOW_H
