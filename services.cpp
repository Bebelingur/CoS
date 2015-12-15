#include "services.h"

using namespace std;

//function that finds the time and adds 1 year to it
int aliveNow()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int exactYearNow = 1900 + ltm->tm_year;
    return exactYearNow + 1;
}
const int alive = aliveNow();

Services::Services()
{

}
//ADD FUNCTIONS
//takes info from user input regarding persons and sends down to data
void Services::addPerson(string name, char gender, int bYear, int dYear)
{
    InfoType p;
    p.name = name;
    p.gender = gender;
    p.birthYear = bYear;
    p.deathYear = dYear;

    data personsToData;
    personsToData.saveDataPersons(p);
}
//takes info from user input regarding computers and sends down to data
void Services::addComputer(string compName, int yearMade, string type, int wasBuilt)
{
    CompType p;
    p.compName = compName;
    p.yearMade = yearMade;
    p.type = type;
    p.wasBuilt = wasBuilt;

    data computersToData;
    computersToData.saveDataComputers(p);
}
//takes info from user input regarding relation and sends down to data
void Services::addRelation(int personId, int computerId)
{
    RelationsType p;
    p.personId = personId;
    p.computerId = computerId;

    data relationsToData;
    relationsToData.saveDataRelations(p);
}
//MAKE FUNCTIONS
//loads a vector of person information from data and returns it
vector<InfoType> Services::makePersonsVector()
{
   vector<InfoType> p = connection.loadPersData();
   return p;
}
//loads a vector of computer information from data and returns it
vector<CompType> Services::makeComputerVector()
{
   vector<CompType> c = connection.loadCompData();
   return c;
}
//function that makes relation between person and computer
bool Services::makeRelation(int compID, int persID)
{
    data d;
    bool check = false;

    check = d.getMakeRelation(compID, persID);
    if(check == false)
    {
        addRelation(persID, compID);
    }

    return check;
}
//VIEW FUNCTIONS
//finds the person id and returns it
int Services::findIDPerson(string persName, vector<string> &names)
{
    data d;
    int persID = 0;
    persID = d.getFindIDPerson(persName, names);
    return persID;
}
//finds the computer id and returns it
int Services::findIDComputer(string compName, vector<string>&names)
{
    data d;
    int compID = 0;
    compID = d.getFindIDComputer(compName, names);
    return compID;
}

//function that finds relations between person and computers
vector<CompType> Services::getViewRelationPerson(int ID)
{
    vector<CompType> computers = connection.viewRelationPerson(ID);
    return computers;
}
//function that finds relations between computer and persons
vector<InfoType> Services::getViewRelationComputer(int ID)
{
    vector<InfoType> people = connection.viewRelationComputer(ID);
    return people;
}
//SORT PERSONS BOOL FUNCTIONS
//function that compares the first character of each string, used to sort in alphabetical order
bool compareNameAsc(const InfoType& a, const InfoType& b)
{
    string str1 = a.name;
    str1[0] = tolower(str1[0]);

    string str2 = b.name;
    str2[0] = tolower(str2[0]);

    return str1 < str2;
}
//function that compares the first character of each string, used to sort in reverse alphabetical order
bool compareNameDesc(const InfoType& a, const InfoType& b)
{
    string str1 = a.name;
    str1[0] = tolower(str1[0]);

    string str2 = b.name;
    str2[0] = tolower(str2[0]);

    return str1 > str2;
}
//function that compares M and F and returns M(true) to sort list by gender, where M is first in list
bool compareGenderMaleFirst(const InfoType& a, const InfoType& b)
{
    return a.gender > b.gender;
}
//function that compares M and F and returns F(true) to sort list by gender, where F is first in list
bool compareGenderFemaleFirst(const InfoType& a, const InfoType& b)
{
    return a.gender < b.gender;
}
//function that compares birthYear and returns the older
bool compareYearAsc(const InfoType& a, const InfoType& b)
{
    return a.birthYear < b.birthYear;
}
//function that compares birthYear and returns the younger
bool compareYearDesc(const InfoType& a, const InfoType& b)
{
    return a.birthYear > b.birthYear;
}
//function that compares deathYear and returns the older
bool compareDeathYearAsc(const InfoType& a, const InfoType& b)
{
    int year1 = a.deathYear;
    int year2 = b.deathYear;

    if(year1 == 0)
    {
        year1 = alive;
    }
    else if(year2 == 0)
    {
        year2 = alive;
    }
    return year1 < year2;
}
//function that compares birthYear and returns the younger
bool compareDeathYearDesc(const InfoType& a, const InfoType& b)
{
    int year1 = a.deathYear;
    int year2 = b.deathYear;

    if(year1 == 0)
    {
        year1 = alive;
    }
    else if(year2 == 0)
    {
        year2 = alive;
    }
    return year1 > year2;
}
//SORT PERSONS FUNCTIONS
//function that returns the sorted vector in alphabetical order
vector <InfoType> Services::sortByNameAsc()
{
    vector <InfoType> FP = makePersonsVector();
    sort(FP.begin(), FP.end(), compareNameAsc);
    return FP;
}
//function that returns the sorted vector in reverse alphabetical order
vector <InfoType> Services::sortByNameDesc()
{
    vector <InfoType> FP = makePersonsVector();
    sort(FP.begin(), FP.end(), compareNameDesc);
    return FP;
}

