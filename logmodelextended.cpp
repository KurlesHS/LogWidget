#include "logmodelextended.h"
#include <QDateTime>
#include <QTimer>
#include <QDebug>
#include <Qt>

#include "logmodeldata.h"

LogModelExtended::LogModelExtended(QObject *parent) :
    QStandardItemModel(parent)
{

}


void LogModelExtended::addSimpleText(const QString &text)
{    
    LogModelData data;
    data.type = SIMPLE_TEXT;
    data.time = getDateTime();
    data.text = text;
    auto item = new QStandardItem();
    item->setData(QVariant::fromValue<LogModelData>(data));
    item->setEditable(false);
    auto itemDT = new QStandardItem(data.time);
    itemDT->setData(getDateTime());
    itemDT->setEditable(false);
    appendRow(QList<QStandardItem*>() << itemDT << item);
}


void LogModelExtended::addPopup(const QString &text)
{
    LogModelData data;
    data.type = POPUP_TEXT;
    data.time = getDateTime();
    data.text = text;
    auto item = new QStandardItem();
    item->setData(QVariant::fromValue<LogModelData>(data));    
    item->setEditable(false);
    item->setData(true,PopupClickRole);
    auto itemDT = new QStandardItem(data.time);
    itemDT->setData(getDateTime());
    itemDT->setEditable(false);
    appendRow(QList<QStandardItem*>() << itemDT << item);
}

void LogModelExtended::addFileRow(const QString &uuid, const QString &description)
{
    LogModelData data;

    data.type = INCOMING_FILE;
    data.time = getDateTime();
    data.text = description;
    data.fileDataUuid = uuid;    
    auto item = new QStandardItem();
    item->setData(QVariant::fromValue<LogModelData>(data));    
    item->setEditable(false);
    auto itemDT = new QStandardItem(data.time);
    itemDT->setEditable(false);
    itemDT->setData(getDateTime());
    appendRow(QList<QStandardItem*>() << itemDT << item);

    m_hashOfFileItems[uuid] = item;
}

void LogModelExtended::addFileInFileRow(const QString &uuid, const QString &filePath)
{
    QStandardItem *item = m_hashOfFileItems.value(uuid, nullptr);
    if (item) {
        auto data = item->data().value<LogModelData>();        
        data.listOfFiles.append(filePath);        
        item->setData(QVariant::fromValue<LogModelData>(data));
    }
}

void LogModelExtended::addOpenMsg(const QString &text, const QString &uuid)
{
    LogModelData data;

    data.type = OPEN_MESSAGE;
    data.time = getDateTime();
    data.text = text;
    data.fileDataUuid = uuid;
    auto item = new QStandardItem();
    item->setData(QVariant::fromValue<LogModelData>(data));
    item->setEditable(false);
    item->setData(true,PopupClickRole);
    auto itemDT = new QStandardItem(data.time);
    itemDT->setEditable(false);
    itemDT->setData(getDateTime());
    appendRow(QList<QStandardItem*>() << itemDT << item);
    m_hashOfFileItems[uuid] = item;
}

bool LogModelExtended::proceesIndex(const QModelIndex &index)
{
    QStandardItem *item = itemFromIndex(index);
    if (item) {
            bool state = item->data(PopupFlashRole).toBool();
            item->setData(!state, PopupFlashRole);
    }
    return item;
}

void LogModelExtended::clickPopup(const QModelIndex &index)
{    
    QStandardItem *item = itemFromIndex(index);
    qDebug() << "Item " << item->column() ;
    if (item) {        
        bool state = item->data(PopupClickRole).toBool();
        item->setData(!state, PopupClickRole);
        LogModelData data = item->data().value<LogModelData>();
        data.timeConfirm = getDateTime();
        item->setData(QVariant::fromValue<LogModelData>(data));

        qDebug()<< "State " << state;
    }
}

QString LogModelExtended::getDateTime(){
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTimeString =  dateTime.toString("yyyy.MM.dd hh:mm:ss");
    return dateTimeString;
}
