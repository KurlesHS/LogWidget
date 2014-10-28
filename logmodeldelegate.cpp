#include "logmodeldelegate.h"
#include "logmodeldata.h"
#include "filelogwidget.h"
#include "logmodelextended.h"
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include <QMouseEvent>

LogModelDelegate::LogModelDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

void LogModelDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    QVariant x = index.data(LogDataRole);
    if (x.canConvert<LogModelData>()){
        LogModelData data = x.value<LogModelData>();
        data.paint(painter, option, index);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }

}

QSize LogModelDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size(0, 0);
    QVariant x = index.data(LogDataRole);
    if (x.canConvert<LogModelData>()){
        LogModelData data = x.value<LogModelData>();
        size = data.sizeHint(option, index);
    } else {
        size = QStyledItemDelegate::sizeHint(option, index);
    }
    return size;
}

bool LogModelDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
   bool retVal = false;
    if (event->type() == QEvent::MouseButtonDblClick) {
    QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent *>(event);
    qDebug() << "mouse Pos" <<  mouseEvent->pos();
    qDebug() << "fileRect" << option.rect;
    qDebug() << "reult" << mouseEvent->pos().y() - option.rect.topLeft().y();
    QPoint mousePoint = mouseEvent->pos();
    QRect localRect = option.rect;
    mousePoint.setX(mousePoint.x()-localRect.x());
    mousePoint.setY(mousePoint.y()-localRect.y());
    if (mousePoint.x() > 0){
      QVariant x = index.data(LogDataRole);
        if (x.canConvert<LogModelData>()){
            LogModelData data = x.value<LogModelData>();
            data.checkDblClickFile(mousePoint, option.rect);
        }
      }
   }
   retVal = QStyledItemDelegate::editorEvent(event,model,option,index);
   return retVal;
}
