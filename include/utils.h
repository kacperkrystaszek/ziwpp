#ifndef _UTILS_H
#define _UTILS_H

#include <vector>


typedef std::vector<std::vector<int>> OperationsMatrix_t;
typedef std::vector<int> Sequence_t;
typedef std::vector<std::vector<double>> CompletionTimeMatrix_t;
typedef std::pair<int, int> Move_t;


namespace SolverUtils {
    void printVector(Sequence_t& sequence);
};

#endif