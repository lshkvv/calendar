#include "categorydialog.h"
#include "ui_categorydialog.h"
#include <QColorDialog>

CategoryDialog::CategoryDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CategoryDialog)
{
    ui->setupUi(this);

    connect(ui->colorBtn, &QPushButton::clicked,
            this, &CategoryDialog::chooseColor);

    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected,
            this, &QDialog::reject);
}

CategoryDialog::~CategoryDialog()
{
    delete ui;
}

void CategoryDialog::setName(const QString &name)
{
    ui->nameEdit->setText(name);
}

void CategoryDialog::setColor(const QColor &c)
{
    m_color = c;
    updateColorPreview();
}

QString CategoryDialog::name() const
{
    return ui->nameEdit->text().trimmed();
}

QColor CategoryDialog::color() const
{
    return m_color;
}

void CategoryDialog::chooseColor()
{
    QColor c = QColorDialog::getColor(
        m_color.isValid() ? m_color : QColor("#3498db"),
        this,
        "Выберите цвет категории"
        );
    if (!c.isValid())
        return;

    m_color = c;
    updateColorPreview();
}

void CategoryDialog::updateColorPreview()
{
    QString css = QString(
                      "background:%1; border:1px solid #444; border-radius:4px;")
                      .arg(m_color.isValid() ? m_color.name() : "#000000");
    ui->colorPreview->setStyleSheet(css);
}
