#ifndef CATEGORYDIALOG_H
#define CATEGORYDIALOG_H

#include <QDialog>
#include <QColor>

QT_BEGIN_NAMESPACE
namespace Ui { class CategoryDialog; }
QT_END_NAMESPACE

class CategoryDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CategoryDialog(QWidget *parent = nullptr);
    ~CategoryDialog();

    void setName(const QString &name);
    void setColor(const QColor &c);

    QString name() const;
    QColor  color() const;

private slots:
    void chooseColor();

private:
    Ui::CategoryDialog *ui;
    QColor m_color;

    void updateColorPreview();
};

#endif // CATEGORYDIALOG_H
