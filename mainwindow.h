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
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct st;
class MainWindow : public QMainWindow
{
    Q_OBJECT  

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    struct st
    {
        QString lokKod, index, name, zavod, edIzmer, osnovanie;
        int count, GCX, HCX;
        double aurum = 0.0, argentum = 0.0, platina = 0.0, platinaGroup = 0.0;
        bool lose = false, metalls = false;
    };
    QStandardItemModel *allDataModel, *loseModel, *metallsModel;

    QVector <st> data;
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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
