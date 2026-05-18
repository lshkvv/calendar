#include "categorybadgedelegate.h"
#include <QPainter>

CategoryBadgeDelegate::CategoryBadgeDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void CategoryBadgeDelegate::setCategoryColors(const QHash<QString, QColor> &map)
{
    m_colors = map;
}

void CategoryBadgeDelegate::paint(QPainter *painter,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    painter->save();

    QString name = index.data().toString();
    QColor base = m_colors.value(name, QColor("#3d5a80"));

    QColor fill = base;
    fill.setAlpha(90);
    QColor border = base.darker(120);
    QColor text = Qt::white;

    QRect r = option.rect.adjusted(6, 6, -6, -6);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(border);
    painter->setBrush(fill);
    painter->drawRoundedRect(r, 8, 8);

    painter->setPen(text);
    QFont f = option.font;
    f.setBold(true);
    painter->setFont(f);
    painter->drawText(r.adjusted(8, 0, -8, 0),
                      Qt::AlignVCenter | Qt::AlignLeft,
                      name);

    painter->restore();
}
