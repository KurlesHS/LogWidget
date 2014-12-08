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

void LogModelExtended::addMessage(const QString &text, const int type, const int module, const QString &uuid, const bool confirm)
{
    LogModelData data;

    data.type = INFO_MESSAGE;
    data.text = text;
    data.typeMsg = type;
    data.module = module;
    data.fileDataUuid = uuid;    
    auto item = new QStandardItem();
    item->setData(QVariant::fromValue<LogModelData>(data));
    item->setEditable(false);
    item->setData(false,MsgShowRole);
    item->setData(confirm,MsgConfirmRole);
    item->setToolTip(QString("<table><tr><td>").append(text).append("</td></td></table>"));
    auto itemDT = new QStandardItem(data.time);
    itemDT->setEditable(false);        
    auto itemType = new QStandardItem(QIcon(":/Icons/Icon/error_message.png"),"");
    itemType->setEditable(false);
    appendRow(QList<QStandardItem*>() << itemDT << itemType << item);
    if (!uuid.isEmpty()) {
        m_hashOfFileItems[uuid] = item;
    }
}

void LogModelExtended::addMessage(const QString &text, const int type, const int module)
{
    LogModelData data;

    data.type = TEHNICAL_MESSAGE;
    data.text = text;
    data.typeMsg = type;
    data.module = module;
    auto item = new QStandardItem();
    item->setData(QVariant::fromValue<LogModelData>(data));
    item->setEditable(false);
    item->setData(false,MsgShowRole);
    item->setData(false,MsgConfirmRole);
    item->setToolTip(QString("<table><tr><td>").append(text).append("</td></td></table>"));
    auto itemDT = new QStandardItem(data.time);
    itemDT->setEditable(false);
    auto itemType = new QStandardItem(data.typeMsg);
    itemType->setEditable(false);
    appendRow(QList<QStandardItem*>() << itemDT << itemType << item);
}


//void LogModelExtended::addSimpleText(const QString &text)
//{
//    LogModelData data;
//    data.type = SIMPLE_TEXT;
//    data.text = text;
//    auto item = new QStandardItem();
//    item->setData(QVariant::fromValue<LogModelData>(data));
//    item->setEditable(false);
//    auto itemDT = new QStandardItem(data.time);
//    itemDT->setData(data.time);
//    itemDT->setEditable(false);
//    appendRow(QList<QStandardItem*>() << itemDT << item);
//}


//void LogModelExtended::addPopup(const QString &text)
//{
//    LogModelData data;
//    data.type = POPUP_TEXT;
//    data.text = text;
//    auto item = new QStandardItem();
//    item->setData(QVariant::fromValue<LogModelData>(data));
//    item->setEditable(false);
//    item->setData(false,MsgShowRole);
//    auto itemDT = new QStandardItem(data.time);
//    itemDT->setData(data.time);
//    itemDT->setEditable(false);
//    appendRow(QList<QStandardItem*>() << itemDT << item);
//}

//void LogModelExtended::addFileRow(const QString &uuid, const QString &description)
//{
//    LogModelData data;

//    data.type = OPEN_MESSAGE;
//    data.text = description;
//    data.fileDataUuid = uuid;
//    auto item = new QStandardItem();
//    item->setData(QVariant::fromValue<LogModelData>(data));
//    item->setEditable(false);
//    auto itemDT = new QStandardItem(data.time);
//    itemDT->setEditable(false);
//    itemDT->setData(data.time);
//    appendRow(QList<QStandardItem*>() << itemDT << item);

//    m_hashOfFileItems[uuid] = item;
//}

void LogModelExtended::addFileInMsg(const QString &uuid, const QString &filePath)
{
    QStandardItem *item = m_hashOfFileItems.value(uuid, nullptr);
    if (item) {
        auto data = item->data().value<LogModelData>();        
        data.listOfFiles.append(filePath);        
        if (item->data(MsgConfirmRole) == false && data.timeConfirm.isEmpty()){
            item->setData(true,MsgConfirmRole);
        }
        item->setData(QVariant::fromValue<LogModelData>(data));
    }
}

//void LogModelExtended::addInfoMsg(const QString &text, const QString &uuid)
//{
//    LogModelData data;

//    data.type = INFO_MESSAGE;
//    data.text = text;
//    data.fileDataUuid = uuid;
//    auto item = new QStandardItem();
//    item->setData(QVariant::fromValue<LogModelData>(data));
//    item->setEditable(false);
//    item->setData(false,MsgShowRole);
//    item->setToolTip(QString("<table><tr><td>").append(text).append("</td></td></table>"));
//    auto itemDT = new QStandardItem(data.time);
//    itemDT->setEditable(false);
//    appendRow(QList<QStandardItem*>() << itemDT << item);
//    m_hashOfFileItems[uuid] = item;
//}

bool LogModelExtended::proceesIndex(const QModelIndex &index)
{
    QStandardItem *item = itemFromIndex(index);
    if (item) {
            bool state = item->data(MsgFlashRole).toBool();
            item->setData(!state, MsgFlashRole);
    }
    return item;
}

//void LogModelExtended::clickPopup(const QModelIndex &index)
//{
//    QStandardItem *item = itemFromIndex(index);
//    qDebug() << "Item " << item->column() ;
//    if (item) {
//        bool state = item->data(MsgShowRole).toBool();
//        item->setData(!state, MsgShowRole);
//        LogModelData data = item->data().value<LogModelData>();
//        if (data.timeConfirm.isNull()){
//            data.timeConfirm = data.getCurrentTime();
//            item->setData(QVariant::fromValue<LogModelData>(data));
//        }

//        qDebug()<< "State " << state;
//    }
//}

//QString LogModelExtended::getDateTime(){
//    QDateTime dateTime = QDateTime::currentDateTime();
//    QString dateTimeString =  dateTime.toString("yyyy.MM.dd hh:mm:ss");
//    return dateTimeString;
//}
