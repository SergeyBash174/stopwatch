#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>
#include <QMessageBox>

QTimer *tmr = new QTimer();
QTime t(0, 0, 0, 0);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(tmr, SIGNAL(timeout()), this, SLOT(stopwatch()));
    ui->label->setText(t.toString("hh:mm:ss.zzz"));
    ui->ResetButton->setDisabled(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::stopwatch()
{

    t = t.addMSecs(1);
    ui->label->setText(t.toString("hh:mm:ss.zzz"));
}

void MainWindow::on_StartStopButton_clicked()
{
    if(tmr->isActive())
    {
        tmr->stop();
        ui->StartStopButton->setText("Старт");
        ui->ResetButton->setDisabled(1);
    }
    else
    {
         tmr->start(1);
         ui->StartStopButton->setText("Стоп");
         ui->ResetButton->setEnabled(1);
    }
}

void MainWindow::on_ResetButton_clicked()
{
    tmr->stop();
    ui->StartStopButton->setText("Старт");
    t.setHMS(0,0,0,0);
    ui->label->setText(t.toString("hh:mm:ss.zzz"));
    ui->ResetButton->setDisabled(1);
}

void MainWindow::on_action_triggered()
{

}
