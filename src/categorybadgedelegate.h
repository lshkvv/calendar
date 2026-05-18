#ifndef CATEGORYBADGEDELEGATE_H
#define CATEGORYBADGEDELEGATE_H

#include <QStyledItemDelegate>
#include <QHash>
#include <QColor>

class CategoryBadgeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CategoryBadgeDelegate(QObject *parent = nullptr);

    void setCategoryColors(const QHash<QString, QColor> &map);

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

private:
    QHash<QString, QColor> m_colors;
};

#endif // CATEGORYBADGEDELEGATE_H
