#include "doprava.hpp"
#include <iomanip>
#include <numeric>
using namespace std;

void print_timetable(const Network& net, const string& stop);
void print_line_stations(const Network &net, int ln);