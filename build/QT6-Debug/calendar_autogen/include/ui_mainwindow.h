/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QTabWidget *tabWidget;
    QWidget *tabToday;
    QVBoxLayout *todayLayout;
    QLabel *todayTitleLabel;
    QTableView *todayTableView;
    QWidget *tabEvents;
    QVBoxLayout *eventsLayout;
    QLabel *evtTitleLabel;
    QTableView *eventsTableView;
    QLabel *eventTagsLabel;
    QHBoxLayout *evtButtonsLayout;
    QPushButton *addEventBtn;
    QPushButton *editEventBtn;
    QPushButton *deleteEventBtn;
    QSpacerItem *spacerItem;
    QWidget *tabWishlist;
    QVBoxLayout *wishlistLayout;
    QLabel *wishlistTitleLabel;
    QTableView *wishlistTableView;
    QWidget *tabCalendar;
    QVBoxLayout *calendarMainLayout;
    QLabel *calendarTitleLabel;
    QHBoxLayout *calendarLayout;
    QCalendarWidget *calendarWidget;
    QTableView *calendarTableView;
    QWidget *tabCategories;
    QVBoxLayout *categoriesLayout;
    QLabel *catTitleLabel;
    QTableView *categoriesTableView;
    QHBoxLayout *catButtonsLayout;
    QPushButton *addCategoryBtn;
    QPushButton *editCategoryBtn;
    QPushButton *deleteCategoryBtn;
    QSpacerItem *spacerItem1;
    QWidget *tabTags;
    QVBoxLayout *tagsLayout;
    QLabel *tagsTitleLabel;
    QTableView *tagsTableView;
    QHBoxLayout *tagsButtonsLayout;
    QPushButton *addTagBtn;
    QPushButton *editTagBtn;
    QPushButton *deleteTagBtn;
    QSpacerItem *spacerItem2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1040, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setSpacing(0);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabToday = new QWidget();
        tabToday->setObjectName("tabToday");
        todayLayout = new QVBoxLayout(tabToday);
        todayLayout->setSpacing(10);
        todayLayout->setObjectName("todayLayout");
        todayLayout->setContentsMargins(16, 12, 16, 12);
        todayTitleLabel = new QLabel(tabToday);
        todayTitleLabel->setObjectName("todayTitleLabel");

        todayLayout->addWidget(todayTitleLabel);

        todayTableView = new QTableView(tabToday);
        todayTableView->setObjectName("todayTableView");
        todayTableView->setAlternatingRowColors(true);

        todayLayout->addWidget(todayTableView);

        tabWidget->addTab(tabToday, QString());
        tabEvents = new QWidget();
        tabEvents->setObjectName("tabEvents");
        eventsLayout = new QVBoxLayout(tabEvents);
        eventsLayout->setSpacing(10);
        eventsLayout->setObjectName("eventsLayout");
        eventsLayout->setContentsMargins(16, 12, 16, 12);
        evtTitleLabel = new QLabel(tabEvents);
        evtTitleLabel->setObjectName("evtTitleLabel");

        eventsLayout->addWidget(evtTitleLabel);

        eventsTableView = new QTableView(tabEvents);
        eventsTableView->setObjectName("eventsTableView");
        eventsTableView->setAlternatingRowColors(true);

        eventsLayout->addWidget(eventsTableView);

        eventTagsLabel = new QLabel(tabEvents);
        eventTagsLabel->setObjectName("eventTagsLabel");

        eventsLayout->addWidget(eventTagsLabel);

        evtButtonsLayout = new QHBoxLayout();
        evtButtonsLayout->setSpacing(10);
        evtButtonsLayout->setObjectName("evtButtonsLayout");
        addEventBtn = new QPushButton(tabEvents);
        addEventBtn->setObjectName("addEventBtn");

        evtButtonsLayout->addWidget(addEventBtn);

        editEventBtn = new QPushButton(tabEvents);
        editEventBtn->setObjectName("editEventBtn");

        evtButtonsLayout->addWidget(editEventBtn);

        deleteEventBtn = new QPushButton(tabEvents);
        deleteEventBtn->setObjectName("deleteEventBtn");

        evtButtonsLayout->addWidget(deleteEventBtn);

        spacerItem = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        evtButtonsLayout->addItem(spacerItem);


        eventsLayout->addLayout(evtButtonsLayout);

        tabWidget->addTab(tabEvents, QString());
        tabWishlist = new QWidget();
        tabWishlist->setObjectName("tabWishlist");
        wishlistLayout = new QVBoxLayout(tabWishlist);
        wishlistLayout->setSpacing(10);
        wishlistLayout->setObjectName("wishlistLayout");
        wishlistLayout->setContentsMargins(16, 12, 16, 12);
        wishlistTitleLabel = new QLabel(tabWishlist);
        wishlistTitleLabel->setObjectName("wishlistTitleLabel");

        wishlistLayout->addWidget(wishlistTitleLabel);

        wishlistTableView = new QTableView(tabWishlist);
        wishlistTableView->setObjectName("wishlistTableView");
        wishlistTableView->setAlternatingRowColors(true);

        wishlistLayout->addWidget(wishlistTableView);

        tabWidget->addTab(tabWishlist, QString());
        tabCalendar = new QWidget();
        tabCalendar->setObjectName("tabCalendar");
        calendarMainLayout = new QVBoxLayout(tabCalendar);
        calendarMainLayout->setSpacing(10);
        calendarMainLayout->setObjectName("calendarMainLayout");
        calendarMainLayout->setContentsMargins(16, 12, 16, 12);
        calendarTitleLabel = new QLabel(tabCalendar);
        calendarTitleLabel->setObjectName("calendarTitleLabel");

        calendarMainLayout->addWidget(calendarTitleLabel);

        calendarLayout = new QHBoxLayout();
        calendarLayout->setSpacing(12);
        calendarLayout->setObjectName("calendarLayout");
        calendarWidget = new QCalendarWidget(tabCalendar);
        calendarWidget->setObjectName("calendarWidget");
        calendarWidget->setGridVisible(true);

        calendarLayout->addWidget(calendarWidget);

        calendarTableView = new QTableView(tabCalendar);
        calendarTableView->setObjectName("calendarTableView");
        calendarTableView->setAlternatingRowColors(true);

        calendarLayout->addWidget(calendarTableView);


        calendarMainLayout->addLayout(calendarLayout);

        tabWidget->addTab(tabCalendar, QString());
        tabCategories = new QWidget();
        tabCategories->setObjectName("tabCategories");
        categoriesLayout = new QVBoxLayout(tabCategories);
        categoriesLayout->setSpacing(10);
        categoriesLayout->setObjectName("categoriesLayout");
        categoriesLayout->setContentsMargins(16, 12, 16, 12);
        catTitleLabel = new QLabel(tabCategories);
        catTitleLabel->setObjectName("catTitleLabel");

        categoriesLayout->addWidget(catTitleLabel);

        categoriesTableView = new QTableView(tabCategories);
        categoriesTableView->setObjectName("categoriesTableView");
        categoriesTableView->setAlternatingRowColors(true);

        categoriesLayout->addWidget(categoriesTableView);

        catButtonsLayout = new QHBoxLayout();
        catButtonsLayout->setSpacing(10);
        catButtonsLayout->setObjectName("catButtonsLayout");
        addCategoryBtn = new QPushButton(tabCategories);
        addCategoryBtn->setObjectName("addCategoryBtn");

        catButtonsLayout->addWidget(addCategoryBtn);

        editCategoryBtn = new QPushButton(tabCategories);
        editCategoryBtn->setObjectName("editCategoryBtn");

        catButtonsLayout->addWidget(editCategoryBtn);

        deleteCategoryBtn = new QPushButton(tabCategories);
        deleteCategoryBtn->setObjectName("deleteCategoryBtn");

        catButtonsLayout->addWidget(deleteCategoryBtn);

        spacerItem1 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        catButtonsLayout->addItem(spacerItem1);


        categoriesLayout->addLayout(catButtonsLayout);

        tabWidget->addTab(tabCategories, QString());
        tabTags = new QWidget();
        tabTags->setObjectName("tabTags");
        tagsLayout = new QVBoxLayout(tabTags);
        tagsLayout->setSpacing(10);
        tagsLayout->setObjectName("tagsLayout");
        tagsLayout->setContentsMargins(16, 12, 16, 12);
        tagsTitleLabel = new QLabel(tabTags);
        tagsTitleLabel->setObjectName("tagsTitleLabel");

        tagsLayout->addWidget(tagsTitleLabel);

        tagsTableView = new QTableView(tabTags);
        tagsTableView->setObjectName("tagsTableView");
        tagsTableView->setAlternatingRowColors(true);

        tagsLayout->addWidget(tagsTableView);

        tagsButtonsLayout = new QHBoxLayout();
        tagsButtonsLayout->setSpacing(10);
        tagsButtonsLayout->setObjectName("tagsButtonsLayout");
        addTagBtn = new QPushButton(tabTags);
        addTagBtn->setObjectName("addTagBtn");

        tagsButtonsLayout->addWidget(addTagBtn);

        editTagBtn = new QPushButton(tabTags);
        editTagBtn->setObjectName("editTagBtn");

        tagsButtonsLayout->addWidget(editTagBtn);

        deleteTagBtn = new QPushButton(tabTags);
        deleteTagBtn->setObjectName("deleteTagBtn");

        tagsButtonsLayout->addWidget(deleteTagBtn);

        spacerItem2 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        tagsButtonsLayout->addItem(spacerItem2);


        tagsLayout->addLayout(tagsButtonsLayout);

        tabWidget->addTab(tabTags, QString());

        mainLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\233\320\270\321\207\320\275\321\213\320\271 \320\232\320\260\320\273\320\265\320\275\320\264\320\260\321\200\321\214", nullptr));
        MainWindow->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"    QMainWindow { background-color: #1e1e2e; }\n"
