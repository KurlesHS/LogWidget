#include "logmodeldata.h"
#include <QLabel>
#include "filelogwidget.h"
#include "popupwidget.h"
#include <QPainter>
#include <QDebug>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>


FileLogWidget *LogModelData::m_fileLogWidget = nullptr;
PopupWidget *LogModelData::m_popupWidget = nullptr;

LogModelData::LogModelData()
{   
   if (m_fileLogWidget == nullptr){
        m_fileLogWidget = new FileLogWidget();
    }
   if (m_popupWidget == nullptr){
        m_popupWidget = new PopupWidget();
    }

}

void LogModelData::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPalette p = option.palette;
    auto color = index.data(Qt::BackgroundRole).value<QBrush>();
    p.setBrush(QPalette::Window, color);
    painter->setFont(option.font);
    if (type == SIMPLE_TEXT) {        
        painter->save();
        QFontMetrics fm(option.font);
        fm.height();
        int delta = option.rect.height() - fm.height();
        delta /= 2;
        painter->translate(0, delta);
        painter->drawText(option.rect,Qt::TextWordWrap, text);        
        painter->restore();
    } else if(type == INCOMING_FILE) {
        m_fileLogWidget->setDescription(text);
        m_fileLogWidget->cleanFiles();
        m_fileLogWidget->setPalette(p);
        for (const QString &file : listOfFiles) {
            m_fileLogWidget->addFile(file);
        }
        painter->save();
        painter->translate(option.rect.x(), option.rect.y());
        m_fileLogWidget->render(painter);
        painter->restore();
    } else if(type == POPUP_TEXT) {
        m_popupWidget->setDescription(text);
        m_popupWidget->setTime(time);
        m_popupWidget->resize(option.rect.width(),m_popupWidget->height());
        m_popupWidget->setPalette(p);
        if (index.data(PopupClickRole).toBool()){
            bool x = index.data(PopupFlashRole).toBool();
            Qt::GlobalColor c = x ?
                        Qt::red : Qt::transparent;
            p.setColor(QPalette::Window, QColor(c));
            painter->fillRect(option.rect, c);
        }
        painter->save();
        painter->translate(option.rect.x(), option.rect.y());
        m_popupWidget->render(painter);        
        painter->restore();        
    }
}

QSize LogModelData::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    QSize retVal(0, 0);
    if (type == SIMPLE_TEXT) {
        QFontMetrics fm(option.font);
        int width = fm.width(text);
        int height = fm.height() + 6;
        retVal = QSize(width, height);
    } else if(type == INCOMING_FILE) {
        m_fileLogWidget->setDescription(text);
        m_fileLogWidget->cleanFiles();
        for (const QString &file : listOfFiles) {
             m_fileLogWidget->addFile(file);
        }
        m_fileLogWidget->adjustSize();
        retVal = m_fileLogWidget->size();
    } else if (type == POPUP_TEXT) {
        m_popupWidget->setDescription(text);        
        m_popupWidget->setTime(time);
        retVal = m_popupWidget->size();
    }
    return retVal;

}

void LogModelData::checkDblClickFile(const QPoint &pos)
{
   m_fileLogWidget->setDescription(text);
   m_fileLogWidget->cleanFiles();
   QList<QPushButton*> buttons;
   for (const QString &file : listOfFiles) {
       QPushButton *b = m_fileLogWidget->addFile(file);
       buttons.append(b);
   }
   m_fileLogWidget->adjustSize();
   for (int i = 0; i <buttons.size(); ++i) {
    QRect r(buttons.at(i)->mapToParent(QPoint(0, 0)), buttons.at(i)->size());
    //проверка попадание курсора в кнопку на виджете
       if (r.contains(pos)) {
       QString file ("file:///"+listOfFiles.at(i));
       QDesktopServices::openUrl(file);
       break;
       }
   }

}




