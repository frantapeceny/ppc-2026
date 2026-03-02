
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

    for (int i = 0; i < poleKonfiguraci.size(); i++){
        cout << poleKonfiguraci[i].funkce << " " << poleKonfiguraci[i].hodnota << endl;
    }

    cout << "checkpoint - zpracovany config" << endl;
    
    //cout << "pocet ulozenych configu: " << poleKonfiguraci.size() << endl;
}

void loadNums(){
    string cislo, radek;
    vector <string> poleCisel;
    vector <int> pocetCisel;
    int maxPocetCiselNaRadku = 0;
    int pocetCiselNaRadku = 0;

    while (cin.peek() != EOF){
        getline(cin, radek, '\n');   
        stringstream radekSS(radek);

        cout << "loaded radek: " << radekSS.str() << endl;

        while(radekSS.peek() != EOF){
            getline(radekSS, cislo, ';');

            poleCisel.push_back(cislo);
            pocetCiselNaRadku ++;

            /*
            if (poziceDvojtecky = cislo.find(':')){ //nemusi fungovat
                prvniPoziceProSum = cislo[poziceDvojtecky-1] - 'A' + 1; // nebo -65
                druhaPoziceProSum = cislo[poziceDvojtecky+1] - 'A' + 1;
                //druhaPoziceProSum - prvniPoziceProSum;
                cout << prvniPoziceProSum << " " << druhaPoziceProSum << endl;

            } else {
                poleCisel.push_back(cislo);
            }*/
        }

        pocetCisel.push_back(pocetCiselNaRadku);

        if (pocetCiselNaRadku > maxPocetCiselNaRadku){
            maxPocetCiselNaRadku = pocetCiselNaRadku;
        }
    }

    cout << "extraktovana cisla: " << endl;
    cout<< "pocetcisel.size: " << pocetCisel.size() << endl;

    int pocetRadku = pocetCisel.size();

    for (int h = 0; h < pocetRadku; h++){
        cout <<"radek cislo " << h << ": " << endl;
        for (int i = 0; i < pocetCisel.at(h); i++){
            cout << poleCisel[i] << endl;
        }        
    }
}

int main(){
    loadConfig();

    loadNums();

    return 0;
}    

// line.find(), line.substr(), line.erase(), line.replace(), line.insert(), line.append(), line.compare(), line.find_first_of(), line.find_last_of(), line.find_first_not_of(), line.find_last_not_of()
