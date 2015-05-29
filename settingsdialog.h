#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

private slots:
    void on_nextButton1_clicked(int index);

    void on_inputFromFileRadioButton_clicked();

    void on_inputSelfRadioButton_clicked();

    void on_addColomnButton_clicked();

    void on_addRowButton_clicked();

    void on_chooseFileButton_clicked();

public slots:
    bool on_buildButton_clicked(bool);

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
