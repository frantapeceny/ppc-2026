
#include <iostream>
#include <iomanip>
#include <string>
#include <set>

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
        string issue;

    public:
        Journal(string name, string volume, string issue, string year)
            : issue(issue) { this->name = name; this->year = year; this->author = volume; }
};

class Book : public Publication{
    private:
    public:
    Book(string name, string author, string year) { this->name = name; this->year = year; this->author = author; }

};

class Database{
    private:
        set <Publication> publikace;

    public:
    int count = 0;

    void add(Publication p){
        p.setId(count);
        publikace.insert(p);
        count++;
    }

    void list() const {
        cout << "+" << setw(58) << setfill('-') << "" << "+" << endl;
        cout << "| " << setw(56) << setfill(' ') << left << "List of all records" << " |" << endl;
        for (const auto &tiskovina : publikace){
            cout << "+----+" << setw(53) << setfill('-') << "" << "+" << endl;
            cout << "| " << setw(2) << setfill(' ') << right << tiskovina.getId()+1 << " | " << setw(51) << left << tiskovina.getName() << " |" << endl;
            cout << "|    | " << setw(51) << setfill(' ') << left << tiskovina.getYear() + ", "  + tiskovina.getAuthor() << " |" << endl;
        }
        cout << "+----+" << setw(53) << setfill('-') << "" << "+" << endl;
        cout << "| " << setw(56) << setfill(' ') << left << "Total: " + to_string(count) << " |" << endl;
        cout << "+" << setw(58) << setfill('-') << "" << "+" << endl;
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

        int pozice = command.find("remove");

        if (command == "list"){
            databaze.list();
        } else if (pozice != string::npos){
            if (command.find(":") != string::npos){
                string id = command.substr(pozice+7); // prectu od ":" do konce slova

                if (id == ""){
                    cerr << "nuh uh, not like this" << endl;
                    return -1;
                } else if (databaze.count < stoi(id) || stoi(id) <= 0){
                    printBox("ID = " + id + " is not in the database");
                } else {
                    //database.remove(id);
                }
            } else {
                printBox("Command \"remove\" expects some argument");
            }
        } else {
            printBox("Unknown command \"" + command + "\"");
        }

    }
    return 0;
}
