#include "logmodeldata.h"
#include <QLabel>
#include "filelogwidget.h"
#include <QPainter>
#include <QDebug>
#include <QFileInfo>
#include <QFileIconProvider>

FileLogWidget *LogModelData::m_fileLogWidget = nullptr;

LogModelData::LogModelData()
{
 //   static bool first = true;
//    if (first){
        m_fileLogWidget = new FileLogWidget();
 //       first = false;
 //   }
}

void LogModelData::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //painter->drawText(0, 20, text);
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
        painter->drawText(option.rect, text);
        painter->restore();
    } else if(type == INCOMING_FILE) {
        //m_fileLogWidget->setPalette(p);
        //bool x = index.data(Qt::UserRole + 2).toBool();
//        Qt::GlobalColor c = x ?
//                    Qt::red : Qt::transparent;
//        p.setColor(QPalette::Window, QColor(c));
//        painter->fillRect(option.rect, c);
        painter->save();
        painter->translate(option.rect.x(), option.rect.y());
        QFontMetrics fm(option.font);
        fm.height();
        int delta = option.rect.height() - fm.height();
        delta /= 2;
        //painter->translate(0, delta);
        //m_fileLogWidget->render(painter);
        //painter->drawText(option.rect, text);
        QString FileName = text;
        if (!FileName.isEmpty()){
            QFileInfo fInfo(FileName);
            QFileIconProvider FIcon;
            QIcon iFile = FIcon.icon(fInfo);
            iFile.paint(painter,0,0,20,20);
        }
        painter->drawText(option.rect, text+delta);
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
        m_fileLogWidget->adjustSize();
        retVal = m_fileLogWidget->size();
    }
    return retVal;

}

void LogModelData::setFile()
{
    if(type == INCOMING_FILE) {
        m_fileLogWidget->setFilename(text);
    }
}


