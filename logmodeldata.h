#ifndef LOGMODELDATA_H
#define LOGMODELDATA_H

#include <QObject>
#include <QMetaType>
#include <QStringList>
#include <QStyleOptionViewItem>
#include <QLabel>
#include "filelogwidget.h"
#include "popupwidget.h"

#define SIMPLE_TEXT 0
#define POPUP_TEXT 1
#define INCOMING_FILE 2

enum {
    LogDataRole = Qt::UserRole+1,
    PopupFlashRole = Qt::UserRole+2,
    PopupClickRole = Qt::UserRole+3
};

class LogModelData
{
public:
    LogModelData();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    QSize sizeHint (const QStyleOptionViewItem &option, const QModelIndex &index) const;

public:
    QString fileDataUuid;
    QStringList listOfFiles;
    QString text;
    QString time;
    int type;    

private:
    static FileLogWidget *m_fileLogWidget;
    static PopupWidget *m_popupWidget;

};

Q_DECLARE_METATYPE(LogModelData)

#endif // LOGMODELDATA_H
