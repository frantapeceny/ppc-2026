
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

void printBox(string text) {
    cout << "+" << setw(58) << setfill('-') << "" << "+" << endl;
    cout << "| " << setw (56) << setfill(' ') << left << text << " |" << endl;
    cout << "+" << setw(58) << setfill('-') << "" << "+" << endl;
}

class Publication{
    protected:
        string name;
        string year;
        string author;
        int id = 0;
    public:
        int getId() const { return id; }
        void setId(int i) { id = i; }
        string getName() const { return name; }
        string getYear() const { return year; }
        void setYear(string rok) { year = rok; }
        string getAuthor() const { return author; }

        /*bool operator<(const Publication &p) const {
            return id < p.id;
        }*/

};

class Journal : public Publication{
    private:
    public:
        Journal(string name, string volume, string issue, string year)
            { this->name = name; this->author = volume + "(" + issue + ")"; this->year = year; }
};

class Book : public Publication{
    private:
    public:
    Book(string name, string author, string year)
            { this->name = name; this->year = year; this->author = author; }

};

struct sortByNameAsc {
    bool operator()(const Publication &a, const Publication &b) const {
        return a.getName() < b.getName();
    }
};
struct sortByNameDesc {
    bool operator()(const Publication &a, const Publication &b) const {
        return a.getName() > b.getName();
    }
};
struct sortByIdAsc {
    bool operator()(const Publication &a, const Publication &b) const {
        return a.getId() < b.getId();
    }
};
struct sortByIdDesc {
    bool operator()(const Publication &a, const Publication &b) const {
        return a.getId() > b.getId();
    }
};
struct sortByYearAsc {
    bool operator()(const Publication &a, const Publication &b) const {
        return a.getYear() < b.getYear();
    }
};
struct sortByYearDesc {
    bool operator()(const Publication &a, const Publication &b) const {
        return a.getYear() > b.getYear();
    }
};

class Database{
    private:
        vector <Publication> publikace;
        
    public:
    vector <int> ids;
    int count = 0;

    void add(Publication p){
        count++;
        p.setId(count);
        ids.push_back(count);
        if (p.getYear().size() > 4){
            string year = p.getYear().substr(5, 4);
            p.setYear(year);
        }
        publikace.push_back(p);
    }

    void list() const {
        cout << "+" << setw(58) << setfill('-') << "" << "+" << endl;
        cout << "| " << setw(56) << setfill(' ') << left << "List of all records" << " |" << endl;
        for (const auto &tiskovina : publikace){
            cout << "+----+" << setw(53) << setfill('-') << "" << "+" << endl;
            cout << "| " << setw(2) << setfill(' ') << right << tiskovina.getId() << " | " << setw(51) << left << tiskovina.getName() << " |" << endl;
            cout << "|    | " << setw(51) << setfill(' ') << left << tiskovina.getYear() + ", "  + tiskovina.getAuthor() << " |" << endl;
        }
        cout << "+----+" << setw(53) << setfill('-') << "" << "+" << endl;
        cout << "| " << setw(56) << setfill(' ') << left << "Total: " + to_string(count) << " |" << endl;
        cout << "+" << setw(58) << setfill('-') << "" << "+" << endl;
    }

    void remove(int id) {
        for (auto it = publikace.begin(); it != publikace.end(); it++){
            if (it->getId() == id){
                publikace.erase(it);
                ids.erase(std::remove(ids.begin(), ids.end(), id), ids.end());
                count--;
                break;
            }
        }
    }

    void find(string text) {
        vector <Publication> subSet;
        for (const auto &p : publikace){
            if (p.getName().find(text) != string::npos || p.getAuthor().find(text) != string::npos || p.getYear() == text){ //stejne jako std::find(p.getName().begin(), p.getName().end(), text) != p.getName().end()
                subSet.push_back(p);
            }
        }
        if (subSet.empty()){

        } else {
            cout << "+" << setw(58) << setfill('-') << "" << "+" << endl;
            cout << "| " << setw(56) << setfill(' ') << left << "Search for \"" + text + "\"" << " |" << endl;
            for (const auto &tiskovina : subSet){
                cout << "+----+" << setw(53) << setfill('-') << "" << "+" << endl;
                cout << "| " << setw(2) << setfill(' ') << right << tiskovina.getId() << " | " << setw(51) << left << tiskovina.getName() << " |" << endl;
                cout << "|    | " << setw(51) << setfill(' ') << left << tiskovina.getYear() + ", "  + tiskovina.getAuthor() << " |" << endl;
            }
            cout << "+----+" << setw(53) << setfill('-') << "" << "+" << endl;
            cout << "| " << setw(56) << setfill(' ') << left << "Total: " + to_string(subSet.size()) << " |" << endl;
            cout << "+" << setw(58) << setfill('-') << "" << "+" << endl;
        }   
    }

