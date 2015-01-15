#ifndef LOGMODELDELEGATE_H
#define LOGMODELDELEGATE_H

#include "popupwidget.h"
#include <logmodeldata.h>

#include <QStyledItemDelegate>
#include <QTreeView>
class LogModelDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    LogModelDelegate(QTreeView *parentWidget);
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    virtual QSize sizeHint (const QStyleOptionViewItem &option, const QModelIndex &index) const;

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option, const QModelIndex &index);

    bool eventFilter ( QObject * editor, QEvent * event );

    int getItemWidth() const;
    void setItemWidth(int value);
    void movePopup(const QPoint &pos) const;

private:
    int itemWidth;
    PopupWidget *m_popupWidget;
    QPoint offsetPopup;

    void openPopup(const LogModelData &data, const QFont &font, const int &width, const QPoint &pos) const;

};

#endif // LOGMODELDELEGATE_H
