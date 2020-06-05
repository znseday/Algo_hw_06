#include "linearsortclass.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <array>



using namespace std;

void CountingSort(vector<uint16_t> &v)
{
    array<size_t, 65536> s = {0};

    for (const auto &x : v)
        s[x]++;

    for (size_t i = 0; i < s.size()-1; ++i)
        s[i+1] += s[i];

    vector<uint16_t> res;
//    res.reserve(v.size());
    res.resize(v.size());

    for (auto rit = v.rbegin(); rit != v.rend(); ++rit)
    {
        s[*rit]--;
        res[s[*rit]] = move(*rit);
    }

    v = move(res);  // v.swap(res);
}

vector<string> LinearSortClass::Run(const string &file_name, size_t N)
{
    string resFileName = "res_linear_sort.out";
    size_t M = pow(10, N);

    vector<uint16_t> v;
    v.resize(M);

    ifstream in_f(file_name, ios::binary);
    if (!in_f)
    {
        cout << "Error: " << file_name << " not found" << endl;
        exit(0);
    }

    in_f.read((char*)v.data(), M*sizeof(uint16_t));

    in_f.close();


    std::chrono::time_point<ClockType> TimeStart = ClockType::now();

    CountingSort(v);

    std::chrono::time_point<ClockType> TimeEnd = ClockType::now();
    double Time = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(TimeEnd - TimeStart).count();
    Time /= 1.0e9;


    ofstream f_out(resFileName, ios::binary);
    if (!f_out)
    {
        cout << "Error: " << resFileName << " can't be created" << endl;
        exit(0);
    }

    f_out.write((const char*)v.data(), M*sizeof(uint16_t));

    vector<string> resVec;
    resVec.emplace_back(move(resFileName));
    resVec.emplace_back(to_string(Time));

    return resVec;
}
