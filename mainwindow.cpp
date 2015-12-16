#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "services.h"
#include <string>
#include <vector>
#include <QMessageBox>
#include <QMainWindow>
#include "editdialog.h"
#include "editcompdialog.h"

using namespace std;

//function that finds the time
int timeNow()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int exactYearNow = 1900 + ltm->tm_year;
    return exactYearNow;
}
const int yearNow = timeNow();
const int startCS = 1791;
const QString notAvailable = "N/A";
const QString notBuilt = "Not built";
const QString notDead = "Not deceased";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix("../logo");
    ui->label_logoPic->setPixmap(pix);
    //QPixmap pix2("C:/Users/BerglindÓsk/Desktop/info");
    //ui->label_infoPic->setPixmap(pix2);

    player = new QMediaPlayer; // þetta fall er tengt music
    ui->label_christmas->setText("<span style='color: #ff0000'>Are you in a christmas mood?</span>");

    ui->tab_insertInfo->setCurrentIndex(0);

    viewStatistics();
    displayAllPersons();
    displayAllPersonsRemove();
    displayAllComputersRemove();
    displayAllPersonsSearch();
    displayAllComputerSearch();
    displayAllPersonsEdit();
    displayAllComputersEdit();

    //prepare the person display table
    ui->list_inputPersonDisplay->horizontalHeader()->setVisible(true);
    ui->list_inputPersonDisplay->clearContents();
    ui->list_inputPersonDisplay->setRowCount(1);
    ui->list_inputPersonDisplay->setColumnCount(4);

    //prepare the computer display table
    ui->list_inputComputerDisplay->horizontalHeader()->setVisible(true);
    ui->list_inputComputerDisplay->clearContents();
    ui->list_inputComputerDisplay->setRowCount(1);
    ui->list_inputComputerDisplay->setColumnCount(4);

    //prepare the person display table in relation
    ui->list_personRelationDisplay->horizontalHeader()->setVisible(true);
    ui->list_personRelationDisplay->clearContents();
    ui->list_personRelationDisplay->setRowCount(1);
    ui->list_personRelationDisplay->setColumnCount(4);

    //prepare the computer display table in relation
    ui->list_computerRelationDisplay->horizontalHeader()->setVisible(true);
    ui->list_computerRelationDisplay->clearContents();
    ui->list_computerRelationDisplay->setRowCount(1);
    ui->list_computerRelationDisplay->setColumnCount(4);

    //search relation table function
    ui->table_searchRelationComputerDisplay->show();
    ui->table_searchRelationPersonDisplay->hide();
}
MainWindow::~MainWindow()
{
    delete ui;
}
//MAIN MENU
void MainWindow::on_playChristmasMusicButton_clicked() // þetta fall er tengt music
{
    //file path needs to be changed for music to play music, copy new filepath in between the double quotes
    player->setMedia(QUrl::fromLocalFile("../CoS/It's Beginning to look a lot like Christmas Lyrics.mp3"));
    player->setVolume(100);
    player->play();
}

void MainWindow::on_playNonChristmasMusicButton_clicked() // þetta fall er tengt music
{
    //file path needs to be changed for music to play music, copy new filepath in between the double quotes
    player->setMedia(QUrl::fromLocalFile("../CoS/The Grinch Song.mp3"));
    player->setVolume(100);
    player->play();
}

void MainWindow::on_stopMusicButton_clicked() // þetta fall er tengt music
{
    player->pause();
}
void MainWindow::viewStatistics()
{
    vector<InfoType> FP = sConnect.makePersonsVector();
    vector<CompType> Comp = sConnect.makeComputerVector();

    int totalPersonCount = 0;
    int maleCount = 0;
    int femaleCount = 0;
    int deadCount = 0;
    int aliveCount = 0;
    int totalComputerCount = 0;
    int wasBuilt = 0;
    int notBuilt = 0;

    for(unsigned int i = 0; i < FP.size(); i++)
    {
        if(FP[i].gender == 'F' || FP[i].gender == 'f')
            femaleCount++;
        if(FP[i].gender == 'M' || FP[i].gender == 'm')
            maleCount++;
        if(FP[i].deathYear > 0)
            deadCount++;
        if(FP[i].deathYear == 0)
            aliveCount++;
        totalPersonCount++;
    }
    for(unsigned int i = 0; i < Comp.size(); i++)
    {
        if(Comp[i].wasBuilt != 0)
            wasBuilt++;
        if(Comp[i].wasBuilt == 0)
            notBuilt++;
        totalComputerCount++;
    }
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(9);

    QString persons = QString::fromStdString("Persons in database: ");
    QString totalPers = QString::number(totalPersonCount);
    QString malePersons = QString::fromStdString("Male persons in database: ");
    QString totalMalePers = QString::number(maleCount);
    QString femalePersons = QString::fromStdString("Female persons in database: ");
    QString totalFemalePers = QString::number(femaleCount);
    QString alivePersons = QString::fromStdString("Alive persons in database: ");
    QString totalAlivePers = QString::number(aliveCount);
    QString deceasedPersons = QString::fromStdString("Deceased persons in database: ");
    QString totalDeceasedPers = QString::number(deadCount);
    QString comp = QString::fromStdString("Computers in database: ");
    QString totalComp = QString::number(totalComputerCount);
    QString wasBuiltComp = QString::fromStdString("Computers built in database: ");
    QString totalBuiltComp = QString::number(wasBuilt);
    QString notBuiltComp = QString::fromStdString("Computers not built in database: ");
    QString totalNotBuiltComp = QString::number(notBuilt);
    QString persComp = QString::fromStdString("Total of persons and computers in database: ");
    QString totalPersComp = QString::number(totalComputerCount + totalPersonCount);

    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(persons));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(totalPers));
    ui->tableWidget->setItem(1, 0, new QTableWidgetItem(malePersons));
    ui->tableWidget->setItem(1, 1, new QTableWidgetItem(totalMalePers));
    ui->tableWidget->setItem(2, 0, new QTableWidgetItem(femalePersons));
    ui->tableWidget->setItem(2, 1, new QTableWidgetItem(totalFemalePers));
    ui->tableWidget->setItem(3, 0, new QTableWidgetItem(alivePersons));
    ui->tableWidget->setItem(3, 1, new QTableWidgetItem(totalAlivePers));
    ui->tableWidget->setItem(4, 0, new QTableWidgetItem(deceasedPersons));
    ui->tableWidget->setItem(4, 1, new QTableWidgetItem(totalDeceasedPers));
    ui->tableWidget->setItem(5, 0, new QTableWidgetItem(comp));
    ui->tableWidget->setItem(5, 1, new QTableWidgetItem(totalComp));
    ui->tableWidget->setItem(6, 0, new QTableWidgetItem(wasBuiltComp));
    ui->tableWidget->setItem(6, 1, new QTableWidgetItem(totalBuiltComp));
    ui->tableWidget->setItem(7, 0, new QTableWidgetItem(notBuiltComp));
    ui->tableWidget->setItem(7, 1, new QTableWidgetItem(totalNotBuiltComp));
    ui->tableWidget->setItem(8, 0, new QTableWidgetItem(persComp));
    ui->tableWidget->setItem(8, 1, new QTableWidgetItem(totalPersComp));
}

