#include "editcompdialog.h"
#include "ui_editcompdialog.h"
#include <QMessageBox>

//function that finds the time
int timeNow3()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int exactYearNow = 1900 + ltm->tm_year;
    return exactYearNow;
}
const int yearNow = timeNow3();
const int startCS = 1791;

editCompDialog::editCompDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editCompDialog)
{
    ui->setupUi(this);
}

editCompDialog::~editCompDialog()
{
    delete ui;
}

void editCompDialog::setCompName(std::string compName)
{
    ui->lineEditInside->setText(QString::fromStdString(compName));
}

void editCompDialog::setType(std::string type)
{
    if(type == "Mechanical")
        ui->radioButtonMech->setChecked(true);
    else if(type == "Electronic")
        ui->radioButtonElec->setChecked(true);
    else if(type == "Transistor")
        ui->radioButtonTrans->setChecked(true);
    else
    {
        ui->radioButtonOth->setChecked(true);
        ui->lineEditOther->setText(QString::fromStdString(type));
        ui->lineEditOther->setEnabled(true);
    }
}

void editCompDialog::setYearMade(int yearMade)
{
    ui->lineEditInsideYearMade->setText(QString::number(yearMade));
}

void editCompDialog::setWasBuilt(int wasBuilt)
{
    ui->lineEditInsideWasBuilt->setText(QString::number(wasBuilt));
}

void editCompDialog::setID(int id)
{
    ui->idLabelComp->setText(QString::number(id));
}

std::string editCompDialog::getCompName()
{
    return compName;
}

int editCompDialog::getYearMade()
{
    return yearMade;
}

std::string editCompDialog::getType()
{
    return type;
}

int editCompDialog::getWasBuilt()
{
    return wasBuilt;
}

int editCompDialog::getID()
{
    return id;
}

void editCompDialog::on_savePushButton_clicked()
{
    id = ui->idLabelComp->text().toInt();

    compName = ui->lineEditInside->text().toStdString();
    bool checkName = false;
    if(compName.empty())
    {
        checkName = false;
    }
    else
    {
        checkName = true;
    }

    bool checkType = false;
    if(ui->radioButtonMech->isChecked())
    {
        type = "Mechanical";
        checkType = true;
    }
    else if(ui->radioButtonElec->isChecked())
    {
        type = "Electronic";
        checkType = true;
    }
    else if(ui->radioButtonTrans->isChecked())
    {
        type = "Transistor";
        checkType = true;
    }
    else
    {
        type = ui->lineEditOther->text().toStdString();
        checkType = true;
    }

    yearMade = ui->lineEditInsideYearMade->text().toInt();
    bool checkDesignYear = false;
    if(yearMade >= startCS && yearMade <= yearNow)
    {
        checkDesignYear = true;
    }

    wasBuilt = ui->lineEditInsideWasBuilt->text().toInt();
    bool checkBuiltYear = false;
    if(wasBuilt == 0 || (wasBuilt >= yearMade && wasBuilt <= yearNow))
    {
        checkBuiltYear = true;
    }

    bool checkDuplicateComp = m.duplicateCheckComputers(compName, yearMade, type, wasBuilt);
    if(checkName == true && checkDesignYear == true && checkType == true && checkBuiltYear == true && checkDuplicateComp == true && (yearMade < wasBuilt || wasBuilt == 0))
    {
        int answer = QMessageBox::question(this, "Confirm", "Are you sure you want to save these changes?");
        if(answer == QMessageBox::No)
        {
            return;
        }
        this->done(1);
    }
    else
    {
        ui->label_dialogComputerError->setText("<span style='color: #ff0000'>Invalid input for edit</span>");

    }
}

void editCompDialog::on_cancelPushButton_clicked()
{
    this->done(2);
}


void editCompDialog::on_radioButtonOth_clicked()
{
    ui->lineEditOther->setEnabled(true);
}

void editCompDialog::on_radioButtonTrans_clicked()
{
    ui->lineEditOther->setEnabled(false);
}

void editCompDialog::on_radioButtonElec_clicked()
{
    ui->lineEditOther->setEnabled(false);
}

void editCompDialog::on_radioButtonMech_clicked()
{
    ui->lineEditOther->setEnabled(false);
}
