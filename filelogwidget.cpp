#include "filelogwidget.h"
#include "ui_filelogwidget.h"

#include <QFileIconProvider>
#include <QFileInfo>
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

void FileLogWidget::setFilename(QString FileName)
{    
    if (!FileName.isEmpty()){
        ui->label_2->setText(FileName);
        QFileInfo fInfo(FileName);
        QFileIconProvider FIcon;
        QIcon iFile = FIcon.icon(fInfo);
        QPushButton *but =new QPushButton();
        but->setIcon(iFile);
        ui->horizontalLayoutFile->addWidget(but);
    }
}

void FileLogWidget::addButton(QIcon fIcon)
{
    if (!fIcon.isNull()){
        QPushButton but;
        but.setIcon(fIcon);
        ui->verticalLayout->addWidget(&but);
    }
}
