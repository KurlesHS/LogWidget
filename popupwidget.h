#ifndef POPUPWIDGET_H
#define POPUPWIDGET_H

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

private:
    Ui::PopupWidget *ui;
};

#endif // POPUPWIDGET_H
