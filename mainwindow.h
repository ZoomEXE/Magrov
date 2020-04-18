#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QSqlDatabase dataBase;
    QSqlQuery sqlQuery;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_localCodeAction_triggered();

    void on_zavodAction_triggered();

    void on_vidVSAction_triggered();

    void fillTable();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
