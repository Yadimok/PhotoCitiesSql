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