//PERSON INPUT
void MainWindow::on_inputAddPerson_clicked()
{
    //NAME
    string personNameText = ui->text_inputPersonName->text().toStdString();
    string correctNameText = letterCheck(personNameText);
    bool checkName = false;
    if(correctNameText.empty())
    {
        checkName = false;
    }
    else
    {
        checkName = true;
    }
    QString name = QString::fromStdString(personNameText);
    //name is displayed at the same time user is writing it in
    on_text_inputPersonName_textChanged(name);

    //GENDER
    char personGender;
    bool checkGender = false;
    if(ui->radioB_inputGenderFemale->isChecked())
    {
        personGender = 'f';
        checkGender = true;
    }
    else if(ui->radioB_inputGenderMale->isChecked())
    {
        personGender = 'm';
        checkGender = true;
    }
    else if(ui->radioB_inputGenderUnknown->isChecked())
    {
        personGender = '?';
        checkGender = true;
    }
    else
    {
        checkGender = false; //gender has not been chosen
    }
    //BIRTHYEAR
    int personBirthYear = ui->text_inputBirthYear->text().toInt();
    QString yearBorn = QString::number(personBirthYear);
    on_text_inputBirthYear_textChanged(yearBorn);
    bool checkBirthYear = false;
    if(personBirthYear >= startCS && personBirthYear <= yearNow)
    {
        checkBirthYear = true;
    }
    //DEATHYEAR
    int personDeathYear;
    if(ui->checkBox_inputDeath->isChecked())
    {
        personDeathYear = ui->text_inputDeathYear->text().toInt();
        QString yearDead = QString::number(personDeathYear);
        on_text_inputDeathYear_textChanged(yearDead);
    }
    else
    {
        personDeathYear = 0;
    }
    bool checkDeathYear = false;
    if(personDeathYear == 0 || (personDeathYear >= startCS && personDeathYear <= yearNow && personDeathYear > personBirthYear))
    {
        checkDeathYear = true;
    }

    //DUPLICATE PERSON
    bool checkDuplicate = duplicateCheckPersons(personNameText, personGender, personBirthYear, personDeathYear);

    //ADD PERSON
    if(checkName == true && checkGender == true && checkBirthYear == true && checkDeathYear == true && checkDuplicate == true)
    {
        sConnect.addPerson(personNameText, personGender, personBirthYear, personDeathYear);
        ui->label_inputError->setText("<span style='color: #006600'>Person successfully added!</span>");
    }
    else
    {
        //Error, cannot add person
        ui->label_inputError->setText("<span style='color: #ff0000'>Could not add person. Invalid input</span>");
    }
    displayAllPersons();
    displayAllPersonsRemove();
    displayAllPersonsSearch();
    displayAllPersonsEdit();
}
string MainWindow::letterCheck(string name)
{
    string result = "";
    for (unsigned int i = 0; i < name.length(); i++)
    {
        char currentChar = name[i];
        if(isUpperCaseCharacther(currentChar) || isLowerCaseCharacther(currentChar) || isSpaceCharacther(currentChar) || isSpecialLettersCharacther(currentChar))
        {
            result += currentChar;
        }
        else
        {
            return result = "";
        }
    }
    return result;
}
bool MainWindow::isUpperCaseCharacther(char character)
{
    int characterAsciiValue = static_cast<int>(character);
    return (characterAsciiValue >= 65 && characterAsciiValue <= 90);
}
bool MainWindow::isLowerCaseCharacther(char character)
{
    int characterAsciiValue = static_cast<int>(character);
    return (characterAsciiValue >= 97 && characterAsciiValue <= 122);
}
bool MainWindow::isSpaceCharacther(char character)
{
    int characterAsciiValue = static_cast<int>(character);
    return (characterAsciiValue == 32);
}
bool MainWindow::isSpecialLettersCharacther(char character)
{
    int characterAsciiValue = static_cast<int>(character);
    return (characterAsciiValue >= 128 && characterAsciiValue <= 154 && characterAsciiValue >= 160 && characterAsciiValue <= 165);
}
/*string MainWindow::digitCheck(string number)
{
    string result = "";

    for (unsigned int i = 0; i < number.length(); i++)
    {
        char currentChar = number[i];

        if(number.length() != 4)
        {
            return "";
        }
        else if(isDigitCharacther(currentChar))
        {
            result = currentChar;
        }
        else
        {
            return "";
        }
    }
    return result;
}*/
/*
bool MainWindow::isDigitCharacther(char character)
{
    int characterAsciiValue = static_cast<int>(character);
    return (characterAsciiValue >= 48 && characterAsciiValue <= 57);
}
*/
void MainWindow::on_inputPersonClear_clicked()
{
    ui->text_inputPersonName->clear();

    //use setAutoExclusive twice to reset radio buttons with clear
    ui->radioB_inputGenderFemale->setAutoExclusive(false);
    ui->radioB_inputGenderFemale->setChecked(false);
    ui->radioB_inputGenderFemale->setAutoExclusive(true);

    ui->radioB_inputGenderMale->setAutoExclusive(false);
    ui->radioB_inputGenderMale->setChecked(false);
    ui->radioB_inputGenderMale->setAutoExclusive(true);

    ui->radioB_inputGenderUnknown->setAutoExclusive(false);
    ui->radioB_inputGenderUnknown->setChecked(false);
    ui->radioB_inputGenderUnknown->setAutoExclusive(true);

    ui->text_inputBirthYear->clear();
    ui->checkBox_inputDeath->setChecked(false);
    ui->text_inputDeathYear->clear();
    ui->list_inputPersonDisplay->clearContents();

    ui->label_inputError->clear();
}

void MainWindow::on_checkBox_inputDeath_toggled(bool checked)
{
    if(checked == true)
    {
        ui->label_deathYear->setEnabled(true);
        ui->text_inputDeathYear->setEnabled(true);
    }
    else if(checked == false)
    {
        ui->label_deathYear->setEnabled(false);
        ui->text_inputDeathYear->setEnabled(false);
    }
}

