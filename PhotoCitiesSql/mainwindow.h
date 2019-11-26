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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QSqlQueryModel>
#include <QSqlTableModel>

#include "database.h"
#include "logindialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QPointer<QPushButton> pbConnectToDb;
    QPointer<QPushButton> pbAddToDb;
    QPointer<QTableView> tbView;
    QPointer<QLabel> lPhoto;

    QPointer<QVBoxLayout> mainLayout;
    QPointer<QHBoxLayout> hBoxLayoutL;
    QPointer<QHBoxLayout> hBoxLayoutR;

    QSqlTableModel *mModel;
    Database *dbObj;

    enum {
        HEIGHT_SIZE = 1280,
        WIDTH_SIZE = 960
    };

private slots:
    void slotLoadToTable(QSqlQueryModel *model);
    void slotCurrentPhoto(QModelIndex index);

    void connectToDb();
    void addToDb();



};
#endif // MAINWINDOW_H
