// Header-only library for otus-algo homework testing
// Written by Sergey Tsynikin, 2020

#ifndef TESTER_H
#define TESTER_H

#include <string>
#include <iostream>
#include <fstream>
#include <experimental\filesystem>
#include <chrono>
#include <iomanip>
#include <list>
#include <tuple>
#include <cstring>

#include "itask.h"

namespace fs = std::experimental::filesystem;

using ClockType = std::chrono::steady_clock;

const size_t BlockSize = 1024*64;

bool IsIdenticFiles(const std::string &f1, const std::string &f2)
{
    size_t firstSize = fs::file_size(f1);
    size_t secondSize = fs::file_size(f2);

    if (firstSize != secondSize)
        return false;

    size_t blockCount = firstSize / BlockSize + 1;
    size_t lastSize = firstSize % BlockSize;

    std::vector<char> buf_1(BlockSize);
    std::vector<char> buf_2(BlockSize);

    std::ifstream in_f_1(f1, std::ios::binary);
    if (!in_f_1)
    {
        std::cout << "error: file " << f1 << " not found" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::ifstream in_f_2(f2, std::ios::binary);
    if (!in_f_2)
    {
        std::cout << "error: file " << f2 << " not found" << std::endl;
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < blockCount; i++)
    {
        if (i == blockCount - 1)
        {
            in_f_1.read(buf_1.data(), lastSize);
            std::memset(buf_1.data() + lastSize, 0, buf_1.size() - lastSize);
            in_f_2.read(buf_2.data(), lastSize);
            std::memset(buf_2.data() + lastSize, 0, buf_2.size() - lastSize);
        }
        else
        {
            in_f_1.read(buf_1.data(), buf_1.size());
            in_f_2.read(buf_2.data(), buf_2.size());
        }

        if ( memcmp(buf_1.data(), buf_2.data(), BlockSize) )
            return false;
    }

    return true;
}


class Tester
{
protected:

    std::list<std::tuple<std::string, ITask*>> Tasks;

    std::string Path;

    ITask *ActiveTask = nullptr;

    size_t MaxTestNumber = 20;

    void RunTests()
    {
        std::cout << std::setw(6) << "Test#" << std::setw(8) <<
                     "Status" << std::setw(14) << "Time, s" << std::endl;

        std::cout << std::boolalpha;

        for (size_t nr = 0; nr <= MaxTestNumber; ++nr)
        {
            std::string inFile  = Path + "\\test." + std::to_string(nr) + ".in";
            std::string outFile = Path + "\\test." + std::to_string(nr) + ".out";

            if ( !fs::exists(inFile) || !fs::exists(outFile) )
                continue;

            std::cout << std::setw(6) << nr << ":" << std::endl;
            bool res_test = RunTest(inFile, outFile, nr);
            std::cout << "Test passed: " << res_test << std::endl << std::endl;

        }
    }

    bool RunTest(const std::string &_inFile, const std::string &_outFile, size_t N)
    {
        //std::chrono::time_point<ClockType> TimeStart = ClockType::now();

        std::vector<std::string> ResultVec = ActiveTask->Run(_inFile, N);
        std::string ResultFileName = ResultVec.front();

        //std::chrono::time_point<ClockType> TimeEnd = ClockType::now();

        std::string Time = ResultVec.back();

        std::string t = _outFile;
        auto pos = t.find_last_of('\\');
        t = t.substr(0, pos);
        pos = t.find_last_of('\\');
        t = t.substr(0, pos+1);
        ResultFileName = t + ResultFileName;

        bool res = IsIdenticFiles(_outFile, ResultFileName);

        std::cout <<  std::setw(14) << res << std::setw(14) << Time << std::endl;

        return res;
    }

public:
    Tester() = delete;

    void AddTask(ITask *_task, const std::string &_name)
    {
        Tasks.emplace_back(_name, _task);
    }

    Tester(ITask *_task, const std::string &_name, const std::string &_path) : Path(_path)
    {
        AddTask(_task, _name);
    }

    void RunTasks()
    {
        for (const auto [name, task] : Tasks)
        {
            std::cout << "Task - " << name << ":" << std::endl;
            ActiveTask = task;
            RunTests();
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

    void SetMaxTestNumber(size_t _maxTestNumber) {MaxTestNumber = _maxTestNumber;}

};

#endif // TESTER_H
