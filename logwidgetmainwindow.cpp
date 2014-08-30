#include "logwidgetmainwindow.h"
#include "ui_logwidgetmainwindow.h"
#include "logmodeldelegate.h"
#include "logmodelextended.h"
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
    ui->treeView->setItemDelegateForColumn(0, new LogModelDelegate(this));
    ui->treeView->setModel(m_model);
    for (int i = 0; i < 10000; ++i) {
        m_model->addFileRow(QUuid::createUuid().toString(), "");
        m_model->addSimpleText(QString("row: %0").arg(i * 2 + 1));
    }
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
    m_model->addSimpleText(ui->lineEditSimpleText->text());
}

void LogWidgetMainWindow::on_pushButtonAddFile_clicked()
{
    m_model->addFileRow(QUuid::createUuid().toString(), ui->lineEditFileName->text());
}

void LogWidgetMainWindow::onTimer()
{
    int topRow = ui->treeView->indexAt(QPoint(0, 0)).row();

    int bottomRow = ui->treeView->indexAt(QPoint(0, ui->treeView->size().height())).row();
    qDebug() << topRow << bottomRow;
    if (topRow >= 0) {
        if (bottomRow < 0) {
            bottomRow = topRow + 10000;
        }
        for (; topRow < bottomRow; ++topRow) {
            QModelIndex index = m_model->index(topRow, 0);
            if (!m_model->proceesIndex(index)) {
                break;
            }
        }
    }
}