void MainWindow::on_text_inputPersonName_textChanged(const QString &name)
{
    ui->list_inputPersonDisplay->setItem(0,0,new QTableWidgetItem(name));
}
void MainWindow::on_radioB_inputGenderFemale_clicked()
{
    ui->list_inputPersonDisplay->setItem(0,1,new QTableWidgetItem("Female"));
}
void MainWindow::on_radioB_inputGenderMale_clicked()
{
    ui->list_inputPersonDisplay->setItem(0,1,new QTableWidgetItem("Male"));
}
void MainWindow::on_radioB_inputGenderUnknown_clicked()
{
    ui->list_inputPersonDisplay->setItem(0,1,new QTableWidgetItem("Unknown"));
}
void MainWindow::on_text_inputBirthYear_textChanged(const QString &yearBorn)
{
    ui->list_inputPersonDisplay->setItem(0,2,new QTableWidgetItem(yearBorn));
    //put here to show user that person is not deceased until box is checked
    ui->list_inputPersonDisplay->setItem(0,3,new QTableWidgetItem("Not deceased"));
}
void MainWindow::on_text_inputDeathYear_textChanged(const QString &yearDead)
{
    ui->list_inputPersonDisplay->setItem(0,3,new QTableWidgetItem(yearDead));
}
bool MainWindow::duplicateCheckPersons(string name, char gender, int bYear, int dYear)
{
    bool check = true;
    vector<InfoType> FP = sConnect.makePersonsVector();
    string temp1, temp2;
    temp1 = sConnect.changeName(name);
    for(unsigned int i = 0; i < FP.size(); i++)
    {
        temp2 = sConnect.changeName(FP.at(i).name);
        if((temp1 == temp2) && (gender == FP.at(i).gender) && (bYear == FP.at(i).birthYear) && (dYear == FP.at(i).deathYear))
        {
            check = false;
        }
    }
    return check;
}
//COMPUTER INFO
void MainWindow::on_button_inputAddComputer_clicked()
{
    //NAME
    string computerName = ui->text_inputComputerName->text().toStdString();
    bool checkName = false;
    if(computerName.empty())
    {
        checkName = false;
    }
    else
    {
        checkName = true;
    }
    QString compName = QString::fromStdString(computerName);
    //name is displayed at the same time user is writing it in
    on_text_inputComputerName_textChanged(compName);

    //YEAR DESIGNED
    int computerYearMade = ui->text_inputDesignYear->text().toInt();
    QString compYearMade = QString::number(computerYearMade);
    on_text_inputDesignYear_textChanged(compYearMade);
    bool checkDesignYear = false;
    if(computerYearMade >= startCS && computerYearMade <= yearNow)
    {
        checkDesignYear = true;
    }

    //TYPE
    string computerType;
    bool checkType = false;
    if(ui->radioB_inputTypeMechanical->isChecked())
    {
        computerType = "Mechanical";
        checkType = true;
    }
    else if(ui->radioB_inputTypeElectrical->isChecked())
    {
        computerType = "Electronic";
        checkType = true;
    }
    else if(ui->radioB_inputTypeTransistor->isChecked())
    {
        computerType = "Transistor";
        checkType = true;
    }
    else if(ui->radioB_inputTypeOther->isChecked())
    {
        computerType = ui->text_inputTypeNameOther->text().toStdString();
        QString compType = QString::fromStdString(computerType);
        checkType = true;
    }
    else
    {
        checkType = false; //type has not been chosen
    }

    //YEAR BUILT
    int wasBuilt;
    if(ui->check_inputBuilt->isChecked())
    {
        wasBuilt = ui->text_inputComputerYearBuilt->text().toInt();
        QString compBuilt = QString::number(wasBuilt);
        on_text_inputComputerYearBuilt_textChanged(compBuilt);
    }
    else
    {
        wasBuilt = 0;
    }
    bool checkBuiltYear = false;
    if(wasBuilt == 0 || (wasBuilt >= computerYearMade && wasBuilt >= startCS && wasBuilt <= yearNow))
    {
        checkBuiltYear = true;
    }

    //ADD COMPUTER
    bool checkDuplicateComp = duplicateCheckComputers(computerName, computerYearMade, computerType, wasBuilt);
    if(checkName == true && checkDesignYear == true && checkType == true && checkBuiltYear == true && checkDuplicateComp == true)
    {
        sConnect.addComputer(computerName, computerYearMade, computerType, wasBuilt);
        ui->label_inputErrorComputer->setText("<span style='color: #006600'>Computer successfully added!</span>");
    }
    else
    {
        //Error, cannot add computer
        ui->label_inputErrorComputer->setText("<span style='color: #ff0000'>Could not add computer. Invalid input</span>");
    }
    displayAllComputersRemove();
    displayAllComputerSearch();
    displayAllComputersEdit();
}

void MainWindow::on_text_inputComputerName_textChanged(const QString &computerName)
{
    ui->list_inputComputerDisplay->setItem(0,0,new QTableWidgetItem(computerName));
}
//function that checks for duplicate computer input from user
bool MainWindow::duplicateCheckComputers(string computerName, int computerYearMade, string computerType, int wasBuilt)
{
    bool check = true;
    vector<CompType> Comp = sConnect.makeComputerVector();
    string temp1, temp2, temp3, temp4;

    temp1 = sConnect.changeName(computerName);
    temp2 = sConnect.changeName(computerType);

    for(unsigned int i = 0; i < Comp.size(); i++)
    {
        temp3 = sConnect.changeName(Comp.at(i).compName);
        temp4 = sConnect.changeName(Comp.at(i).type);
        if((temp1 == temp3) && (computerYearMade == Comp.at(i).yearMade) && (temp2 == temp4) && (wasBuilt == Comp.at(i).wasBuilt))
        {
            check = false;
        }
    }
    return check;
}
void MainWindow::on_text_inputDesignYear_textChanged(const QString &yearMade)
{
    ui->list_inputComputerDisplay->setItem(0,2,new QTableWidgetItem(yearMade));
    //put here to show user that computer is not built until box is checked
    ui->list_inputComputerDisplay->setItem(0,3,new QTableWidgetItem("Not built"));

}

void MainWindow::on_text_inputComputerYearBuilt_textChanged(const QString &wasBuilt)
{
    ui->list_inputComputerDisplay->setItem(0,3,new QTableWidgetItem(wasBuilt));
}

void MainWindow::on_radioB_inputTypeMechanical_clicked()
{
    ui->list_inputComputerDisplay->setItem(0,1,new QTableWidgetItem("Mechanical"));
    ui->text_inputTypeNameOther->setEnabled(false);
}

