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
    QStyledItemDelegate::paint(painter, option, index);
    QVariant x = index.data(LogDataRole);
    //int i = index.column();
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
    qDebug() << x;
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
    QPoint mousePoint = mouseEvent->pos();
    QRect localRect = option.rect;
    mousePoint.setX(mousePoint.x()-localRect.x());
    mousePoint.setY(mousePoint.y()-localRect.y());
    if (mousePoint.x() > 0){
      QVariant x = index.data(LogDataRole);
        if (x.canConvert<LogModelData>()){
            LogModelData data = x.value<LogModelData>();
            if (data.type == INCOMING_FILE){
                data.checkDblClickFile(mousePoint);
            }
        }
      }
   }
   retVal = QStyledItemDelegate::editorEvent(event,model,option,index);
   return retVal;
}
