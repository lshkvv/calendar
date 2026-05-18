/********************************************************************************
** Form generated from reading UI file 'eventdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVENTDIALOG_H
#define UI_EVENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_EventDialog
{
public:
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QFormLayout *formLayout;
    QLabel *labelName;
    QLineEdit *titleEdit;
    QLabel *labelDesc;
    QPlainTextEdit *descriptionEdit;
    QLabel *labelDate;
    QDateEdit *dateEdit;
    QLabel *labelType;
    QComboBox *typeComboBox;
    QLabel *labelCategory;
    QComboBox *categoryComboBox;
    QLabel *labelDeadline;
    QCheckBox *deadlineCheckBox;
    QGroupBox *tagsGroupBox;
    QVBoxLayout *tagsLayout;
    QListWidget *tagsListWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *EventDialog)
    {
        if (EventDialog->objectName().isEmpty())
            EventDialog->setObjectName("EventDialog");
        EventDialog->resize(480, 560);
        mainLayout = new QVBoxLayout(EventDialog);
        mainLayout->setSpacing(10);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(16, 16, 16, 16);
        titleLabel = new QLabel(EventDialog);
        titleLabel->setObjectName("titleLabel");

        mainLayout->addWidget(titleLabel);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setHorizontalSpacing(12);
        formLayout->setVerticalSpacing(10);
        labelName = new QLabel(EventDialog);
        labelName->setObjectName("labelName");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelName);

        titleEdit = new QLineEdit(EventDialog);
        titleEdit->setObjectName("titleEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, titleEdit);

        labelDesc = new QLabel(EventDialog);
        labelDesc->setObjectName("labelDesc");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelDesc);

        descriptionEdit = new QPlainTextEdit(EventDialog);
        descriptionEdit->setObjectName("descriptionEdit");
        descriptionEdit->setMaximumHeight(70);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, descriptionEdit);

        labelDate = new QLabel(EventDialog);
        labelDate->setObjectName("labelDate");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, labelDate);

        dateEdit = new QDateEdit(EventDialog);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setCalendarPopup(true);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, dateEdit);

        labelType = new QLabel(EventDialog);
        labelType->setObjectName("labelType");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, labelType);

        typeComboBox = new QComboBox(EventDialog);
        typeComboBox->addItem(QString());
        typeComboBox->addItem(QString());
        typeComboBox->addItem(QString());
        typeComboBox->addItem(QString());
        typeComboBox->setObjectName("typeComboBox");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, typeComboBox);

        labelCategory = new QLabel(EventDialog);
        labelCategory->setObjectName("labelCategory");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, labelCategory);

        categoryComboBox = new QComboBox(EventDialog);
        categoryComboBox->setObjectName("categoryComboBox");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, categoryComboBox);

        labelDeadline = new QLabel(EventDialog);
        labelDeadline->setObjectName("labelDeadline");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, labelDeadline);

        deadlineCheckBox = new QCheckBox(EventDialog);
        deadlineCheckBox->setObjectName("deadlineCheckBox");

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, deadlineCheckBox);


        mainLayout->addLayout(formLayout);

        tagsGroupBox = new QGroupBox(EventDialog);
        tagsGroupBox->setObjectName("tagsGroupBox");
        tagsLayout = new QVBoxLayout(tagsGroupBox);
        tagsLayout->setObjectName("tagsLayout");
        tagsListWidget = new QListWidget(tagsGroupBox);
        tagsListWidget->setObjectName("tagsListWidget");
        tagsListWidget->setMinimumHeight(120);

        tagsLayout->addWidget(tagsListWidget);


        mainLayout->addWidget(tagsGroupBox);

        buttonBox = new QDialogButtonBox(EventDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        mainLayout->addWidget(buttonBox);


        retranslateUi(EventDialog);

        QMetaObject::connectSlotsByName(EventDialog);
    } // setupUi

    void retranslateUi(QDialog *EventDialog)
    {
        EventDialog->setWindowTitle(QCoreApplication::translate("EventDialog", "\320\241\320\276\320\261\321\213\321\202\320\270\320\265", nullptr));
        EventDialog->setStyleSheet(QCoreApplication::translate("EventDialog", "\n"
"    QDialog { background: #1e1e2e; }\n"
"    QLabel  { color: #ccc; font-size: 13px; }\n"
"    QLineEdit, QPlainTextEdit, QDateEdit, QComboBox {\n"
"      background: #252535;\n"
"      color: #e0e0e0;\n"
"      border: 1px solid #3a3a5a;\n"
"      border-radius: 5px;\n"
"      padding: 6px;\n"
"      font-size: 13px;\n"
"    }\n"
"    QLineEdit:focus, QPlainTextEdit:focus, QDateEdit:focus, QComboBox:focus {\n"
"      border: 1px solid #3d5a80;\n"
"    }\n"
"    QCheckBox { color: #ccc; font-size: 13px; }\n"
"    QGroupBox {\n"
"      color: #98c1d9;\n"
"      font-size: 13px;\n"
"      border: 1px solid #3a3a5a;\n"
"      border-radius: 6px;\n"
"      margin-top: 8px;\n"
"      padding-top: 6px;\n"
"    }\n"
"    QGroupBox::title {\n"
"      subcontrol-origin: margin;\n"
"      left: 10px;\n"
"    }\n"
"    QListWidget {\n"
"      background: #252535;\n"
"      color: #e0e0e0;\n"
"      border: 1px solid #3a3a5a;\n"
"      border-radius: 5px;\n"
"      font-size: 13px;\n"
"    }\n"
"    QListWidget::item"
                        ":hover   { background: #2d2d45; }\n"
"    QListWidget::item:selected{ background: #3d5a80; }\n"
"    QPushButton {\n"
"      background: #3d5a80;\n"
"      color: white;\n"
"      border: none;\n"
"      padding: 10px 28px;\n"
"      border-radius: 6px;\n"
"      font-size: 13px;\n"
"      min-width: 100px;\n"
"    }\n"
"    QPushButton:hover { background: #4d6a90; }\n"
"   ", nullptr));
        titleLabel->setText(QCoreApplication::translate("EventDialog", "\320\235\320\276\320\262\320\276\320\265 \321\201\320\276\320\261\321\213\321\202\320\270\320\265", nullptr));
        titleLabel->setStyleSheet(QCoreApplication::translate("EventDialog", "font-size:18px; font-weight:bold; color:#e9c46a; padding-bottom:4px;", nullptr));
        labelName->setText(QCoreApplication::translate("EventDialog", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 *", nullptr));
        titleEdit->setPlaceholderText(QCoreApplication::translate("EventDialog", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\265...", nullptr));
        labelDesc->setText(QCoreApplication::translate("EventDialog", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        descriptionEdit->setPlaceholderText(QCoreApplication::translate("EventDialog", "\320\224\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214\320\275\320\260\321\217 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217...", nullptr));
        labelDate->setText(QCoreApplication::translate("EventDialog", "\320\224\320\260\321\202\320\260 *", nullptr));
        dateEdit->setDisplayFormat(QCoreApplication::translate("EventDialog", "dd.MM.yyyy", nullptr));
        labelType->setText(QCoreApplication::translate("EventDialog", "\320\242\320\270\320\277", nullptr));
        typeComboBox->setItemText(0, QCoreApplication::translate("EventDialog", "\321\201\320\276\320\261\321\213\321\202\320\270\320\265", nullptr));
        typeComboBox->setItemText(1, QCoreApplication::translate("EventDialog", "\320\264\320\265\320\264\320\273\320\260\320\271\320\275", nullptr));
        typeComboBox->setItemText(2, QCoreApplication::translate("EventDialog", "\320\266\320\265\320\273\320\260\320\275\320\270\320\265", nullptr));
        typeComboBox->setItemText(3, QCoreApplication::translate("EventDialog", "\320\275\320\260\320\277\320\276\320\274\320\270\320\275\320\260\320\275\320\270\320\265", nullptr));

        labelCategory->setText(QCoreApplication::translate("EventDialog", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217 *", nullptr));
        labelDeadline->setText(QCoreApplication::translate("EventDialog", "\320\224\320\265\320\264\320\273\320\260\320\271\320\275", nullptr));
        deadlineCheckBox->setText(QCoreApplication::translate("EventDialog", "\320\237\320\276\320\274\320\265\321\202\320\270\321\202\321\214 \320\272\320\260\320\272 \320\264\320\265\320\264\320\273\320\260\320\271\320\275", nullptr));
        tagsGroupBox->setTitle(QCoreApplication::translate("EventDialog", "\320\242\320\265\320\263\320\270 (\320\274\320\276\320\266\320\275\320\276 \320\262\321\213\320\261\321\200\320\260\321\202\321\214 \320\275\320\265\321\201\320\272\320\276\320\273\321\214\320\272\320\276 \342\200\224 \321\201\320\262\321\217\320\267\321\214 M:M)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EventDialog: public Ui_EventDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVENTDIALOG_H
