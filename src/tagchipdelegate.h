#ifndef TAGCHIPDELEGATE_H
#define TAGCHIPDELEGATE_H

#include <QStyledItemDelegate>
#include <QHash>
#include <QColor>

class TagChipDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TagChipDelegate(QObject *parent = nullptr);

    void setTagColors(const QHash<QString, QColor> &map);

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

private:
    QHash<QString, QColor> m_colors;
};

#endif // TAGCHIPDELEGATE_H
