#ifndef EDITCOMPDIALOG_H
#define EDITCOMPDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class editCompDialog;
}

class editCompDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editCompDialog(QWidget *parent = 0);
    ~editCompDialog();

    void setCompName(std::string compName);
    void setYearMade(int yearMade);
    void setType(std::string type);
    void setWasBuilt(int wasBuilt);
    void setID(int id);
    std::string getCompName();
    int getYearMade();
    std::string getType();
    int getWasBuilt();
    int getID();

private slots:
    void on_savePushButton_clicked();
    void on_cancelPushButton_clicked();
    void on_radioButtonOth_clicked();
    void on_radioButtonTrans_clicked();
    void on_radioButtonElec_clicked();
    void on_radioButtonMech_clicked();

private:
    Ui::editCompDialog *ui;
    int id;
    std::string compName;
    int yearMade;
    std::string type;
    int wasBuilt;
    MainWindow m;
};
#endif // EDITCOMPDIALOG_H