void MainWindow::on_radioB_inputTypeElectrical_clicked()
{
    ui->list_inputComputerDisplay->setItem(0,1,new QTableWidgetItem("Electronic"));
    ui->text_inputTypeNameOther->setEnabled(false);
}

void MainWindow::on_radioB_inputTypeTransistor_clicked()
{
    ui->list_inputComputerDisplay->setItem(0,1,new QTableWidgetItem("Transistor"));
    ui->text_inputTypeNameOther->setEnabled(false);
}
void MainWindow::on_text_inputTypeNameOther_textChanged(const QString &computerTypeOther)
{
    ui->list_inputComputerDisplay->setItem(0,1,new QTableWidgetItem(computerTypeOther));
}

void MainWindow::on_button_inputComputerClear_clicked()
{
    ui->text_inputComputerName->clear();

    //use setAutoExclusive twice to reset radio buttons with clear
    ui->radioB_inputTypeMechanical->setAutoExclusive(false);
    ui->radioB_inputTypeMechanical->setChecked(false);
    ui->radioB_inputTypeMechanical->setAutoExclusive(true);

    ui->radioB_inputTypeElectrical->setAutoExclusive(false);
    ui->radioB_inputTypeElectrical->setChecked(false);
    ui->radioB_inputTypeElectrical->setAutoExclusive(true);

    ui->radioB_inputTypeTransistor->setAutoExclusive(false);
    ui->radioB_inputTypeTransistor->setChecked(false);
    ui->radioB_inputTypeTransistor->setAutoExclusive(true);

    ui->radioB_inputTypeOther->setAutoExclusive(false);
    ui->radioB_inputTypeOther->setChecked(false);
    ui->radioB_inputTypeOther->setAutoExclusive(true);

    ui->text_inputTypeNameOther->clear();
    ui->text_inputDesignYear->clear();
    ui->check_inputBuilt->setChecked(false);
    ui->text_inputComputerYearBuilt->clear();
    ui->list_inputComputerDisplay->clearContents();

    ui->label_inputErrorComputer->clear();
}

void MainWindow::on_check_inputBuilt_toggled(bool checked)
{
    if(checked == true)
    {
        ui->label_yearBuilt->setEnabled(true);
        ui->text_inputComputerYearBuilt->setEnabled(true);
    }
    else if(checked == false)
    {
        ui->label_yearBuilt->setEnabled(false);
        ui->text_inputComputerYearBuilt->setEnabled(false);
    }
}

void MainWindow::on_button_inputAddRelation_clicked()
{
    //if(ui->table_searchNameDisplay->currentIndex().isValid())

    //checks if database is empty or not
    vector<InfoType> FP = sConnect.makePersonsVector();
    vector<CompType> C = sConnect.makeComputerVector();
    bool checkDatabase = false;
    checkDatabase = checkDatabaseEmpty(FP, C);
    FP.clear();
    C.clear();

    if(checkDatabase == true)
    {
        //PERSON NAME
        string personNameText = ui->text_inputRelationNamePerson->text().toStdString();
        QString pName = QString::fromStdString(personNameText);
        //get person row id to get ID from database
        int currentlySelectedPersonIndex = ui->list_personRelationDisplay->currentIndex().row();
        InfoType p = currentlyDisplaydPerson.at(currentlySelectedPersonIndex);
        int persID = p.id;

        //COMPUTER NAME
        string computerNameText = ui->text_inputRelationNameComputer->text().toStdString();
        QString cName = QString::fromStdString(computerNameText);
        //get computer row id to get ID from database
        int currentlySelectedComputerIndex = ui->list_computerRelationDisplay->currentIndex().row();
        CompType c = currentlyDisplaydComputers.at(currentlySelectedComputerIndex);
        int compID = c.id;
        if(!(sConnect.makeRelation(compID, persID)))
        {
            ui->label_inputErrorRelation->setText("<span style='color: #006600'>Relation successfully added!</span>");
        }
        else
        {
            ui->label_inputErrorRelation->setText("<span style='color: #ff0000'>Relation is already in database.</span>");

        }
    }
}
void MainWindow::on_list_personRelationDisplay_clicked()
{
    if((ui->list_personRelationDisplay->currentIndex().isValid())&&(ui->list_computerRelationDisplay->currentIndex().isValid()))
    {
        ui->button_inputAddRelation->setEnabled(true);
    }
}

void MainWindow::on_list_computerRelationDisplay_clicked()
{
    if((ui->list_personRelationDisplay->currentIndex().isValid())&&(ui->list_computerRelationDisplay->currentIndex().isValid()))
    {
        ui->button_inputAddRelation->setEnabled(true);
    }
}
void MainWindow::on_button_inputRelationClear_clicked()
{
    ui->text_inputRelationNamePerson->clear();
    ui->text_inputRelationNameComputer->clear();
    ui->list_personRelationDisplay->clearContents();
    ui->list_computerRelationDisplay->clearContents();
    ui->button_inputAddRelation->setEnabled(false);
    ui->label_inputErrorRelation->clear();
}

bool MainWindow::checkDatabaseEmpty(vector<InfoType> FP, vector<CompType> C)
{
    if((FP.size() == 0) && (C.size() == 0))
    {
        return false;
    }
    else
    {
        return true;
    }
}

void MainWindow::displayAllPersons()
{
    vector<InfoType> FP = sConnect.makePersonsVector();
    displayPersonsRelations(FP);
}

void MainWindow::displayPersonsRelations(vector<InfoType> FP)
{
    ui->list_personRelationDisplay->clearContents();
    ui->list_personRelationDisplay->setRowCount(FP.size());
    for(unsigned int i = 0; i < FP.size(); i++)
    {
        InfoType p = FP.at(i);
        QString name = QString::fromStdString(p.name);
        string gender = "";
        if(toupper(p.gender) == 'F')
        {
            gender = "Female";
        }
        else if(toupper(p.gender) == 'M')
        {
            gender = "Male";
        }
        else if(p.gender == '?')
        {
            gender = "Unknown";
        }

        QString genderP = QString::fromStdString(gender);
        QString yearBorn = QString::number(p.birthYear);
        QString yearDead = QString::number(p.deathYear);

        ui->list_personRelationDisplay->setItem(i, 0, new QTableWidgetItem(name));
        ui->list_personRelationDisplay->setItem(i, 1, new QTableWidgetItem(genderP));
        ui->list_personRelationDisplay->setItem(i, 2, new QTableWidgetItem(yearBorn));
        ui->list_personRelationDisplay->setItem(i, 3, new QTableWidgetItem(yearDead));
    }
    currentlyDisplaydPerson = FP;
}

