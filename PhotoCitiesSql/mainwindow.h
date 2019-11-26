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
