#ifndef INSTRUCTIONDIALOG_H
#define INSTRUCTIONDIALOG_H

#include <QDialog>

namespace Ui {
class InstructionDialog;
}

class InstructionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InstructionDialog(QWidget *parent = 0);
    ~InstructionDialog();
    //void ReadReadyFile();/////////////////////////////////////

private slots:
    void on_okButton_clicked();
    //void ReadReadyFile(const QString &filePath);

private:
    Ui::InstructionDialog *ui;
};

#endif // INSTRUCTIONDIALOG_H
