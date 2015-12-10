#ifndef SERVICES_H
#define SERVICES_H
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <string>
#include <ctime>
#include "data.h"
#include "infotype.h"
#include "comptype.h"
#include "relationstype.h"

using namespace std;

class Services{

public:
    Services();
    //ADD FUNCTIONS
    void addPerson(string name, char gender, int bYear, int dYear);
    void addComputer(string compName, int yearMade, string type, int wasBuilt);
    void addRelation(int personId, int computerId);
    //MAKE FUNCTIONS
    vector<InfoType> makePersonsVector();
    vector<CompType> makeComputerVector();
    bool makeRelation(int compID, int persID);
    //VIEW FUNCTIONS
    vector<CompType> getViewRelationPerson(int ID);
    vector<InfoType> getViewRelationComputer(int ID);
    //SORT PERSONS FUNCTIONS
    vector <InfoType> sortByNameAsc();
    vector <InfoType> sortByNameDesc();
    vector <InfoType> sortByYearAsc();
    vector <InfoType> sortByYearDesc();
    vector <InfoType> sortByGenderMale();
    vector <InfoType> sortByGenderFemale();
    vector <InfoType> sortByGenderUndecided();
    vector <InfoType> sortByDeathYearAsc();
    vector <InfoType> sortByDeathYearDesc();
    vector <InfoType> sortByDeceased();
    vector <InfoType> sortByNotDeceased();
    //SORT COMPUTER FUNCTIONS
    vector <CompType> sortByComputerNameAsc();
    vector <CompType> sortByComputerNameDesc();
    vector <CompType> sortByYearMadeAsc();
    vector <CompType> sortByYearMadeDesc();
    vector <CompType> sortByComputerTypeAsc();
    vector <CompType> sortByComputerTypeDesc();
    vector <CompType> sortByYearBuiltAsc();
    vector <CompType> sortByYearBuiltDesc();
    vector <CompType> sortByYearNotBuiltAsc();
    vector <CompType> sortByYearNotBuiltDesc();
    vector <CompType> sortByYearUnknownBuiltAsc();
    vector <CompType> sortByYearUnknownBuiltDesc();
    //SEARCH PERSONS FUNCTIONS
    vector<InfoType> searchVectorName(string nameSearch);
    vector<InfoType> searchVectorGender(string genderSearch);
    vector<InfoType> searchVectorBirthYear(string birthYearSearch);
    vector<InfoType> searchVectorDeathYear(string deathYearSearch);
    //SEARCH COMPUTERS FUNCTIONS
    vector<CompType> searchVectorComputersName(string name);
    //REMOVE FUNCTIONS
    vector<InfoType> getPerson(int ID);
    vector<CompType> getComputer(int ID);
    void getPersID(int ID);
    void getCompID(int ID);
    //OTHER
    string changeName(string tempName);
    int findIDPerson(string persName, vector<string> &names);
    int findIDComputer(string compName, vector<string> &names);
private:
    vector <InfoType> FP;
    vector <CompType> Comp;
    vector <RelationsType> Rel;
    data connection;
};

#endif // SERVICES_H