void MainWindow::displayComputersRelations(vector<CompType> C)
{
    ui->list_computerRelationDisplay->clearContents();
    ui->list_computerRelationDisplay->setRowCount(C.size());
    for(unsigned int i = 0; i < C.size(); i++)
    {
        CompType c = C.at(i);
        QString name = QString::fromStdString(c.compName);
        QString type = QString::fromStdString(c.type);
        QString yearDesign = QString::number(c.yearMade);
        QString yearBuilt = QString::number(c.wasBuilt);

        ui->list_computerRelationDisplay->setItem(i, 0, new QTableWidgetItem(name));
        ui->list_computerRelationDisplay->setItem(i, 1, new QTableWidgetItem(type));
        ui->list_computerRelationDisplay->setItem(i, 2, new QTableWidgetItem(yearDesign));
        ui->list_computerRelationDisplay->setItem(i, 3, new QTableWidgetItem(yearBuilt));
    }
    currentlyDisplaydComputers = C;
}

void MainWindow::on_text_inputRelationNamePerson_textEdited()
{
    lineSearchPersons();
}
void MainWindow::lineSearchPersons()
{
    vector<InfoType> FP;
    string userInput = ui->text_inputRelationNamePerson->text().toStdString();
    FP = sConnect.searchVectorName(userInput);
    displayPersonsRelations(FP);
}

void MainWindow::on_text_inputRelationNameComputer_textEdited()
{
    lineSearchComputers();
}
void MainWindow::lineSearchComputers()
{
    vector<CompType> C;
    string userInput = ui->text_inputRelationNameComputer->text().toStdString();
    C = sConnect.searchVectorComputersName(userInput);
    displayComputersRelations(C);
}
//REMOVE PERSON
void MainWindow::displayAllPersonsRemove()
{
    vector<InfoType> FP = sConnect.makePersonsVector();
    displayPersonsRemove(FP);
}

void MainWindow::displayPersonsRemove(vector<InfoType> FP)
{
    ui->personTableWidget->clearContents();
    ui->personTableWidget->setRowCount(FP.size());

    for(unsigned int i = 0; i < FP.size(); i++)
    {
        InfoType p = FP.at(i);
        string gend = "";
        p.gender = tolower(p.gender);
        if(p.gender == 'm')
        {
            gend = "Male";
        }else if(p.gender == 'f')
        {
            gend = "Female";
        }else
        {
            gend = "Other";
        }

        QString name = QString::fromStdString(p.name);
        QString gender = QString::fromStdString(gend);
        QString yearBorn = QString::number(p.birthYear);
        QString yearDead = QString::number(p.deathYear);
        ui->personTableWidget->setItem(i, 0, new QTableWidgetItem(name));
        ui->personTableWidget->setItem(i, 1, new QTableWidgetItem(gender));
        ui->personTableWidget->setItem(i, 2, new QTableWidgetItem(yearBorn));
        if(p.deathYear == 0)
        {
            ui->personTableWidget->setItem(i, 3, new QTableWidgetItem(notDead));
        }else
        {
            ui->personTableWidget->setItem(i, 3, new QTableWidgetItem(yearDead));
        }
    }
    currentlyDisplaydPerson = FP;
}

//updates the persons displayd everytime the text changes in the lineEdit box
void MainWindow::on_removeLineEdit_textEdited()
{
    string userInput = ui->removeLineEdit->text().toStdString();
    vector<InfoType> p = sConnect.searchVectorName(userInput);
    ui->removePushButton->setEnabled(false);
    displayPersonsRemove(p);
}

//removes the person chosen when the remove button is clicked(including features such as message box etc.)

void MainWindow::on_removePushButton_clicked()
{
    int currentlySelectedIndex = ui->personTableWidget->currentIndex().row();

    InfoType p = currentlyDisplaydPerson.at(currentlySelectedIndex);

    int answer = QMessageBox::question(this, "Confirm", "Are you sure you want to delete this person?");

    if(answer == QMessageBox::No)
    {
        return;
    }

    bool success = sConnect.getPersIDToRemove(p.id);

    if (success)
    {
        ui->statusBar->showMessage("Person was removed", 1500);
        ui->removeLineEdit->setText("");
        displayAllPersonsRemove();
        ui->removePushButton->setEnabled(false);
    }
    else
    {
        ui->statusBar->showMessage("Could not remove person", 1500);
    }
}

//makes the remove button enabled when a person is chosen
void MainWindow::on_personTableWidget_clicked()
{
    ui->removePushButton->setEnabled(true);
}

//REMOVE COMPUTER
void MainWindow::displayAllComputersRemove()
{
    vector<CompType> c = sConnect.makeComputerVector();
    displayComputersRemove(c);
}

void MainWindow::displayComputersRemove(vector<CompType> c)
{
    ui->computerTableWidget->clearContents();
    ui->computerTableWidget->setRowCount(c.size());

    for(unsigned int i = 0; i < c.size(); i++)
    {
        CompType x = c.at(i);
        QString name = QString::fromStdString(x.compName);
        QString yearMade = QString::number(x.yearMade);
        QString type = QString::fromStdString(x.type);
        QString wasBuilt = QString::number(x.wasBuilt);
        ui->computerTableWidget->setItem(i, 0, new QTableWidgetItem(name));
        if(x.yearMade == 0)
        {
            ui->computerTableWidget->setItem(i, 2, new QTableWidgetItem(notAvailable));
        }else
        {
            ui->computerTableWidget->setItem(i, 2, new QTableWidgetItem(yearMade));
        }
        ui->computerTableWidget->setItem(i, 1, new QTableWidgetItem(type));
        if(x.wasBuilt == 0)
        {
            ui->computerTableWidget->setItem(i, 3, new QTableWidgetItem(notBuilt));
        }else
        {
            ui->computerTableWidget->setItem(i, 3, new QTableWidgetItem(wasBuilt));
        }
    }
    currentlyDisplaydComputers = c;
}

//updates the computers displayd everytime the text changes in the lineEdit box
void MainWindow::on_compRemoveLineEdit_textEdited()
{
    string userInput = ui->compRemoveLineEdit->text().toStdString();
    vector<CompType> c = sConnect.searchVectorComputersName(userInput);
    ui->compRemovePushButton->setEnabled(false);
    displayComputersRemove(c);
}

//removes the computer chosen when the remove button is clicked(including features such as message box etc.)

