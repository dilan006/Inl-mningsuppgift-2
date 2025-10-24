#include <iostream>     // För cout och cin
#include <utility>
#include <vector>       // För att lagra flera mätvärden i en lista
#include <string>       // För att hantera text
#include <fstream>      // För att läsa och skriva till filer
#include <algorithm>    // För sortering och andra algoritmer
#include <cmath>        // För matematiska funktioner
using namespace std;    // Gör att vi slipper skriva "std::"

// En struktur som håller ett enda mätvärde och dess tidsstämpel
struct Measurement {
    float value;
    string timestamp;
};

// ===== Klass för att hantera mätdata =====
// Klassen ansvarar för att spara, läsa, sortera, visa och räkna statistik
class DataManager {
private:
    vector<Measurement> data;   // Lista som lagrar alla mätningar
    string filename;            // Namnet på filen där data sparas

public:
    explicit DataManager(string  file) : filename(std::move(file)) {
        loadFromFile();
    }

    // === Lägg till nytt mätvärde ===
    void addMeasurement(float value, const string& time) {
        data.push_back({value, time}); // Lägger till ett nytt värde med tidsstämpel i listan
    }

    // === Visa alla mätvärden ===
    void showAll() const {
        if (data.empty()) {  // Kolla om listan är tom
            cout << "Listan är tom.\n";
            return;
        }

        cout << "\n--- Mätdata ---\n";
        // Loopar igenom listan och skriver ut varje mätvärde
        for (size_t i = 0; i < data.size(); ++i)
            cout << i + 1 << ". " << data[i].timestamp << "  " << data[i].value << "\n";
    }

    // === Sortera listan ===
    void sortList(bool ascending) {
        if (ascending)
            ranges::sort(data.begin(), data.end(), [](auto& a, auto& b){ return a.value < b.value; });
        else
            ranges::sort(data.begin(), data.end(), [](auto& a, auto& b){ return a.value > b.value; });

        cout << "Listan sorterad " << (ascending ? "stigande" : "fallande") << ".\n";
    }

    // === Visa statistik (antal, medel, min, max, standardavvikelse) ===
    void showStats() const {
        if (data.empty()) {
            cout << "Ingen data att visa.\n";
            return;
        }

        // Startvärden
        float sum = 0, minVal = data[0].value, maxVal = data[0].value;

        for (auto& m : data) {
            sum += m.value;
            if (m.value < minVal) minVal = m.value;
            if (m.value > maxVal) maxVal = m.value;
        }

        // Beräkna medelvärde
        float mean = sum / data.size();

        float var = 0;
        for (auto& m : data)
            var += pow(m.value - mean, 2);
        var /= data.size();

        // Skriv ut statistiken
        cout << "\n--- Statistik ---\n";
        cout << "Antal värden: " << data.size() << "\n";
        cout << "Medelvärde: " << mean << "\n";
        cout << "Min: " << minVal << "\n";
        cout << "Max: " << maxVal << "\n";
        cout << "Standardavvikelse: " << sqrt(var) << "\n";
    }

    // === Ta bort ett värde ===
    void removeValue(int index) {
        if (index < 1 || index > static_cast<int>(data.size())) {
            cout << "Ogiltigt val.\n";
            return;
        }
        data.erase(data.begin() + index - 1);
        cout << "Värde borttaget.\n";
    }

    // === Läs in data från fil ===
    void loadFromFile() {
        ifstream file(filename);  // Försök öppna filen
        if (!file.is_open()) {    // Om den inte finns
            cout << "Ingen tidigare data hittades.\n";
            return;
        }

        string time;
        float val;

        // Läs varje rad i formatet: tidsstämpel, värde
        while (file >> ws && getline(file, time, ',') && file >> val)
            data.push_back({val, time});

        cout << "Data inläst (" << data.size() << " värden).\n";
    }

    // === Spara data till fil ===
    void saveToFile() const {
        ofstream file(filename);
        for (auto& m : data)
            file << m.timestamp << "," << m.value << "\n";
        cout << "Data sparad till " << filename << ".\n";
    }
};

string currentTime() {
    time_t now = time(nullptr);          // Hämtar nuvarande tid
    tm* t = localtime(&now);             // Gör om till lokal tid
    char buf[20];                        // Skapar en char-array för tidsträngen
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", t); // Formaterar tiden
    return buf;                          // Returnerar som sträng
}

// ===== Huvudprogram =====
int main() {
    DataManager manager("data.csv"); // Skapar en DataManager som automatiskt läser in filen
    int val;                         // Variabel för menyval
    bool asc = true;                 // Variabel för sorteringsriktning (true = stigande)

    do {
        // Skriver ut meny
        cout << "\n--- MENY ---\n";
        cout << "1. Lägg till mätvärde\n";
        cout << "2. Visa alla\n";
        cout << "3. Sortera\n";
        cout << "4. Visa statistik\n";
        cout << "5. Ta bort värde\n";
        cout << "6. Avsluta\n";
        cout << "Val: ";
        cin >> val;

        if (!cin) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Felaktig inmatning!\n";
            continue;
        }

        // === Menyval ===
        switch (val) {
            case 1: {
                cout << "Skriv in mätvärden (skriv 'q' för att avsluta):\n";
                string input;
                while (true) {
                    cout << "Värde: ";
                    cin >> input;
                    if (input == "q" || input == "x")
                        break;

                    try {
                        float v = stof(input);
                        manager.addMeasurement(v, currentTime());
                    } catch (...) {
                        cout << "Ogiltig inmatning, försök igen.\n";
                        cin.clear();
                    }
                }
                break;
            }

            case 2: // Visa alla värden
                manager.showAll();
                break;

            case 3: // Sortera listan
                cout << "1 = stigande, 0 = fallande: ";
                cin >> asc;
                manager.sortList(asc);
                break;

            case 4: // Visa statistik
                manager.showStats();
                break;

            case 5: { // Ta bort ett värde
                manager.showAll();
                int index;
                cout << "Vilket nummer vill du ta bort? ";
                cin >> index;
                manager.removeValue(index);
                break;
            }

            case 6: // Avsluta programmet
                cout << "Sparar och avslutar...\n";
                manager.saveToFile(); // Spara alla värden till fil
                break;

            default: // Ogiltigt menyval
                cout << "Ogiltigt val.\n";
        }

    } while (val != 6); // Loopen körs tills användaren väljer 6 (avsluta)

    return 0; // Programmet avslutas
}