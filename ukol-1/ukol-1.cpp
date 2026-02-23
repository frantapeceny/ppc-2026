
#include <iostream>
#include <string>



using namespace std;



int main(){
    string function, configFormalita, value;

    cout << "zkouska" << endl;

    while (cin.peek() != '='){
        getline(cin, configFormalita,'.');
        getline(cin, function, '=');
        getline(cin, value);
        cout << configFormalita << "\n" << function << "\n" << value << endl;

    }

    // line.find(), line.substr(), line.erase(), line.replace(), line.insert(), line.append(), line.compare(), line.find_first_of(), line.find_last_of(), line.find_first_not_of(), line.find_last_not_of()

    cout << value << "\n" << function << "\n" << configFormalita << endl;
    return 0;

}