"    QTabWidget::pane { border: none; background: #1e1e2e; }\n"
"    QTabBar::tab {\n"
"      background: #2a2a3e;\n"
"      color: #aaa;\n"
"      padding: 10px 24px;\n"
"      font-size: 14px;\n"
"      border: none;\n"
"      margin-right: 2px;\n"
"    }\n"
"    QTabBar::tab:selected {\n"
"      background: #3d5a80;\n"
"      color: white;\n"
"      font-weight: bold;\n"
"      border-radius: 4px 4px 0 0;\n"
"    }\n"
"    QTableView {\n"
"      background: #252535;\n"
"      color: #e0e0e0;\n"
"      gridline-color: #3a3a4a;\n"
"      font-size: 13px;\n"
"      selection-background-color: #3d5a80;\n"
"      border: 1px solid #3a3a4a;\n"
"      border-radius: 6px;\n"
"    }\n"
"    QHeaderView::section {\n"
"      background: #2a2a3e;\n"
"      color: #aaa;\n"
"      padding: 6px;\n"
"      border: none;\n"
"      font-size: 13px;\n"
"    }\n"
"    QPushButton {\n"
"      background: #3d5a80;\n"
"      color: white;\n"
"      border: none;\n"
"      pad"
                        "ding: 10px 20px;\n"
