#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    QXlsx::Document z16("z16.xlsx");
    for(int i = 2;; ++i)
    {
        for(int j = 1; j < 16; ++j)
        {
            z16.read(i, j);
        }
        if (QXlsx::Cell *cell = z16.cellAt(i, 1))
        {
            Dialog::st temp;
            temp.lokKod = z16.cellAt(i,1)->value().toString();
            temp.name = z16.cellAt(i,2)->value().toString();
            temp.index = z16.cellAt(i,3)->value().toString();
            temp.index = z16.cellAt(i,4)->value().toString();
            temp.edIzmer = z16.cellAt(i,5)->value().toString();
            temp.count = z16.cellAt(i,6)->value().toInt();
            temp.GCX = z16.cellAt(i,7)->value().toInt();
            temp.HCX = z16.cellAt(i,8)->value().toInt();
            temp.aurum = z16.cellAt(i,9)->value().toDouble();
            temp.argentum = z16.cellAt(i,10)->value().toDouble();
            temp.platina = z16.cellAt(i,11)->value().toDouble();
            temp.platinaGroup = z16.cellAt(i,12)->value().toDouble();
            if(z16.cellAt(i,13)->value().toString() == "Да")
            {
                temp.lose = true;
                temp.osnovanie = z16.cellAt(i, 15)->value().toString();
            }
            else {
                temp.lose = false;
            }

            if(z16.cellAt(i,14)->value().toString() == "Да")
            {
                temp.metalls = true;
            }
            else {
                temp.metalls = false;
            }

            data.push_back(temp);
        }
        else
        {
            break;
        }
    }

    fillTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Заполнение таблицы записями из БД
