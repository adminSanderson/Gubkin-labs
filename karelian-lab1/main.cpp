#include <fstream>
#include <iostream>
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

void addPipe(Pipe& pipe, bool& pipeExists) {
    if (pipeExists) {
        cout << "Pipe already exists. Only one pipe allowed.\n";
        return;
    }

    cout << "Enter pipe name: ";
    getline(cin >> ws, pipe.name);

    cout << "Enter pipe length: ";
    cin >> pipe.length;

    cout << "Enter pipe diameter: ";
    cin >> pipe.diameter;

    pipe.underRepair = false;
    pipeExists = true;
}

void addCompressorStation(CompressorStation& station, bool& stationExists) {
    if (stationExists) {
        cout << "Compressor station already exists. Only one allowed.\n";
        return;
    }

    cout << "Enter station name: ";
    getline(cin >> ws, station.name);

    cout << "Enter number of workshops: ";
    cin >> station.workshopecount;

    cout << "Enter number of working workshops: ";
    cin >> station.workshopworkingcount;

    cout << "Enter station class: ";
    cin >> station.stationClass;

    stationExists = true;
}

void printPipe(const Pipe& pipe, bool pipeExists) {
    if (!pipeExists) {
        cout << "No pipe exists.\n";
        return;
    }

    cout << "Name: " << pipe.name
         << ", Length: " << pipe.length
         << ", Diameter: " << pipe.diameter
         << ", Under Repair: " << (pipe.underRepair ? "Yes" : "No")
         << endl;
}

void printCS(const CompressorStation& station, bool stationExists) {
    if (!stationExists) {
        cout << "No compressor station exists.\n";
        return;
    }

    cout << "Name: " << station.name
         << ", Workshops: " << station.workshopecount
         << ", Working Workshops: " << station.workshopworkingcount
         << ", Class: " << station.stationClass
         << endl;
}

void redactPipe(Pipe& pipe, bool pipeExists) {
    if (!pipeExists) {
        cout << "No pipe to redact.\n";
        return;
    }

    cout << "Enter the name of the pipe to redact: ";
    string name;
    getline(cin >> ws, name);

    if (pipe.name == name) {
        pipe.underRepair = true;
    }
    else {
        cout << "Pipe not found.\n";
    }
}

void redactCompressorStation(CompressorStation& station, bool stationExists) {
    if (!stationExists) {
        cout << "No compressor station to redact.\n";
        return;
    }

    cout << "Enter the name of the compressor station to redact: ";
    string name;
    getline(cin >> ws, name);

    if (station.name == name) {
        station.workshopworkingcount = 0;
    }
    else {
        cout << "Station not found.\n";
    }
}

void savePipe(ofstream& file, Pipe pipe) {
    file << pipe.name << '\n';
    file << pipe.length << '\n';
    file << pipe.diameter << '\n';
    file << pipe.underRepair << '\n';
}

void saveCS(ofstream& file, CompressorStation station) {
    file << station.name << '\n';
    file << station.workshopecount << '\n';
    file << station.workshopworkingcount << '\n';
    file << station.stationClass << '\n';
}

void saveData(Pipe pipe, bool pipeExists,
              CompressorStation station, bool stationExists) {
    if (!pipeExists && !stationExists) {
        cout << "Nothing to save.\n";
        return;
    }

    ofstream file("data.txt");

    if (!file) {
        cout << "Cannot open data.txt.\n";
        return;
    }

    file << pipeExists << '\n';

    if (pipeExists) {
        savePipe(file, pipe);
    }

    file << stationExists << '\n';

    if (stationExists) {
        saveCS(file, station);
    }

    file.close();
    cout << "\nData saved.\n";
}

void savePipeToFile(Pipe pipe, bool pipeExists,
                    CompressorStation station, bool stationExists) {
    if (!pipeExists) {
        cout << "No pipe to save.\n";
        return;
    }

    saveData(pipe, pipeExists, station, stationExists);
}

void saveStationToFile(Pipe pipe, bool pipeExists,
                       CompressorStation station, bool stationExists) {
    if (!stationExists) {
        cout << "No station to save.\n";
        return;
    }

    saveData(pipe, pipeExists, station, stationExists);
}

// Загрузка данных

