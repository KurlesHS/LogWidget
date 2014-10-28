#include "logmodeldelegate.h"
#include "logmodeldata.h"
#include "filelogwidget.h"
#include "logmodelextended.h"
#include <QPainter>
#include <QDebug>
#include <QLabel>
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
    QVariant x = index.data(LogDataRole);
    if (x.canConvert<LogModelData>()){
        LogModelData data = x.value<LogModelData>();
        retVal = data.editorEvent(event,model,option,index);
    } else {
        retVal = QStyledItemDelegate::editorEvent(event,model,option,index);
    }
    return retVal;
}
