/*
* This file is part of the PhotoCitiesSql
*
* Copyright (C) Yadimok2019
*
* EncDecryptor is free software; you can redistribute it and/or
* modify it under the terms of the GNU Library General Public
* License as published by the Free Software Foundation; either
* version 2 of the License, or (at your option) any later version.
*
* EncDecryptor is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Library General Public License for more details.
*
* You should have received a copy of the GNU Library General Public License
* along with EncDecryptor. If not, write to
* the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301, USA.
**/

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


