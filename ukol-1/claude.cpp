#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <set>

using namespace std;

struct konfigurace{
    string funkce;
    string hodnota;
};

struct parametry{
    vector <int> poleCisel;
    vector <int> pocetCisel;
    int pocetRadku;
    int maxDelka;
};

konfigurace* najdiConfig(vector<konfigurace>& poleKonfiguraci, const string& nazev){
    for (auto& k : poleKonfiguraci)
        if (k.funkce == nazev) return &k;
    return nullptr;
}

void deliciRada(int sirka, int pocetSloupcu, int zahlavi){
    for (int i = zahlavi; i <= pocetSloupcu; i++){
        cout << "+";
        for (int h = 0; h < (sirka+2); h++){
            cout << "-";
        }
    }
    cout << "+" << endl;
}

void prvniRadek(int sirka, int pocetSloupcu, string zarovnani, int zahlavi){
    deliciRada (sirka, pocetSloupcu, zahlavi);
    for (int i = 0; i <= pocetSloupcu; i++){
        cout << "| ";
        if (zarovnani == "left"){
            if (i == 0){
                cout << left << setw(sirka+1);
            } else {
                cout << left << setw(sirka) << char(64 + i);
            }
        } else {
            if (i == 0){
                cout << right << setw(sirka+1);
            } else {
                cout << right << setw(sirka) << char(64 + i);
            }
        }
        cout << " ";   
    }
    cout << "|" << endl;
}

void printTable(int sirka, int pocetSloupcu, string zarovnani, vector <int> pocetCisel, vector <int> poleCisel, int vyhashtagovat, vector <konfigurace> poleKonfiguraci){

    int zahlavi = 0;

    konfigurace* headerConfig = najdiConfig(poleKonfiguraci, "header");
    if (headerConfig != nullptr && stoi(headerConfig->hodnota) == 0){
        zahlavi = 1;
    }

    if (zahlavi == 0){
        prvniRadek(sirka, pocetSloupcu, zarovnani, zahlavi);
    }
    
    int pocetRadku = pocetCisel.size();

    for (int z = 0; z < pocetRadku; z++){
        deliciRada (sirka, pocetSloupcu, zahlavi);

        int rowOffset = 0;
        for (int r = 0; r < z; r++) rowOffset += pocetCisel[r];

        for (int i = zahlavi; i <= pocetSloupcu; i++){
            cout << "| ";
            if (zarovnani == "left"){
                if (i == 0){
                    cout << left << setw(sirka) << z + 1;
                } else if (i <= pocetCisel[z] && i > 0){
                    int something = to_string(poleCisel[rowOffset + (i - 1)]).size();
                    if (vyhashtagovat == 1 && something > sirka){
                        for (int g = 0; g < sirka; g++){
                            cout << "#";
                        }
                    } else {
                        cout << left << setw(sirka) << poleCisel[rowOffset + (i - 1)];
                    }
                } else if (zahlavi == 0){
                    cout << left << setw(sirka+1);
                }
            } else {
                if (i == 0){
                    cout << right << setw(sirka) << z+1;
                } else if (i <= pocetCisel[z] && i > 0){
                    int something = to_string(poleCisel[rowOffset + (i - 1)]).size();
                    if (vyhashtagovat == 1 && something > sirka){
                        cout << right << setw(sirka);
                        for (int g = 0; g < sirka; g++){
                            cout << "#";
                        }
                    } else {
                        cout << right << setw(sirka) << poleCisel[rowOffset + (i - 1)];
                    }
                } else if (zahlavi == 0){
                    cout << right << setw(sirka+1);
                }
            }
            cout << " ";
        }
        cout << "|" << endl;
        
    }
    deliciRada (sirka, pocetSloupcu, zahlavi);
}

void printConfig(vector <konfigurace> poleKonfiguraci){
    vector <string> poradiTisku = {"min", "max", "width", "align", "stretch", "header"};
    
    for (auto target : poradiTisku){
        int something = poleKonfiguraci.size();
        for (int i = 0; i < something; i++) {
            if (poleKonfiguraci[i].funkce == target) {
                cout << "config." << poleKonfiguraci[i].funkce << "=" << poleKonfiguraci[i].hodnota << endl;
                break;
            }
        }
    }
    cout << endl;
}

