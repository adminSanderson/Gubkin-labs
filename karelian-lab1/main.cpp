#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

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

void addPipe(Pipe* pipes, int& pipeCount) {
    std::cout << "Enter pipe name: ";
    std::cin >> pipes[pipeCount].name;
    std::cout << "Enter pipe length: ";
    std::cin >> pipes[pipeCount].length;
    std::cout << "Enter pipe diameter: ";
    std::cin >> pipes[pipeCount].diameter;
    pipes[pipeCount].underRepair = false;
    pipeCount++;
}

void addCompressorStation(CompressorStation* stations, int& stationCount) {
    std::cout << "Enter station name: ";
    std::cin >> stations[stationCount].name;
    std::cout << "Enter number of workshops: ";
    std::cin >> stations[stationCount].workshopecount;
    std::cout << "Enter number of working workshops: ";
    std::cin >> stations[stationCount].workshopworkingcount;
    std::cout << "Enter station class: ";
    std::cin >> stations[stationCount].stationClass;
    stationCount++;
}

void printAllObjects(Pipe* pipes, int pipeCount, CompressorStation* stations, int stationCount) {
    std::cout << "Pipes:" << std::endl;
    for (int i = 0; i < pipeCount; i++) {
        std::cout << "Name: " << pipes[i].name << ", Length: " << pipes[i].length
                  << ", Diameter: " << pipes[i].diameter
                  << ", Under Repair: " << (pipes[i].underRepair ? "Yes" : "No") << std::endl;
    }

    std::cout << "Compressor Stations:" << std::endl;
    for (int i = 0; i < stationCount; i++) {
        std::cout << "Name: " << stations[i].name
                  << ", Workshops: " << stations[i].workshopecount
                  << ", Working Workshops: " << stations[i].workshopworkingcount
                  << ", Class: " << stations[i].stationClass << std::endl;
    }
}

void redactPipe(Pipe* pipes, int pipeCount) {
    std::cout << "Enter the name of the pipe to redact: ";
    std::string name;
    std::cin >> name;

    for (int i = 0; i < pipeCount; i++) {
        if (pipes[i].name == name) {
            pipes[i].underRepair = true;
            break;
        }
    }
}

void redactCompressorStation(CompressorStation* stations, int stationCount) {
    std::cout << "Enter the name of the compressor station to redact: ";
    std::string name;
    std::cin >> name;

    for (int i = 0; i < stationCount; i++) {
        if (stations[i].name == name) {
            stations[i].workshopworkingcount = 0;
            break;
        }
    }
}


void saveToFile(Pipe* pipes, int pipeCount, CompressorStation* stations, int stationCount) {
    std::ofstream outFile("data.txt");
    if (!outFile) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    outFile << "Pipes:" << std::endl;
    for (int i = 0; i < pipeCount; i++) {
        outFile << pipes[i].name << " " << pipes[i].length << " "
                << pipes[i].diameter << " " << pipes[i].underRepair << std::endl;
    }

    outFile << "Compressor Stations:" << std::endl;
    for (int i = 0; i < stationCount; i++) {
        outFile << stations[i].name << " " << stations[i].workshopecount
                << " " << stations[i].workshopworkingcount
                << " " << stations[i].stationClass << std::endl;
    }

    outFile.close();
}

void loadFromFile(Pipe* pipes, int& pipeCount, CompressorStation* stations, int& stationCount) {
    std::ifstream inFile("data.txt");
    if (!inFile) {
        std::cerr << "Error opening file for reading." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (line == "Pipes:") {
            while (std::getline(inFile, line) && !line.empty()) {
                std::istringstream iss(line);
                iss >> pipes[pipeCount].name >> pipes[pipeCount].length
                    >> pipes[pipeCount].diameter >> pipes[pipeCount].underRepair;
                pipeCount++;
            }
        } else if (line == "Compressor Stations:") {
            while (std::getline(inFile, line) && !line.empty()) {
                std::istringstream iss(line);
                iss >> stations[stationCount].name >> stations[stationCount].workshopecount
                    >> stations[stationCount].workshopworkingcount
                    >> stations[stationCount].stationClass;
                stationCount++;
            }
        }
    }

    inFile.close();
}

int main() {
    std::cout << "Hello, user!" << std::endl;
    while (true) {
        std::cout << "Enter a number (or 0 to quit): ";
        int input;
        std::cin >> input;

        if (input == 0) {
            break;
        }

        switch (input) {
            case 1: {
                Pipe pipes[100];
                int pipeCount = 0;
                addPipe(pipes, pipeCount);
                break;
            }
            case 2: {
                CompressorStation stations[100];
                int stationCount = 0;
                addCompressorStation(stations, stationCount);
                break;
            }
            case 3: {
                Pipe pipes[100];
                int pipeCount = 0;
                CompressorStation stations[100];
                int stationCount = 0;
                printAllObjects(pipes, pipeCount, stations, stationCount);
                break;
            }
            case 4: {
                Pipe pipes[100];
                int pipeCount = 0;
                redactPipe(pipes, pipeCount);
                break;
            }
            case 5: {
                CompressorStation stations[100];
                int stationCount = 0;
                redactCompressorStation(stations, stationCount);
                break;
            }
            case 6: {
                Pipe pipes[100];
                int pipeCount = 0;
                CompressorStation stations[100];
                int stationCount = 0;
                saveToFile(pipes, pipeCount, stations, stationCount);
                break;
            }
            case 7: {
                Pipe pipes[100];
                int pipeCount = 0;
                CompressorStation stations[100];
                int stationCount = 0;
                loadFromFile(pipes, pipeCount, stations, stationCount);
                break;
            }
            default:
                std::cout << "Invalid input. Please try again." << std::endl;
        }


    }
}