#include "logmodeldelegate.h"
#include "logmodeldata.h"
#include "logmodelextended.h"
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include <QMouseEvent>
#include <popupwidget.h>
#include <QTreeView>

LogModelDelegate::LogModelDelegate(QTreeView *parentWidget) :
    QStyledItemDelegate(parentWidget)
{
   m_popupWidget = new PopupWidget(parentWidget);
}

void LogModelDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{    
    QStyledItemDelegate::paint(painter, option, index);
    QVariant x = index.data(LogDataRole);        
    if (x.canConvert<LogModelData>()){        
        LogModelData data = x.value<LogModelData>();        
            data.paint(painter, option, index);
    }
    else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize LogModelDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size(0, 0);
    QVariant x = index.data(LogDataRole);
    if (x.canConvert<LogModelData>()){
        LogModelData data = x.value<LogModelData>();        
            size = data.sizeHint(option, index, itemWidth);
    } else {
        size = QStyledItemDelegate::sizeHint(option, index);                
    }        
    return size;
}

bool LogModelDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
   bool retVal = false;  
   if (event->type() == QEvent::MouseButtonDblClick || event->type() == QEvent::MouseButtonPress) {
    QVariant x = index.data(LogDataRole);
        if (x.canConvert<LogModelData>()){
            QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent *>(event);
            QPoint mousePoint = mouseEvent->pos();
            QRect localRect = option.rect;
            //qDebug() << mousePoint << localRect;
            mousePoint.setX(mousePoint.x()-localRect.x());
            mousePoint.setY(mousePoint.y()-localRect.y());
            int popupX = mouseEvent->globalPos().x()-mousePoint.x();
            int popupY = mouseEvent->globalPos().y()-mousePoint.y();
            QPoint popupP(popupX,popupY);
            //QSize popupSize(itemWidth,m_popupWidget->geometry().height());
            //QRect r(popupP,popupSize);
            LogModelData data = x.value<LogModelData>();
            //qDebug() << itemWidth;
            if (data.type == INFO_MESSAGE && event->type() == QEvent::MouseButtonPress)
//                    if (index.data(MsgShowRole).toBool()) {
//                            if (data.checkClickMsg(mousePoint,option)){
//                                model->setData(index,false, MsgShowRole);
//                            }
//                    } else {
                       if (option.rect.width()-mousePoint.x()<20){
                            if (data.checkBigMsg(option)){
                                if (!data.listOfFiles.isEmpty() || index.data(MsgConfirmRole).toBool())
                                    data.setConfirm();
                                model->setData(index,true, MsgShowRole);
                                model->setData(index,QVariant::fromValue<LogModelData>(data),LogDataRole);
                                //data.openPopup(option.font,popupP,itemWidth);
                                offsetPopup.setX(option.rect.x()+2);
                                offsetPopup.setY(option.rect.y()+2);
                                //offsetPopup.setX(mousePoint.x());
                                //offsetPopup.setY(mousePoint.y());
                                openPopup(data,option.font,itemWidth,popupP);
                                qDebug() << m_popupWidget->pos();
                            }
//                       }
                    }
             else if (data.type == INFO_MESSAGE && event->type() == QEvent::MouseButtonDblClick && index.data(MsgConfirmRole).toBool()){
                if (!data.checkBigMsg(option)) {
                    data.setConfirm();
                qDebug() << "DblClick";
                model->setData(index,false,MsgConfirmRole);
                model->setData(index,QVariant::fromValue<LogModelData>(data),LogDataRole);
                }
            }
            //m_popupWidget->resize(200,100);
//            m_popupWidget->setFixedSize(popupSize);
//            qDebug() << m_popupWidget->size();
//            m_popupWidget->move(popupX,popupY);
//            qDebug() << m_popupWidget->rect();
//            m_popupWidget->setDescription(data.text);
//            m_popupWidget->setTime(data.timeConfirm);
//            m_popupWidget->show();
            //m_popupWidget->setFixedSize();
         }
   }
   retVal = QStyledItemDelegate::editorEvent(event,model,option,index);
   return retVal;
}

bool LogModelDelegate::eventFilter(QObject *editor, QEvent *event)
{
    qDebug() << event;
}
int LogModelDelegate::getItemWidth() const
{
    return itemWidth;
}

void LogModelDelegate::setItemWidth(int value)
{
    itemWidth = value;
}

void LogModelDelegate::movePopup(const QPoint &pos) const
{
    QPoint popupPos = pos+offsetPopup;
    //popupPos.setX(pos.x()+offsetPopup.x());
    //popupPos.setY(pos.y()+offsetPopup.y());
    //popupPos. setX(pos.x()+offsetPopup.x());
    qDebug() << m_popupWidget->pos() << popupPos << pos << offsetPopup;
    m_popupWidget->move(popupPos);
}

void LogModelDelegate::openPopup(const LogModelData &data, const QFont &font, const int &width,const QPoint &pos) const
{
    //int width = m_popupWidget->width();
    m_popupWidget->cleanFiles();
    m_popupWidget->setTime(data.timeConfirm);
    m_popupWidget->showIconFile(data.listOfFiles.isEmpty());
    if (!data.listOfFiles.isEmpty())
        m_popupWidget->setFileInfo();

    for (const QString &file : data.listOfFiles) {
        m_popupWidget->addFileLb(file);
    }

    m_popupWidget->setDescription(data.text);

    QFontMetrics fm(font);
    QRect textRect = fm.boundingRect(QRect(QPoint(0,0),QPoint(width,100)),Qt::TextWordWrap,data.text);
    int fileHeight = m_popupWidget->getFileHeight();

    m_popupWidget->adjustSize();
    m_popupWidget->setFixedSize(width,textRect.height()+fileHeight);
    m_popupWidget->move(pos);
    m_popupWidget->show();

}


