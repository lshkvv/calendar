#include "colorcelldelegate.h"
#include <QPainter>
#include <QColor>

ColorCellDelegate::ColorCellDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void ColorCellDelegate::paint(QPainter *painter,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    painter->save();

    QColor c(index.data().toString());
    if (!c.isValid())
        c = QColor("#3498db");

    int barWidth  = 60;
    int barHeight = option.rect.height() - 10;
    if (barHeight < 8)
        barHeight = 8;

    int x = option.rect.center().x() - barWidth / 2;
    int y = option.rect.center().y() - barHeight / 2;
    QRect r(x, y, barWidth, barHeight);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);
    painter->setBrush(c);
    painter->drawRoundedRect(r, 4, 4);

    painter->restore();
}
