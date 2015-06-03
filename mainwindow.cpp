#include <QMessageBox>
#include "mainwindow.h"
#include "instructiondialog.h"
#include "settingsdialog.h"
#include "ui_mainwindow.h"
#include "network.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("Готов к работе!");

    ui->nextStepButton->setEnabled(false);
    ui->backToSettingsButton->setEnabled(false);
    //MainWindow *wnd = new MainWindow(this);
    SettingsDialog *setDlg = new SettingsDialog(this);

    //здесь дб объект кнопка buildButton и clicked(bool)
    connect(setDlg, SIGNAL(accepted()), this, SLOT(nextStepButtonEnable()));
    connect(setDlg, SIGNAL(accepted()), this, SLOT(backToSettingsButtonEnable()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_about_triggered()    //показать справку
{
    QMessageBox::information(this,"О программе","<h4>Выпускная квалификационная работа на тему: </h4><i>Разработка программного эмулятора карты Кохонена для использования в учебном процессе.</i>\n<b>Автор:</b> Князева В.К., ФКТИ, группа 1303");
}

void MainWindow::on_action_info_triggered() //показать инструкцию
{
    InstructionDialog *instruction = new InstructionDialog(this);
    instruction->show();
}

void MainWindow::on_action_exit_triggered() //выход из программы
{
    close();
}

void MainWindow::on_action_new_triggered()  //создать новую карту Кохонена
{
    SettingsDialog *setDlg = new SettingsDialog(this);
    setDlg->show();
}

void MainWindow::nextStepButtonEnable(){
    SettingsDialog *settingsDlg = new SettingsDialog(this);
    QMessageBox::information(this,"fuid","sdoij");
    if(settingsDlg->on_buildButton_clicked(true))
    {

        ui->nextStepButton->setEnabled(true);
        ui->backToSettingsButton->setEnabled(true);
    }
}

void MainWindow::backToSettingsButtonEnable(){
    SettingsDialog *settingsDlg = new SettingsDialog(this);
    if(settingsDlg->on_buildButton_clicked(true))
    {
        ui->nextStepButton->setEnabled(true);
        ui->backToSettingsButton->setEnabled(true);
    }
}
