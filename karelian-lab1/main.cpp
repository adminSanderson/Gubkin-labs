#include <fstream>
#include <iostream>
#include <string>
using namespace std; //мои хотелки :)

struct Pipe {
    string name;
    int length;
    int diameter;
    bool underRepair = false;
};

struct CompressorStation {
    string name;
    int workshopecount;
    int workshopworkingcount;
    int stationClass;
};

void addPipe(Pipe& pipe, bool& pipeExists) {
    if (pipeExists) {
        std::cout << "Pipe already exists. Only one pipe allowed.\n";
        return;
    }
    std::cout << "Enter pipe name: ";
    std::cin >> pipe.name;
    std::cout << "Enter pipe length: ";
    std::cin >> pipe.length;
    std::cout << "Enter pipe diameter: ";
    std::cin >> pipe.diameter;
    pipe.underRepair = false;
    pipeExists = true;
}

void addCompressorStation(CompressorStation& station, bool& stationExists) {
    if (stationExists) {
        std::cout << "Compressor station already exists. Only one allowed.\n";
        return;
    }
    std::cout << "Enter station name: ";
    std::cin >> station.name;
    std::cout << "Enter number of workshops: ";
    std::cin >> station.workshopecount;
    std::cout << "Enter number of working workshops: ";
    std::cin >> station.workshopworkingcount;
    std::cout << "Enter station class: ";
    std::cin >> station.stationClass;
    stationExists = true;
}

void printAllObjects(const Pipe& pipe, bool pipeExists,
                     const CompressorStation& station, bool stationExists) {
    std::cout << "Pipes:" << std::endl;
    if (pipeExists) {
        std::cout << "Name: " << pipe.name << ", Length: " << pipe.length
                  << ", Diameter: " << pipe.diameter
                  << ", Under Repair: " << (pipe.underRepair ? "Yes" : "No") << std::endl;
    }

    std::cout << "Compressor Stations:" << std::endl;
    if (stationExists) {
        std::cout << "Name: " << station.name
                  << ", Workshops: " << station.workshopecount
                  << ", Working Workshops: " << station.workshopworkingcount
                  << ", Class: " << station.stationClass << std::endl;
    }
}

void redactPipe(Pipe& pipe, bool pipeExists) {
    if (!pipeExists) {
        std::cout << "No pipe to redact.\n";
        return;
    }
    std::cout << "Enter the name of the pipe to redact: ";
    std::string name;
    std::cin >> name;

    if (pipe.name == name) {
        pipe.underRepair = true;
    } else {
        std::cout << "Pipe not found.\n";
    }
}

void redactCompressorStation(CompressorStation& station, bool stationExists) {
    if (!stationExists) {
        std::cout << "No compressor station to redact.\n";
        return;
    }
    std::cout << "Enter the name of the compressor station to redact: ";
    std::string name;
    std::cin >> name;

    if (station.name == name) {
        station.workshopworkingcount = 0;
    } else {
        std::cout << "Station not found.\n";
    }
}

void saveToFile(const Pipe& pipe, bool pipeExists,
                const CompressorStation& station, bool stationExists) {
    std::ofstream outFile("data.txt");
    if (!outFile) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    if (pipeExists) {
        outFile << "PIPE " << pipe.name << " " << pipe.length << " "
                << pipe.diameter << " " << pipe.underRepair << std::endl;
    }

    if (stationExists) {
        outFile << "STATION " << station.name << " " << station.workshopecount
                << " " << station.workshopworkingcount
                << " " << station.stationClass << std::endl;
    }

    outFile.close();
}

void loadFromFile(Pipe& pipe, bool& pipeExists,
                  CompressorStation& station, bool& stationExists) {
    std::ifstream inFile("data.txt");
    if (!inFile) {
        std::cerr << "Error opening file for reading." << std::endl;
        return;
    }

    pipeExists = false;
    stationExists = false;

    std::string tag;
    while (inFile >> tag) {
        if (tag == "PIPE") {
            inFile >> pipe.name >> pipe.length >> pipe.diameter >> pipe.underRepair;
            pipeExists = true;
        } else if (tag == "STATION") {
            inFile >> station.name >> station.workshopecount
                   >> station.workshopworkingcount >> station.stationClass;
            stationExists = true;
        }
    }

    inFile.close();
}

int main() {
    Pipe pipe;
    bool pipeExists = false;
    CompressorStation station;
    bool stationExists = false;

    std::cout << "Hello, user!" << std::endl;
    while (true) {
        std::cout << "Enter a number (or 0 to quit): ";
        int input;
        std::cin >> input;

        if (input == 0) break;

        switch (input) {
            case 1: addPipe(pipe, pipeExists); break;
            case 2: addCompressorStation(station, stationExists); break;
            case 3: printAllObjects(pipe, pipeExists, station, stationExists); break;
            case 4: redactPipe(pipe, pipeExists); break;
            case 5: redactCompressorStation(station, stationExists); break;
            case 6: saveToFile(pipe, pipeExists, station, stationExists); break;
            case 7: loadFromFile(pipe, pipeExists, station, stationExists); break;
            default: std::cout << "Invalid input\n";
        }
    }
}