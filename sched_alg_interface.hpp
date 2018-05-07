#pragma once

#include "process.hpp"
#include "states.hpp"

class SchedAlgorithmInterface
{

public:

    using OutputSignal = struct { const Process* const m_process;  const State m_state; };

    virtual std::pair<OutputSignal, OutputSignal> algorithm(const std::vector<const Process*>& readyProcesses) = 0;

};
