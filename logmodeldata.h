#ifndef LOGMODELDATA_H
#define LOGMODELDATA_H

#include <QObject>
#include <QMetaType>
#include <QStringList>
#include <QStyleOptionViewItem>
#include "filelogwidget.h"
#include "popupwidget.h"

#define INFO_MESSAGE 0
#define TEHNICAL_MESSAGE 1

#define LOCAL_MSG 0
#define RECEIVE_MSG 1
#define SEND_MSG 2

#define WARM_MSG 3
#define INFO_MSG 4
#define ERROR_MSG 5

enum {
    LogDataRole = Qt::UserRole+1,   //данные из модели
    MsgFlashRole = Qt::UserRole+2,    //
    MsgShowRole = Qt::UserRole+3,    //Сообщение открыто (false- свернуто, true - раазвернуто)
    MsgConfirmRole = Qt::UserRole+4,    //Сообщение требует подтверждения
    MsgTypeRole = Qt::UserRole+5
};

class LogModelData
{
public:
    LogModelData();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    QSize sizeHint (const QStyleOptionViewItem &option, const QModelIndex &index) const;

    //void checkDblClickFile(const QPoint &pos);
    bool checkClickMsg(const QPoint &pos,const QStyleOptionViewItem &option);
    QString getCurrentTime();
    void setConfirm();
    bool checkBigMsg(const QStyleOptionViewItem &option);

public:
    QString fileDataUuid;
    QStringList listOfFiles;    
    QString text;
    QString time;
    QString timeConfirm;
    int type;
    int typeMsg;
    int module;

private:
    //static FileLogWidget *m_fileLogWidget;
    static PopupWidget *m_popupWidget;
    //void setFileLogWidget() const;
    void setPopipWidget() const;


};

Q_DECLARE_METATYPE(LogModelData)

#endif // LOGMODELDATA_H
