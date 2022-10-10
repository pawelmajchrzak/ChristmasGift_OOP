#include <iostream>

using namespace std;

struct Person
{
    int id = 0;
    string name = "", email = "";
};

//string loadLine();
//Uzytkownik pobierzDaneUzytkownika(string daneJednegoUzytkownikaOddzielonePionowymiKreskami);
//void wczytajUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy);

void implementationPerson (vector <Person> &persons)
{

    Person person = setDataNewPerson(persons);
    persons.push_back(person);

}



int main()
{
    vector <Person> persons;
    int numbersOfPersons=setNumbersOfPersons();
    for (int i=0; i<numbersOfPersons; i++)
    {
        implementationPerson(persons);
    }


    return 0;
}
