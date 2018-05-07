#pragma once

#include <vector>

struct Process
{
    const int m_pid;
    const int m_arivalTime;
    const std::vector<int> m_bursts;
};
