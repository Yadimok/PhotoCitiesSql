#include "database.h"
#include <QDebug>

Database::Database(QObject *parent) : QObject(parent)
{
    model = new QSqlQueryModel();

    db = QSqlDatabase();
    db = QSqlDatabase::addDatabase("QMYSQL");
}

Database::~Database()
{
    if (db.isOpen())
        db.close();
}

bool Database::connectToMySQL(QString server, int port, QString database, QString login, QString password)
{
    db.setHostName(server);
    db.setPort(port);
    if (!db.contains(database))
        db.setDatabaseName(database);
    db.setUserName(login);
    db.setPassword(password);

    return db.open();
}

void Database::createTable()
{
    QSqlQuery query(db);
    query.prepare("CREATE TABLE IF NOT EXISTS PhotoCitiesSql ( id INTEGER UNIQUE PRIMARY KEY AUTO_INCREMENT,"
                  "name CHAR(255),"
                  "photo LONGBLOB )");
    if (query.exec()) {
        qDebug() << tr("Table is created!");
    } else {
        qDebug() <<query.lastError().text();
    }
}

void Database::insertToDb(const QStringList &data)
{
    QFile file;
    QByteArray array;
    QString fileName;
    QFileInfo fileInfo;
    QSqlQuery query(db);


    for (int idx=0; idx<data.size(); idx++)
    {
        file.setFileName(data.at(idx));
        if (!file.open(QFile::ReadOnly))
        {
            qDebug() << tr("File %1 not open").arg(file.fileName());
            break;
        }

        fileInfo.setFile(file.fileName());
        fileName = fileInfo.fileName();

        array = file.readAll();

        if (file.isOpen())
            file.close();


        query.prepare("INSERT INTO PhotoCitiesSql (name, photo)"
                      "VALUES (:name, :photo)");
        query.bindValue(":name", fileName);
        query.bindValue(":photo", array);

        if (query.exec()) {
            qDebug() << tr("Data inserted!");
        } else {
            qDebug() << query.lastError().text();
        }

        fileName = "";
        array.clear();
    }//for
}

void Database::refresh()
{

    QSqlQuery query(db);
    query.prepare("SELECT * FROM PhotoCitiesSql");

    if (query.exec()) {
        qDebug() << tr("Data refreshed!");
    } else {
        qDebug() << query.lastError().text();
    }

    model->setQuery(query);

    emit setModelResult(model);
}
