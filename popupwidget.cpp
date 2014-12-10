#include "popupwidget.h"
#include "ui_popupwidget.h"

#include <QFileIconProvider>
#include <QFileInfo>
#include <QPushButton>
#include <QDebug>

PopupWidget::PopupWidget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::PopupWidget)
{
    ui->setupUi(this);
    ui->lb_file->resize(0,0);
}

PopupWidget::~PopupWidget()
{
    delete ui;
}

void PopupWidget::setDescription(const QString &desc)
{
    ui->label_desc->setText(desc);
    //ui->label_desc->setWordWrap(true);
}

void PopupWidget::setTime(const QString &time)
{    
    ui->label_time->setText(time);
}

void PopupWidget::setFileInfo()
{
     QLabel *lbinfo = new QLabel(trUtf8("Вложенные файлы:"));
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
        QLabel *lb =new QLabel(tmpFile);
        lb->setToolTip(filename);
        lb->adjustSize();
        ui->Layout_file->addWidget(lb);
        return lb;
    }
    return 0;
}

QLabel *PopupWidget::checkHide()
{
    QLabel *lb_hide = ui->lb_icon;    
    return lb_hide;
}

void PopupWidget::showIconFile(const bool show)
{
        ui->lb_file->setHidden(show);
}



