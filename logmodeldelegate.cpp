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

    QVariant x = index.data(Qt::UserRole + 1);
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
    QVariant x = index.data(Qt::UserRole + 1);
    if (x.canConvert<LogModelData>()){
        LogModelData data = x.value<LogModelData>();
        size = data.sizeHint(option, index);
    } else {
        size = QStyledItemDelegate::sizeHint(option, index);
    }
    return size;
}
