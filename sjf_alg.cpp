#include "sjf_alg.hpp"

#include <iostream>

void ShortestJobFirst::remove_waiting(const int index){

}

void ShortestJobFirst::attach_ready(){

}

std::pair <SchedAlgorithmInterface::OutputSignal, SchedAlgorithmInterface::OutputSignal>
            ShortestJobFirst::algorithm(const std::vector <const Process*> &readyProcesses){

    static int test = 0;
    if(readyProcesses.size() > 0)
        std::cout<<"Time: "<<test<<std::endl;
    ++test;

    if(currentRunning.m_processAddress != nullptr && currentRunning.m_stateIndex % 2 == 0){
        --currentRunning.m_remainingBurstTime;
        --currentRunning.m_bursts[currentRunning.m_stateIndex];
    }

    int readySize = readyProcesses.size(), burstTime, burstSize;

    for (std::size_t i = 0; i < readySize; ++i){
        burstTime = 0;
        burstSize = readyProcesses[i]->m_bursts.size();
        if(stateIndexes.count(readyProcesses[i]) == 0)
            stateIndexes[readyProcesses[i]] = 0;

        for (std::size_t j = 0; j < burstSize; j += 2)
            burstTime += readyProcesses[i]->m_bursts[j];

        if(stateIndexes[readyProcesses[i]] == 0){
            ProcessStateAlg to_push = {const_cast <Process *> (readyProcesses[i]), burstTime,
                                                            readyProcesses[i]->m_bursts, stateIndexes[readyProcesses[i]]};
            ready_queue.push(to_push);
        }
        else if(stateIndexes[readyProcesses[i]] % 2 == 1 && currentRunning.m_bursts[currentRunning.m_stateIndex] == 0){
            std::cerr<<test<<std::endl;
            while(ready_queue.top().m_processAddress != readyProcesses[i]){
                buffer.push_back(ready_queue.top());
                ready_queue.pop();
            }
            buffer.push_back(ready_queue.top());
            ready_queue.pop();
            ++buffer.back().m_stateIndex;
            ++stateIndexes[buffer.back().m_processAddress];
            for(auto &it : buffer)
                ready_queue.push(it);
        }
    }

    /*if(ready_queue.size() > 0){
        auto temp = ready_queue.top();
        ready_queue.pop();
        temp.waiting = false;
    }*/
    //ready_queue.push(temp);

    if(currentRunning.m_processAddress != nullptr) {
        if(currentRunning.m_remainingBurstTime == 0) {
            if(ready_queue.size() > 0) {
                auto to_terminate = currentRunning;
                currentRunning = ready_queue.top();
                ready_queue.pop();
                OutputSignal out1 = {to_terminate.m_processAddress, State::E_TERMINATED};
                OutputSignal out2 = {currentRunning.m_processAddress, State::E_RESPONDED};
                return std::make_pair(out1, out2);
            }
            else {
                OutputSignal out1 = {currentRunning.m_processAddress, State::E_TERMINATED};
                OutputSignal out2 = {nullptr, State::E_RESPONDED};
                return std::make_pair(out1, out2);
            }
        } else if (currentRunning.m_bursts[currentRunning.m_stateIndex] == 0) {
            ++currentRunning.m_stateIndex;
            ++stateIndexes[currentRunning.m_processAddress];
            ready_queue.push(currentRunning);
            currentRunning = ready_queue.top();
            //ready_queue.push(currentRunning);
            //currentRunning.m_processAddress = nullptr;
            //auto temp = currentRunning;
            //currentRunning = ready_queue.top();
            //ready_queue.pop();
            //ready_queue.push(temp);
            //currentRunning.waiting = true;
            /*if(ready_queue.size() > 0){
                auto temp = ready_queue.top();
                ready_queue.pop();
                temp.waiting = false;
                ready_queue.push(temp);
            }*/
            OutputSignal out1 = {currentRunning.m_processAddress, State::E_WAITING_FOR_IO};
            OutputSignal out2 = {nullptr, State::E_RESPONDED};
            return std::make_pair(out1, out2);
        } else if (ready_queue.size() > 0 && currentRunning.m_remainingBurstTime > ready_queue.top().m_remainingBurstTime) {
            ready_queue.push(currentRunning);
            currentRunning = ready_queue.top();
            //ready_queue.pop();
            OutputSignal out1 = {nullptr, State::E_WAITING_FOR_IO};
            OutputSignal out2 = {currentRunning.m_processAddress, State::E_RESPONDED};
            return std::make_pair(out1, out2);
        } else {
            OutputSignal out1 = {nullptr, State::E_WAITING_FOR_IO};
            OutputSignal out2 = {currentRunning.m_processAddress, State::E_RESPONDED};
            return std::make_pair(out1, out2);
        }
    }
    else {
        if(ready_queue.size() > 0){//} && ready_queue.top().m_bursts[ready_queue.top().m_stateIndex] % 2 == 0) {
            currentRunning = ready_queue.top();
            //ready_queue.pop();
        }
        else {
            OutputSignal out1 = {nullptr, State::E_TERMINATED};
            OutputSignal out2 = {nullptr, State::E_TERMINATED};
            return std::make_pair(out1, out2);
        }
    }
}
