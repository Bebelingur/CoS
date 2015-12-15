//bla
#include "data.h"

using namespace std;

data::data()
{
}
//CONNECTION
//function that connects the program to the database
void data::connectionToDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "first");
    db = QSqlDatabase::database("first");
    QString dbName = "database.sqlite";

    db.setDatabaseName(dbName);
         if(!db.open())
         {
             qDebug() << "Error: " << db.lastError().text();
         }

    QSqlQuery query(db);
    QSqlQuery query2(db);
    QSqlQuery query3(db);

    string queryCreate = "CREATE TABLE persons(id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR NOT NULL, sex VARCHAR NOT NULL, yearBorn INTEGER NOT NULL, yearDead INTEGER NOT NULL);";
    string queryCreate2 = "CREATE TABLE computers(id INTEGER PRIMARY KEY AUTOINCREMENT, compName VARCHAR NOT NULL, yearMade INTEGER NOT NULL, type VARCHAR NOT NULL, wasBuilt INTEGER NOT NULL);";
    string queryCreate3 = "CREATE TABLE relations(idPerson INEGER, idComputer INTEGER,FOREIGN KEY(idPerson) REFERENCES persons(id), FOREIGN KEY(idComputer) REFERENCES computers(id));";

    query.exec(QString(queryCreate.c_str()));
    query2.exec(QString(queryCreate2.c_str()));
    query3.exec(QString(queryCreate3.c_str()));
}
//VECTOR INPUT TO DATABASE
//function that loads person information from database to vector and returns it
vector<InfoType> data::loadPersData()
{
    vector<InfoType> people;

    QSqlDatabase db = QSqlDatabase::database("first");
    QSqlQuery query(db);
    query.exec("SELECT * FROM persons");

    while(query.next())
    {
        InfoType p;
        p.id = query.value("id").toUInt();
        p.name = query.value("name").toString().toStdString();
        p.gender = convertToChar(query.value("sex").toString().toStdString());
        p.birthYear = query.value("yearBorn").toUInt();
        p.deathYear = query.value("yearDead").toUInt();
        people.push_back(p);
    }
    return people;
}
//function that loads computer information from database to vector and returns it
vector<CompType> data::loadCompData()
{
    vector<CompType> computers;

    QSqlDatabase db = QSqlDatabase::database("first");
    QSqlQuery query(db);
    query.exec("SELECT * FROM computers");

    while(query.next())
    {
        CompType c;
        c.id = query.value("id").toUInt();
        c.compName = query.value("compName").toString().toStdString();
        c.yearMade = query.value("yearMade").toUInt();
        c.type = query.value("type").toString().toStdString();
        c.wasBuilt = query.value("wasBuilt").toUInt();
        computers.push_back(c);
    }
    return computers;
}
//VECTOR OUTPUT TO DATABASE
//function that saves relation info between person and computer to database
void data::saveDataRelations(RelationsType p)
{
    QSqlDatabase db = QSqlDatabase::database("first");
    QSqlQuery query(db);

    query.prepare("Insert Into relations(idPerson, idComputer)Values(:idPerson, :idComputer)");
    query.bindValue(":idPerson", p.personId);
    query.bindValue(":idComputer", p.computerId);
    if(!query.exec())
    {
        qDebug() << "addRelations error:  " << query.lastError();
    }
}

//function that saves person info to database
void data::saveDataPersons(InfoType p)
{
    QSqlDatabase db = QSqlDatabase::database("first");
    QSqlQuery query(db);

    string sex = convertToString(p.gender);
    QString qName = QString::fromUtf8(p.name.c_str());
    QString qSex = QString::fromUtf8(sex.c_str());

    query.prepare("INSERT INTO persons(name, sex, yearBorn, yearDead)VALUES(:name, :sex, :yearBorn, :yearDead)");
    query.bindValue(":name", qName);
    query.bindValue(":sex", qSex);
    query.bindValue(":yearBorn", p.birthYear);
    query.bindValue(":yearDead", p.deathYear);

    if(!query.exec())
    {
        qDebug() << "addPersons error:  " << query.lastError();
    }
}
//function that saves computer info to database
void data::saveDataComputers(CompType p)
{
    QSqlDatabase db = QSqlDatabase::database("first");
    QSqlQuery query(db);

    QString qcompName = QString::fromUtf8(p.compName.c_str());
    QString qtype = QString::fromUtf8(p.type.c_str());

    query.prepare("INSERT INTO computers(compName, yearMade, type, wasBuilt)VALUES(:compName, :yearMade, :type, :wasBuilt)");
    query.bindValue(":compName", qcompName);
    query.bindValue(":yearMade", p.yearMade);
    query.bindValue(":type", qtype);
    query.bindValue(":wasBuilt", p.wasBuilt);

    if(!query.exec())
    {
        qDebug() << "addComputer error:  " << query.lastError();
    }
}


