#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow()
{
    delete ui;
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