void MainWindow::on_compRemovePushButton_clicked()
{
    int currentlySelectedIndex = ui->computerTableWidget->currentIndex().row();

    CompType c = currentlyDisplaydComputers.at(currentlySelectedIndex);

    int answer = QMessageBox::question(this, "Confirm", "Are you sure you want to delete this computer?");

    if(answer == QMessageBox::No)
    {
        return;
    }

    bool success = sConnect.getCompIDToRemove(c.id);

    if (success)
    {
        ui->statusBar->showMessage("Computer was removed", 1500);
        ui->compRemoveLineEdit->setText("");
        displayAllComputersRemove();

        ui->compRemovePushButton->setEnabled(false);
    }
    else
    {
       ui->statusBar->showMessage("Could not remove computer", 1500);
    }
}

//makes the remove button enabled when a computer is chosen
void MainWindow::on_computerTableWidget_clicked()
{
    ui->compRemovePushButton->setEnabled(true);
}
//SEARCH PERSON
void MainWindow::displayAllPersonsSearch()
{
    vector<InfoType> FP = sConnect.makePersonsVector();
    displayPersonsSearch(FP);
}

void MainWindow::displayPersonsSearch(vector<InfoType> FP)
{
    ui->table_searchPerson->clearContents();
    ui->table_searchPerson->setRowCount(FP.size());
    for(unsigned int i = 0; i < FP.size(); i++)
    {
        InfoType p = FP.at(i);
        QString name = QString::fromStdString(p.name);
        string gender = "";
        if(toupper(p.gender) == 'F')
        {
            gender = "Female";
        }
        else if(toupper(p.gender) == 'M')
        {
            gender = "Male";
        }
        else if(p.gender == '?')
        {
            gender = "Unknown";
        }
        QString genderP = QString::fromStdString(gender);
        QString yearBorn = QString::number(p.birthYear);
        QString yearDead = QString::number(p.deathYear);
        ui->table_searchPerson->setItem(i, 0, new QTableWidgetItem(name));
        ui->table_searchPerson->setItem(i, 1, new QTableWidgetItem(genderP));
        ui->table_searchPerson->setItem(i, 2, new QTableWidgetItem(yearBorn));
        ui->table_searchPerson->setItem(i, 3, new QTableWidgetItem(yearDead));
    }
    currentlyDisplaydPerson = FP;
}

void MainWindow::lineSearchForSearch()
{
    vector<InfoType> FP;
    string userInput = ui->text_searchPerson->text().toStdString();

    if(ui->radioB_searchPersonName->isChecked())
    {
        FP = sConnect.searchVectorName(userInput);
    }
    if(ui->radioB_searchPersonGender->isChecked())
    {

    }
    if(ui->radioB_searchPersoBirthYear->isChecked())
    {
        FP = sConnect.searchVectorBirthYear(userInput);
    }
    if(ui->radioB_searchPersonDeathYear->isChecked())
    {
        FP = sConnect.searchVectorDeathYear(userInput);
    }
        displayPersonsSearch(FP);
}

void MainWindow::on_text_searchPerson_textEdited()
{
    lineSearchForSearch();
}

void MainWindow::on_radioB_searchPersonGender_toggled(bool checked)
{
    if(checked == true)
    {
        ui->radioB_searchGenderFemale->setEnabled(true);
        ui->radioB_searchGenderMale->setEnabled(true);
        ui->radioB_searchGenderUnknown->setEnabled(true);
    }
    else if(checked == false)
    {
        ui->radioB_searchGenderFemale->setEnabled(false);
        ui->radioB_searchGenderMale->setEnabled(false);
        ui->radioB_searchGenderUnknown->setEnabled(false);
    }

}
//SEARCH COMPUTER
void MainWindow::displayAllComputerSearch()
{
    vector<CompType> C = sConnect.makeComputerVector();
    displayComputerSearch(C);
}

void MainWindow::displayComputerSearch(vector<CompType> C)
{
    ui->table_searchComputer->clearContents();
    ui->table_searchComputer->setRowCount(C.size());
    for(unsigned int i = 0; i < C.size(); i++)
    {
        CompType c = C.at(i);
        QString name = QString::fromStdString(c.compName);
        QString type = QString::fromStdString(c.type);
        QString yearDesigned = QString::number(c.yearMade);
        QString yearBuilt = QString::number(c.wasBuilt);
        ui->table_searchComputer->setItem(i, 0, new QTableWidgetItem(name));
        ui->table_searchComputer->setItem(i, 1, new QTableWidgetItem(type));
        ui->table_searchComputer->setItem(i, 2, new QTableWidgetItem(yearDesigned));
        ui->table_searchComputer->setItem(i, 3, new QTableWidgetItem(yearBuilt));
    }
    currentlyDisplaydComputers = C;
}

void MainWindow::on_text_searchComputer_textEdited()
{
    vector<CompType> C;
    string userInput = ui->text_searchComputer->text().toStdString();
    if(ui->radioB_searchComputerName->isChecked())
    {
        C = sConnect.searchVectorComputersName(userInput);
    }
    if(ui->radioB_searchComputerType->isChecked())
    {
        C = sConnect.searchVectorComputersType(userInput);
    }
    if(ui->radioB_searchComputerYearDesign->isChecked())
    {
        C = sConnect.searchVectorComputersYearMade(userInput);
    }
    if(ui->radioB_searchComputerYearBuilt->isChecked())
    {
        C = sConnect.searchVectorComputersWasBuilt(userInput);
    }
        displayComputerSearch(C);
}
//SEARCH RELATION
void MainWindow::on_button_searchRelation_clicked()
{
    if(ui->table_searchNameDisplay->currentIndex().isValid())
    {
        ui->label_errorRelationSearch->clear();
        //persons name input should display computers related
        if(ui->radioB_searchRelationComputer->isChecked())
        {
            vector<InfoType> FP;
            int currentlySelectedPersonIndex = ui->table_searchNameDisplay->currentIndex().row();
            CompType c = currentlyDisplaydComputers.at(currentlySelectedPersonIndex);
            int compID = c.id;
            FP = sConnect.getViewRelationComputer(compID);
            displayPersonsRelationsSearch(FP);
        }
        //computer name input should display persons related
        if(ui->radioB_searchRelationPerson->isChecked())
        {
            ui->label_errorRelationSearch->clear();
            vector<CompType> C;
            int currentlySelectedPersonIndex = ui->table_searchNameDisplay->currentIndex().row();
            InfoType p = currentlyDisplaydPerson.at(currentlySelectedPersonIndex);
            int persID = p.id;
            C = sConnect.getViewRelationPerson(persID);
            displayComputersRelationsSearch(C);
        }
    }
    else
    {
        ui->label_errorRelationSearch->setText("<span style='color: #ff0000'>Invalid input. Please select name from list and press button.</span>");
    }
}

