#include "logmodeldata.h"
#include <QLabel>
#include "filelogwidget.h"
#include "popupwidget.h"
#include <QPainter>
#include <QDebug>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>
#include <QDateTime>


//FileLogWidget *LogModelData::m_fileLogWidget = nullptr;
PopupWidget *LogModelData::m_popupWidget = nullptr;

LogModelData::LogModelData()
{   
//   if (m_fileLogWidget == nullptr){
//        m_fileLogWidget = new FileLogWidget();
//    }
   if (m_popupWidget == nullptr){
        m_popupWidget = new PopupWidget();
    }
    time = getCurrentTime();
}

void LogModelData::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPalette p = option.palette;
    auto color = index.data(Qt::BackgroundRole).value<QBrush>();
    p.setBrush(QPalette::Window, color);
    painter->setFont(option.font);
    if (type == TEHNICAL_MESSAGE) {
        painter->save();
        QFontMetrics fm(option.font);
        fm.height();
        int delta = option.rect.height() - fm.height();
        delta /= 2;
        painter->translate(2, delta);
        painter->drawText(option.rect, text);
        painter->restore();
//    } else if(type == INCOMING_FILE) {
//        setFileLogWidget();
//        m_fileLogWidget->setPalette(p);
//        painter->save();
//        painter->translate(option.rect.x(), option.rect.y());
//        m_fileLogWidget->render(painter);
//        painter->restore();
//    } else if(type == POPUP_TEXT) {
//        setPopipWidget();
//        m_popupWidget->resize(option.rect.width(),m_popupWidget->height());
//        m_popupWidget->setPalette(p);
//        if (timeConfirm.isEmpty()){
//            bool x = index.data(MsgFlashRole).toBool();
//            Qt::GlobalColor c = x ?
//                        Qt::red : Qt::transparent;
//            p.setColor(QPalette::Window, QColor(c));
//            painter->fillRect(option.rect, c);
//        }
//        painter->save();
//        painter->translate(option.rect.x(), option.rect.y());
//        m_popupWidget->render(painter);
//        painter->restore();
      } else if (type == INFO_MESSAGE) {
            if (!index.data(MsgShowRole).toBool()){
                if (timeConfirm.isEmpty()){
                    bool x = index.data(MsgFlashRole).toBool();
                    Qt::GlobalColor c = x ?
                                Qt::red : Qt::transparent;
                    p.setColor(QPalette::Window, QColor(c));
                    painter->fillRect(option.rect, c);
                }
                painter->save();
                QFontMetrics fm(option.font);
                fm.height();
                int delta = option.rect.height() - fm.height();
                delta /= 2;
                painter->translate(2,delta);
                //painter->drawText(option.rect,Qt::TextWordWrap, text);
                int offset = 0;
                if (timeConfirm != ""){
                    offset = 130;
                }
                painter->drawText(option.rect.x(),option.rect.y(),option.rect.width()-offset,option.rect.height(),Qt::TextSingleLine,text);
                //painter->translate(option.rect.x(), option.rect.y());
                QPixmap pixmap( ":/Icons/arrow-down.png" );
                int x = option.rect.right() - pixmap.width();
                int y = option.rect.top() + ( option.rect.height() - pixmap.height() ) / 2;
                painter->drawText(option.rect.x()-20,option.rect.y(),option.rect.width(),option.rect.height(),Qt::AlignRight,timeConfirm);
                painter->drawPixmap(x-2,y-3,pixmap);
                if (!listOfFiles.isEmpty()){
                    pixmap.load(":/Icons/page_white_text.png");
                    painter->drawPixmap(x-22,y-3,pixmap);
                }
                painter->restore();
            } else {
                setPopipWidget();                
                m_popupWidget->resize(option.rect.width(),m_popupWidget->height());
                qDebug()<< "paint " << text << " size "<< m_popupWidget->height();
                m_popupWidget->setPalette(p);
                painter->save();
                painter->translate(option.rect.x(), option.rect.y());
                m_popupWidget->render(painter);
                painter->restore();
            }
        }

}

