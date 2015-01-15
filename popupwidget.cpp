#include "popupwidget.h"
#include "ui_popupwidget.h"

#include <QFileIconProvider>
#include <QFileInfo>
#include <QPushButton>
#include <QDebug>
#include <QMouseEvent>
#include <math.h>
#include <myLabel.h>

PopupWidget::PopupWidget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::PopupWidget)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::Popup);
    setWindowFlags(Qt::SplashScreen);
    ui->lb_file->resize(0,0);
}

PopupWidget::~PopupWidget()
{
    delete ui;
}

void PopupWidget::setDescription(const QString &desc)
{
    ui->label_desc->setText(desc);    
}

void PopupWidget::setTime(const QString &time)
{    
    ui->label_time->setText(time);
}

void PopupWidget::setFileInfo()
{
     QLabel *lbinfo = new QLabel(trUtf8("Вложенные файлы:"));
     lbinfo->adjustSize();
     fileHeight += lbinfo->size().height();
     ui->Layout_file->addWidget(lbinfo);
}

void PopupWidget::cleanFiles()
{
    QLayoutItem *child;    
    while ((child = ui->Layout_file->takeAt(0)) != 0) {
        if (child->widget()) {
            delete child->widget();
            }
            delete child;
    }
    ui->label_desc->setText("1");
    fileHeight = 0;
    this->adjustSize();
}

QPushButton *PopupWidget::addFile(const QString &filename)
{
    if (!filename.isEmpty()){
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
        but->setStyleSheet("border: 1px solid #8f8f91;"
                           "border-radius: 6px;"
                           "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                       "stop: 0 #f6f7fa, stop: 1 #dadbde);"
                           "min-width: 80px;");
        but->adjustSize();        
        fileHeight += ui->Layout_file->layout()->spacing()+but->size().height();
        ui->Layout_file->addWidget(but);
        return but;
    }
    return 0;

}

QLabel *PopupWidget::addFileLb(const QString &filename)
{
    if (!filename.isEmpty()){
        int i = filename.lastIndexOf("/");
        QString tmpFile = filename;
        tmpFile.remove(0,i+1);
        //QLabel *lb =new QLabel(tmpFile);
        myLabel *lb = new myLabel(this);
        lb->setText(tmpFile);
        lb->setFileName(filename);
        lb->setToolTip(filename);
        lb->setStyleSheet("text-decoration: underline;");
        lb->adjustSize();
        fileHeight += ui->Layout_file->layout()->spacing()+lb->size().height();
        ui->Layout_file->addWidget(lb);
        return lb;
    }
    return 0;
}

QLabel *PopupWidget::checkHide()
{
    QLabel *lb_hide = ui->label_desc;
    return lb_hide;
}

void PopupWidget::showIconFile(const bool show)
{
    ui->lb_file->setHidden(show);
}

int PopupWidget::getFileHeight() const
{

    int retVal;
    if (fileHeight == 0){
        retVal = 20;
    } else {
        retVal = fileHeight;
    }
    int offset = ui->verticalLayout->layout()->spacing()+2;
    retVal +=offset;
    return retVal;
}

void PopupWidget::setFileHeight(int value)
{
    fileHeight = value;
}

void PopupWidget::setOpenFile()
{
    openFile = true;
}


void PopupWidget::click()
{
    hide();
}

void PopupWidget::resizeEvent(QResizeEvent *event)
{
 //   qDebug() << "Resize";
}

void PopupWidget::changeEvent(QEvent *)
{
    qDebug() << "changeEvent";
}

void PopupWidget::closeEvent(QCloseEvent *event)
{
    qDebug() << "closeEvent" << event;
    if (openFile)
    {
        event->ignore();
        openFile = false;
    }
    event->ignore();
}
