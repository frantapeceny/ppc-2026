
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct konfigurace{
    string funkce;
    string hodnota;
};

int main(){
    string funkce, formalita, hodnota;
    vector <konfigurace> poleKonfiguraci;
    int i = 0;

    cout << "zkouska" << endl;

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

    for (int i = 0; i < poleKonfiguraci.size(); i++){
        cout << poleKonfiguraci[i].funkce << " " << poleKonfiguraci[i].hodnota << endl;
    }

    // line.find(), line.substr(), line.erase(), line.replace(), line.insert(), line.append(), line.compare(), line.find_first_of(), line.find_last_of(), line.find_first_not_of(), line.find_last_not_of()

    return 0;

}
