// Header-only library for otus-algo homework testing
// Written by Sergey Tsynikin, 2020

#ifndef ITASK_H
#define ITASK_H

#include <string>
#include <vector>

#include <chrono>

using ClockType = std::chrono::steady_clock;

class ITask
{
public:
    virtual std::vector<std::string> Run(const std::string &file_name, size_t N) = 0;
    virtual ~ITask() {};
};

#endif // ITASK_H
