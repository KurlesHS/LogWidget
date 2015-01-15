#include "logwidgetmainwindow.h"
#include "ui_logwidgetmainwindow.h"
#include "logmodeldelegate.h"
#include "logmodelextended.h"
#include "logmodeldata.h"

#include <QFileDialog>
#include <QUuid>
#include <QTimer>
#include <QDebug>
#include <QObject>


LogWidgetMainWindow::LogWidgetMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LogWidgetMainWindow),
    m_model(new LogModelExtended(this)),
    m_timer(new QTimer(this))
{   
    m_timer->start(500);
    connect(m_timer, SIGNAL(timeout()),
            this, SLOT(onTimer()));
    ui->setupUi(this);
    ui->treeView->installEventFilter(this);

    mDelegate = new LogModelDelegate(this);

    filterLogModel = new QSortFilterProxyModel(this);
    filterLogModel->setSourceModel(m_model);

    m_model->setColumnCount(3);
    m_model->setHorizontalHeaderItem(0,new QStandardItem(trUtf8("Время")));
    m_model->setHorizontalHeaderItem(1,new QStandardItem(trUtf8("Тип")));
    m_model->setHorizontalHeaderItem(2,new QStandardItem(trUtf8("Сообщение")));    
    ui->treeView->setItemDelegate(mDelegate);
    //ui->treeView->setModel(m_model);
    ui->treeView->setModel(filterLogModel);
    ui->treeView->setColumnWidth(0,112);
    ui->treeView->setColumnWidth(1,27);
    ui->treeView->viewport()->installEventFilter(this);

     QTimer::singleShot(200, this, SLOT(init()));

}

LogWidgetMainWindow::~LogWidgetMainWindow()
{
    delete ui;
}

void LogWidgetMainWindow::init(){
    mDelegate->setItemWidth(ui->treeView->columnWidth(COLUMN_MESSAGE));
    qDebug() << mapToGlobal(ui->treeView->pos());
    qDebug() << mapToParent(ui->treeView->pos());
}

void LogWidgetMainWindow::resizeEvent(QResizeEvent *event)
{
    mDelegate->setItemWidth(ui->treeView->columnWidth(COLUMN_MESSAGE));
    return QWidget::resizeEvent(event);
}

bool LogWidgetMainWindow::eventFilter(QObject *obj, QEvent *e)
{
    if (obj->objectName() == "treeView")
       if ( e->type() == QEvent::Resize ) {
           QEvent e( QEvent::StyleChange );
           qApp->sendEvent( obj, &e );
       }
    return QObject::eventFilter( obj, e );
}

void LogWidgetMainWindow::moveEvent(QMoveEvent *event)
{
    qDebug() << mapToGlobal(ui->treeView->pos());
    mDelegate->movePopup(mapToParent(ui->treeView->pos()));
}


void LogWidgetMainWindow::on_toolButtonSelectFile_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, trUtf8("Файло выбери"));
    if (!file.isEmpty()) {
        ui->lineEditFileName->setText(file);
    }
}

void LogWidgetMainWindow::on_pushButtonAddSimpleText_clicked()
{
    m_model->addMessage(ui->lineEditTehText->text(),1,ERROR_MSG);
    //ui->lineEditTehText->setText("");
}

void LogWidgetMainWindow::on_pushButtonAddFile_clicked()
{
    if (LogUUID.isNull()){
        LogUUID = QUuid::createUuid().toString();
        //m_model->addFileRow(LogUUID, ui->lineEditSimpleText->text());
        m_model->addMessage(ui->lineEditPopup->text(),1,ERROR_MSG,LogUUID);
    }
        m_model->addFileInMsg(LogUUID,ui->lineEditFileName->text());
        ui->lineEditFileName->setText("");
        ui->lineEditPopup->setText("");
}

void LogWidgetMainWindow::onTimer()
{
    int topRow = ui->treeView->indexAt(QPoint(0, 0)).row();

    int bottomRow = ui->treeView->indexAt(QPoint(0, ui->treeView->size().height())).row();
    if (topRow >= 0) {
        if (bottomRow < 0) {
            bottomRow = topRow + 10000;
        }
        for (; topRow <= bottomRow; ++topRow) {
            QModelIndex index = m_model->index(topRow, 0);                        
            if (index.data(MsgShowRole).toBool())
                if (!m_model->proceesIndex(index)) {
                    break;
                }
        }
    }
}

void LogWidgetMainWindow::on_pushButton_2_clicked()
{
    if (!ui->lineEditFileName->text().isEmpty()){
        LogUUID = QUuid::createUuid().toString();        
        m_model->addMessage(ui->lineEditPopup->text(),1,LOCAL_MSG,LogUUID);
        m_model->addFileInMsg(LogUUID,ui->lineEditFileName->text());
        ui->lineEditFileName->setText("");
    }
}


void LogWidgetMainWindow::on_pushButton_clicked()
{
    m_model->addMessage(ui->lineEditPopup->text(),1,LOCAL_MSG,nullptr,ui->confirm->checkState());
   // ui->lineEditPopup->setText("");
}

void LogWidgetMainWindow::on_pushButton_3_clicked()
{
    QString regExp("*22*");
    //QString regExp("^(?:[%0]+)");
    //QString temp = "asd";

    //filterLogModel->setFilterRegExp(QRegExp(regExp));
    //filterLogModel->setFilterKeyColumn(0);
    filterLogModel->setFilterFixedString(ui->lineEditTehText->text());
    filterLogModel->setFilterKeyColumn(2);
    filterLogModel->setFilterRole(DataSortRole);
}

void LogWidgetMainWindow::on_pushButton_4_clicked()
{
    PopupWidget *m_popupWidget = new PopupWidget();
    QRect rect = m_popupWidget->geometry();
    rect.setX(10);
    m_popupWidget->setGeometry(rect);
    m_popupWidget->show();
}

void LogWidgetMainWindow::on_treeView_clicked(const QModelIndex &index)
{
//    PopupWidget *m_popupWidget = new PopupWidget();
//    QRect rect = m_popupWidget->geometry();
//    //index.data()
//    m_popupWidget->setGeometry(rect);
//    m_popupWidget->show();
}
