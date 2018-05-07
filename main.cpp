#include <iostream>
#include "simulator.hpp"
#include "sjf_alg.hpp"

int main()
{
    std::cout << "Enter the number of processes you wish to simulate: ";
    auto numberOfProcesses = 0; std::cin >> numberOfProcesses;
    std::vector<Process> processes;
    for (auto i = 0; i < numberOfProcesses; ++i) {
        std::cout << "Current process: PID " << i << "\n";
        std::cout << "\tEnter the arival time: ";
        int arivalTime; std::cin >> arivalTime;
        std::cout << "\tEnter the number of bursts: ";
        int numberOfBursts; std::cin >> numberOfBursts;
        std::vector<int> bursts;
        for (auto j = 0; j < numberOfBursts; ++j) {
            std::cout << "\t\t" << ((j & 1) ? "I/O" : "CPU") << " burst length: ";
            int currentBurst; std::cin >> currentBurst;
            bursts.push_back(currentBurst);
        }
        processes.push_back({ i, arivalTime, bursts });
    }
    SchedAlgorithmInterface* schedAlgorithm = nullptr;
    std::cout << "Choose which algorithm to simulate [0 - SJF]: ";
    auto algorithmChoice = 0; std::cin >> algorithmChoice;
    switch (algorithmChoice) {
        case 0: {
            schedAlgorithm = new ShortestJobFirst();
        } break;
        default: {
            std::cout << "Invalid algorithm choice!\n";
            return 0;
        }
    }
    simulate(schedAlgorithm, processes);
    return 0;
}
