
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct konfigurace{
    string funkce;
    string hodnota;
};

void loadConfig(){
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

        //cout << formalita << "\n" << funkce << "\n" << hodnota << endl;
    }
    cin.ignore(); // preskocim "="
    cin.ignore(); // preskocim newline

    if (poleKonfiguraci.size() == 4){
        for (int i = 0; i < poleKonfiguraci.size(); i++){
        cout << poleKonfiguraci[i].funkce << " " << poleKonfiguraci[i].hodnota << endl;
    }
    }

    for (int i = 0; i < poleKonfiguraci.size(); i++){
        if poleKonfiguraci[i]
    }
    
    

}

void loadNums(){
    string cislo, radek;
    vector <int> poleCisel;
    vector <int> pocetCisel;
    int maxDelka = 0;
    int pocetCiselNaRadku = 0;
    int sum = 0;

    while (cin.peek() != EOF){
        getline(cin, radek, '\n');   
        stringstream radekSS(radek);

        cout << "loaded radek: " << radekSS.str() << endl;

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

    cout << "pocet cisel na radek: ";

    for (int h = 0; h < pocetRadku; h++){
        cout << pocetCisel[h] << ", ";
    }

    cout << "max pocet cisel na radek: " << maxDelka << endl;    

    // cisla jsou ulozena v poli poleCisel, delky radku jsou v poli pocetCisel, pocet radku je v hodnota promenne pocetRadku, maximalni delka radku je v promenne maxDelka
}



int main(){
    loadConfig();
    loadNums();



    return 0;
}    

// line.find(), line.substr(), line.erase(), line.replace(), line.insert(), line.append(), line.compare(), line.find_first_of(), line.find_last_of(), line.find_first_not_of(), line.find_last_not_of()


// zeptat na this - co ze to nahrazuje