"      border-radius: 6px;\n"
"      font-size: 13px;\n"
"      min-width: 120px;\n"
"    }\n"
"    QPushButton:hover  { background: #4d6a90; }\n"
"    QPushButton:pressed{ background: #2d4a70; }\n"
"    QStatusBar { color: #888; background: #1e1e2e; font-size: 12px; }\n"
"    QLabel { color: #e0e0e0; }\n"
"    QCalendarWidget QWidget {\n"
"      alternate-background-color: #252535;\n"
"      background-color: #252535;\n"
"      color: #e0e0e0;\n"
"    }\n"
"    QCalendarWidget QToolButton {\n"
"      color: white;\n"
"      background-color: #3d5a80;\n"
"      border: none;\n"
"      margin: 4px;\n"
"      padding: 6px;\n"
"      border-radius: 4px;\n"
"    }\n"
"    QCalendarWidget QMenu {\n"
"      background-color: #2a2a3e;\n"
"      color: white;\n"
"    }\n"
"    QCalendarWidget QSpinBox {\n"
"      background: #252535;\n"
"      color: white;\n"
"      selection-background-color: #3d5a80;\n"
"    }\n"
"   ", nullptr));
        todayTitleLabel->setText(QCoreApplication::translate("MainWindow", "\320\241\320\265\320\263\320\276\320\264\320\275\321\217", nullptr));
        todayTitleLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size:20px; font-weight:bold; color:#e9c46a; padding:4px 0px;", nullptr));
        todayTableView->setStyleSheet(QCoreApplication::translate("MainWindow", "QTableView { alternate-background-color: #2d2d42; }", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabToday), QCoreApplication::translate("MainWindow", "\320\241\320\265\320\263\320\276\320\264\320\275\321\217", nullptr));
        evtTitleLabel->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\261\321\213\321\202\320\270\321\217 \320\270 \320\267\320\260\320\264\320\260\321\207\320\270", nullptr));
        evtTitleLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size:20px; font-weight:bold; color:#e9c46a; padding:4px 0px;", nullptr));
        eventsTableView->setStyleSheet(QCoreApplication::translate("MainWindow", "QTableView { alternate-background-color: #2d2d42; }", nullptr));
        eventTagsLabel->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\263\320\270 \320\262\321\213\320\261\321\200\320\260\320\275\320\275\320\276\320\263\320\276 \321\201\320\276\320\261\321\213\321\202\320\270\321\217: \342\200\224", nullptr));
        eventTagsLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"            background:#1a3a5c;\n"
