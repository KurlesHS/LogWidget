#include "logwidgetmainwindow.h"
#include "ui_logwidgetmainwindow.h"
#include "logmodeldelegate.h"
#include "logmodelextended.h"
#include "logmodeldata.h"

#include <QFileDialog>
#include <QUuid>
#include <QTimer>
#include <QDebug>


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
    LogModelDelegate *mDelegate = new LogModelDelegate(this);
    //ui->treeView->setItemDelegateForColumn(0, new LogModelDelegate(this));
    //ui->treeView->setItemDelegateForColumn(1, new LogModelDelegate(this));
    m_model->setColumnCount(3);
    m_model->setHorizontalHeaderItem(0,new QStandardItem(trUtf8("Время")));
    m_model->setHorizontalHeaderItem(1,new QStandardItem(trUtf8("Тип")));
    m_model->setHorizontalHeaderItem(2,new QStandardItem(trUtf8("Сообщение")));
    ui->treeView->setItemDelegate(mDelegate);
    ui->treeView->setModel(m_model);
    ui->treeView->setColumnWidth(0,112);
    ui->treeView->setColumnWidth(1,30);

//    ui->tableView->setItemDelegate(mDelegate);
//    ui->tableView->setModel(m_model);

//    ui->tableView->verticalHeader()->setVisible(false);
//    ui->tableView->verticalHeader()->setDefaultSectionSize(18);
//    //ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
//    ui->tableView->setColumnWidth(0,110);
//    ui->tableView->horizontalHeader()->setStretchLastSection(true);


    //ui->tableView->verticalHeader()->setMinimumHeight(22);
    //ui->tableView->verticalHeader()->setMaximumHeight(22);
//    for (int i = 0; i < 10000; ++i) {
//        m_model->addFileRow(QUuid::createUuid().toString(), "");
//        m_model->addSimpleText(QString("row: %0").arg(i * 2 + 1));
//    }
}

LogWidgetMainWindow::~LogWidgetMainWindow()
{
    delete ui;
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
    ui->lineEditTehText->setText("");
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

//void LogWidgetMainWindow::on_treeView_doubleClicked(const QModelIndex &index)
//{
////    if (!index.data(MsgShowRole).toBool())
////        m_model->clickPopup(index);

//}


//void LogWidgetMainWindow::on_pushButton_3_clicked()
//{
//    m_model->addOpenMsg(ui->lineEditOpenMsg->text(),ui->lineEditFileName->text());
//    //ui->lineEditOpenMsg->setText("");
//}


void LogWidgetMainWindow::on_pushButton_clicked()
{
    m_model->addMessage(ui->lineEditPopup->text(),1,LOCAL_MSG,nullptr);
    ui->lineEditPopup->setText("");
}
