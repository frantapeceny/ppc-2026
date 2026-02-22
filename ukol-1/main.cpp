#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <iomanip>
#include "main.hpp"
#include "parse.hpp"

int main(){  
    // variable for decoded config
    config_t config;
    std::string line;
    do{
        std::getline(std::cin, line);

        config = getConfig(line);
        if(config.valid){
           // todo
        }
    }
    while(config.valid);
    
    std::vector<std::vector<int>> values;

    while(std::getline(std::cin, line)){
        std::stringstream ss(line);
        std::vector<int> row;
        std::string cell;
        int number;

        while (std::getline(ss,cell, ';')) {
            try {   // if loaded cell is number
                number = std::stoi(cell);
				row.push_back(number);
            }
            catch(const std::exception& e){ // if there is a text (SUM?)
                int sum = 1;
                row.push_back(sum);
            }
        }   
        values.push_back(row);     
    }

    // print out the config - TODO
    
	// print table
    for (std::size_t i = 0; i < values.size(); i++){
        for (std::size_t j = 0; j < values[i].size(); j++){
            std::cout << values[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}