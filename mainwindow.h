#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QVector>
#include <QString>
#include "xlsxdocument.h"
#include "xlsxdatavalidation.h"
#include "QStandardItemModel"
#include "QStandardItem"
#include "dialog.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT  

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QStandardItemModel *allDataModel, *loseModel, *metallsModel;

    QVector <Dialog::st> data;

    Dialog::st findLokKod(QString key);   //Поиск по локальному коду
    Dialog::st findName(QString key);     //Поиск по наименованию
    Dialog::st findIndex(QString key);    //Поиск по чертежному индексу
    //QXlsx::Document z16;
private slots:
    void on_localCodeAction_triggered();

    void on_zavodAction_triggered();

    void on_vidVSAction_triggered();

    void fillTable();

    void on_pushButton_clicked();

    void on_nameAction_triggered();

    void on_IndexAction_triggered();

    void on_metallsAction_triggered();

    void on_loseAction_triggered();

    void on_AllData_triggered();

private:
    Ui::MainWindow *ui;

signals:
    void sendInfo(Dialog::st temp);
};
#endif // MAINWINDOW_H
