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

    QFile mFile(":/Info/instruction.txt");
    mFile.open(QFile::ReadOnly);
    QTextStream stream(&mFile);
    QString buffer = stream.readAll();
    ui->textBrowser->setText(buffer);
    mFile.flush();
    mFile.close();

    QFile mFile_2(":/Info/instruction_2.txt");
    mFile_2.open(QFile::ReadOnly);
    QTextStream stream_2(&mFile_2);
    QString buffer_2 = stream_2.readAll();
    ui->textBrowser_2->setText(buffer_2);
    mFile_2.flush();
    mFile_2.close();

    QFile mFile_3(":/Info/instruction_3.txt");
    mFile_3.open(QFile::ReadOnly);
    QTextStream stream_3(&mFile_3);
    QString buffer_3 = stream_3.readAll();
    ui->textBrowser_3->setText(buffer_3);
    mFile_3.flush();
    mFile_3.close();

    QFile mFile_4(":/Info/instruction_4.txt");
    mFile_4.open(QFile::ReadOnly);
    QTextStream stream_4(&mFile_4);
    QString buffer_4 = stream_4.readAll();
    ui->textBrowser_4->setText(buffer_4);
    mFile_4.flush();
    mFile_4.close();
}

InstructionDialog::~InstructionDialog()
{
    delete ui;
}

void InstructionDialog::on_okButton_clicked()
{
    emit closeWindow();
}
