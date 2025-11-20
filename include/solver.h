#ifndef _SOLVER_H
#define _SOLVER_H

#include "utils.h"
#include "problem.h"
#include <vector>


class Solver{
    public:
        Solver(const Problem& problem, int maxIter, int tabuTenure);
        void solve();
        double getBestMakespan() const { return minMakespan_m; };
        Sequence_t getBestSequence() const { return bestSequence_m; };
    private:
        int calculateMakespan(const Sequence_t& sequence);
        Sequence_t generateInitialSolution();
        const Problem& problemInst_m;
        int maxIter_m;
        OperationsMatrix_t tabuList_m;
        Sequence_t bestSequence_m;
        double minMakespan_m;
        int tabuTenure_m;
};

#endif