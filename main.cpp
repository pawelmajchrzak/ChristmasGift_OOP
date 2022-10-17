#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <time.h>

using namespace std;

struct Person
{
    int id = 0;
    string name = "", email = "";
    int makeGiftForId=-1;
};

string loadLine();
int convertStringToInt(string number);


Person loadPersonData(string dataForOnePersonInLineWithSpaces);
void loadPersonsFromFile(vector <Person> &persons);
void displayPersonData(Person person);

void giftDraw(int tableOfPersons[], int numberOfPersons);
void assigningDrawToPersons(vector <Person> &persons,int tableOfPersons[]);


int main()
{
    vector <Person> persons;
    loadPersonsFromFile(persons);
    int numbersOfPersons=persons.size();

    int tableOfPersons[numbersOfPersons];
    for (int i=0; i<numbersOfPersons; i++) tableOfPersons[i]=-2;
    giftDraw(tableOfPersons,numbersOfPersons);
    assigningDrawToPersons(persons,tableOfPersons);




    for (int i=0; i<numbersOfPersons; i++)
    {
        //tableOfPersons[i]=i;
        cout <<tableOfPersons[i] << " ";
    }
    cout << endl;


    auto iter= persons.begin();
    //displayPersonData(*(iter+0));

    for (vector <Person>::iterator  itr = persons.begin(); itr != persons.end(); itr++)
    {
            displayPersonData(*itr);
    }


    return 0;
}

string loadLine()
{
    string input = "";
    getline(cin, input);
    return input;
}

int convertStringToInt(string number)
{
    int numberInt;
    istringstream iss(number);
    iss >> numberInt;

    return numberInt;
}



void loadPersonsFromFile(vector <Person> &persons)
{
    Person person;
    string dataForOnePersonInLineWithSpaces = "";

    fstream textFile;
    textFile.open("PersonsData.txt", ios::in);
    int numberOfPerson=0;

    if (textFile.good() == true)
    {
        while (getline(textFile, dataForOnePersonInLineWithSpaces))
        {
            person = loadPersonData(dataForOnePersonInLineWithSpaces);
            numberOfPerson++;
            person.id=numberOfPerson;
            persons.push_back(person);
        }
    }
    textFile.close();
}

Person loadPersonData(string dataForOnePersonInLineWithSpaces)
{
    Person person;
    for (int positionOfCharakter = dataForOnePersonInLineWithSpaces.length()-1; positionOfCharakter > 0 ; positionOfCharakter--)
    {
        if (dataForOnePersonInLineWithSpaces[positionOfCharakter] == ' ')
        {
            person.name = dataForOnePersonInLineWithSpaces.substr(0,positionOfCharakter);
            person.email = dataForOnePersonInLineWithSpaces.substr(positionOfCharakter+1,dataForOnePersonInLineWithSpaces.length()-positionOfCharakter);
            break;
        }
    }
    return person;
}

void displayPersonData(Person person)
{
    cout << endl << "Id:               " << person.id << endl;
    cout <<         "Imie i nazwisko:  " << person.name << endl;
    cout <<         "Email:            " << person.email << endl;
    cout <<         "Robie prezent dla:" << person.makeGiftForId << endl;
}

void giftDraw(int* tableOfPersons, int numberOfPersons)
{
    srand(time(NULL));

    for (int i=0; i<numberOfPersons; i++)
    {
        tableOfPersons[i] = rand()%numberOfPersons;
        for (int j=0; j<numberOfPersons; j++)
        {
            if (tableOfPersons[i]==tableOfPersons[j]&&i!=j)
            {
                tableOfPersons[i] = rand()%numberOfPersons;
                j=-1;
            }
            else if (tableOfPersons[i]==i)
            {
                tableOfPersons[i] = rand()%numberOfPersons;
                j=-1;
            }
        }
    }
}

void assigningDrawToPersons(vector <Person> &persons,int* tableOfPersons)
{
    for (int i = 0; i < persons.size(); i++)
    {
        persons[i].makeGiftForId = tableOfPersons[i];
    }
}


