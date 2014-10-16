#ifndef FILELOGWIDGET_H
#define FILELOGWIDGET_H

#include <QWidget>

namespace Ui {
class FileLogWidget;
}

class FileLogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileLogWidget(QWidget *parent = 0);
    ~FileLogWidget();
    void setFile(QString filename);
private:
    Ui::FileLogWidget *ui;
};

#endif // FILELOGWIDGET_H
