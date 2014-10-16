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

void FileLogWidget::setFile(QString filename)
{
    ui->label->setText(filename);
    QPushButton *but = new QPushButton();
    QFileInfo fInfo(filename);
    QFileIconProvider iconProv;
    QIcon fIcon = iconProv.icon(fInfo);
    but->setIcon(fIcon);
    ui->fileIconLayout->addWidget(but);
}
