#include <iostream>
#include "utils.h"

void SolverUtils::printVector(Sequence_t& sequence){
    int size = sequence.size();
    for (int i = 1; i < size + 1; i++)
    {
        int jobId = sequence[i-1] + 1;
        std::cout << "Order: " << i << " " << "JobID: " << jobId << std::endl;
    }
    return;
};