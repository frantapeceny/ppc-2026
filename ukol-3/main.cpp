
#include <iostream>
#include <string>
#include <set>

using namespace std;

class Journal{
    private:
        string name;
        string volume;
        string issue;
        string year;    
        int id;

    public:
    Journal(string name, string volume, string issue, string year)
        : name(name), volume(volume), issue(issue), year(year) {}

    bool operator<(const Journal &a) const {
        return id < a.id;
    }

};

class Book{
    private: 
        string name;
        string author;
        string year;
        int id;

    public:
    Book(string name, string author, string year)
        : name(name), author(author), year(year) {}

    bool operator<(const Book &a) const {
        return id < a.id;
    }
};

class Database{
    private:
        set <Journal> journals;
        set <Book> books;
        
    public:
    int count = 0;

    void add(Journal j){
        journals.insert(j);
        count++;
    }
    
    void add(Book b){
        books.insert(b);
        count++;
    }

    void list() const {
        if ()
        for (const auto &tiskovina : )
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

        cout << "pocet vlozenych knih: " << databaze.count << endl;

        if (command == "list"){
           
        }

    }
    return 0;
}
