
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
        string getAuthor() const { return author; }

        bool operator<(const Publication &p) const {
            return id < p.id;
        }
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

class Database{
    private:
        set <Publication> publikace;
        
    public:
    vector <int> ids;
    int count = 0;

    void add(Publication p){
        count++;
        p.setId(count);
        ids.push_back(count);
        publikace.insert(p);
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
        set <Publication> subSet;
        for (const auto &p : publikace){
            if (p.getName().find(text) != string::npos || p.getAuthor().find(text) != string::npos || p.getYear() == text){ //stejne jako std::find(p.getName().begin(), p.getName().end(), text) != p.getName().end()
                subSet.insert(p);
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
        for (auto it = publikace.begin(); it != publikace.end(); it++){
            int id = it->getId();
            if (it->getName().find(text) != string::npos ||
                it->getAuthor().find(text) != string::npos ||
                it->getYear().find(text) != string::npos) {

                publikace.erase(it);
                ids.erase(std::remove(ids.begin(), ids.end(), id), ids.end());
                count--;
            }
        }
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

    string command;
    while(true){
        getline(cin, command);

        int poziceR = command.find("remove");
        int poziceF = command.find("find");
        int poziceE = command.find("erase");

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
        } else {
            printBox("Unknown command \"" + command + "\"");
        }
    }
    return 0;
}
