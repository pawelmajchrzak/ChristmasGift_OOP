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
    int id = -1;
    string name = "", email = "";
    int makeGiftForId=-1;
};

string loadLine();
int convertStringToInt(string number);


Person loadPersonData(string dataForOnePersonInLineWithSpaces);
void loadPersonsFromFile(vector <Person> &persons);

void giftDraw(int tableOfPersons[], int numberOfPersons);
void assigningDrawToPersons(vector <Person> &persons,int tableOfPersons[]);
void createOutputTextFileForPersons(vector <Person> persons);


int main()
{
    vector <Person> persons;
    loadPersonsFromFile(persons);
    int numbersOfPersons=persons.size();
    int tableOfPersons[numbersOfPersons];

    giftDraw(tableOfPersons,numbersOfPersons);
    assigningDrawToPersons(persons,tableOfPersons);
    createOutputTextFileForPersons(persons);

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
    int numberOfPerson=-1;

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

void giftDraw(int* tableOfPersons, int numberOfPersons)
{
    srand(time(NULL));
    do
    {
        for (int i=0; i<numberOfPersons; i++) tableOfPersons[i]=-2;

        for (int i=0; i<numberOfPersons; i++)
        {
            tableOfPersons[i] = rand()%numberOfPersons;
            for (int j=0; j<numberOfPersons; j++)
            {
                if ((tableOfPersons[i]==tableOfPersons[j]&&i!=j)||(tableOfPersons[i]==i&&tableOfPersons[numberOfPersons-1]!=numberOfPersons-1))
                {
                    tableOfPersons[i] = rand()%numberOfPersons;
                    j=-1;
                }
            }
        }
    }
    while (tableOfPersons[numberOfPersons-1]==numberOfPersons-1);
}

void assigningDrawToPersons(vector <Person> &persons,int* tableOfPersons)
{
    for (int i = 0; i < persons.size(); i++)
    {
        persons[i].makeGiftForId = tableOfPersons[i];
    }
}

void createOutputTextFileForPersons(vector <Person> persons)
{
    for (int i=0; i< persons.size(); i++)
    {
        fstream file;
        string fileName="WyslijDo"+persons[i].email+".txt";
        file.open(fileName,ios::out);
        file<< "Masz przygotowac prezent dla osoby: " << persons[persons[i].makeGiftForId].name << endl;
        file.close();
    }
    cout << "Wszystko sie udalo! Kazdy zaraz sie dowie komu robi prezent, musisz tylko powysylac maile!" << endl;
}