void printOutput(vector <konfigurace> poleKonfiguraci, parametry infoProTabulku){
    int sirka = 0;
    string zarovnani;
    int vyhashtagovat = 0;

    konfigurace* stretchConfig = najdiConfig(poleKonfiguraci, "stretch");
    konfigurace* widthConfig   = najdiConfig(poleKonfiguraci, "width");
    konfigurace* alignConfig   = najdiConfig(poleKonfiguraci, "align");

    if (stretchConfig != nullptr && stoi(stretchConfig->hodnota) == 1){
        int something = infoProTabulku.poleCisel.size();
        for (int h = 0; h < something; h++){
            int somethingConcrete = to_string(infoProTabulku.poleCisel[h]).size();
            if (somethingConcrete > sirka){
                sirka = somethingConcrete;
            }
        }
        vyhashtagovat = 1;
    } else if (stretchConfig != nullptr && stoi(stretchConfig->hodnota) == 0){
        sirka = stoi(widthConfig->hodnota);
        vyhashtagovat = 1;
    } else {
        sirka = stoi(widthConfig->hodnota);
        vyhashtagovat = 0;
    }

    widthConfig->hodnota = to_string(sirka);
    zarovnani = alignConfig->hodnota;

    // check error
    int something = infoProTabulku.poleCisel.size();
    for (int i = 0; i < something; i++){
        int somethingConcrete = to_string(infoProTabulku.poleCisel[i]).size();
        if (somethingConcrete > sirka && vyhashtagovat == 0){
            cerr << "Cell is too short" << endl;
            exit (103);
        }
    }
    
    printConfig(poleKonfiguraci);
    
    int pocetSloupcu = infoProTabulku.maxDelka;

    printTable(sirka, pocetSloupcu, zarovnani, infoProTabulku.pocetCisel, infoProTabulku.poleCisel, vyhashtagovat, poleKonfiguraci);
}

void doplnChybejiciConfig(vector <konfigurace>* poleKonfiguraci){
    
    vector <string> mam;
    int something = (*poleKonfiguraci).size();
    for (int i = 0; i < something; i ++){
        mam.push_back((*poleKonfiguraci)[i].funkce);
    }

    vector <string> chci = {"min", "max", "width", "align"};

    for (const string& target : chci) {
        if (find(mam.begin(), mam.end(), target) != mam.end()){
            // did find it in the configuration
        } else {
            if (target == "max"){
                konfigurace currentConfig;
                currentConfig.funkce = target;
                currentConfig.hodnota = "100";
                (*poleKonfiguraci).push_back(currentConfig);
            }
            if (target == "min"){
                konfigurace currentConfig;
                currentConfig.funkce = target;
                currentConfig.hodnota = "-99";
                (*poleKonfiguraci).push_back(currentConfig);
            }
            if (target == "width"){
                konfigurace currentConfig;
                currentConfig.funkce = target;
                currentConfig.hodnota = "3";
                (*poleKonfiguraci).push_back(currentConfig);
            }
            if (target == "align"){
                konfigurace currentConfig;
                currentConfig.funkce = target;
                currentConfig.hodnota = "left";
                (*poleKonfiguraci).push_back(currentConfig);
            }
        }
    }
}

