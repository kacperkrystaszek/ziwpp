#include <chrono>
#include <string>
#include <iostream>
#include "solver.h"
#include "problem.h"
#include "utils.h"

int main(int argc, char* argv[]){
    if (argc != 4){
        std::cerr << "Badly passed argument. Need to pass <path_to_problem_instance> <max_iterations> <tabu_tenure>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    int maxIter = 0;
    int tabuTenure = 0;

    try {
        maxIter = std::stoi(argv[2]);
        tabuTenure = std::stoi(argv[3]);
    } catch (std::exception& e) {
        std::cerr << "<max_iterations> and <tabu_tenure> arguments have to be integers";
        return 1;
    }

    Problem problemInst;
    try {
        bool loaded = problemInst.loadFromFile(filename);
        if (!loaded) {
            return 1;
        }
    } catch (std::exception& e) {
        std::cerr << "Could not parse file. Make sure file is in format like below" << std::endl <<
        "<nJobs> <Machines> <tau>" << std::endl << 
        "job_i_j ... job_i_nMachines" << std::endl <<
        "..." << std::endl <<
        "job_nJobs_j ... job_nJobs_nMachines" << std::endl;
    }
    std::cout << "filename: " << filename << " max_iterations: " << maxIter << " tabu_tenure " << tabuTenure << std::endl;
    Solver s(problemInst, maxIter, tabuTenure);

    auto start = std::chrono::high_resolution_clock::now();
    s.solve();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Solution" << std::endl;
    Sequence_t bestFoundSequence = s.getBestSequence();
    double bestFoundMakespan = s.getBestMakespan();
    SolverUtils::printVector(bestFoundSequence);
    std::cout << "Makespan: " << bestFoundMakespan << std::endl;
    std::cout << "Elapsed: " << elapsed.count() << std::endl;

    return 0;
}