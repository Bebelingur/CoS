#include "editdialog.h"
#include "ui_editdialog.h"
#include <QMessageBox>

int timeNow2()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int exactYearNow = 1900 + ltm->tm_year;
    return exactYearNow;
}
const int yearNow = timeNow2();
const int startCS = 1791;

editDialog::editDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editDialog)
{
    ui->setupUi(this);
}

editDialog::~editDialog()
{
    delete ui;
}

void editDialog::setName(std::string name)
{
    ui->lineEditInside->setText(QString::fromStdString(name));
}

void editDialog::setGender(char gender)
{
    if(gender == 'f' || gender == 'F')
        ui->radioButtonFemale->setChecked(true);
    else if(gender == 'm' || gender == 'M')
        ui->radioButtonMale->setChecked(true);
    else
        ui->radioButtonOther->setChecked(true);
}

void editDialog::setBirthYear(int byear)
{
    ui->lineEditInsideBirth->setText(QString::number(byear));
}

void editDialog::setDeathYear(int dyear)
{
    ui->lineEditInsideDeath->setText(QString::number(dyear));
}

void editDialog::setID(int id)
{
    ui->idLabel->setText(QString::number(id));
}

string editDialog::getName()
{
    return name;
}

char editDialog::getGender()
{
    return gender;
}

int editDialog::getBirthYear()
{
    return birthYear;
}

int editDialog::getDeathYear()
{
    return deathYear;
}

int editDialog::getID()
{
    return id;
}

void editDialog::on_savePushButton_clicked()
{
    id = ui->idLabel->text().toInt();

    name = ui->lineEditInside->text().toStdString();
    string correctNameText = m.letterCheck(name);
    bool checkName = false;
    if(correctNameText.empty())
    {
        checkName = false;
    }
    else
    {
        checkName = true;
    }
    bool checkGender = false;
    if(ui->radioButtonFemale->isChecked())
    {
        gender = 'f';
        checkGender = true;
    }else if(ui->radioButtonMale->isChecked())
    {
        gender = 'm';
        checkGender = true;
    }else if(ui->radioButtonOther->isChecked())
    {
        gender = '?';
        checkGender = true;
    }

    birthYear = ui->lineEditInsideBirth->text().toInt();
    bool checkBirthYear = false;
    if(birthYear >= startCS && birthYear <= yearNow && birthYear < deathYear)
    {
        checkBirthYear = true;
    }
    deathYear = ui->lineEditInsideDeath->text().toInt();
    bool checkDeathYear = false;
    if(deathYear == 0 || (deathYear >= startCS && deathYear <= yearNow && birthYear < deathYear))
    {
        checkDeathYear = true;
    }
    bool checkDuplicate = m.duplicateCheckPersons(name, gender, birthYear, deathYear);

    if(checkName == true && checkGender == true && checkBirthYear == true && checkDeathYear == true && checkDuplicate == true)
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
        ui->label_dialogPersonError->setText("<span style='color: #ff0000'>Invalid input for edit</span>");
    }



}

void editDialog::on_cancelPushButton_clicked()
{
    this->done(2);
}
