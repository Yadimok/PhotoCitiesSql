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
