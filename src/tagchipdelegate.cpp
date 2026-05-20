#include "tagchipdelegate.h"
#include <QPainter>

TagChipDelegate::TagChipDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void TagChipDelegate::setTagColors(const QHash<QString, QColor> &map)
{
    m_colors = map;
}

void TagChipDelegate::paint(QPainter *painter,
                            const QStyleOptionViewItem &option,
                            const QModelIndex &index) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    QString raw = index.data().toString().trimmed();
    if (raw.isEmpty()) {
        painter->restore();
        return;
    }

    QStringList tags = raw.split(", ", Qt::SkipEmptyParts);

    int x = option.rect.x() + 6;
    int y = option.rect.y() + 6;
    int h = option.rect.height() - 12;
    if (h < 16)
        h = 16;

    QFont f = option.font;
    f.setBold(true);
    painter->setFont(f);

    for (const QString &tag : tags) {
        QColor color = m_colors.value(tag, QColor("#7f8c8d"));
        QColor fill = color;
        fill.setAlpha(95);

        int textW = painter->fontMetrics().horizontalAdvance(tag);
        int chipW = textW + 18;
        QRect r(x, y, chipW, h);

        painter->setPen(color.darker(130));
        painter->setBrush(fill);
        painter->drawRoundedRect(r, 8, 8);

        painter->setPen(Qt::white);
        painter->drawText(r, Qt::AlignCenter, tag);

        x += chipW + 6;
        if (x > option.rect.right() - 60)
            break;
    }

    painter->restore();
}