bool loadPipe(ifstream& file, Pipe& pipe) {
    int repair;

    if (!getline(file, pipe.name) ||
        !(file >> pipe.length >> pipe.diameter >> repair))
        return false;

    file.ignore(10000, '\n');

    if (pipe.name.empty() ||
        pipe.length <= 0 ||
        pipe.diameter <= 0 ||
        (repair != 0 && repair != 1))
        return false;

    pipe.underRepair = repair;
    return true;
}

bool loadCS(ifstream& file, CompressorStation& station) {
    if (!getline(file, station.name) ||
        !(file >> station.workshopecount
               >> station.workshopworkingcount
               >> station.stationClass))
        return false;

    if (station.name.empty() ||
        station.workshopecount <= 0 ||
        station.workshopworkingcount < 0 ||
        station.workshopworkingcount > station.workshopecount ||
        station.stationClass < 0)
        return false;

    file.ignore(10000, '\n');
    return true;
}

void loadData(Pipe& pipe, bool& pipeExists,
              CompressorStation& station, bool& stationExists) {
    ifstream file("data.txt");

    if (!file) {
        cout << "data.txt not found.\n";
        return;
    }

    int hasPipe, hasStation;

    if (!(file >> hasPipe) || (hasPipe != 0 && hasPipe != 1)) {
        cout << "Invalid file.\n";
        return;
    }

    file.ignore(10000, '\n');

    Pipe tempPipe;
    CompressorStation tempStation;

    if (hasPipe && !loadPipe(file, tempPipe)) {
        cout << "Invalid pipe data.\n";
        return;
    }

    if (!(file >> hasStation) || (hasStation != 0 && hasStation != 1)) {
        cout << "Invalid file.\n";
        return;
    }

    file.ignore(10000, '\n');

    if (hasStation && !loadCS(file, tempStation)) {
        cout << "Invalid station data.\n";
        return;
    }

    pipe = tempPipe;
    station = tempStation;

    pipeExists = (hasPipe == 1);
    stationExists = (hasStation == 1);

    cout << "\nData loaded.\n";
}

void loadPipeFromFile(Pipe& pipe, bool& pipeExists) {
    CompressorStation station;
    bool stationExists = false;

    ifstream file("data.txt");

    if (!file) {
        cout << "data.txt not found.\n";
        return;
    }

    file.close();

    loadData(pipe, pipeExists, station, stationExists);
}

void loadStationFromFile(CompressorStation& station, bool& stationExists) {
    Pipe pipe;
    bool pipeExists = false;

    ifstream file("data.txt");

    if (!file) {
        cout << "data.txt not found.\n";
        return;
    }

    file.close();

    loadData(pipe, pipeExists, station, stationExists);
}

void printMenu() {
    cout << "\n===== MENU =====\n";
    cout << "1 - Add pipe\n";
    cout << "2 - Add compressor station\n";
    cout << "3 - Show pipe\n";
    cout << "4 - Show compressor station\n";
    cout << "5 - Edit pipe (mark as under repair)\n";
    cout << "6 - Edit compressor station (stop all workshops)\n";
    cout << "7 - Save pipe to file\n";
    cout << "8 - Save compressor station to file\n";
    cout << "9 - Load pipe from file\n";
    cout << "10 - Load station from file\n";
    cout << "0 - Exit\n";
    cout << "================\n";
    cout << "Your choice: ";
}

int main() {
    Pipe pipe;
    bool pipeExists = false;

    CompressorStation station;
    bool stationExists = false;

    cout << "Hello, user!" << endl;

    while (true) {
        printMenu();

        int input;
        cin >> input;

        if (input == 0) break;

        switch (input) {
            case 1: addPipe(pipe, pipeExists); break;
            case 2: addCompressorStation(station, stationExists); break;
            case 3: printPipe(pipe, pipeExists); break;
            case 4: printCS(station, stationExists); break;
            case 5: redactPipe(pipe, pipeExists); break;
            case 6: redactCompressorStation(station, stationExists); break;
            case 7: savePipeToFile(pipe, pipeExists, station, stationExists); break;
            case 8: saveStationToFile(pipe, pipeExists, station, stationExists); break;
            case 9: loadPipeFromFile(pipe, pipeExists); break;
            case 10: loadStationFromFile(station, stationExists); break;
            default: cout << "Invalid input\n";
        }
    }

    return 0;
}
