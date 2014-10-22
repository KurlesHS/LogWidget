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

void FileLogWidget::addFilename(const QString &fileName)
{    
    if (!fileName.isEmpty()){
        QFileInfo fInfo(fileName);

        QFileIconProvider FIcon;
        QIcon iFile = FIcon.icon(fInfo);
        QLabel *but =new QLabel;
        but->setPixmap(iFile.pixmap(QSize(32, 32)));
        ui->horizontalLayoutFile->addWidget(but);
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
