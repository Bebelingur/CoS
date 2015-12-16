#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <string>
#include "infotype.h"
#include "services.h"
#include "mainwindow.h"

namespace Ui {
class editDialog;
}

class editDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editDialog(QWidget *parent = 0);
    ~editDialog();

    void setName(std::string name);
    void setGender(char gender);
    void setBirthYear(int byear);
    void setDeathYear(int dyear);
    void setID(int id);
    std::string getName();
    char getGender();
    int getBirthYear();
    int getDeathYear();
    int getID();

private slots:
    void on_savePushButton_clicked();
    void on_cancelPushButton_clicked();

private:
    Ui::editDialog *ui;
    Services s;
    MainWindow m;
    string name;
    int id;
    char gender;
    int birthYear;
    int deathYear;
};

#endif // EDITDIALOG_H
