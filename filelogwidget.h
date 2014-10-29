#ifndef FILELOGWIDGET_H
#define FILELOGWIDGET_H

#include <QPushButton>
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
    QPushButton* addFile(const QString &filename);
    void setDescription(const QString &desc);
    void cleanFiles();

private:
    Ui::FileLogWidget *ui;
};

#endif // FILELOGWIDGET_H
