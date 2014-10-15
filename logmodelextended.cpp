#include "logmodelextended.h"
#include <QDateTime>
#include <QTimer>
#include <QDebug>

#include "logmodeldata.h"
LogModelExtended::LogModelExtended(QObject *parent) :
    QStandardItemModel(parent)
{

}

void LogModelExtended::addSimpleText(const QString &text)
{
    //QString currentDateTime = QDateTime::currentDateTime().toString();
    LogModelData data;
    data.type = SIMPLE_TEXT;
    data.text = text;
    auto item = new QStandardItem();
    item->setData(QVariant::fromValue<LogModelData>(data));
    item->setEditable(false);
    appendRow(item);

}

void LogModelExtended::addPopup(const QString &text)
{
    LogModelData data;
    data.type = POPUP_TEXT;
    data.text = text;
    auto item = new QStandardItem();
    item->setData(QVariant::fromValue<LogModelData>(data));
    appendRow(item);
}

void LogModelExtended::addFileRow(const QString &uuid, const QString &description)
{
    LogModelData data;

    data.type = INCOMING_FILE;
    data.text = description;
    data.fileDataUuid = uuid;
    //data.setFile();
    auto item = new QStandardItem();
    item->setData(QVariant::fromValue<LogModelData>(data));
    appendRow(item);
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

bool LogModelExtended::proceesIndex(const QModelIndex &index)
{
    QStandardItem *item = itemFromIndex(index);
    if (item) {
        bool state = item->data(Qt::UserRole + 2).toBool();
        item->setData(!state, Qt::UserRole + 2);
        //item->setText("1234");
    }
    return item;
}
