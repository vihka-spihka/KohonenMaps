#include <QGridLayout>
#include <QTextBrowser>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "instructiondialog.h"
#include "ui_instructiondialog.h"

InstructionDialog::InstructionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InstructionDialog)
{
    ui->setupUi(this);

    //InstructionDialog *instruction = new InstructionDialog(this);
    //instruction->ReadReadyFile();
   // connect(instruction,SIGNAL(on_action_info_triggered()),this,SLOT(ReadReadyFile(QString)));

    QFile mFile(":/Info/instruction.txt");
    mFile.open(QFile::ReadOnly);
    QTextStream stream(&mFile);
    QString buffer = stream.readAll();
    ui->textBrowser->setText(buffer);
    mFile.flush();
    mFile.close();

}

InstructionDialog::~InstructionDialog()
{
    delete ui;
}

void InstructionDialog::on_okButton_clicked()
{
    close();
}
//wrong
/*void InstructionDialog::ReadReadyFile()
{
    QFile mFile(":/Info/instruction.txt");

    mFile.open(QFile::ReadOnly);
    QTextStream stream(&mFile);
    QString buffer = stream.readAll();
    ui->textBrowser->setText(buffer);
    mFile.flush();
    mFile.close();
}*/

/*void InstructionDialog::ReadReadyFile(const QString &filePath)
{
    QFile mFile(":/Info/instruction.txt");

    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Error", "We have a problem");
        return;
    }
    mFile.open(QFile::ReadOnly);
    QTextStream stream(&mFile);
    QString buffer = stream.readAll();
    ui->textBrowser->setText(buffer);
    mFile.flush();
    mFile.close();
}*/
