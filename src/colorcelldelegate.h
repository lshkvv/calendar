#ifndef COLORCELLDELEGATE_H
#define COLORCELLDELEGATE_H

#include <QStyledItemDelegate>

class ColorCellDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ColorCellDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

#endif // COLORCELLDELEGATE_H
