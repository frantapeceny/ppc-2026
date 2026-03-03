
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

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

void printTable(vector <konfigurace> poleKonfiguraci, parametry infoProTabulku){
    int sirka;
    string zarovnani;
    for (int i = 0; i < poleKonfiguraci.size(); i ++){
        if (poleKonfiguraci[i].funkce == "width"){
            sirka = stoi(poleKonfiguraci[i].hodnota);
        }
        if (poleKonfiguraci[i].funkce == "align"){
            zarovnani = poleKonfiguraci[i].hodnota;
        }
    }

    cout << "width: " << sirka << endl;
    cout << "align: " << zarovnani << endl;
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

    printConfig(poleKonfiguraci);

    return poleKonfiguraci;
}

parametry loadNums(){
    string cislo, radek;
    vector <int> poleCisel;
    vector <int> pocetCisel;
    int maxDelka = 0;
    int pocetCiselNaRadku = 0;
    int sum = 0;

    while (cin.peek() != EOF){
        getline(cin, radek, '\n');   
        stringstream radekSS(radek);

        //cout << "loaded radek: " << radekSS.str() << endl;

        while(radekSS.peek() != EOF){
            getline(radekSS, cislo, ';');

            if (cislo.at(0) == 'S'){
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
                poleCisel.push_back(stoi(cislo));
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

    parametry infoProTabulku = loadNums();

    printTable(poleKonfiguraci, infoProTabulku);

    return 0;
}    

// line.find(), line.substr(), line.erase(), line.replace(), line.insert(), line.append(), line.compare(), line.find_first_of(), line.find_last_of(), line.find_first_not_of(), line.find_last_not_of()


// zeptat na this - co ze to nahrazuje