/********************************************************************************
** Form generated from reading UI file 'categorydialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CATEGORYDIALOG_H
#define UI_CATEGORYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CategoryDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *labelName;
    QLineEdit *nameEdit;
    QLabel *labelColor;
    QHBoxLayout *colorLayout;
    QFrame *colorPreview;
    QPushButton *colorBtn;
    QSpacerItem *spacerItem;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CategoryDialog)
    {
        if (CategoryDialog->objectName().isEmpty())
            CategoryDialog->setObjectName("CategoryDialog");
        verticalLayout = new QVBoxLayout(CategoryDialog);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        labelName = new QLabel(CategoryDialog);
        labelName->setObjectName("labelName");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelName);

        nameEdit = new QLineEdit(CategoryDialog);
        nameEdit->setObjectName("nameEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, nameEdit);

        labelColor = new QLabel(CategoryDialog);
        labelColor->setObjectName("labelColor");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelColor);

        colorLayout = new QHBoxLayout();
        colorLayout->setObjectName("colorLayout");
        colorPreview = new QFrame(CategoryDialog);
        colorPreview->setObjectName("colorPreview");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(colorPreview->sizePolicy().hasHeightForWidth());
        colorPreview->setSizePolicy(sizePolicy);
        colorPreview->setMinimumSize(QSize(60, 20));
        colorPreview->setMaximumSize(QSize(80, 20));
        colorPreview->setFrameShape(QFrame::Box);

        colorLayout->addWidget(colorPreview);

        colorBtn = new QPushButton(CategoryDialog);
        colorBtn->setObjectName("colorBtn");

        colorLayout->addWidget(colorBtn);

        spacerItem = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        colorLayout->addItem(spacerItem);


        formLayout->setLayout(1, QFormLayout::ItemRole::FieldRole, colorLayout);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(CategoryDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(CategoryDialog);

        QMetaObject::connectSlotsByName(CategoryDialog);
    } // setupUi

    void retranslateUi(QDialog *CategoryDialog)
    {
        CategoryDialog->setWindowTitle(QCoreApplication::translate("CategoryDialog", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217", nullptr));
        labelName->setText(QCoreApplication::translate("CategoryDialog", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        labelColor->setText(QCoreApplication::translate("CategoryDialog", "\320\246\320\262\320\265\321\202", nullptr));
        colorBtn->setText(QCoreApplication::translate("CategoryDialog", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214\342\200\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CategoryDialog: public Ui_CategoryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CATEGORYDIALOG_H
