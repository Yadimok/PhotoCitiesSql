#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    ui->lineEdit_4->setEchoMode(QLineEdit::Password);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

QString LoginDialog::getServer() const
{
    return ui->lineEdit->text();
}

int LoginDialog::getPort() const
{
    return ui->spinBox->value();
}

QString LoginDialog::getDatabaseName() const
{
    return ui->lineEdit_2->text();
}

QString LoginDialog::getUsername() const
{
    return ui->lineEdit_3->text();
}

QString LoginDialog::getPassword() const
{
    return ui->lineEdit_4->text();
}