vector <konfigurace> loadConfig(){
    string funkce, formalita, hodnota;
    vector <konfigurace> poleKonfiguraci;

    while (cin.peek() != EOF && cin.peek() != '='){

        getline(cin, formalita,'.');
        getline(cin, funkce, '=');
        getline(cin, hodnota);

        // Trim trailing \r in case of Windows line endings
        while (!hodnota.empty() && (hodnota.back() == '\r' || hodnota.back() == ' '))
            hodnota.pop_back();

        konfigurace currentConfig;
        currentConfig.funkce = funkce;
        currentConfig.hodnota = hodnota;

        poleKonfiguraci.push_back(currentConfig);
    }

    while (cin.peek() == '=' || cin.peek() == ' ' || cin.peek() == '\n'){
        cin.ignore();
    }

    doplnChybejiciConfig(&poleKonfiguraci);

    vector <string> poradi = {"min", "max", "width", "align", "stretch", "header"};

    sort((poleKonfiguraci).begin(), (poleKonfiguraci).end(),
    [&poradi](const konfigurace& a, const konfigurace& b) {
        auto posA = find(poradi.begin(), poradi.end(), a.funkce);
        auto posB = find(poradi.begin(), poradi.end(), b.funkce);
        return posA < posB;
    });
    
    // Safely find min, max, width, align by name instead of hardcoded index
    konfigurace* minConfig   = najdiConfig(poleKonfiguraci, "min");
    konfigurace* maxConfig   = najdiConfig(poleKonfiguraci, "max");
    konfigurace* widthConfig = najdiConfig(poleKonfiguraci, "width");
    konfigurace* alignConfig = najdiConfig(poleKonfiguraci, "align");

    if (!minConfig || !maxConfig || !widthConfig || !alignConfig){
        cerr << "Invalid configuration" << endl;
        exit(102);
    }

    if (stoi(minConfig->hodnota) > stoi(maxConfig->hodnota) ||
        stoi(widthConfig->hodnota) < 1 ||
        (alignConfig->hodnota != "left" && alignConfig->hodnota != "right")){
        cerr << "Invalid configuration" << endl;
        exit (102);
    }

    return poleKonfiguraci;
}

parametry loadNums(vector <konfigurace> poleKonfiguraci){
    string cislo, radek;
    vector <int> poleCisel;
    vector <int> pocetCisel;
    int maxDelka = 0;
    int pocetCiselNaRadku = 0;
    int sum = 0;

    konfigurace* minConfig = najdiConfig(poleKonfiguraci, "min");
    konfigurace* maxConfig = najdiConfig(poleKonfiguraci, "max");

    while (cin.peek() != EOF){
        getline(cin, radek, '\n');

        // Skip empty lines
        if (radek.empty() || radek == "\r") continue;

        stringstream radekSS(radek);

        int rowOffset = 0;
        int something = pocetCisel.size();
        for (int r = 0; r < something; r++) rowOffset += pocetCisel[r];
    
        while(radekSS.peek() != EOF){
            getline(radekSS, cislo, ';');

            // Trim \r
            while (!cislo.empty() && cislo.back() == '\r') cislo.pop_back();

            // SUM formula: check length before accessing characters
            if (cislo.size() >= 8 && cislo.compare(0, 4, "SUM(") == 0 && cislo.at(7) == ')'){
                if (cislo.at(6) >= char(pocetCiselNaRadku + 'A')){
                    cerr << "Invalid input" << endl;
                    exit (101);
                }
                
                char zacatekIntervalu = cislo.at(4);
                char konecIntervalu = cislo.at(6);

                int prvniNum = zacatekIntervalu - 'A';
                int druhyNum = konecIntervalu - 'A';

                for (int i = prvniNum; i <= druhyNum; i++){
                    sum = sum + poleCisel[i + rowOffset];
                }

                poleCisel.push_back(sum);
            } else {
                try {
                    int cisloI = stoi(cislo);
                    if (cisloI < stoi(minConfig->hodnota) || cisloI > stoi(maxConfig->hodnota)){
                        cerr << "Out of range" << endl;
                        exit (100);
                    }
                    poleCisel.push_back(cisloI);
                } catch (invalid_argument&){
                    cerr << "Invalid input" << endl;
                    exit (101);
                }   
            }
            pocetCiselNaRadku++;
            sum = 0;
        }

        pocetCisel.push_back(pocetCiselNaRadku);

        if (pocetCiselNaRadku > maxDelka){
            maxDelka = pocetCiselNaRadku;
        }
        pocetCiselNaRadku = 0;
    }

    int pocetRadku = pocetCisel.size();   

    parametry returnValues;
    returnValues.poleCisel = poleCisel;
    returnValues.pocetCisel = pocetCisel;
    returnValues.pocetRadku = pocetRadku;
    returnValues.maxDelka = maxDelka;

    return returnValues;
}

int main(){
    vector <konfigurace> poleKonfiguraci = loadConfig();
    parametry infoProTabulku = loadNums(poleKonfiguraci);
    printOutput(poleKonfiguraci, infoProTabulku);
    return 0;
}