#include "pch.h"
#include "Dll.h"

void ManageTimer(TimerAction action) {
    if (action == TIMER_START) {
        if (!timer_running) {
            start_time = GetTickCount64();
            timer_running = true;
            cout << "Pradetas matuoti programos veikimo laikas." <<endl;
        }
    }
    else if (action == TIMER_END) {
        if (timer_running) {
            end_time = GetTickCount64();
            timer_running = false;
            cout << "Baigtas matuoti programos veikimo laikas." << endl;
        }
    }
}
double GetElapsedTime() {
    if (timer_running) {
        return static_cast<double>(GetTickCount64() - start_time) / 1000.0; 
    }
    else {
        return static_cast<double>(end_time - start_time) / 1000.0; 
    }
}

void modifyUserTime(const std::string& username, const std::string& days, const std::string& timeInterval) {
    // command eilute
    std::string command = "net user " + username + " /time:" + days + "," + timeInterval;
    // iskvieciama eilute
    system(command.c_str());
    cout << "Laikas naudotojui apribotas" << endl;
}

void createDirectoriesAndFiles(const string& name, const string& surname) {
    cout << "Kuriami failai pagal varda ir pavarde." << endl;
    // Sukuriamas pagrindinis aplankalas pagal pavardę
    string mainDirCommand = "mkdir " + surname;
    system(mainDirCommand.c_str());

    // Sukuriami trys aplankalai pagrindiniame aplankale
    for (int i = 1; i <= 3; ++i) {
        string subDirCommand = "mkdir " + surname + "\\" + name + to_string(i);
        system(subDirCommand.c_str());

        // Sukuriami trys aplankalai kiekviename iš praeitu"
        for (int j = 1; j <= 3; ++j) {
            string subSubDirCommand = "mkdir " + surname + "\\" + name + to_string(i) + "\\" + name + to_string(i) + name + to_string(j);
            system(subSubDirCommand.c_str());
        }
    }

    // Sukuriami .txt failai kiekviename aplankale
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            string createFileCommand = "echo. > " + surname + "\\" + name + to_string(i) + "\\" + name + to_string(i) + name + to_string(j) + "\\" + name + "Failas" + to_string(i) + to_string(j) + ".txt";

            system(createFileCommand.c_str());
        }
    }
    cout << "Failai sukurti."<<endl;
}

// Funkcija, kuri įrašo rezultatus į failą
void writeToFile(const string& filename, double x, double y) {
 
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << x << " " << y << endl;
        file.close();

    }
    else {
        cout << "Nepavyko atidaryti failo " << filename << endl;
    }
}

// Funkcija kuri skaičiuoja Tšrinhauseno kilpa ir cikliškai įrašo duomenis į failus
void calculateAndWriteData(double F, double x0, double xn, double dx) {
    cout << "Skaiciuojama Tsrinhauseno kilpa pagal F = " << F << endl;
    double x = x0;
    int i = 1; 
    int j = 1; 
    while (x <= xn) {
        double y = sqrt(pow(x, 3) + 3 * pow(x, 2) - F);

        // jeigu Tšrinhauseno kilpa egzistuoja
        if (!isnan(y)) {
            // failo pavadinimas
            std::string filename = surname + "\\" + name + std::to_string(i) + "\\" +
                name + std::to_string(i) + name + std::to_string(j) + "\\" +
                name + "Failas" + std::to_string(i) + std::to_string(j) + ".txt";

            // irasymas
            writeToFile(filename, x, y);
            if (j % 3 == 0) {
                j = 1;
                i = (i % 3) + 1; 
            }
            else {
                j++;
            }
        }
        // pajudama pagal x
        x += dx;
    }
}


// tasku nuskaitymui
Point* readPointsFromFile(const string& filename, int& numPoints) {
    ifstream file(filename);
    Point* points = nullptr;

    if (file.is_open()) {
        numPoints = 0;
        double x, y;
        while (file >> x >> y) {
            numPoints++;
        }
        points = new Point[numPoints];
        file.clear();
        file.seekg(0, ios::beg);
        for (int i = 0; i < numPoints; ++i) {
            file >> points[i].x >> points[i].y;
        }

        file.close();
    }
    else {
        cout << "Nepavyko atidaryti failo " << filename << endl;
    }
    return points;
}

// Funkcija skirta įrašyti taškus į failą
void writePointsToFile(const std::string& filename, const Point* points, int numPoints) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < numPoints; ++i) {
            file << "X: " << points[i].x << ", Y: " << points[i].y << std::endl;
        }
        file.close();
        std::cout << "Taskai irasyti i faila: " << filename << std::endl;
    }
    else {
        std::cerr << "Neatidarytas failas: " << filename << std::endl;
    }
}

bool customPointSort(const Point& a, const Point& b) {
    return a.x < b.x;
}

void customSort(std::vector<Point>& arr) {
    std::sort(arr.begin(), arr.end(), customPointSort);
}
void mergeAndSortFiles(const string& rootDir, const string& outputFilePrefix) {
    vector<Point> allPoints; 

    // einama per failus
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            std::string filename = surname + "\\" + name + std::to_string(i) + "\\" +
                name + std::to_string(i) + name + std::to_string(j) + "\\" +
                name + "Failas" + std::to_string(i) + std::to_string(j) + ".txt";
            int numPoints;
           
            Point* points = readPointsFromFile(filename, numPoints);
           
            if (points) {
                allPoints.insert(allPoints.end(), points, points + numPoints);
                delete[] points;
            }
            // isvalomi praeiti x ir y is failu
            std::ofstream ofs(filename, std::ios::out | std::ios::trunc);
            ofs.close(); 
        }
    }
    
    if (!allPoints.empty()) {
        customSort(allPoints);
        // gaunamas sakninis folderis
        TCHAR mod[MAX_PATH];
        GetModuleFileName(NULL, mod, MAX_PATH);
        wstring rootDirectory(mod);
        size_t lastSlashIndex = rootDirectory.find_last_of(L"\\/");
        if (lastSlashIndex != wstring::npos) {
            rootDirectory = rootDirectory.substr(0, lastSlashIndex);
        }
        string narrowRootDirectory(rootDirectory.begin(), rootDirectory.end());
        string outputPath = narrowRootDirectory + "\\" + outputFilePrefix;
        writePointsToFile(outputFilePrefix, allPoints.data(), allPoints.size());
    }
}

// Funkcija skirta ištrinti sukurtus aplankalus
void deleteDirectories(const string& name, const string& surname) {
    string mainDir = surname;
    string removeDirCommand = "rmdir /s /q " + mainDir;
    int result = system(removeDirCommand.c_str());
    if (result == 0) {
        cout << "Istrintas aplankalas: " << mainDir << endl;
    }
    else {
        cout << "Nepavyko istrinti aplankalo: " << mainDir << endl;
    }
}