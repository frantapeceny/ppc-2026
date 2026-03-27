#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "doprava.hpp"
#include "student.hpp"

using namespace std;

struct ridic {
    string jmeno;
    int linka;
    int pocetJizd;
    int pocetZastavek;
};

struct seradRidice {
    bool operator()(const ridic &a, const ridic &b) const {
        if (a.pocetZastavek != b.pocetZastavek) {
            return a.pocetZastavek > b.pocetZastavek;
        }
        return a.jmeno < b.jmeno;
    }
};

void LnC (ridic * r){

    ifstream file("network.txt");

    if (!file.is_open()) {
        cerr << "Error" << endl;
        return;
    }

    string line;
    int odstavec = 0;
    int pocetJizd = 0;

    while (getline(file, line)) {
        if (line == "#####") {
            odstavec++;
        }

        if (line.find(r->jmeno) != string::npos) {
            pocetJizd++;
            r->linka = odstavec;
        }
    }
    file.close();

    int delkaTrasy = 0;
    switch(r->linka){
        case 0:
            delkaTrasy = 16;
            break;
        case 1: 
            delkaTrasy = 16;
            break;
        case 2:
            delkaTrasy = 9;
            break;
        case 3:
            delkaTrasy = 8;
            break;
        default:
            break;
    }

    r->pocetJizd = pocetJizd;
    r->pocetZastavek = delkaTrasy * pocetJizd;
}


int main(int argc, char** argv) {

    // Load files:
    DriverList dl;
    dl.loadFromFile("driver_list.txt");

    Network net;
    net.loadFromFile("network.txt");

    // variables for argument decoding
    string flag_in;
    list<string> stop_in;

    if (argc > 1)
        flag_in = string(argv[1]);
    else
    {
        cerr << "Missing argument. Terminating." << endl;
        return 1;
    }

    if ((!flag_in.compare("--schedule")))
    {
        // input check - do not edit
        if (argc > 2)
        {
            for (int i = 2; i < argc; i++)
            {
                string temp = argv[i];
                replace(temp.begin(), temp.end(), '_', ' ');
                stop_in.push_back(temp);
            }
        }
        else
        {
            cerr << "Missing stop name. Terminating." << endl;
            return 2;
        }
        // end of input check

        

        /* here should start the code for printing timetables*/
        /* stop_in contains names of stops, for which the timetable is to be printed. */

        // This is an example, how it can be done using lambda-function
        for_each(stop_in.begin(), stop_in.end(), [&] (string stop_name) {print_timetable(net,stop_name);} );
        // This is an example, how it can be done using for-loop 
        // for( auto iter = stop_in.begin(); iter != stop_in.end(); iter++) print_timetable(net,*iter);

        // hint code: use and modify prepared print_timetable(...) function in the student.cpp file 

        /* here should end the code for printing timetables*/
    }
    else if ((!flag_in.compare("--line-routing")))
    {

        /* here should start the code for printing line routes without stats*/

        // hint code: use and modify prepared print_line_stations(...) function in the student.cpp file 
        for (int i = 0; i < net.nlines(); i++)  print_line_stations(net,i);

        /* here should end the code for printing line routes without stats*/
    }
    else if ((!flag_in.compare("--driver-stops")))
    {

        cout << "+----------------------+---+----+-----+" << endl;
        cout << "| " << setw(20) << setfill(' ') << std::left << "Driver Name" << " | L | nC | nSt |" << endl;
        cout << "+----------------------+---+----+-----+" << endl;

        int pocetRidicu;
        set <ridic, seradRidice> ridici;

        for (auto &driver : dl){
            ridic r;
            r.jmeno = driver.name;
            LnC(&r);

            ridici.insert(r);
            pocetRidicu ++;
        }

        for (auto &ridic : ridici){
            string jmeno = ridic.jmeno;
            int linka = ridic.linka;
            int pocetJizd = ridic.pocetJizd;
            int pocetZastavek = ridic.pocetZastavek;

            if (pocetZastavek == 0){
                cout << "| " << setw(20) << std::left << jmeno << " | " << "X" << " | "
                         << setw(2) << std::right << setfill(' ') << "XX" << " | "
                         << setw(3) << std::right << setfill(' ') << "XXX" << " |" << endl;
            } else {
                cout << "| " << setw(20) << std::left << jmeno << " | " << linka << " | "
                         << setw(2) << std::right << setfill(' ') << pocetJizd << " | "
                         << setw(3) << std::right << setfill(' ') << pocetZastavek << " |" << endl;
            }
        }
        cout << "+----------------------+---+----+-----+" << endl;
    }
    else
    {
        cout << "Flag not recognized, terminating." << endl;
    }
    
    return 0;
}