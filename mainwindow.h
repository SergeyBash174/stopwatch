#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_StartStopButton_clicked();

    void on_ResetButton_clicked();

    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_4_triggered();

    void on_action_5_triggered();

public slots:
    void stopwatch();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
