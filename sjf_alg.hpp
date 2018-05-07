#pragma once

#include <queue>
#include <map>

#include "sched_alg_interface.hpp"

struct ProcessStateAlg {
    Process *m_processAddress;
    int m_remainingBurstTime;
    std::vector <int> m_bursts;
    int m_stateIndex;
    bool waiting;
};

class myComparator {

    public:

    int operator() (const ProcessStateAlg &p1, const ProcessStateAlg &p2) {
        return p1.m_remainingBurstTime > p2.m_remainingBurstTime;
    }
};

class ShortestJobFirst : public SchedAlgorithmInterface {

    ProcessStateAlg currentRunning;

    std::vector <ProcessStateAlg> buffer;

    std::priority_queue <ProcessStateAlg, std::vector <ProcessStateAlg>, myComparator> ready_queue;

    std::map <const Process *, ProcessStateAlg> processMap;

    std::map <const Process *, int> stateIndexes;

    void remove_waiting(const int);

    void attach_ready();

    public:

    ShortestJobFirst() { currentRunning.m_processAddress = nullptr; }

    virtual ~ShortestJobFirst() = default;

    virtual std::pair <OutputSignal, OutputSignal> algorithm(const std::vector<const Process*>& readyProcesses) override;

};

