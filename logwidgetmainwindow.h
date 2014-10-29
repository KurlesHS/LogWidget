#ifndef LOGWIDGETMAINWINDOW_H
#define LOGWIDGETMAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

class LogModelExtended;

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
    void on_toolButtonSelectFile_clicked();

    void on_pushButtonAddSimpleText_clicked();

    void on_pushButtonAddFile_clicked();

    void onTimer();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_treeView_doubleClicked(const QModelIndex &index);

private:
    Ui::LogWidgetMainWindow *ui;
    LogModelExtended *m_model;
    QTimer *m_timer;
    QString LogUUID;
};

#endif // LOGWIDGETMAINWINDOW_H