    void erase(string text) {
        for (auto it = publikace.begin(); it != publikace.end();){
            int id = it->getId();
            if (it->getName().find(text) != string::npos ||
                it->getAuthor().find(text) != string::npos ||
                it->getYear().find(text) != string::npos) {

                publikace.erase(it);
                ids.erase(std::remove(ids.begin(), ids.end(), id), ids.end());
                count--;
            } else {
                it++;
            }
        }
    }

    void sort(string klic, string order) {
        vector <Publication> setridene (publikace.begin(), publikace.end());
        if (klic == "id" && (order == "asc" || order == "")){
            std::sort(setridene.begin(), setridene.end(), sortByIdAsc());
        } else if (klic == "id" && order == "desc"){
            std::sort(setridene.begin(), setridene.end(), sortByIdDesc());
        } else if (klic == "name" && (order == "asc" || order == "")){
            std::sort(setridene.begin(), setridene.end(), sortByNameAsc());
        } else if (klic == "name" && order == "desc"){
            std::sort(setridene.begin(), setridene.end(), sortByNameDesc());
        } else if (klic == "year" && (order == "asc" || order == "")){
            std::sort(setridene.begin(), setridene.end(), sortByYearAsc());
        } else if (klic == "year" && order == "desc"){
            std::sort(setridene.begin(), setridene.end(), sortByYearDesc());
        }
        publikace = setridene;
    }
};

int main(){
    Database databaze;
    databaze.add(Journal("IEEE Transaction on Computers", "C-35", "10", "Oct. 1986"));
    databaze.add(Journal("IEEE Transaction on Computers", "C-35", "11", "Dec. 1986"));
    databaze.add(Journal("IEEE Transactions on Communications", "28", "8", "Aug. 1980"));
    databaze.add(Book("Dva roky prazdnin", "Jules Verne", "1888"));
    databaze.add(Book("Tajuplny ostrov", "Jules Verne", "1874"));
    databaze.add(Book("Ocelove mesto", "Jules Verne", "1879"));

    databaze.sort("id", "asc");

    string command;
    while(cin.peek() != EOF){
        getline(cin, command);

        size_t poziceR = command.find("remove");
        size_t poziceF = command.find("find");
        size_t poziceE = command.find("erase");
        size_t poziceS = command.find("sort");

        if (command == "list"){
            databaze.list();
        } else if (poziceR != string::npos){
            if (command.find(":") != string::npos){
                string id = command.substr(poziceR+7); // prectu od ":" do konce slova

                if (id == ""){
                    printBox("Unknown command \"" + command + "\"");
                } else if (std::find(databaze.ids.begin(), databaze.ids.end(), stoi(id)) == databaze.ids.end()){
                    printBox("ID = " + id + " is not in the database");
                } else {
                    databaze.remove(stoi(id));  
                }   
            } else {
                printBox("Command \"remove\" expects some argument");
            }
        } else if (poziceF != string::npos){
            if (command.find(":") != string::npos){
                string text = command.substr(poziceF+5);
                if (text == ""){
                    printBox("Unknown command \"" + command + "\"");
                } else {
                    databaze.find(text);
                }
            } else {
                printBox("Command \"find\" expects some argument");
            }
        } else if (poziceE != string::npos){
            if (command.find(":") != string::npos){
                string text = command.substr(poziceE+6);
                if (text == ""){
                    printBox("Unknown command \"" + command + "\"");
                } else {
                    databaze.erase(text);
                }
            } else {
                printBox("Command \"erase\" expects some argument");
            }
        } else if (poziceS != string::npos){
            if (command.find(":") != string::npos ){
                string text = command.substr(poziceS+5);
                string keyWord;
                string order;

                int poziceDvojtecky = text.find(":");
                if (poziceDvojtecky == 0){
                    keyWord = text.substr(0);
                    order = "";
                } else {
                    keyWord = text.substr(0, poziceDvojtecky);
                    order = text.substr(poziceDvojtecky+1);
                }
                databaze.sort(keyWord, order);
            } else {
                printBox("Unknown sorting order");
            }
            
        } else {
            printBox("Unknown command \"" + command + "\"");
        }
    }
    return 0;
}
