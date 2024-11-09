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
#include <fstream>
#include <sstream>
#include <map>
#include <array>
#include <list>
#include <vector>
using namespace std;

const int ITER = 25;

struct Organism{
    int age;
    int hunger;
    Organism(int a) {age = a; hunger = -1;} // For plants only
    Organism(int a, int h) {age = a; hunger = h;}
};

void simulate(map<int, array<list<Organism>, 3>> &data);
void populateData(map<int, array<list<Organism>, 3>> &data);
vector<string> splitStrBy(string str, char delimiter);

int main(){
    map<int, array<list<Organism>, 3>> data;

    data[5] = {list<Organism>{Organism(2, 10), Organism(5, 3)},
               list<Organism>{Organism(1, 3), Organism(6, 7)},
               list<Organism>{Organism(7), Organism(10)}};
    
    string testStr1 = "a,b,2c,aSf,va3sfg,b_as,svesa";
    string testStr2 = "1|245|21|235|23536|232";

    return 0;
}

void simulate(map<int, array<list<Organism>, 3>> &data){
    for (auto it = data.begin(); it != data.end(); ++it)
    for (int i = 0; i < 3; i ++){ // Loop through all organisms
        list<Organism> &orgs = it->second[i];
        for (Organism &org : orgs){
            org.age++;
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

void populateData(map<int, array<list<Organism>, 3>> &data){

}

vector<string> splitStrBy(string str, char delimiter){

}