/*
* This file is part of the PhotoCitiesSql
*
* Copyright (C) Yadimok2019
*
* PhotoCitiesSql is free software; you can redistribute it and/or
* modify it under the terms of the GNU Library General Public
* License as published by the Free Software Foundation; either
* version 2 of the License, or (at your option) any later version.
*
* PhotoCitiesSql is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Library General Public License for more details.
*
* You should have received a copy of the GNU Library General Public License
* along with PhotoCitiesSql. If not, write to
* the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301, USA.
**/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainLayout = new QVBoxLayout();

    tbView = new QTableView();
    tbView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tbView->setSelectionMode(QAbstractItemView::SingleSelection);
    tbView->resizeColumnsToContents();
    tbView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tbView->horizontalHeader()->setStretchLastSection(true);

    hBoxLayoutL = new QHBoxLayout();
    hBoxLayoutL->addWidget(tbView);

    hBoxLayoutR = new QHBoxLayout();
    pbConnectToDb = new QPushButton();
    pbConnectToDb->setText("Connect to DB");
    hBoxLayoutR->addWidget(pbConnectToDb);

    pbAddToDb = new QPushButton();
    pbAddToDb->setText("Add to DB");
    hBoxLayoutR->addWidget(pbAddToDb);

    mainLayout->addLayout(hBoxLayoutL, 3);
    mainLayout->addLayout(hBoxLayoutR);

    lPhoto = new QLabel();
    lPhoto->setFixedSize(HEIGHT_SIZE, WIDTH_SIZE);
    lPhoto->show();

    ui->centralwidget->setLayout(mainLayout);


    dbObj = new Database();
    connect(dbObj, SIGNAL(setModelResult(QSqlQueryModel *)), this, SLOT(slotLoadToTable(QSqlQueryModel *)));

    connect(pbConnectToDb, SIGNAL(clicked()), this, SLOT(connectToDb()));
    connect(pbAddToDb, SIGNAL(clicked()), this, SLOT(addToDb()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotLoadToTable(QSqlQueryModel *model)
{
    tbView->setModel(model);
}

void MainWindow::slotCurrentPhoto(QModelIndex index)
{
    QPixmap pixmap;
    pixmap.loadFromData(tbView->model()->index(index.row(), 2).data().toByteArray());
    lPhoto->setPixmap(pixmap.scaled(HEIGHT_SIZE, WIDTH_SIZE));
}

void MainWindow::connectToDb()
{
    LoginDialog loginDialog;
    if (loginDialog.exec() == QDialog::Accepted)
    {
        bool isOk = dbObj->connectToMySQL(loginDialog.getServer(),
                                             loginDialog.getPort(),
                                             loginDialog.getDatabaseName(),
                                             loginDialog.getUsername(),
                                             loginDialog.getPassword());
        if (isOk)
        {
            dbObj->createTable();
            dbObj->refresh();

            connect(tbView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                    this, SLOT(slotCurrentPhoto(QModelIndex)));
        }
        else
            return;
    }

}

void MainWindow::addToDb()
{
    QStringList strList = QFileDialog::getOpenFileNames(this,
                                                        "Select one or more files to open",
                                                        QDir::currentPath(),
                                                        "Images (*.png *.jpeg *.jpg)");
    if (strList.isEmpty())
    {
        qDebug() << "File not chosen";
        return;
    }

    dbObj->insertToDb(strList);
    dbObj->refresh();
}

