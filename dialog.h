#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}
struct st;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    struct st
    {
        QString lokKod, index, name, zavod, edIzmer, osnovanie;
        int count, GCX, HCX;
        double aurum = 0.0, argentum = 0.0, platina = 0.0, platinaGroup = 0.0;
        bool lose = false, metalls = false;
    };
private:
    Ui::Dialog *ui;

public slots:
    void recieveInfo(Dialog::st temp);
};

#endif // DIALOG_H