//function that returns the sorted vector by gender, males first
vector <InfoType> Services::sortByGenderMale()
{
    vector <InfoType> FP = makePersonsVector();
    sort(FP.begin(), FP.end(), compareNameAsc);
    sort(FP.begin(), FP.end(), compareGenderMaleFirst);
    return FP;
}
//function that returns the sorted vector by gender, females first
vector <InfoType> Services::sortByGenderFemale()
{
    vector <InfoType> FP = makePersonsVector();
    sort(FP.begin(), FP.end(), compareNameAsc);
    sort(FP.begin(), FP.end(), compareGenderFemaleFirst);
    return FP;
}
//function that returns the sorted vector by gender, undecided first
vector <InfoType> Services::sortByGenderUndecided()
{
    vector <InfoType> FP = makePersonsVector();
    sort(FP.begin(), FP.end(), compareNameAsc);
    sort(FP.begin(), FP.end(), compareGenderFemaleFirst);
    return FP;
}

//function that returns the sorted vector by birthYear in ascending order
vector <InfoType> Services::sortByYearAsc()
{
    vector <InfoType> FP = makePersonsVector();
    sort(FP.begin(), FP.end(), compareNameAsc);
    sort(FP.begin(), FP.end(), compareYearAsc);
    return FP;
}
//function that returns the sorted vector by birthYear in descending order
vector <InfoType> Services::sortByYearDesc()
{
    vector <InfoType> FP = makePersonsVector();
    sort(FP.begin(), FP.end(), compareNameAsc);
    sort(FP.begin(), FP.end(), compareYearDesc);
    return FP;
}

