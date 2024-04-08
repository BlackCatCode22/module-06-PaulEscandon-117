#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <ctime>
#include <iomanip>

using namespace std;

class Animal {
public:
    Animal(string species, string name, int age, string sex, string color, double weight, string birthSeason, time_t arrivalDate)
        : species(species), name(name), age(age), sex(sex), color(color), weight(weight), birthSeason(birthSeason), arrivalDate(arrivalDate) {}

    string getSpecies() const { return species; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getSex() const { return sex; }
    string getColor() const { return color; }
    double getWeight() const { return weight; }
    string getBirthSeason() const { return birthSeason; }
    time_t getArrivalDate() const { return arrivalDate; }

private:
    string species;
    string name;
    int age;
    string sex;
    string color;
    double weight;
    string birthSeason;
    time_t arrivalDate;
};

string generateUniqueID(const string& species, int& counter) {
    return species.substr(0, 2) + to_string(counter++);
}

time_t generateBirthday(const string& birthSeason) {
    // Logic to generate birthday from birth season
    // Assuming current date as the birthdate for simplicity
    return time(nullptr);
}

void readAnimals(const string& fileName, vector<Animal>& animals) {
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file " << fileName << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        // Parse each line and create Animal objects
        stringstream ss(line);
        string species, name, sex, color, birthSeason;
        int age;
        double weight;
        ss >> age >> name >> sex >> species;
        getline(ss, birthSeason, ',');
        getline(ss, color, ',');
        ss.ignore(1); // Ignore the space after color
        ss >> weight;

        time_t arrivalDate = time(nullptr); // Placeholder, use current time
        animals.emplace_back(species, name, age, sex, color, weight, birthSeason, arrivalDate);
    }

    inputFile.close();
}

map<string, string> readAnimalNames(const string& fileName) {
    map<string, string> animalNames;
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file " << fileName << endl;
        return animalNames;
    }

    string species, name;
    while (inputFile >> species >> name) {
        animalNames[species] = name;
    }

    inputFile.close();
    return animalNames;
}

void assignNamesToAnimals(vector<Animal>& animals, const map<string, string>& animalNames) {
    int counter = 1;
    for (auto& animal : animals) {
        string species = animal.getSpecies();
        if (animalNames.find(species) != animalNames.end()) {
            animalNames.at(species);
        }
        string uniqueID = generateUniqueID(species, counter);
        // Assign unique ID to animal
        // For now, let's just print the unique ID
        cout << "Assigned unique ID to " << animal.getName() << ": " << uniqueID << endl;
    }
}

void organizeAnimals(vector<Animal>& animals) {
    // Organize animals into their habitats
    // Let's just print a message
    cout << "Organizing animals into habitats..." << endl;
}

void generatePopulationReport(const vector<Animal>& animals, const string& fileName) {
    ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open file " << fileName << " for writing." << endl;
        return;
    }

    outputFile << "Zoo Population Report:" << endl;
    for (const auto& animal : animals) {
        time_t arrivalTime = animal.getArrivalDate();
        struct tm* arrivalDate = localtime(&arrivalTime);
        outputFile << "Species: " << animal.getSpecies() << ", Name: " << animal.getName()
                   << ", Age: " << animal.getAge() << ", Sex: " << animal.getSex()
                   << ", Color: " << animal.getColor() << ", Weight: " << animal.getWeight()
                   << " pounds" << ", Birth Season: " << animal.getBirthSeason()
                   << ", Arrival Date: " << put_time(arrivalDate, "%Y-%m-%d") << endl;
    }

    outputFile.close();
}

int main() {
    vector<Animal> animals;
    readAnimals("arrivingAnimals.txt", animals);

    map<string, string> animalNames = readAnimalNames("animalNames.txt");
    assignNamesToAnimals(animals, animalNames);

    organizeAnimals(animals);

    generatePopulationReport(animals, "zooPopulation.txt");

    return 0;
}