void MainWindow::fillTable()
{
    //Модель для отображения всех данных
    allDataModel = new QStandardItemModel;
    QStandardItem *item = new QStandardItem;

    //Заголовки столбцов
    QStringList horizontalHeader;
    horizontalHeader.append("Локальный код");
    horizontalHeader.append("Наименование");
    horizontalHeader.append("Чертежный индекс");
    horizontalHeader.append("Количество");
    horizontalHeader.append("ГСХ");
    horizontalHeader.append("НСХ");

    allDataModel->setHorizontalHeaderLabels(horizontalHeader);

    //Заполнение таблицы
    for(int i = 0; i < data.size(); ++i)
    {
        item = new QStandardItem(data[i].lokKod);
        allDataModel->setItem(i, 0, item);

        item = new QStandardItem(data[i].name);
        allDataModel->setItem(i, 1, item);

        item = new QStandardItem(data[i].index);
        allDataModel->setItem(i, 2, item);

        item = new QStandardItem(QString::number(data[i].GCX));
        allDataModel->setItem(i, 3, item);

        item = new QStandardItem(QString::number(data[i].HCX));
        allDataModel->setItem(i, 4, item);

        item = new QStandardItem(QString::number(data[i].count));
        allDataModel->setItem(i, 5, item);
    }
    ui->tableView->setModel(allDataModel);

    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::on_localCodeAction_triggered()
{
    ui->statusbar->showMessage("Найти по локальному коду");
    ui->label->setText("Введите локальный код");
}

void MainWindow::on_zavodAction_triggered()
{
    ui->statusbar->showMessage("Сортировка по заводу изготовителю");
}

void MainWindow::on_vidVSAction_triggered()
{
    ui->statusbar->showMessage("Сортировка по виду вооруженных сил");
}

Dialog::st MainWindow::findLokKod(QString key)
{
    for(int i = 0; i < data.size();++i)
    {
        if(data[i].lokKod == key) {
            return data[i];
        }
    }
    QMessageBox::information(this, "Не найден", "Элемент с введенным локальным кодом не найден!");
    Dialog::st temp;
    temp.name = "Не найден";
    return temp;
}

Dialog::st MainWindow::findName(QString key)
{
    for(int i = 0; i < data.size();++i)
    {
        if(data[i].name == key) {
            return data[i];
        }
    }
    QMessageBox::information(this, "Не найден", "Элемент с введенным наименованием не найден!");
    Dialog::st temp;
    temp.name = "Не найден";
    return temp;
}

Dialog::st MainWindow::findIndex(QString key)
{
    for(int i = 0; i < data.size();++i)
    {
        if(data[i].index == key) {
            return data[i];
        }
    }
    QMessageBox::information(this, "Не найден", "Элемент с введенным чертежным индексом не найден!");
    Dialog::st temp;
    temp.name = "Не найден";
    return temp;
}

//Нажатие кнопки Поиск
void MainWindow::on_pushButton_clicked()
{
    Dialog *info = new Dialog();
    connect(this, SIGNAL(sendInfo(Dialog::st)), info, SLOT(recieveInfo(Dialog::st)));
    if(ui->label->text() == "Введите локальный код")
    {
        Dialog::st temp = findLokKod(ui->lineEdit->text());
        if(temp.name != "Не найден")
        {
            emit sendInfo(temp);
            info->show();
        }
    }

    if(ui->label->text() == "Введите наименование")
    {
        Dialog::st temp = findName(ui->lineEdit->text());
        if(temp.name != "Не найден")
        {
            emit sendInfo(temp);
            info->show();
        }
    }

    if(ui->label->text() == "Введите чертежный индекс")
    {
        Dialog::st temp = findIndex(ui->lineEdit->text());
        if(temp.name != "Не найден")
        {
            emit sendInfo(temp);
            info->show();
        }
    }
}

void MainWindow::on_nameAction_triggered()
{
    ui->statusbar->showMessage("Найти по наименованию");
    ui->label->setText("Введите наименование");
}

void MainWindow::on_IndexAction_triggered()
{
    ui->statusbar->showMessage("Найти по чертежному индексу");
    ui->label->setText("Введите чертежный индекс");
}

//Отобразить элементы содержащие драгоценные металлы
void MainWindow::on_metallsAction_triggered()
{
    metallsModel = new QStandardItemModel;
    QStandardItem *item = new QStandardItem;

    //Заголовки столбцов
    QStringList horizontalHeader;
    horizontalHeader.append("Локальный код");
    horizontalHeader.append("Наименование");
    horizontalHeader.append("Чертежный индекс");
    horizontalHeader.append("Золото");
    horizontalHeader.append("Серебро");
    horizontalHeader.append("Платина");
    horizontalHeader.append("Пл. группа");

    metallsModel->setHorizontalHeaderLabels(horizontalHeader);

    //Заполнение таблицы
    int ind = 0;
    for(int i = 0; i < data.size(); ++i)
    {
        if(data[i].metalls)
        {
            item = new QStandardItem(data[i].lokKod);
            metallsModel->setItem(ind, 0, item);

            item = new QStandardItem(data[i].name);
            metallsModel->setItem(ind, 1, item);

            item = new QStandardItem(data[i].index);
            metallsModel->setItem(ind, 2, item);

            item = new QStandardItem(QString::number(data[i].aurum));
            metallsModel->setItem(ind, 3, item);

            item = new QStandardItem(QString::number(data[i].argentum));
            metallsModel->setItem(ind, 4, item);

            item = new QStandardItem(QString::number(data[i].platina));
            metallsModel->setItem(ind, 5, item);

            item = new QStandardItem(QString::number(data[i].platinaGroup));
            metallsModel->setItem(ind, 6, item);
            ind++;
        }
    }
    ui->tableView->setModel(metallsModel);

    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::on_loseAction_triggered()
{
    loseModel = new QStandardItemModel;
    QStandardItem *item = new QStandardItem;

    //Заголовки столбцов
    QStringList horizontalHeader;
    horizontalHeader.append("Локальный код");
    horizontalHeader.append("Наименование");
    horizontalHeader.append("Чертежный индекс");
    horizontalHeader.append("Основание");

    loseModel->setHorizontalHeaderLabels(horizontalHeader);

    //Заполнение таблицы
    int ind = 0;
    for(int i = 0; i < data.size(); ++i)
    {
        if(data[i].lose)
        {
            item = new QStandardItem(data[i].lokKod);
            loseModel->setItem(ind, 0, item);

            item = new QStandardItem(data[i].name);
            loseModel->setItem(ind, 1, item);

            item = new QStandardItem(data[i].index);
            loseModel->setItem(ind, 2, item);

            item = new QStandardItem(data[i].osnovanie);
            loseModel->setItem(ind, 3, item);

            ind++;
        }
    }
    ui->tableView->setModel(loseModel);

    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::on_AllData_triggered()
{
    fillTable();
}