void MainWindow::displayComputersRelationsSearch(vector<CompType> C)
{
    ui->table_searchRelationComputerDisplay->clearContents();
    ui->table_searchRelationComputerDisplay->setRowCount(C.size());
    for(unsigned int i = 0; i < C.size(); i++)
    {
        CompType c = C.at(i);
        QString qname = QString::fromStdString(c.compName);
        QString qyearMade = QString::number(c.yearMade);
        QString qtype = QString::fromStdString(c.type);
        QString qwasBuilt = QString::number(c.wasBuilt);
        ui->table_searchRelationComputerDisplay->setItem(i, 0, new QTableWidgetItem(qname));
        ui->table_searchRelationComputerDisplay->setItem(i, 1, new QTableWidgetItem(qtype));
        ui->table_searchRelationComputerDisplay->setItem(i, 2, new QTableWidgetItem(qyearMade));
        ui->table_searchRelationComputerDisplay->setItem(i, 3, new QTableWidgetItem(qwasBuilt));
    }
}

void MainWindow::displayPersonsRelationsSearch(vector<InfoType> FP)
{
    ui->table_searchRelationPersonDisplay->clearContents();
    ui->table_searchRelationPersonDisplay->setRowCount(FP.size());
    for(unsigned int i = 0; i < FP.size(); i++)
    {
        InfoType p = FP.at(i);
        QString name = QString::fromStdString(p.name);

        string gend = "";
        p.gender = tolower(p.gender);
        if(p.gender == 'm')
        {
            gend = "Male";
        }else if(p.gender == 'f')
        {
            gend = "Female";
        }else
        {
            gend = "Other";
        }

        QString gender = QString::fromStdString(gend);
        QString bYear = QString::number(p.birthYear);
        QString dYear = QString::number(p.deathYear);
        ui->table_searchRelationPersonDisplay->setItem(i, 0, new QTableWidgetItem(name));
        ui->table_searchRelationPersonDisplay->setItem(i, 1, new QTableWidgetItem(gender));
        ui->table_searchRelationPersonDisplay->setItem(i, 2, new QTableWidgetItem(bYear));
        ui->table_searchRelationPersonDisplay->setItem(i, 3, new QTableWidgetItem(dYear));
    }
}

void MainWindow::on_radioB_searchRelationComputer_clicked()
{
    ui->table_searchRelationPersonDisplay->show();
    ui->table_searchRelationComputerDisplay->hide();
}

void MainWindow::on_radioB_searchRelationPerson_clicked()
{
    ui->table_searchRelationComputerDisplay->show();
    ui->table_searchRelationPersonDisplay->hide();
}

void MainWindow::on_text_searchRelation_textEdited()
{
    ui->label_errorRelationSearch->clear();

    if(ui->radioB_searchRelationComputer->isChecked())
    {
        vector<CompType> C;
        string userInput = ui->text_searchRelation->text().toStdString();

        C = sConnect.searchVectorComputersName(userInput);
        ui->table_searchNameDisplay->clearContents();
        ui->table_searchNameDisplay->setRowCount(C.size());
        for(unsigned int i = 0; i < C.size(); i++)
        {
            CompType comp = C.at(i);
            QString name = QString::fromStdString(comp.compName);
            ui->table_searchNameDisplay->setItem(i,0,new QTableWidgetItem(name));
        }
        currentlyDisplaydComputers = C;
    }
    if(ui->radioB_searchRelationPerson->isChecked())
    {
        vector<InfoType> FP;
        string userInput = ui->text_searchRelation->text().toStdString();

        FP = sConnect.searchVectorName(userInput);
        ui->table_searchNameDisplay->clearContents();
        ui->table_searchNameDisplay->setRowCount(FP.size());
        for(unsigned int i = 0; i < FP.size(); i++)
        {
            InfoType pers = FP.at(i);
            QString name = QString::fromStdString(pers.name);
            ui->table_searchNameDisplay->setItem(i,0,new QTableWidgetItem(name));
        }
        currentlyDisplaydPerson = FP;
    }
}
//EDIT


void MainWindow::on_editLineEdit_textEdited()
{
    string userInput = ui->editLineEdit->text().toStdString();
    vector<InfoType> p = sConnect.searchVectorName(userInput);
    ui->editPushButton->setEnabled(false);
    displayPersonsEdit(p);
}


void MainWindow::displayPersonsEdit(vector<InfoType> FP)
{
    ui->personTableWidgetToEdit->clearContents();
    ui->personTableWidgetToEdit->setRowCount(FP.size());

    for(unsigned int i = 0; i < FP.size(); i++)
    {
        InfoType p = FP.at(i);
        string gend = "";
        p.gender = tolower(p.gender);
        if(p.gender == 'm')
        {
            gend = "Male";
        }else if(p.gender == 'f')
        {
            gend = "Female";
        }else
        {
            gend = "Other";
        }

        QString name = QString::fromStdString(p.name);
        QString gender = QString::fromStdString(gend);
        QString yearBorn = QString::number(p.birthYear);
        QString yearDead = QString::number(p.deathYear);
        ui->personTableWidgetToEdit->setItem(i, 0, new QTableWidgetItem(name));
        ui->personTableWidgetToEdit->setItem(i, 1, new QTableWidgetItem(gender));
        ui->personTableWidgetToEdit->setItem(i, 2, new QTableWidgetItem(yearBorn));
        if(p.deathYear == 0)
        {
            ui->personTableWidgetToEdit->setItem(i, 3, new QTableWidgetItem(notDead));
        }else
        {
            ui->personTableWidgetToEdit->setItem(i, 3, new QTableWidgetItem(yearDead));
        }
    }
    currentlyDisplaydPerson = FP;
}

void MainWindow::displayAllPersonsEdit()
{
    vector <InfoType> p = sConnect.makePersonsVector();
    displayPersonsEdit(p);
}

void MainWindow::on_editPushButton_clicked()
{
    editDialog e;

    int currentlySelectedIndex = ui->personTableWidgetToEdit->currentIndex().row();

    InfoType p = currentlyDisplaydPerson.at(currentlySelectedIndex);

    string nameValue = p.name;

    e.setName(nameValue);

    e.setGender(p.gender);

    e.setBirthYear(p.birthYear);

    e.setDeathYear(p.deathYear);

    e.setID(p.id);

    int returnValue = e.exec();

    if(returnValue == 1)
    {
        int id = e.getID();
        string name = e.getName();
        char gender = e.getGender();
        int birthYear = e.getBirthYear();
        int deathYear = e.getDeathYear();
        bool success = sConnect.editPerson(name, gender, birthYear, deathYear, id);

        if(success)
        {
            ui->statusBar->showMessage("Information was edited", 1500);
            ui->editLineEdit->setText("");
            displayAllPersonsEdit();

            ui->editPushButton->setEnabled(false);
        }else
        {
            ui->statusBar->showMessage("Could not edit information", 1500);
        }

    }else if(returnValue == 2)
    {
        ui->editLineEdit->setText("");
        displayAllPersonsEdit();
        ui->editPushButton->setEnabled(false);
    }

}

