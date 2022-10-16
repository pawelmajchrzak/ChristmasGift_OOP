#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct Person
{
    int id = 0;
    string name = "", email = "";
};

string loadLine();
int convertStringToInt(string number);


Person loadPersonData(string dataForOnePersonInLineWithSpaces);
void loadPersonsFromFile(vector <Person> &persons);
void displayPersonData(Person person);



int main()
{
    vector <Person> persons;
    loadPersonsFromFile(persons);
    int numbersOfPersons=persons.size();

    cout << numbersOfPersons<< endl;

    //vector <Person>::iterator  iter = persons.begin();
    auto iter= persons.begin();
    //iter-=2;
    displayPersonData(*(iter+0));

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
}
