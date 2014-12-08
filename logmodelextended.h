#ifndef LOGMODELEXTENDED_H
#define LOGMODELEXTENDED_H

#include <QStandardItemModel>
#include <QHash>

class LogModelExtended : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit LogModelExtended(QObject *parent = 0);    
    void addMessage(const QString &text,const int type, const int module,const QString &uuid, const bool flash = false);
    void addMessage(const QString &text,const QString &type, const QString &module);
    void addFileInMsg(const QString &uuid, const QString &filePath);
    bool proceesIndex(const QModelIndex &index);
    void clickPopup(const QModelIndex &index);    
    QString getDateTime();

signals:

private:
    QHash<QString, QStandardItem *> m_hashOfFileItems;
    QTimer *m_timer;    

};

#endif // LOGMODELEXTENDED_H
