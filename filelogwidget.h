#ifndef FILELOGWIDGET_H
#define FILELOGWIDGET_H

#include <QWidget>

class QPushButton;


namespace Ui {
class FileLogWidget;
}

class FileLogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileLogWidget(QWidget *parent = 0);
    ~FileLogWidget();
    QPushButton *addFile(const QString &filename);
    void setDescription(const QString &desc);
    void cleanFiles();

private slots:
    void on_pushButton_clicked();

private:
    Ui::FileLogWidget *ui;
};

#endif // FILELOGWIDGET_H
