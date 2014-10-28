#include "filelogwidget.h"
#include "ui_filelogwidget.h"

#include <QFileIconProvider>
#include <QFileInfo>
#include <QProcess>
#include <QPushButton>

FileLogWidget::FileLogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileLogWidget)
{
    ui->setupUi(this);
}

FileLogWidget::~FileLogWidget()
{
    delete ui;
}

QRect FileLogWidget::addFile(const QString &filename)
{    
    if (!filename.isEmpty()){
        //ui->label_2->setText(filename);
        QFileInfo fInfo(filename);
        QFileIconProvider FIcon;
        QIcon iFile = FIcon.icon(fInfo);
        QPushButton *but =new QPushButton();       
        int i = filename.lastIndexOf("/");
        QString tmpFile = filename;
        tmpFile.remove(0,i+1);
        but->setToolTip(filename);
        but->setText(tmpFile);
        but->setIcon(iFile);
        but->adjustSize();
        ui->horizontalLayoutFile->addWidget(but);
        return but->rect();
    }
}

void FileLogWidget::setDescription(const QString &desc)
{
    ui->label_2->setText(desc);    
}


void FileLogWidget::cleanFiles()
{
QLayoutItem *child;
while ((child = ui->horizontalLayoutFile->takeAt(0)) != 0) {
    if (child->widget()) {
        delete child->widget();
        }
        delete child;
    }
}

void FileLogWidget::on_pushButton_clicked()
{
    QProcess process;
    QString file = "C:\\test.txt";
    process.execute(file);
}
