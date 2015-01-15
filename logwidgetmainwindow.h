#ifndef LOGWIDGETMAINWINDOW_H
#define LOGWIDGETMAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QSortFilterProxyModel>

class LogModelExtended;
class LogModelDelegate;

namespace Ui {
class LogWidgetMainWindow;
}

class LogWidgetMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogWidgetMainWindow(QWidget *parent = 0);
    ~LogWidgetMainWindow();

private slots:
    virtual void resizeEvent (QResizeEvent * event);

    virtual bool eventFilter( QObject* obj, QEvent* e );
    virtual void moveEvent ( QMoveEvent * event );

    void on_toolButtonSelectFile_clicked();

    void on_pushButtonAddSimpleText_clicked();

    void on_pushButtonAddFile_clicked();

    void onTimer();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void init();
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::LogWidgetMainWindow *ui;
    LogModelExtended *m_model;
    QTimer *m_timer;
    QString LogUUID;
    LogModelDelegate *mDelegate;
    QSortFilterProxyModel *filterLogModel;
};

#endif // LOGWIDGETMAINWINDOW_H
