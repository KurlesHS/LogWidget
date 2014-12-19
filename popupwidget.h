#ifndef POPUPWIDGET_H
#define POPUPWIDGET_H

#include <QLabel>
#include <QPushButton>
#include <QWidget>


namespace Ui {
class PopupWidget;
}

class PopupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PopupWidget(QWidget *parent = 0);
    ~PopupWidget();
    void setDescription(const QString &desc);
    void setTime(const QString &time);
    void setFileInfo();
    void cleanFiles();
    QPushButton *addFile(const QString &filename);
    QLabel *addFileLb(const QString &filename);
    QLabel *checkHide();
    void showIconFile(const bool show);

    int getFileHeight() const;
    void setFileHeight(int value);

private:
    Ui::PopupWidget *ui;
    int fileHeight = 0;
};

#endif // POPUPWIDGET_H
