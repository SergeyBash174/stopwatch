#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>
#include <QMessageBox>

//задаем стиль для неактивной кнопки
const QString style1 = "background-color: gray; border-radius: 5px; color: white;";
//задаем стиль для активной кнопки
const QString style2 = "QPushButton {background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0 rgb(51, 125, 255), stop:1 rgb(51,70,129)); border-radius: 5px; color: white;}"
                       "QPushButton:pressed {background-color: #337dff;}";
//задаем стили для светлого и темного оформления
const QString style_Black = "background-color: rgb(46, 47, 48); color: white";
const QString style_White = "background-color: rgb(255, 255, 255); color: black";
//Текст, показываемый в меню "о программе" и "справка"
const QString infotext = "Версия программы: 0.2 <br><br> Программа Секндомер - это программа, созданная для <br> точного засекания времени "
                         "<br><br> Автор программы: Башарин Сергей, ЮУрГУ 2019 <br><br> Программа создана для прохождения конкурсного отбора в Napoleon IT";
const QString help = "Для начала отсчета времени нажмите кнопку 'Старт' <br> При этом станет активной кнопка 'Сброс' и кнопка 'Старт' изменит надпись на 'Стоп'."
                         "<br> При нажатии кнопки 'Сброс' произойдет обнуление секундомера, после этого кнопка 'Сброс' станет снова неактивной а кнопка 'Стоп' изменит надпись на 'Старт'. "
                         "<br> Кнопка 'Сброс' активна только во время отсчета времени, т.к. это было прописано в техзадании";
//Инициализируем таймер
static QTimer *tmr = new QTimer();
//Задаем нулевое время для таймера. Переменная будет доступна только в данном файле
static QTime t (0, 0, 0, 0);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Соединяем таймер с блолкм, ответсвенным за вывод
    connect(tmr, SIGNAL(timeout()), this, SLOT(stopwatch()));
    //По умолчанию выводим время на дисплей и делаем кнопку сброса неактивной и серой
    ui->label->setText(t.toString("hh:mm:ss.zzz"));
    ui->ResetButton->setDisabled(1);
    ui->ResetButton->setStyleSheet(style1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//блок, ответственный за вывод времени. Задаем шаг времени, равный 1 милисекунде
void MainWindow::stopwatch()
{
    t = t.addMSecs(1);
    ui->label->setText(t.toString("hh:mm:ss.zzz"));
}

//Кнопка старт \ стоп. Проверяем, если таймер уже запущен, то тормозим его, меняем надпись на кнопке и делаем нективной кнопку сброс
// Соответсвенно наоборот, если таймер неактивен
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

//Кнопка сброс. По нажатию на нее томозим таймер, меняем надпись на кнопке старт \ стоп. Устанавливаем время на 0 и выводим его. После этого отключаем кнопку сброс
void MainWindow::on_ResetButton_clicked()
{
    tmr->stop();
    ui->StartStopButton->setText("Старт");
    t.setHMS(0,0,0,0);
    ui->label->setText(t.toString("hh:mm:ss.zzz"));
    ui->ResetButton->setDisabled(1);
    ui->ResetButton->setStyleSheet(style1);
}

//Блок меню О программе
void MainWindow::on_action_triggered()
{
    QMessageBox::information(this, "О программе Секундомер", infotext);
}

//Блок меню Справка
void MainWindow::on_action_2_triggered()
{
    QMessageBox::information(this, "Справка", help);
}

//Блок меню Темная тема
void MainWindow::on_action_4_triggered()
{
    ui->centralWidget->setStyleSheet(style_Black);
    ui->label->setStyleSheet("color: white");
}

//Блок меню Светлая тема
void MainWindow::on_action_5_triggered()
{
    ui->centralWidget->setStyleSheet(style_White);
    ui->label->setStyleSheet("color: black");
}
