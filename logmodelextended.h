#ifndef LOGMODELEXTENDED_H
#define LOGMODELEXTENDED_H

#include <QStandardItemModel>
#include <QHash>

class LogModelExtended : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit LogModelExtended(QObject *parent = 0);
    void addSimpleText(const QString &text);
    void addPopup(const QString &text);
    void addFileRow(const QString &uuid, const QString &description);
    void addFileInFileRow(const QString &uuid, const QString &filePath);
    bool proceesIndex(const QModelIndex &index);
    void clickPopup(const QModelIndex &index);

signals:

private:
    QHash<QString, QStandardItem *> m_hashOfFileItems;
    QTimer *m_timer;
    QString getDateTime();

};

#endif // LOGMODELEXTENDED_H
