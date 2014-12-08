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
#define SENT_MSG 2

#define WARM_MSG 3
#define INFO_MSG 4
#define ERROR_MSG 5

enum {
    LogDataRole = Qt::UserRole+1,   //данные из модели
    MsgFlashRole = Qt::UserRole+2,    //Сообщение должно моргать (false - не моргает, true - моргает)
    MsgShowRole = Qt::UserRole+3    //Сообщение открыто (false- свернуто, true - раазвернуто)
};

class LogModelData
{
public:
    LogModelData();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    QSize sizeHint (const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void checkDblClickFile(const QPoint &pos);
    bool checkDblClickMsg(const QPoint &pos);
    QString getCurrentTime();

public:
    QString fileDataUuid;
    QStringList listOfFiles;    
    QString text;
    QString time;
    QString timeConfirm;
    int type;
    int typeMsg;

private:
    //static FileLogWidget *m_fileLogWidget;
    static PopupWidget *m_popupWidget;
    void setFileLogWidget() const;
    void setPopipWidget() const;

};

Q_DECLARE_METATYPE(LogModelData)

#endif // LOGMODELDATA_H
