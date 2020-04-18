#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    //Открытие базы данных
    dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("data.sqlite");

    //Загрузка записей из базы данных в TableView
    if(!dataBase.open())
    {
        qDebug() << dataBase.lastError().text();
    }else{
        qDebug() << "All is OK";
        sqlQuery = QSqlQuery(dataBase);

        fillTable();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Заполнение таблицы записями из БД
void MainWindow::fillTable()
{
    QSqlQueryModel *model = new QSqlQueryModel;

    sqlQuery.exec("SELECT * FROM Z16");
    model->setQuery(sqlQuery);

    /*for(int i = 0; i < horizontalHeader.size(); ++i)
    {
        model->setHeaderData(i, Qt::Horizontal, horizontalHeader[i]);
    }*/

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::on_localCodeAction_triggered()
{
    ui->statusbar->showMessage("Сортировка по локальному коду");
}

void MainWindow::on_zavodAction_triggered()
{
    ui->statusbar->showMessage("Сортировка по заводу изготовителю");
}

void MainWindow::on_vidVSAction_triggered()
{
    ui->statusbar->showMessage("Сортировка по виду вооруженных сил");
}
