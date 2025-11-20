#include "solver.h"
#include <algorithm>
#include <limits>
#include <random>

Solver::Solver(const Problem& problem, int maxIter, int tabuTenure):
    problemInst_m(problem),
    maxIter_m(maxIter),
    minMakespan_m(std::numeric_limits<double>::max()),
    tabuTenure_m(tabuTenure)
{
    int nJobs = problem.getJobsN();
    int nMachines = problem.getMachinesN();
    tabuList_m.resize(nJobs, std::vector<int>(nMachines, 0));
    bestSequence_m.resize(nJobs, 0);
};

void Solver::solve(){
    int nJobs = problemInst_m.getJobsN();

    if (nJobs == 0) return;
    
    Sequence_t currentSequence = generateInitialSolution();
    bestSequence_m = currentSequence;
    minMakespan_m = calculateMakespan(bestSequence_m);

    for (int iter = 0; iter < maxIter_m; iter++)
    {
        Sequence_t bestNeighborSequence;
        double bestNeighborMakespan = std::numeric_limits<double>::max();
        Move_t bestMove = {-1, 1};

        for (int i = 0; i < nJobs; i++)
        {
            for (int j = i + 1; j < nJobs; j++)
            {
                Sequence_t neighborSequence = currentSequence;
                std::swap(neighborSequence[i], neighborSequence[j]);
                double neighborMakespan = calculateMakespan(neighborSequence);

                int job1 = currentSequence[i];
                int job2 = currentSequence[j];

                bool isTabu = tabuList_m[job1][job2] > iter;
                bool aspiration = neighborMakespan < minMakespan_m;
                bool condition = aspiration || (!isTabu && neighborMakespan < bestNeighborMakespan);

                if (!condition) continue;

                bestNeighborMakespan = neighborMakespan;
                bestNeighborSequence = neighborSequence;
                bestMove = {i, j};
            }
        }
        
        if (bestMove.first != -1) {
            currentSequence = bestNeighborSequence;
            int job1Moved = currentSequence[bestMove.second];
            int job2Moved = currentSequence[bestMove.first];

            tabuList_m[job1Moved][job2Moved] = iter + tabuTenure_m;
            tabuList_m[job2Moved][job1Moved] = iter + tabuTenure_m;

            if(bestNeighborMakespan < minMakespan_m){
                minMakespan_m = bestNeighborMakespan;
                bestSequence_m = bestNeighborSequence;
            }
        }
    }
};

int Solver::calculateMakespan(const Sequence_t& sequence){
    int nJobs = problemInst_m.getJobsN();
    int nMachines = problemInst_m.getMachinesN();
    double tau = problemInst_m.getTau();
    const OperationsMatrix_t operations = problemInst_m.getOperations();

    if(nJobs == 0) return 0.0;

    CompletionTimeMatrix_t completionTimes(nJobs, std::vector<double>(nMachines, 0.0));

    for (int k = 0; k < nJobs; k++)
    {
        int jobIndex = sequence[k];
        double learningFactor = pow(static_cast<double>(k+1), tau);
        for (int i = 0; i < nMachines; i++)
        {
            double currentTime = operations[jobIndex][i] * learningFactor;

            double timeAfterPrevOpOnSameMachine = (k == 0) ? 0.0 : completionTimes[k-1][i];
            double timeAfterPrevOpOfSameJob = (i == 0) ? 0.0 : completionTimes[k][i-1];

            completionTimes[k][i] = std::max(
                timeAfterPrevOpOnSameMachine,
                timeAfterPrevOpOfSameJob
            ) + currentTime;
        }
    }
    
    return completionTimes[nJobs-1][nMachines-1];
};

Sequence_t Solver::generateInitialSolution(){
    int nJobs = problemInst_m.getJobsN();
    Sequence_t solution(nJobs);
    std::iota(solution.begin(), solution.end(), 0);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(solution.begin(), solution.end(), g);

    return solution;
};
