//bla
#ifndef DATA
#define DATA
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <QtSql>
#include <QtDebug>
#include <QtCore>
#include <QCoreApplication>
#include "infotype.h"
#include "comptype.h"
#include "relationstype.h"

using namespace std;

class data{

public:
    data();
    //CONNECTION
    void connectionToDatabase();
    //VECTOR INPUT TO DATABASE
    vector<InfoType> loadPersData();
    vector<CompType> loadCompData();
    //VECTOR OUTPUT TO DATABASE
    void saveDataRelations(RelationsType p);
    void saveDataPersons(InfoType p);
    void saveDataComputers(CompType p);

    //Remove functions
    vector<InfoType> findPerson(int ID);
    vector<CompType> findComputer(int ID);
    bool removePerson(int ID);
    bool removeComputer(int ID);

    char convertToChar(string a);
    string convertToString(char a);
    bool getMakeRelation(int compID, int persID);
    int getFindIDPerson(string persName, vector<string> &names);
    int getFindIDComputer(string compName, vector<string>&names);

    vector<CompType> viewRelationPerson(int ID);
    vector<InfoType> viewRelationComputer(int ID);

private:
    string personFilename, computerFilename;
};

#endif // DATA
