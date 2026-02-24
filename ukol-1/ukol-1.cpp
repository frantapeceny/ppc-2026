
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct konfigurace{
    std::string funkce;
    std::string hodnota;
};

void loadConfig(){

    std::string funkce, formalita, hodnota;
    std::vector <konfigurace> poleKonfiguraci;

    while (std::cin.peek() != '='){
        getline(std::cin, formalita,'.');
        getline(std::cin, funkce, '=');
        getline(std::cin, hodnota);

        konfigurace currentConfig;
        
        currentConfig.funkce = funkce;
        currentConfig.hodnota = hodnota;

        poleKonfiguraci.push_back(currentConfig);

        //cout << formalita << "\n" << funkce << "\n" << hodnota << endl;
    }

    for (int i = 0; i < poleKonfiguraci.size(); i++){
        std::cout << poleKonfiguraci[i].funkce << " " << poleKonfiguraci[i].hodnota << std::endl;
    }

    std::cout << "checkpoint - zpracovany config" << std::endl;
    
    //cout << "pocet ulozenych configu: " << poleKonfiguraci.size() << endl;
}

void loadNums(){
    std::string cislo, radek;
    std::vector <std::string> poleCisel;
    int poziceDvojtecky;
    int prvniPoziceProSum, druhaPoziceProSum;

    getline(std::cin, radek);

    std::stringstream radekSS(radek);

    while(getline(radekSS, cislo, ';')){

        if (poziceDvojtecky = cislo.find(':')){ //nemusi fungovat
            prvniPoziceProSum = cislo[poziceDvojtecky-1] - 'A' + 1; // nebo -65
            druhaPoziceProSum = cislo[poziceDvojtecky+1] - 'A' + 1;
            //druhaPoziceProSum - prvniPoziceProSum;
            std::cout << prvniPoziceProSum << " " << druhaPoziceProSum << std::endl;

        } else {
            poleCisel.push_back(cislo);
        }

    }
}

int main(){
    loadConfig();

    loadNums();

    return 0;
}    

// line.find(), line.substr(), line.erase(), line.replace(), line.insert(), line.append(), line.compare(), line.find_first_of(), line.find_last_of(), line.find_first_not_of(), line.find_last_not_of()