//function that converts string to char and returns it
char data::convertToChar(string a)
{
    char result;
    result = a.at(0);
    return result;
}
//function that converts char to string and returns it
string data::convertToString(char a)
{
    string result;
    result = a;
    return result;
}
bool data::getMakeRelation(int compID, int persID)
{

    bool check = false;
    QSqlDatabase db = QSqlDatabase::database("first");
    QSqlQuery query(db);

    query.exec("SELECT* FROM relations");
    while(query.next())
    {
        RelationsType r;
        r.computerId = query.value("idComputer").toUInt();
        r.personId = query.value("idPerson").toUInt();

        if((r.computerId == compID) && (r.personId == persID))
        {
            check = true;
        }

    }

    return check;
}
int data::getFindIDPerson(string persName, vector<string> &names)
{
    int persID = 0;
    string nameCompare = "";

    QSqlDatabase db = QSqlDatabase::database("first");
    QSqlQuery query(db);
    QString qName = QString::fromUtf8(persName.c_str());
    query.exec("SELECT name, id FROM persons WHERE name LIKE '%"+qName+"%'");
    while(query.next())
    {
        InfoType p;
        p.id = query.value("id").toUInt();
        p.name = query.value("name").toString().toStdString();
        nameCompare = p.name;
        names.push_back(nameCompare);
        if(nameCompare == persName)
        {
            persID = p.id;
        }
    }
    return persID;
}
int data::getFindIDComputer(string compName, vector<string>&names)
{
    int compID = 0;
    string compNameCompare = "";
    QSqlDatabase db = QSqlDatabase::database("first");
    QSqlQuery query(db);
    QString qName = QString::fromUtf8(compName.c_str());
    query.exec("SELECT compName, id FROM computers WHERE compName LIKE '%"+qName+"%'");
    while(query.next())
    {
        CompType c;
        c.id = query.value("id").toUInt();
        c.compName = query.value("compName").toString().toStdString();
        compNameCompare = c.compName;
        names.push_back(compNameCompare);
        if(compNameCompare == compName)
        {
            compID = c.id;
        }
    }
    return compID;
}

vector<InfoType> data::findPerson(int ID)
{
    vector<InfoType> p;
    InfoType person;
    QSqlDatabase db = QSqlDatabase::database("first");
    QSqlQuery query(db);
    query.exec("SELECT * FROM persons WHERE id = "+QString::number(ID)+"");

    while(query.next())
    {
        person.id = query.value("id").toUInt();
        person.name = query.value("name").toString().toStdString();
        person.gender = convertToChar(query.value("sex").toString().toStdString());
        person.birthYear = query.value("yearBorn").toUInt();
        person.deathYear = query.value("yearDead").toUInt();
        p.push_back(person);
    }
    return p;
}
//function that finds the computer id and returns it
vector<CompType> data::findComputer(int ID)
{
    vector<CompType> c;
    CompType computer;
    QSqlDatabase db = QSqlDatabase::database("first");
    QSqlQuery query(db);
    query.exec("SELECT * FROM computers WHERE id = "+QString::number(ID)+"");
    while(query.next())
    {
        computer.id = query.value("id").toUInt();
        computer.compName = query.value("compName").toString().toStdString();
        computer.yearMade = query.value("yearMade").toUInt();
        computer.type = query.value("type").toString().toStdString();
        computer.wasBuilt = query.value("wasBuilt").toUInt();
        c.push_back(computer);
    }
    return c;
}
//removes person from database
bool data::removePerson(int ID)
{
    QSqlDatabase db = QSqlDatabase::database("first");
    QSqlQuery query(db);
    QSqlQuery query2(db);
    bool success = query.exec("DELETE FROM persons WHERE id = "+QString::number(ID)+"");
    query2.exec("DELETE FROM relations WHERE idPerson = "+QString::number(ID)+"");
    return success;
}
//removes computer from database
bool data::removeComputer(int ID)
{
    QSqlDatabase db = QSqlDatabase::database("first");
    QSqlQuery query(db);
    QSqlQuery query2(db);
    bool success = query.exec("DELETE FROM computers WHERE id = "+QString::number(ID)+"");
    query2.exec("DELETE FROM relations WHERE idComputer = "+QString::number(ID)+"");
    return success;
}
//function that finds relations between person and computers
vector<CompType> data::viewRelationPerson(int ID)
{
    vector<CompType> computers;
    QSqlDatabase db = QSqlDatabase::database("first");
    QSqlQuery query(db);
    query.exec("SELECT computers.* FROM computers INNER JOIN relations ON persons.id = relations.idPerson INNER JOIN persons ON computers.id = relations.idComputer WHERE idPerson = "+QString::number(ID)+"");
    while(query.next())
    {
        CompType c;
        c.id = query.value("id").toUInt();
        c.compName = query.value("compName").toString().toStdString();
        c.yearMade = query.value("yearMade").toUInt();
        c.type = query.value("type").toString().toStdString();
        c.wasBuilt = query.value("wasBuilt").toUInt();
        computers.push_back(c);
    }
    return computers;
}
//function that finds relations between computer and persons
vector<InfoType> data::viewRelationComputer(int ID)
{
    vector<InfoType> people;

    QSqlDatabase db = QSqlDatabase::database("first");
    QSqlQuery query(db);
    query.exec("SELECT persons.* FROM persons INNER JOIN relations ON persons.id = relations.idPerson INNER JOIN computers ON computers.id = relations.idComputer WHERE idComputer ='"+QString::number(ID)+"'");
    while(query.next())
    {
        InfoType p;
        p.id = query.value("id").toUInt();
        p.name = query.value("name").toString().toStdString();
        p.gender = convertToChar(query.value("sex").toString().toStdString());
        p.birthYear = query.value("yearBorn").toUInt();
        p.deathYear = query.value("yearDead").toUInt();
        people.push_back(p);
    }
    return people;
}
