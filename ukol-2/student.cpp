#include "student.hpp"

using namespace std;


/*helper for printing lines +---+ (argument = 5)*/
void print_hline(int l = 80)
{
    cout << "+";
    for (int i = 0; i < l - 2; i++)
        cout << "-";
    cout << "+\n";
}

/*print timetable for a stop of given name */
void print_timetable(const Network &net, const string &stop)
{
    /*search all lines for the name of stop*/
    for (int ln = 0; ln < net.nlines(); ln++){
        Line tmpL = net.getLine(ln);  // Get one line to work with as a local variable
        
        /* Find if a station in variable "stop" is present in the line "tmpL" */
        auto itS = tmpL.stops.begin();
        // hint 1: cycle through all the stops in tmpL.stops and break when the name is found
        // hint 2: if stop is not found, try in the next line (call continue; on the enclosing for cycle)
        // hint 3: if stop is found, print its timetable (the function continues without interuption)
        

        //prvni doplneni kodu
        for (itS = tmpL.stops.begin(); itS != tmpL.stops.end(); itS++) {
          if (*itS == stop) break;
        }

        if (itS == tmpL.stops.end()) continue;
        


        
        /* ***insert your code here*** */
    
        /* at this point, iterator "itS" should point at the station that was found */
        
        /* Printing header lines */
        print_hline();
        cout << "| " << setw(69) << setfill(' ')<< std::left << stop;
        cout << "Line: " << ln << " |\n";

        cout << "+" << setw(39) << setfill('-') << std::right << "+";
        cout << "+" << setw(39) << setfill('-') << std::right << "+"
             << "\n";
        /* end of header*/
        
        
        int offset = /*insert code for obtaining index of itS within the tmpL.stops vector*/;
        
        /* print timetable head for forward direction (left half) */
        cout << "| To: " << setw(40 - 8) << setfill(' ') << std::left << /*name of the last stop*/ << " |";
        /* print timetable head for backward direction (right half) */
        cout << "| To: " << setw(40 - 8) << setfill(' ') << std::left << /*name of the first stop*/  << " |\n";

        cout << setw(39) << setfill('-') << std::left << "+----+"
             << "+";
        cout << setw(39) << setfill('-') << std::left << "+----+"
             << "+\n";
             
        /* Put all fwd/bwd departures from station "stop" into two vectors*/
        vector<Depart> tmpDvF; // forward departures from station "stop"
        vector<Depart> tmpDvB; // backward departures from station "stop"
        /* fill the vectors tmpDvF and tmpDvB, extract the departures from tmpL.conns_fwd and tmpL.conns_bwd*/
        
        /* ***insert your code here*** */

        auto itDvF = tmpDvF.begin();
        auto itDvB = tmpDvB.begin();

        /* print lines 00 to 24 */
        for (int hour = 00; hour < 24; hour++)
        {
            ostringstream osf, osb; // forward minutes and backward minutes stringstream
            int hh, mm, ss;
            /* Fill osf with minutes of fwd departure times in the current hour */

            // hint 1: Use the "itDvF" iterator, the vector of departures is sorted
            // hint 2: Objects of class Depart have a member Time ti. Use function "void Time::gett(int &hh, int &mm, int &ss)" to obtain hours, minutes, seconds 
            // hint 3: Use this snippet for formatting: osf << setw(2) << std::right << setfill('0') << mm << " ";

            /* ***insert your code here*** */

            /* Fill osb with minutes of bwd departure times in the current hour */
            // hint 1: Use the "itDvB" iterator, the vector of departures is sorted
            // hint 2: The problem is very similar to the forward deprtures. 
            
            /* ***insert your code here*** */

            /* print osf and osb formatted as necessary*/
            cout << "| " << setw(2) << std::right << setfill('0') << hour << " | ";
            cout << setw(40 - 8) << std::left << setfill(' ') << osf.str() << "|";
            cout << "| " << setw(2) << std::right << setfill('0') << hour << " | ";
            cout << setw(40 - 8) << std::left << setfill(' ') << osb.str() << "|\n";
        }
        /* print footer of the table*/
        cout << setw(39) << setfill('-') << std::left << "+----+"
             << "+";
        cout << setw(39) << setfill('-') << std::left << "+----+"
             << "+\n";
    }
}

void print_line_stations(const Network &net, int ln)
{
    Line tmpL = net.getLine(ln);

    /* Printing header lines */
    print_hline();
    cout << "| Line: " << /* insert line number here */ << setw(71) << setfill(' ') << std::right << " |"
         << "\n";

    cout << setw(39) << setfill('-') << std::left << "+---+----+"
         << "+";
    cout << setw(39) << setfill('-') << std::left << "+---+----+"
         << "+\n";
    cout << setw(39) << setfill(' ') << std::left << "| d | rT | ==>"
         << "|";
    cout << setw(39) << setfill(' ') << std::left << "| d | rT | <=="
         << "|\n";
    cout << setw(39) << setfill('-') << std::left << "+---+----+"
         << "+";
    cout << setw(39) << setfill('-') << std::left << "+---+----+"
         << "+\n";

    /* your code modifications of this function should appear below this line */

    /* hint 1: use e.g. following itertors: */
    auto itSf = /* iterator pointing on the first station name of the line */
    auto itDf = /* iterator pointing on the first forward connection of the day */
    auto itSb = /* reverse iterator pointing on the last station name of the line */
    auto itDb = /* iterator pointing on the first backward connection of the day */
    
    /* hint 2: use a single loop to iterate through the station forwards and backwards */
    /*some kind of loop ( )*/
    {

        /*hint 3: use the following snippets for correct formatting*/
        /* forward direction (left half of the output) */
        cout << "| " << setw(1)  << setfill('0') << std::right << /* integer minutes from previous stop*/ 
            << " | " << setw(2)  << setfill('0') << std::right << /* integer minutes from first fwd stop*/
            << " | " << setw(27) << setfill(' ') << std::left << /* name of the current forward stop*/
            << " |";

        /* backward direction (right half of the output) */
        cout << "| " << setw(1)  << setfill('0') << std::right << /* integer minutes from previous stop*/ 
            << " | " << setw(2)  << setfill('0') << std::right << /* integer minutes from first bwd stop*/
            << " | " << setw(27) << setfill(' ') << std::left << /* name of the current backward stop*/
            << " |\n";

        /* hint 4: do not forget to increment the iterators*/
    }

    /*print footer; no modifications necessary below this line*/
    cout << setw(39) << setfill('-') << std::left << "+---+----+" << "+";
    cout << setw(39) << setfill('-') << std::left << "+---+----+" << "+\n";
}