QSize LogModelData::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    QSize retVal(0, 0);
    if (type == TEHNICAL_MESSAGE) {
        QFontMetrics fm(option.font);
        int width = fm.width(text);
        int height = fm.height() + 6;
        retVal = QSize(width, height);        
//    } else if(type == INCOMING_FILE) {
//        setFileLogWidget();
//        retVal = m_fileLogWidget->size();
//    } else if (type == POPUP_TEXT) {
//        setPopipWidget();
//        retVal = m_popupWidget->size();
    } else if (type == INFO_MESSAGE) {
        if (!index.data(MsgShowRole).toBool()){
            QFontMetrics fm(option.font);
            int width = fm.width(text);
            int height = fm.height() + 6;
            retVal = QSize(width, height);
        } else {            
            setPopipWidget();
            retVal = m_popupWidget->size();            
        }
    }
    return retVal;

}

//void LogModelData::checkDblClickFile(const QPoint &pos)
//{
//   m_fileLogWidget->setDescription(text);
//   m_fileLogWidget->cleanFiles();
//   QList<QPushButton*> buttons;
//   for (const QString &file : listOfFiles) {
//       QPushButton *b = m_fileLogWidget->addFile(file);
//       buttons.append(b);
//   }
//   m_fileLogWidget->adjustSize();
//   for (int i = 0; i <buttons.size(); ++i) {
//    QRect r(buttons.at(i)->mapToParent(QPoint(0, 0)), buttons.at(i)->size());
//    //проверка попадание курсора в кнопку на виджете
//       if (r.contains(pos)) {
//       QString file ("file:///"+listOfFiles.at(i));
//       QDesktopServices::openUrl(file);
//       break;
//       }
//   }

//}

//void LogModelData::setFileLogWidget() const
//{
//    m_fileLogWidget->setDescription(text);
//    m_fileLogWidget->cleanFiles();
//    for (const QString &file : listOfFiles) {
//         m_fileLogWidget->addFile(file);
//    }
//    m_fileLogWidget->adjustSize();
//}

void LogModelData::setPopipWidget() const
{
    m_popupWidget->setDescription(text);
    m_popupWidget->setTime(timeConfirm);
    m_popupWidget->cleanFiles();
    for (const QString &file : listOfFiles) {
         m_popupWidget->addFile(file);
    }
    m_popupWidget->adjustSize();
}

bool LogModelData::checkClickMsg(const QPoint &pos)
{
    bool retval = false;
    m_popupWidget->setDescription(text);
    m_popupWidget->setTime(timeConfirm);
    m_popupWidget->cleanFiles();
   QList<QPushButton*> buttons;
   for (const QString &file : listOfFiles) {
       QPushButton *b = m_popupWidget->addFile(file);
       buttons.append(b);
   }
   //QLabel *lb_hide = m_popupWidget->checkHide();
   m_popupWidget->adjustSize();
   for (int i = 0; i <buttons.size(); ++i) {
    QRect r(buttons.at(i)->mapToParent(QPoint(0, 0)), buttons.at(i)->size());
    //проверка попадание курсора в кнопку на виджете
       if (r.contains(pos)) {
       QString file ("file:///"+listOfFiles.at(i));
       QDesktopServices::openUrl(file);
       break;
       }
   }
   QLabel *lb_hide = m_popupWidget->checkHide();
   QRect r(lb_hide->mapToParent(QPoint(0, 0)), lb_hide->size());
   qDebug() << r << " " << pos << " " << lb_hide->mapToGlobal(QPoint(0,0));

   if (r.contains(pos)) {
       if (timeConfirm.isEmpty())
        timeConfirm = getCurrentTime();
       retval = true;
   }
   return retval;

}

QString LogModelData::getCurrentTime()
{
        QDateTime dateTime = QDateTime::currentDateTime();
        QString dateTimeString =  dateTime.toString("yyyy.MM.dd hh:mm:ss");
        return dateTimeString;

}





