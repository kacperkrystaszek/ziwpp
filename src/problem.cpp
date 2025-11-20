#include "problem.h"
#include <fstream>
#include <iostream>

bool Problem::loadFromFile(const std::string& filename){
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr << "Error: Could not open file" << filename << std::endl;
        return false;
    }

    file >> nJobs_m >> nMachines_m >> tau_m;
    operations_m.resize(nJobs_m, std::vector<int>(nMachines_m));
    for (int i = 0; i < nJobs_m; i++)
    {
        for (int j = 0; j < nMachines_m; j++)
        {
            file >> operations_m[i][j];
        }
    }
    file.close();
    return true;
};
