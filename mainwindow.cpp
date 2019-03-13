#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>
#include <QMessageBox>

const QString style1 = "background-color: gray; border-radius: 5px; color: white;";
const QString style2 = "QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0 rgb(51, 125, 255), stop:1 rgb(51,70,129)); border-radius: 5px; color: white;}"
                       "QPushButton:pressed {background-color: #337dff;}";
const QString style_Black = "background-color: rgb(46, 47, 48); color: white";
const QString style_White = "background-color: rgb(255, 255, 255); color: black";
const QString infotext = "Версия программы: 0.2 <br><br> Программа Секндомер - это программа, созданная для <br> точного засекания времени "
                         "<br><br> Автор программы: Башарин Сергей, ЮУрГУ 2019 <br><br> Программа создана для прохождения конкурсного отбора в Napoleon IT";
const QString help = "Для начала отсчета времени нажмите кнопку 'Старт' <br> При этом станет активной кнопка 'Сброс' и кнопка 'Старт' изменит надпись на 'Стоп'."
                         "<br> При нажатии кнопки 'Сброс' произойдет обнуление секундомера, после этого кнопка 'Сброс' станет снова неактивной а кнопка 'Стоп' изменит надпись на 'Старт'. "
                         "<br> Кнопка 'Сброс' активна только во время отсчета времени, т.к. это было прописано в техзадании";
QTimer *tmr = new QTimer();
QTime t (0, 0, 0, 0);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(tmr, SIGNAL(timeout()), this, SLOT(stopwatch()));
    ui->label->setText(t.toString("hh:mm:ss.zzz"));
    ui->ResetButton->setDisabled(1);
    ui->ResetButton->setStyleSheet(style1);
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
        ui->ResetButton->setStyleSheet(style1);
    }
    else
    {
         tmr->start(1);
         ui->StartStopButton->setText("Стоп");
         ui->ResetButton->setEnabled(1);
         ui->ResetButton->setStyleSheet(style2);
    }
}

void MainWindow::on_ResetButton_clicked()
{
    tmr->stop();
    ui->StartStopButton->setText("Старт");
    t.setHMS(0,0,0,0);
    ui->label->setText(t.toString("hh:mm:ss.zzz"));
    ui->ResetButton->setDisabled(1);
    ui->ResetButton->setStyleSheet(style1);
}

void MainWindow::on_action_triggered()
{
    QMessageBox::information(this, "О программе Секундомер", infotext);
}

void MainWindow::on_action_2_triggered()
{
    QMessageBox::information(this, "Справка", help);
}

void MainWindow::on_action_4_triggered()
{
    ui->centralWidget->setStyleSheet(style_Black);
    ui->label->setStyleSheet("color: white");
}

void MainWindow::on_action_5_triggered()
{
    ui->centralWidget->setStyleSheet(style_White);
    ui->label->setStyleSheet("color: black");
}
