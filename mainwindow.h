//bla
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "services.h"
#include <QMainWindow>
#include <QMediaPlayer>


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
    //INPUT INFO
    bool duplicateCheckPersons(string name, char gender, int bYear, int dYear);
    string letterCheck(string name);
    bool duplicateCheckComputers(string computerName, int computerYearMade, string computerType, int wasBuilt);
    bool isLowerCaseCharacther(char character);
    bool isUpperCaseCharacther(char character);
    bool isSpecialLettersCharacther(char character);
    bool isSpaceCharacther(char character);
    //string digitCheck(string number); //not used at the moment
    //bool isDigitCharacther(char character); //not used at the moment
    bool checkDatabaseEmpty(vector<InfoType> FP, vector<CompType> C);
    void displayAllPersons();
    //RELATIONS
    void displayPersonsRelations(vector<InfoType> FP);
    //SEARCH
    void lineSearchPersons();
    void lineSearchComputers();
    void lineSearchForSearch();
    void displayComputersRelations(vector<CompType> C);
    void displayAllPersonsSearch();
    void displayPersonsSearch(vector<InfoType> FP);
    void displayAllComputerSearch();
    void displayComputerSearch(vector<CompType> C);
    void displayComputersRelationsSearch(vector<CompType> C);
    void displayPersonsRelationsSearch(vector<InfoType> FP);
    //REMOVE
    void displayPersonsRemove(vector<InfoType> FP);
    void displayAllPersonsRemove();
    void displayComputersRemove(vector <CompType> c);
    void displayAllComputersRemove();
    //EDIT
    void displayPersonsEdit(vector<InfoType> FP);
    void displayAllPersonsEdit();
    void displayComputersEdit(vector<CompType> c);
    void displayAllComputersEdit();
    //OTHER
    vector<InfoType>currentlyDisplaydPerson;
    vector <CompType> currentlyDisplaydComputers;

private slots:
    //INPUT INFO
    void on_inputAddPerson_clicked();
    void on_inputPersonClear_clicked();
    void on_checkBox_inputDeath_toggled(bool checked);
    void on_text_inputPersonName_textChanged(const QString &name);
    void on_radioB_inputGenderFemale_clicked();
    void on_radioB_inputGenderMale_clicked();
    void on_radioB_inputGenderUnknown_clicked();
    void on_text_inputBirthYear_textChanged(const QString &yearBorn);
    void on_text_inputDeathYear_textChanged(const QString &yearDead);
    void on_button_inputAddComputer_clicked();
    void on_text_inputComputerName_textChanged(const QString &computerName);
    void on_text_inputDesignYear_textChanged(const QString &yearMade);
    void on_text_inputTypeNameOther_textChanged(const QString &computerTypeOther);
    void on_text_inputComputerYearBuilt_textChanged(const QString &wasBuilt);
    void on_radioB_inputTypeMechanical_clicked();
    void on_radioB_inputTypeElectrical_clicked();
    void on_radioB_inputTypeTransistor_clicked();
    void on_button_inputComputerClear_clicked();
    void on_check_inputBuilt_toggled(bool checked);
    //RELATION INPUT
    void on_button_inputAddRelation_clicked();
    void on_list_personRelationDisplay_clicked();
    void on_list_computerRelationDisplay_clicked();
    void on_button_inputRelationClear_clicked();
    void on_text_inputRelationNamePerson_textEdited();
    void on_text_inputRelationNameComputer_textEdited();
    //REMOVE
    void on_removeLineEdit_textEdited();
    void on_removePushButton_clicked();
    void on_personTableWidget_clicked();
    void on_compRemoveLineEdit_textEdited();
    void on_compRemovePushButton_clicked();
    void on_computerTableWidget_clicked();
    //SEARCH PERSON
    void on_text_searchPerson_textEdited();
    void on_radioB_searchPersonGender_toggled(bool checked);
    //SEARCH COMPUTER
    void on_text_searchComputer_textEdited();
    void on_button_searchRelation_clicked();
    void on_radioB_searchRelationComputer_clicked();
    void on_radioB_searchRelationPerson_clicked();
    void on_text_searchRelation_textEdited();
    void on_editLineEdit_textEdited();
    void on_editPushButton_clicked();
    void on_personTableWidgetToEdit_clicked();
    void on_editLineEditComp_textEdited();
    void on_compEditPushButton_clicked();
    void on_computerTableWidgetToEdit_clicked();
    void on_radioB_inputTypeOther_clicked();
    void on_radioB_searchPersonName_clicked();
    void on_radioB_searchPersoBirthYear_clicked();
    void on_radioB_searchPersonDeathYear_clicked();
    void on_radioB_searchGenderFemale_clicked();
    void on_radioB_searchGenderMale_clicked();
    void on_radioB_searchGenderUnknown_clicked();
    //MUSIC
    void on_playChristmasMusicButton_clicked();
    void on_playNonChristmasMusicButton_clicked();
    void on_stopMusicButton_clicked();

private:
    Ui::MainWindow *ui;
    Services sConnect;
    QMediaPlayer* player;
};

#endif // MAINWINDOW_H
