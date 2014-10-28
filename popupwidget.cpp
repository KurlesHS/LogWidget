#include "popupwidget.h"
#include "ui_popupwidget.h"


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



