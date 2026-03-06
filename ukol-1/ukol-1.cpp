
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

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

void checkErrors(){
    

}

void deliciRada(int sirka, int pocetSloupcu){
    for (int i = 0; i <= pocetSloupcu; i++){
        cout << "+";
        for (int h = 0; h < (sirka+2); h++){
            cout << "-";
        }
    }
    cout << "+" << endl;
}

void prvniRadek(int sirka, int pocetSloupcu, string zarovnani){
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

void printTable(int sirka, int pocetSloupcu, string zarovnani, vector <int> pocetCisel, vector <int> poleCisel){

    // z = kolikaty je to radek, i = kolikaty sloupec
    deliciRada (sirka, pocetSloupcu);
    prvniRadek(sirka, pocetSloupcu, zarovnani);
    int pocetRadku = pocetCisel.size();

    for (int z = 0; z < pocetRadku; z++){
        deliciRada (sirka, pocetSloupcu);
        int idx = 0;

        //?
        int rowOffset = 0;
        for (int r = 0; r < z; r++) rowOffset += pocetCisel[r];

        for (int i = 0; i <= pocetSloupcu; i++){
            cout << "| ";
            if (zarovnani == "left"){
                if (i == 0){
                    cout << left << setw(sirka) << z+1;
                } else if (i <= pocetCisel[z] && i > 0){
                    cout << left << setw(sirka) << poleCisel[rowOffset + (i - 1)];
                    idx ++;
                } else {
                    cout << left << setw(sirka+1);
                }
            } else {
                if (i == 0){
                    cout << right << setw(sirka) << z+1;
                } else if (i <= pocetCisel[z] && i > 0){
                    cout << right << setw(sirka) << poleCisel[rowOffset + (i - 1)];
                    idx ++;
                } else {
                    cout << right << setw(sirka+1);
                }
            }
            cout << " ";
        }
        cout << "|" << endl;
        
    }
    deliciRada (sirka, pocetSloupcu);
}

void printConfig(vector <konfigurace> poleKonfiguraci){
    vector <string> poradiTisku = {"min", "max", "width", "align", "stretch", "header"};
    
    for (auto target : poradiTisku){
        for (int i = 0; i < poleKonfiguraci.size(); i++) {
            if (poleKonfiguraci[i].funkce == target) {
                cout << "config." << poleKonfiguraci[i].funkce << "=" << poleKonfiguraci[i].hodnota << endl;
                break;
            }
        }
    }
    cout << endl;
}

void printOutput(vector <konfigurace> poleKonfiguraci, parametry infoProTabulku){
    int sirka;
    string zarovnani;

    printConfig(poleKonfiguraci);

    for (int i = 0; i < poleKonfiguraci.size(); i ++){
        if (poleKonfiguraci[i].funkce == "width"){
            sirka = stoi(poleKonfiguraci[i].hodnota);
        }
        if (poleKonfiguraci[i].funkce == "align"){
            zarovnani = poleKonfiguraci[i].hodnota;
        }
    }
    int pocetSloupcu = infoProTabulku.maxDelka;

    printTable(sirka, pocetSloupcu, zarovnani, infoProTabulku.pocetCisel, infoProTabulku.poleCisel);
}

void doplnChybejiciConfig(vector <konfigurace>* poleKonfiguraci){
    
    vector <string> mam;
    for (int i = 0; i < (*poleKonfiguraci).size(); i ++){
        mam.push_back((*poleKonfiguraci)[i].funkce);
    }

    vector <string> chci = {"min", "max", "width", "align"};

    vector <string> found;
    vector <string> missing;

    for (const string& target : chci) {
        if (find(mam.begin(), mam.end(), target) != mam.end()){
            found.push_back(target);
        } else {
            missing.push_back(target);
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

    while (cin.peek() != '='){

        getline(cin, formalita,'.');
        getline(cin, funkce, '=');
        getline(cin, hodnota);

        konfigurace currentConfig;
        
        currentConfig.funkce = funkce;
        currentConfig.hodnota = hodnota;

        poleKonfiguraci.push_back(currentConfig);

    }
    cin.ignore(); // preskocim "="
    cin.ignore(); // preskocim newline

    doplnChybejiciConfig(&poleKonfiguraci);

    return poleKonfiguraci;
}

parametry loadNums(vector <konfigurace> poleKonfiguraci){
    string cislo, radek;
    vector <int> poleCisel;
    vector <int> pocetCisel;
    int maxDelka = 0;
    int pocetCiselNaRadku = 0;
    int sum = 0;

    while (cin.peek() != EOF){
        getline(cin, radek, '\n');   
        stringstream radekSS(radek);

        while(radekSS.peek() != EOF){
            getline(radekSS, cislo, ';');

            if (cislo.compare(0, 4, "SUM(", 0, 4) == 0 && cislo.at(7) == ')'){
                //error check
                if (cislo.at(6) >= char(pocetCiselNaRadku + 'A')){
                    cerr << "Invalid input" << endl;
                    exit (101);
                }
                
                char zacatekIntervalu = cislo.at(4);
                char konecIntervalu = cislo.at(6);

                // convertuji pismeno na pozici
                int prvniNum = zacatekIntervalu - 'A';
                int druhyNum = konecIntervalu - 'A';

                for (int i = prvniNum; i <= druhyNum; i++){                
                    sum = sum + poleCisel[i];
                }
                poleCisel.push_back(sum);
            } else {
                // check error
                try {
                    int cisloI = stoi(cislo);
                    // check error
                    if (cisloI < stoi(poleKonfiguraci[0].hodnota) || cisloI > stoi(poleKonfiguraci[1].hodnota)){
                        cerr << "Out of range" << endl;
                        exit (100);
                    }
                    poleCisel.push_back(cisloI);
                } catch (invalid_argument&){
                    cerr << "Invalid input" << endl;
                    exit (100);
                }   
            }
            pocetCiselNaRadku ++;
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

    // cisla jsou ulozena v poli poleCisel, delky radku jsou v poli pocetCisel, pocet radku je v hodnota promenne pocetRadku, maximalni delka radku je v promenne maxDelka
}

int main(){
    
    vector <konfigurace> poleKonfiguraci = loadConfig();

    parametry infoProTabulku = loadNums(poleKonfiguraci);

    checkErrors();

    printOutput(poleKonfiguraci, infoProTabulku);

    return 0;
}    

// zeptat na this - co ze to nahrazuje