void MainWindow::on_personTableWidgetToEdit_clicked()
{
    ui->editPushButton->setEnabled(true);
}

//COMP

void MainWindow::on_editLineEditComp_textEdited()
{
    string userInput = ui->editLineEditComp->text().toStdString();
    vector<CompType> c = sConnect.searchVectorComputersName(userInput);
    ui->compEditPushButton->setEnabled(false);
    displayComputersEdit(c);
}


void MainWindow::displayComputersEdit(vector<CompType> c)
{
    ui->computerTableWidgetToEdit->clearContents();
    ui->computerTableWidgetToEdit->setRowCount(c.size());

    for(unsigned int i = 0; i < c.size(); i++)
    {
        CompType x = c.at(i);
        QString name = QString::fromStdString(x.compName);
        QString yearMade = QString::number(x.yearMade);
        QString type = QString::fromStdString(x.type);
        QString wasBuilt = QString::number(x.wasBuilt);

        ui->computerTableWidgetToEdit->setItem(i, 0, new QTableWidgetItem(name));
        if(x.yearMade == 0)
        {
            ui->computerTableWidgetToEdit->setItem(i, 2, new QTableWidgetItem(notAvailable));
        }else
        {
            ui->computerTableWidgetToEdit->setItem(i, 2, new QTableWidgetItem(yearMade));
        }
        ui->computerTableWidgetToEdit->setItem(i, 1, new QTableWidgetItem(type));
        if(x.wasBuilt == 0)
        {
            ui->computerTableWidgetToEdit->setItem(i, 3, new QTableWidgetItem(notBuilt));
        }else
        {
            ui->computerTableWidgetToEdit->setItem(i, 3, new QTableWidgetItem(wasBuilt));
        }
    }
    currentlyDisplaydComputers = c;
}

void MainWindow::displayAllComputersEdit()
{
    vector <CompType> c = sConnect.makeComputerVector();
    displayComputersEdit(c);
}

void MainWindow::on_compEditPushButton_clicked()
{
    editCompDialog e;

    int currentlySelectedIndex = ui->computerTableWidgetToEdit->currentIndex().row();

    CompType c = currentlyDisplaydComputers.at(currentlySelectedIndex);


    e.setCompName(c.compName);

    e.setYearMade(c.yearMade);

    e.setWasBuilt(c.wasBuilt);

    e.setID(c.id);

    e.setType(c.type);


    int returnValue = e.exec();

    if(returnValue == 1)
    {
        int id = e.getID();
        string compName = e.getCompName();
        int yearMade = e.getYearMade();
        string type = e.getType();
        int wasBuilt = e.getWasBuilt();

        bool success = sConnect.editComputer(compName, yearMade, type, wasBuilt, id);

        if(success)
        {
            ui->statusBar->showMessage("Information was edited", 1500);
            ui->editLineEditComp->setText("");
            displayAllComputersEdit();

            ui->compEditPushButton->setEnabled(false);
        }else
        {
            ui->statusBar->showMessage("Could not edit information", 1500);
        }

    }else if(returnValue == 2)
    {
        ui->editLineEditComp->setText("");
        displayAllComputersEdit();
        ui->compEditPushButton->setEnabled(false);
    }

}

void MainWindow::on_computerTableWidgetToEdit_clicked()
{
    ui->compEditPushButton->setEnabled(true);
}

void MainWindow::on_radioB_inputTypeOther_clicked()
{
    ui->text_inputTypeNameOther->setEnabled(true);
}

void MainWindow::on_radioB_searchPersonName_clicked()
{
    ui->radioB_searchGenderFemale->setAutoExclusive(false);
    ui->radioB_searchGenderFemale->setChecked(false);
    ui->radioB_searchGenderFemale->setAutoExclusive(true);

    ui->radioB_searchGenderMale->setAutoExclusive(false);
    ui->radioB_searchGenderMale->setChecked(false);
    ui->radioB_searchGenderMale->setAutoExclusive(true);

    ui->radioB_searchGenderUnknown->setAutoExclusive(false);
    ui->radioB_searchGenderUnknown->setChecked(false);
    ui->radioB_searchGenderUnknown->setAutoExclusive(true);
}

void MainWindow::on_radioB_searchPersoBirthYear_clicked()
{
    ui->radioB_searchGenderFemale->setAutoExclusive(false);
    ui->radioB_searchGenderFemale->setChecked(false);
    ui->radioB_searchGenderFemale->setAutoExclusive(true);

    ui->radioB_searchGenderMale->setAutoExclusive(false);
    ui->radioB_searchGenderMale->setChecked(false);
    ui->radioB_searchGenderMale->setAutoExclusive(true);

    ui->radioB_searchGenderUnknown->setAutoExclusive(false);
    ui->radioB_searchGenderUnknown->setChecked(false);
    ui->radioB_searchGenderUnknown->setAutoExclusive(true);
}

void MainWindow::on_radioB_searchPersonDeathYear_clicked()
{
    ui->radioB_searchGenderFemale->setAutoExclusive(false);
    ui->radioB_searchGenderFemale->setChecked(false);
    ui->radioB_searchGenderFemale->setAutoExclusive(true);

    ui->radioB_searchGenderMale->setAutoExclusive(false);
    ui->radioB_searchGenderMale->setChecked(false);
    ui->radioB_searchGenderMale->setAutoExclusive(true);

    ui->radioB_searchGenderUnknown->setAutoExclusive(false);
    ui->radioB_searchGenderUnknown->setChecked(false);
    ui->radioB_searchGenderUnknown->setAutoExclusive(true);
}

void MainWindow::on_radioB_searchGenderFemale_clicked()
{
    vector<InfoType> FP;

        string genderSearch = "";

           genderSearch = "f";

        FP = sConnect.searchVectorGender(genderSearch);

        displayPersonsSearch(FP);
}

void MainWindow::on_radioB_searchGenderMale_clicked()
{
    vector<InfoType> FP;

        string genderSearch = "";


             genderSearch = "m";

        FP = sConnect.searchVectorGender(genderSearch);

        displayPersonsSearch(FP);
}

void MainWindow::on_radioB_searchGenderUnknown_clicked()
{
    vector<InfoType> FP;

        string genderSearch = "";

             genderSearch = "?";

        FP = sConnect.searchVectorGender(genderSearch);

        displayPersonsSearch(FP);
}
