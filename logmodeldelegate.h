#ifndef LOGMODELDELEGATE_H
#define LOGMODELDELEGATE_H

#include <QStyledItemDelegate>
class LogModelDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    LogModelDelegate(QObject *parent = 0);
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    virtual QSize sizeHint (const QStyleOptionViewItem &option, const QModelIndex &index) const;

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option, const QModelIndex &index);

    int getItemWidth() const;
    void setItemWidth(int value);

private:
    int itemWidth;

};

#endif // LOGMODELDELEGATE_H
