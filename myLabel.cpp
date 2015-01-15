#include "popupwidget.h"

#include <myLabel.h>
#include <QLabel>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

myLabel::myLabel(QWidget * parent )
:QLabel(parent)
{
    connect( this, SIGNAL( clicked() ), this, SLOT( slotClicked() ) );
 //   connect( this, SIGNAL(clickFile()), parentWidget(), SLOT(setOpenFile()) );
}

void myLabel::slotClicked()
{
    //qDebug()<<"Clicked slot" << fileName;
    if (fileName.isEmpty()){
        this->parentWidget()->hide();
    } else {
        QString file ("file:///"+fileName);        
   //     emit clickFile();
        QDesktopServices::openUrl(file);
    }
}

void myLabel::mousePressEvent ( QMouseEvent * event )
{
    //    qDebug()<<"Clicked Event";
    emit clicked();
}
QString myLabel::getFileName() const
{
    return fileName;
}

void myLabel::setFileName(const QString &value)
{
    fileName = value;
}


