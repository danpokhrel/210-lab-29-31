/*
Include necessary headers

Define necessary constants
struct Organism:
    >Age: positive integer
    >Hunger: positive integer *ignored for plants
Define function to iterate simulation by one day:
    >Parameter: reference to std::map variable

Define main function:
    Initialize a map to store data: map<int, array<list<Organism>, 3>>

    Open data file to define initial ecosystem conditions
    If failed to open file:
        print error msg and quit
    Close file

    Simulation:
    Call simulation function the same number of times as the desired time periods / simulation iterations
    Simulation Function:
        Loop through every organism:
            Iterate age by +1
            If age is over limit for that organism type than delete it
        For every organism type:
            Generate a random number between 0 and some % of the population of that organism type
            Randomly place those organisms on the map
        Loop through every prey:
            If there is a plant in the same location then eats it
            Else, the prey looses one hunger
        Loop through every predator:
            If there is prey in the same location then eats it
            Else, the predator looses one hunger
        Loop through every prey and predator:
            Random chance of moving to a random cell
            Random chance of dying if health <5
            Guaranteed death if health is 0
    
    End of main function
*/
// COMSC-210 | Lab 29-31 | Dan Pokhrel
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <array>
#include <list>
#include <vector>
using namespace std;

const int ITER = 25;
//               Predator, Prey, Plant
const int LIFESPAN[] = {10, 8, 15};
const string DATA_FILE = "data.txt";

struct Organism{
    int age;
    int hunger;
    Organism(int a) {age = a; hunger = -1;} // For plants only
    Organism(int a, int h) {age = a; hunger = h;}
};

void simulate(map<int, array<list<Organism>, 3>> &data);
void populateData(map<int, array<list<Organism>, 3>> &data);
void displayData(map<int, array<list<Organism>, 3>> &data);
vector<string> splitStrBy(string str, char delimiter);

int main(){
    map<int, array<list<Organism>, 3>> data;

    populateData(data);

    for (int i = 0; i < ITER; i++)
        simulate(data);
    
    displayData(data);

    return 0;
}

void simulate(map<int, array<list<Organism>, 3>> &data){
    for (auto it = data.begin(); it != data.end(); ++it)
    for (int i = 0; i < 3; i ++){ // Loop through all organisms
        list<Organism> &orgs = it->second[i];
        for (Organism &org : orgs){
            org.age++; // Age by one day
            
            if (org.age > LIFESPAN[i])
                orgs.remove(org); // Dies of old age
        }
    }
    for (int i = 0; i < 3; i++){
        // Reproduce
    }
    for (auto it = data.begin(); it != data.end(); ++it){
        list<Organism> &preys = it->second[1];
        for (Organism &prey : preys){
            // Eat
        }
    }
    for (auto it = data.begin(); it != data.end(); ++it){
        list<Organism> &predators = it->second[0];
        for (Organism &pred : predators){
            // Eat
        }
    }
    for (auto it = data.begin(); it != data.end(); ++it)
    for (int i = 0; i < 2; i ++){ // Loop through every prey and predator
        list<Organism> &orgs = it->second[i];
        for (Organism &org : orgs){
            // Do stuff
        }
    }
}

/* Data.txt format:
    (int) ID of cell
    Array of predators with elements separated by ','
        Each element is two integers separated by '|'
    Array of prey with elements separated by ','
        Each element is two integers separated by '|'
    Array of plants with elements separated by ','
        Each element is an integer for age
    (int) ID of cell
    ...
*/
void populateData(map<int, array<list<Organism>, 3>> &data){
    ifstream fin(DATA_FILE);
    if(!fin.is_open()){
        cout << "Unable to open file.";
        return;
    }

    while(fin.good()){
        // Read the next 4 lines
        string cellID; getline(fin, cellID);
        string str1; getline(fin, str1);
        string str2; getline(fin, str2);
        string str3; getline(fin, str3);

        // Convert lines into proper variables
        int id = stoi(cellID);
        vector<string> vec1 = splitStrBy(str1, ',');
        vector<string> vec2 = splitStrBy(str2, ',');
        vector<string> vec3 = splitStrBy(str3, ',');

        // Convert array elements into proper list objects
        list<Organism> orgs1, orgs2, orgs3;
        int age, hunger;
        for (auto str : vec1){
            auto pair = splitStrBy(str, '|');
            age = stoi(pair[0]); hunger = stoi(pair[1]);
            orgs1.push_back(Organism(age, hunger));
        }
        for (auto str : vec2){
            auto pair = splitStrBy(str, '|');
            age = stoi(pair[0]); hunger = stoi(pair[1]);
            orgs2.push_back(Organism(age, hunger));
        }
        for (auto str : vec3){
            age = stoi(str);
            orgs3.push_back(Organism(age));
        }

        // Populate data object
        data[id] = {orgs1, orgs2, orgs3};
    }
}

/* Region ID:
    1  2  3  4  5  6  7  8  9  10
    11 12 13 14 15 16 17 18 19 20
    21 22 23 24 25 26 27 28 29 30
    ...
*/
void displayData(map<int, array<list<Organism>, 3>> &data){
    cout << "------------------------------------------------------------------------------\n";
    for (int y = 1; y <= 10; y++){
        for (int x = 1; x <= 10; x++){ // Loop through each cell
            int id = (y-1)*10 + x; // cell id
            // Find number of predator,prey,plant in cell
            int predators = (data[id][0]).size();
            int prey = (data[id][1]).size();
            int plants = (data[id][2]).size();
            // Formatted output
            cout << left << predators << "," << prey << "," << setw(4) << plants;
        }
        cout << endl;
    }
    cout << "------------------------------------------------------------------------------\n";
}

vector<string> splitStrBy(string str, char delimiter){
    vector<string> splitStr;
    stringstream ss(str);
    string split;
    while(getline(ss, split, delimiter))
        splitStr.push_back(split);
    
    return splitStr;
}