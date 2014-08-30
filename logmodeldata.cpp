#include "logmodeldata.h"
#include <QLabel>
#include "filelogwidget.h"
#include <QPainter>
#include <QDebug>

FileLogWidget *LogModelData::m_fileLogWidget = nullptr;
QLabel *LogModelData::m_label = nullptr;

LogModelData::LogModelData()
{
    static bool first = true;
    if (first){
        m_fileLogWidget = new FileLogWidget();
        m_label = new QLabel();
        first = false;
    }
}

void LogModelData::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //painter->drawText(0, 20, text);
    QPalette p = option.palette;
    auto color = index.data(Qt::BackgroundRole).value<QBrush>();
    p.setBrush(QPalette::Window, color);
    if (type == SIMPLE_TEXT) {

        m_label->setText(text);
        m_label->setPalette(p);
        m_label->resize(option.rect.width(), option.rect.height());

        QPixmap px(m_label->size());
        px.fill(Qt::transparent);
        m_label->render(&px);
        painter->drawPixmap(option.rect, px);
    } else if(type == INCOMING_FILE) {
        m_fileLogWidget->setPalette(p);
        QPixmap px(option.rect.width(), option.rect.height());
        bool x = index.data(Qt::UserRole + 2).toBool();
        Qt::GlobalColor c = x ?
                    Qt::red : Qt::transparent;
        px.fill(c);
        m_fileLogWidget->render(&px);
        painter->drawPixmap(option.rect, px);
    }
}

QSize LogModelData::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    QSize retVal(0, 0);
    if (type == SIMPLE_TEXT) {
        m_label->setText(text);
        m_label->adjustSize();
        retVal = m_label->size();
        retVal.setHeight(retVal.height() + 5);
    } else if(type == INCOMING_FILE) {

        m_fileLogWidget->adjustSize();
        retVal = m_fileLogWidget->size();
    }
    return retVal;

}