//function that returns the sorted vector by deathYear in ascending order
vector <InfoType> Services::sortByDeathYearAsc()
{
    vector <InfoType> FP = makePersonsVector();
    sort(FP.begin(), FP.end(), compareNameAsc);
    sort(FP.begin(), FP.end(), compareDeathYearAsc);
    return FP;
}
//function that returns the sorted vector by deathYear in descending order
vector <InfoType> Services::sortByDeathYearDesc()
{
    vector <InfoType> FP = makePersonsVector();
    sort(FP.begin(), FP.end(), compareNameAsc);
    sort(FP.begin(), FP.end(), compareDeathYearDesc);
    return FP;
}
//function that returns the sorted vector by deathYear in ascending order, used in special case
vector <InfoType> Services::sortByDeceased()
{
    vector <InfoType> FP = makePersonsVector();
    sort(FP.begin(), FP.end(), compareNameAsc);
    sort(FP.begin(), FP.end(), compareDeathYearAsc);
    return FP;
}
//function that returns the sorted vector by deathYear in ascending order, used in special case
vector <InfoType> Services::sortByNotDeceased()
{
    vector <InfoType> FP = makePersonsVector();
    sort(FP.begin(), FP.end(), compareNameAsc);
    sort(FP.begin(), FP.end(), compareDeathYearAsc);
    return FP;
}
//SORT COMPUTER BOOL FUNCTIONS
//function that compares the first character of each string, used to sort computers in alphabetical order
bool compareCompNameAsc(const CompType& a, const CompType& b)
{
    string str1 = a.compName;
    str1[0] = tolower(str1[0]);

    string str2 = b.compName;
    str2[0] = tolower(str2[0]);

    return str1 < str2;
}
//function that compares the first character of each string, used to sort computers in reverse alphabetical order
bool compareCompNameDesc(const CompType& a, const CompType& b)
{
    string str1 = a.compName;
    str1[0] = tolower(str1[0]);

    string str2 = b.compName;
    str2[0] = tolower(str2[0]);

    return str1 > str2;
}
//function that compares yearMade and returns the older
bool compareComputerYearMadeAsc(const CompType& a, const CompType& b)
{
    return a.yearMade < b.yearMade;
}
//function that compares yearMade and returns the younger
bool compareComputerYearMadeDesc(const CompType& a, const CompType& b)
{
    return a.yearMade > b.yearMade;
}
//function that compares the first character of each string, used to sort computers by type in alphabetical order
bool compareCompTypeAsc(const CompType& a, const CompType& b)
{
    string str1 = a.type;
    str1[0] = tolower(str1[0]);

    string str2 = b.type;
    str2[0] = tolower(str2[0]);

    return str1 < str2;
}
//function that compares the first character of each string, used to sort computers by type in reverse alphabetical order
bool compareCompTypeDesc(const CompType& a, const CompType& b)
{
    string str1 = a.type;
    str1[0] = tolower(str1[0]);

    string str2 = b.type;
    str2[0] = tolower(str2[0]);

    return str1 > str2;
}
//function that compares wasBuilt and returns the older
bool compareComputerYearBuiltAsc(const CompType& a, const CompType& b)
{
    return a.wasBuilt < b.wasBuilt;
}
//function that compares wasBuilt and returns the younger
bool compareComputerYearBuiltDesc(const CompType& a, const CompType& b)
{
    return a.wasBuilt > b.wasBuilt;
}
//SORT COMPUTER FUNCTIONS
//function that returns the sorted vector in alphabetical order
vector <CompType> Services::sortByComputerNameAsc()
{
    vector <CompType> Comp = makeComputerVector();
    sort(Comp.begin(), Comp.end(), compareCompNameAsc);
    return Comp;
}
//function that returns the sorted vector in reverse alphabetical order
vector <CompType> Services::sortByComputerNameDesc()
{
    vector <CompType> Comp = makeComputerVector();
    sort(Comp.begin(), Comp.end(), compareCompNameDesc);
    return Comp;
}
//function that returns the sorted vector by yearMade in ascending order
vector <CompType> Services::sortByYearMadeAsc()
{
    vector <CompType> Comp = makeComputerVector();
    sort(Comp.begin(), Comp.end(), compareCompNameAsc);
    sort(Comp.begin(), Comp.end(), compareComputerYearMadeAsc);
    return Comp;
}
//function that returns the sorted vector by yearMade in descending order
vector <CompType> Services::sortByYearMadeDesc()
{
    vector <CompType> Comp = makeComputerVector();
    sort(Comp.begin(), Comp.end(), compareCompNameAsc);
    sort(Comp.begin(), Comp.end(), compareComputerYearMadeDesc);
    return Comp;
}
//function that returns the sorted vector by type in ascending order
vector <CompType> Services::sortByComputerTypeAsc()
{
    vector <CompType> Comp = makeComputerVector();
    sort(Comp.begin(), Comp.end(), compareCompTypeAsc);
    return Comp;
}
//function that returns the sorted vector by type in descending order
vector <CompType> Services::sortByComputerTypeDesc()
{
    vector <CompType> Comp = makeComputerVector();
    sort(Comp.begin(), Comp.end(), compareCompTypeDesc);
    return Comp;
}
//function that returns the sorted vector by yearBuilt in ascending order
vector <CompType> Services::sortByYearBuiltAsc()
{
    vector <CompType> Comp = makeComputerVector();
    sort(Comp.begin(), Comp.end(), compareCompNameAsc);
    sort(Comp.begin(), Comp.end(), compareComputerYearBuiltAsc);
    return Comp;
}
//function that returns the sorted vector by yearBuilt in descending order
vector <CompType> Services::sortByYearBuiltDesc()
{
    vector <CompType> Comp = makeComputerVector();
    sort(Comp.begin(), Comp.end(), compareCompNameAsc);
    sort(Comp.begin(), Comp.end(), compareComputerYearBuiltDesc);
    return Comp;
}
//function that returns the sorted vector by yearBuilt in ascending order, used in special case
vector <CompType> Services::sortByYearNotBuiltAsc()
{
    vector <CompType> Comp = makeComputerVector();
    sort(Comp.begin(), Comp.end(), compareCompNameAsc);
    sort(Comp.begin(), Comp.end(), compareComputerYearBuiltAsc);
    return Comp;
}
//function that returns the sorted vector by yearBuilt in descending order, used in special case
vector <CompType> Services::sortByYearNotBuiltDesc()
{
    vector <CompType> Comp = makeComputerVector();
    sort(Comp.begin(), Comp.end(), compareCompNameAsc);
    sort(Comp.begin(), Comp.end(), compareComputerYearBuiltDesc);
    return Comp;
}
//function that returns the sorted vector by yearBuilt in ascending order, used in special case
vector <CompType> Services::sortByYearUnknownBuiltAsc()
{
    vector <CompType> Comp = makeComputerVector();
    sort(Comp.begin(), Comp.end(), compareCompNameAsc);
    sort(Comp.begin(), Comp.end(), compareComputerYearBuiltAsc);
    return Comp;
}
//function that returns the sorted vector by yearBuilt in descending order, used in special case
vector <CompType> Services::sortByYearUnknownBuiltDesc()
{
    vector <CompType> Comp = makeComputerVector();
    sort(Comp.begin(), Comp.end(), compareCompNameAsc);
    sort(Comp.begin(), Comp.end(), compareComputerYearBuiltDesc);
    return Comp;
}
//SEARCH PERSONS FUNCTIONS
//function that searches for name/part of name, set results from search to vector and returns the vector
vector<InfoType> Services::searchVectorName(string nameSearch)
{
    vector <InfoType> FP = makePersonsVector();
    vector <InfoType> result;

    int nameSize = nameSearch.size();

    for(int i = 0; i < nameSize; i++)
    {
        //set the input to lower case
        nameSearch[i] = tolower(nameSearch[i]);
    }
    for(unsigned int i = 0; i < FP.size(); i++)
    {
        string tempName = FP[i].name;
        nameSize = tempName.size();

        for(int j = 0; j < nameSize; j++)
        {
            //set name in database to lower case and then compare
            tempName[j] = tolower(tempName[j]);
        }
        int found = tempName.find(nameSearch);//check if input is part of name
        if(found != (int) string::npos)
        {
            result.push_back(FP[i]);
        }
    }
    return result;
}
//function that searches for gender, set results from search to vector and returns the vector
vector<InfoType> Services::searchVectorGender(string genderSearch)
{
    vector <InfoType> FP = makePersonsVector();
    vector <InfoType> result;
    string tempGender;

    for(int i = 0; i <1; i++)//set input to lower case
    {
        genderSearch[i] = tolower(genderSearch[i]);
    }
    for(unsigned int i = 0; i < FP.size(); i++)
    {
        tempGender = FP[i].gender;
        for(int j = 0; j <1; j++)//set info from database to lower case
        tempGender[j] = tolower(tempGender[j]);

        if(genderSearch == tempGender)
        {
            result.push_back(FP[i]);
        }
    }
    FP.clear();
    return result;
}
//function that searches for birthYear, set results from search to vector and returns the vector
vector<InfoType> Services::searchVectorBirthYear(string birthYearSearch)
{
    vector <InfoType> FP = makePersonsVector();
    vector <InfoType> result;
    //check if input is of correct length and check if it only contains numbers
    for(unsigned int i = 0; i < FP.size(); i++)
    {
        int temp = FP[i].birthYear;
        string s = std::to_string(temp);
        int found = s.find(birthYearSearch);
        if(found != (int) string::npos)
        {
            result.push_back(FP[i]);
        }
    }
    FP.clear();
    return result;
}
//function that searches for deathYear, set results from search to vector and returns the vector
vector<InfoType> Services::searchVectorDeathYear(string deathYearSearch)
{
    vector <InfoType> FP = makePersonsVector();
    vector <InfoType> result;
    //check if input is of correct length and check if it only contains numbers
    if(deathYearSearch.size() == 4 && isdigit(deathYearSearch[0]) && isdigit(deathYearSearch[1]) && isdigit(deathYearSearch[2]) && isdigit(deathYearSearch[3]))
    {
        int deathYearSearchI = atoi(deathYearSearch.c_str());//set string to int to be able to compare
        for(unsigned int i = 0; i < FP.size(); i++)
        {
            if(deathYearSearchI == FP[i].deathYear)
            {
                result.push_back(FP[i]);
            }
        }
    }
    else if((deathYearSearch.size() == 1) && isdigit(deathYearSearch[0]) && (deathYearSearch == "0"))
    {
        int deathYearSearchI = atoi(deathYearSearch.c_str());//set string to int to be able to compare
        for(unsigned int i = 0; i < FP.size(); i++)
        {
            if(deathYearSearchI == FP[i].deathYear)
            {
                result.push_back(FP[i]);
            }
        }
    }
    FP.clear();
    return result;
}
//SEARCH COMPUTERS FUNCTIONS
//function that searches for computer name, set results from search to vector and returns the vector
vector<CompType> Services::searchVectorComputersName(string name)
{
    vector<CompType> Comp = makeComputerVector();
    vector<CompType> result;

        for(unsigned int i = 0; i < name.size() ; i++)
        {
            //set input to lowercase
            name[i] = tolower(name[i]);
        }
        for(unsigned int i = 0; i < Comp.size(); i++)
        {
           string tempName = Comp[i].compName;

           for(unsigned int j = 0; j < tempName.size() ; j++)
           {
               //set string to int to be able to compare
               tempName[j] = tolower(tempName[j]);
           }
           //check if input is apart of name
           int found = tempName.find(name);
           if(found != (int) std::string::npos)
           {
               result.push_back(Comp[i]);
           }
        }
        Comp.clear();
        return result;
}
//REMOVE
//function that gets the person id and returns it
vector<InfoType> Services::getPerson(int ID)
{
    vector<InfoType> p = connection.findPerson(ID);
    return p;
}

//function that gets the computer id and returns it
vector<CompType> Services::getComputer(int ID)
{
    vector<CompType> p = connection.findComputer(ID);
    return p;
}
bool Services::getPersIDToRemove(int ID)
{
    return connection.removePerson(ID);
<<<<<<< HEAD
=======

>>>>>>> 6a370e0001469950d2a05512abdb0f4550b50cc9
}

bool Services::getCompIDToRemove(int ID)
{
    return connection.removeComputer(ID);
}


//OTHER
//changes name uppercase/lowercase
string Services::changeName(string tempName)
{
    int NameLength = tempName.size();
    for (int i = 0; i < NameLength; i++)
    {
        if(tempName[i] == ' ')
        {
            tempName[i+1] = toupper(tempName[i+1]);
            i++;
        }
        else if(i ==0)
        {
            tempName[i] = toupper(tempName[i]);
        }
        else
        {
            tempName[i] = tolower(tempName[i]);
        }
    }
    return tempName;
}
