#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "services.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //MAIN MENU
    void viewStatistics();

    //REMOVE
    void displayPersonsRemove(vector<InfoType> FP);
    void displayAllPersonsRemove();
    void displayComputersRemove(vector <CompType> c);
    void displayAllComputersRemove();
    vector<InfoType>currentlyDisplaydPerson;
    vector <CompType> currentlyDisplaydComputers;

private slots:

    void on_inputAddPerson_clicked();

    string letterCheck(string name);
    bool isLowerCaseCharacther(char character);
    bool isUpperCaseCharacther(char character);
    bool isSpecialLettersCharacther(char character);
    bool isSpaceCharacther(char character);
    //string digitCheck(string number);
    //bool isDigitCharacther(char character);

    void on_inputPersonClear_clicked();

    void on_checkBox_inputDeath_toggled(bool checked);

    void on_text_inputPersonName_textChanged(const QString &name);

    void on_radioB_inputGenderFemale_clicked();


    void on_radioB_inputGenderMale_clicked();

    void on_radioB_inputGenderUnknown_clicked();

    void on_text_inputBirthYear_textChanged(const QString &yearBorn);

    void on_text_inputDeathYear_textChanged(const QString &yearDead);

    bool duplicateCheckPersons(string name, char gender, int bYear, int dYear);


    void on_button_inputAddComputer_clicked();

    void on_text_inputComputerName_textChanged(const QString &computerName);

    bool duplicateCheckComputers(string computerName, int computerYearMade, string computerType, int wasBuilt);

    void on_text_inputDesignYear_textChanged(const QString &yearMade);

    void on_text_inputTypeNameOther_textChanged(const QString &computerTypeOther);

    void on_text_inputComputerYearBuilt_textChanged(const QString &wasBuilt);

    void on_radioB_inputTypeMechanical_clicked();

    void on_radioB_inputTypeElectrical_clicked();

    void on_radioB_inputTypeTransistor_clicked();


    void on_button_inputComputerClear_clicked();

    void on_check_inputBuilt_toggled(bool checked);

    void on_button_inputAddRelation_clicked();

    void on_button_inputRelationClear_clicked();

    //void on_text_inputRelationNamePerson_textChanged(const QString &personName);

    //void on_text_inputRelationNameComputer_textChanged(const QString &computerName);

    bool checkDatabaseEmpty(vector<InfoType> FP, vector<CompType> C);

    void displayAllPersons();

    void displayPersonsRelations(vector<InfoType> FP);

    void on_text_inputRelationNamePerson_textEdited();

    void lineSearchPersons();

    void on_text_inputRelationNameComputer_textEdited();
    void lineSearchComputers();

    void displayComputersRelations(vector<CompType> C);

    //REMOVE
    void on_removeLineEdit_textEdited();

    void on_removePushButton_clicked();

    void on_personTableWidget_clicked();

    void on_compRemoveLineEdit_textEdited();

    void on_compRemovePushButton_clicked();

    void on_computerTableWidget_clicked();

    //SEARCH PERSON
    void displayAllPersonsSearch();
    void displayPersonsSearch(vector<InfoType> FP);
    void lineSearchForSearch();
    void on_text_searchPerson_textEdited();
    void on_radioB_searchPersonGender_toggled(bool checked);
    //SEARCH COMPUTER
    void displayAllComputerSearch();
    void displayComputerSearch(vector<CompType> C);
    void lineSearchForSearchComputer();
    void on_text_searchComputer_textEdited();

private:
    Ui::MainWindow *ui;
    Services sConnect;
};

#endif // MAINWINDOW_H