"            border:1px solid #3d5a80;\n"
"            padding:8px 12px;\n"
"            border-radius:6px;\n"
"            color:#98c1d9;\n"
"            font-size:13px;\n"
"           ", nullptr));
        addEventBtn->setText(QCoreApplication::translate("MainWindow", "\357\274\213  \320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        addEventBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "background:#2ecc71; color:white; font-weight:bold;", nullptr));
        editEventBtn->setText(QCoreApplication::translate("MainWindow", "\342\234\216  \320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        editEventBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "background:#e9c46a; color:#1e1e2e; font-weight:bold;", nullptr));
        deleteEventBtn->setText(QCoreApplication::translate("MainWindow", "\342\234\225  \320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        deleteEventBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "background:#e74c3c; color:white; font-weight:bold;", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabEvents), QCoreApplication::translate("MainWindow", "\320\236\320\261\321\211\320\270\320\271 \320\277\320\273\320\260\320\275", nullptr));
        wishlistTitleLabel->setText(QCoreApplication::translate("MainWindow", "\320\245\320\276\321\207\321\203 \320\277\320\276\321\201\320\274\320\276\321\202\321\200\320\265\321\202\321\214 / \320\277\320\276\321\207\320\270\321\202\320\260\321\202\321\214 / \320\277\320\276\320\270\320\263\321\200\320\260\321\202\321\214", nullptr));
        wishlistTitleLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size:20px; font-weight:bold; color:#f4a261; padding:4px 0px;", nullptr));
        wishlistTableView->setStyleSheet(QCoreApplication::translate("MainWindow", "QTableView { alternate-background-color: #2d2d42; }", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabWishlist), QCoreApplication::translate("MainWindow", "\320\226\320\265\320\273\320\260\320\275\320\270\321\217", nullptr));
        calendarTitleLabel->setText(QCoreApplication::translate("MainWindow", "\320\232\320\260\320\273\320\265\320\275\320\264\320\260\321\200\321\214", nullptr));
        calendarTitleLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size:20px; font-weight:bold; color:#98c1d9; padding:4px 0px;", nullptr));
        calendarTableView->setStyleSheet(QCoreApplication::translate("MainWindow", "QTableView { alternate-background-color: #2d2d42; }", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabCalendar), QCoreApplication::translate("MainWindow", "\320\232\320\260\320\273\320\265\320\275\320\264\320\260\321\200\321\214", nullptr));
        catTitleLabel->setText(QCoreApplication::translate("MainWindow", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270 \321\201\320\276\320\261\321\213\321\202\320\270\320\271", nullptr));
        catTitleLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size:20px; font-weight:bold; color:#98c1d9; padding:4px 0px;", nullptr));
        categoriesTableView->setStyleSheet(QCoreApplication::translate("MainWindow", "QTableView { alternate-background-color: #2d2d42; }", nullptr));
        addCategoryBtn->setText(QCoreApplication::translate("MainWindow", "\357\274\213  \320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        addCategoryBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "background:#2ecc71; color:white; font-weight:bold;", nullptr));
        editCategoryBtn->setText(QCoreApplication::translate("MainWindow", "\342\234\216  \320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        deleteCategoryBtn->setText(QCoreApplication::translate("MainWindow", "\342\234\225  \320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        deleteCategoryBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "background:#e74c3c; color:white; font-weight:bold;", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabCategories), QCoreApplication::translate("MainWindow", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270", nullptr));
        tagsTitleLabel->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\263\320\270", nullptr));
        tagsTitleLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size:20px; font-weight:bold; color:#f4a261; padding:4px 0px;", nullptr));
        tagsTableView->setStyleSheet(QCoreApplication::translate("MainWindow", "QTableView { alternate-background-color: #2d2d42; }", nullptr));
        addTagBtn->setText(QCoreApplication::translate("MainWindow", "\357\274\213  \320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        addTagBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "background:#2ecc71; color:white; font-weight:bold;", nullptr));
        editTagBtn->setText(QCoreApplication::translate("MainWindow", "\342\234\216  \320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        editTagBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "background:#f4a261; color:#1e1e2e; font-weight:bold;", nullptr));
        deleteTagBtn->setText(QCoreApplication::translate("MainWindow", "\342\234\225  \320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        deleteTagBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "background:#e74c3c; color:white; font-weight:bold;", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabTags), QCoreApplication::translate("MainWindow", "\320\242\320\265\320\263\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
