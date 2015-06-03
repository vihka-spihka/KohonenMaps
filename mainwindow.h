#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_about_triggered();

    void on_action_info_triggered();

    void on_action_exit_triggered();

    void on_action_new_triggered();

    void nextStepButtonEnable();    //кнопка "След шаг" доступна

    void backToSettingsButtonEnable();  //кнопка "Назад к настройкам" доступна

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
