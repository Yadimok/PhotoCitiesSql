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

#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QFileInfo>
#include <QSqlQueryModel>
#include <QMutexLocker>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    bool connectToMySQL(QString server, int port, QString database,
                        QString login, QString password);

    void createTable();
    void insertToDb(const QStringList &data);
    void refresh();

private:
    QSqlDatabase db;

    QMutex mMutex;
    QSqlQueryModel *model;

signals:
    void setModelResult(QSqlQueryModel *model);


};

#endif // DATABASE_H
