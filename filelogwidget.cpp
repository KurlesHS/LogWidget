#include "filelogwidget.h"
#include "ui_filelogwidget.h"

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
