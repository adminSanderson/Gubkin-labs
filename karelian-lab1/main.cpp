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

//void saveToFile(const Pipe& pipe, bool pipeExists,
//                const CompressorStation& station, bool stationExists) {
//   std::ofstream outFile("data.txt");
//    if (!outFile) {
//        std::cerr << "Error opening file for writing." << std::endl;
//        return;
//    }
//
//    if (pipeExists) {
//        outFile << "PIPE " << pipe.name << " " << pipe.length << " "
//                << pipe.diameter << " " << pipe.underRepair << std::endl;
//   }
//
//    if (stationExists) {
//        outFile << "STATION " << station.name << " " << station.workshopecount
//                << " " << station.workshopworkingcount
//                << " " << station.stationClass << std::endl;
//    }
//
 //   outFile.close();
//}

void savePipeToFile(const Pipe& pipe, bool pipeExists) {
    std::ofstream outfile("pipe.txt");
    if (!outfile) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    if (pipeExists) {
        outfile << "PIPE " << pipe.name << " " << pipe.length << " "
                << pipe.diameter << " " << pipe.underRepair << std::endl;
    }
    outfile.close();
}

void saveStationToFile(const CompressorStation& station, bool stationExists) {
    std::ofstream outfile("station.txt");
    if (!outfile) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    if (stationExists) {
        outfile << "STATION " << station.name << " " << station.workshopecount
                << " " << station.workshopworkingcount
                << " " << station.stationClass << std::endl;
    }
    outfile.close();
}

// void loadFromFile(Pipe& pipe, bool& pipeExists,
//                   CompressorStation& station, bool& stationExists) {
//     std::ifstream inFile("data.txt");
//     if (!inFile) {
//         std::cerr << "Error opening file for reading." << std::endl;
//         return;
//     }

//     pipeExists = false;
//     stationExists = false;

//     std::string tag;
//     while (inFile >> tag) {
//         if (tag == "PIPE") {
//             inFile >> pipe.name >> pipe.length >> pipe.diameter >> pipe.underRepair;
//             pipeExists = true;
//         } else if (tag == "STATION") {
//             inFile >> station.name >> station.workshopecount
//                    >> station.workshopworkingcount >> station.stationClass;
//             stationExists = true;
//         }
//     }

//     inFile.close();
// }

void loadPipeFromFile(Pipe& pipe, bool& pipeExists) {
    std::ifstream inFile("pipe.txt");
    if (!inFile) {
        std::cerr << "Error opening file for reading." << std::endl;
        return;
    }
    pipeExists = false;

    inFile >> pipe.name >> pipe.length >> pipe.diameter >> pipe.underRepair;
    pipeExists = true;

    inFile.close();
}

void loadStationFromFile(CompressorStation& station, bool& stationExists) {
    std::ifstream inFile("station.txt");
    if (!inFile) {
        std::cerr << "Error opening file for reading." << std::endl;
        return;
    }

    stationExists = false;

    inFile >> station.name >> station.workshopecount >> station.workshopworkingcount >> station.stationClass;
    stationExists = true;

    inFile.close();
}

void printMenu() {
    std::cout << "\n===== MENU =====\n";
    std::cout << "1 - Add pipe\n";
    std::cout << "2 - Add compressor station\n";
    std::cout << "3 - Show all objects\n";
    std::cout << "4 - Edit pipe (mark as under repair)\n";
    std::cout << "5 - Edit compressor station (stop all workshops)\n";
    std::cout << "6 - Save pipe to file\n";
    std::cout << "7 - Save compressor station to file\n";
    // std::cout << "8 - Load from file\n";
    std::cout << "8 - Load pipe from file\n";
    std::cout << "9 - Load station from file\n";
    std::cout << "0 - Exit\n";
    std::cout << "================\n";
    std::cout << "Your choice: ";
}

int main() {
    Pipe pipe;
    bool pipeExists = false;
    CompressorStation station;
    bool stationExists = false;

    std::cout << "Hello, user!" << std::endl;
    while (true) {
        printMenu();
        int input;
        std::cin >> input;

        if (input == 0) break;

        switch (input) {
            case 1: addPipe(pipe, pipeExists); break;
            case 2: addCompressorStation(station, stationExists); break;
            case 3: printAllObjects(pipe, pipeExists, station, stationExists); break;
            case 4: redactPipe(pipe, pipeExists); break;
            case 5: redactCompressorStation(station, stationExists); break;
            case 6: savePipeToFile(pipe, pipeExists); break;
            case 7: saveStationToFile(station, stationExists); break;
            // case 8: loadFromFile(pipe, pipeExists, station, stationExists); break;
            case 8: loadPipeFromFile(pipe, pipeExists); break;
            case 9: loadStationFromFile(station, stationExists); break;
            default: std::cout << "Invalid input\n";
        }
    }
}