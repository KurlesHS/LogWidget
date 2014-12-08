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
        but->adjustSize();
        ui->Layout_file->addWidget(but);        
        return but;
    }
    return 0;

}

QLabel *PopupWidget::checkHide()
{
    QLabel *lb_hide = ui->lb_icon;
    qDebug() << lb_hide->mapToGlobal(QPoint(0,0));
    return lb_hide;
}



