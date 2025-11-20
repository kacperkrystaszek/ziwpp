#ifndef _PROBLEM_H
#define _PROBLEM_H

#include "utils.h"
#include <vector>
#include <string>


class Problem{
    public:
        bool loadFromFile(const std::string& filename);
        OperationsMatrix_t getOperations() const { return operations_m; };
        int getJobsN() const {return nJobs_m; };
        int getMachinesN() const { return nMachines_m; };
        double getTau() const {return tau_m; };
    private:
        int nJobs_m;
        int nMachines_m;
        double tau_m;
        OperationsMatrix_t operations_m;
};

#endif