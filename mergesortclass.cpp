#include "mergesortclass.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <experimental\filesystem>
//#include <cstdio>

#define MY_DEL_TEMP_FILES

using namespace std;

namespace fs = std::experimental::filesystem;

string CreateFileNameByLR(int l, int r)
{
    return to_string(l) + "-" + to_string(r);
}

string MergeFiles(const string &file_1, const string &file_2)
{
    int newL = -1, newR = -1;
    sscanf(file_2.c_str(), "%i-%i", &newL, &newR); // newL - игнорируется
    sscanf(file_1.c_str(), "%i", &newL); // а здесь настоящий newL

    string resFile = CreateFileNameByLR(newL, newR);

    ifstream in_1(file_1, ios::binary);
    ifstream in_2(file_2, ios::binary);

    ofstream res_out(resFile, ios::binary);

    uint16_t a, b;

    if ( !in_1.eof() && !in_2.eof() )
    {
        in_1.read((char*)&a, sizeof(a));
        in_2.read((char*)&b, sizeof(b));
    }
    else
        throw invalid_argument("files eof");

    do
    {
        if (a < b)
        {
            res_out.write((const char*)&a, sizeof(a));
            in_1.read((char*)&a, sizeof(a));
        }
        else
        {
            res_out.write((const char*)&b, sizeof(b));
            in_2.read((char*)&b, sizeof(b));
        }

    } while (!in_1.eof() && !in_2.eof());

    while (!in_1.eof())
    {
        res_out.write((const char*)&a, sizeof(a));
        in_1.read((char*)&a, sizeof(a));
    }

    while (!in_2.eof())
    {
        res_out.write((const char*)&b, sizeof(b));
        in_2.read((char*)&b, sizeof(b));
    }

    in_1.close();
    in_2.close();
    res_out.close();

#ifdef MY_DEL_TEMP_FILES
    int rc = remove(file_1.c_str());
    if (rc)
    {
        perror(("remove " + file_1).c_str());
        exit(EXIT_FAILURE);
    }
    rc = remove(file_2.c_str());
    if (rc)
    {
        perror(("remove " + file_2).c_str());
        exit(EXIT_FAILURE);
    }
#endif

// Текстовый вывод для отладки
//    ifstream in_t(resFile, ios::binary);
//    vector<uint16_t> v(newR-newL+1);
//    in_t.read((char*)v.data(), v.size()*sizeof(uint16_t));
//    in_t.close();
//    ofstream out_t(resFile + "_my_out.txt");
//    for (size_t i = 0; i < v.size(); ++i)
//        out_t << v[i] << "  ";

    return resFile;
}

void MergeSortClass::CreateSortedFile(size_t l, size_t r)
{
    ifstream in_f(SrcFile, ios::binary);
    if (!in_f)
    {
        cout << "Error: file" << SrcFile << " is not be open" << endl;
        exit(EXIT_FAILURE);
    }

    in_f.seekg(l*sizeof(uint16_t));

    const int count = r-l+1;
    vector<uint16_t> buff(count);
    in_f.read((char*)buff.data(), count*sizeof(uint16_t));
    in_f.close();

    sort(buff.begin(), buff.end());

    ofstream out_f(CreateFileNameByLR(l, r), ios::binary);
    if (!out_f)
    {
        cout << "Error: file" << CreateFileNameByLR(l, r) << " is not be open" << endl;
        exit(EXIT_FAILURE);
    }
    out_f.write((const char*)buff.data(), count*sizeof(uint16_t));

// Текстовый вывод для отладки
//    ifstream in_t(CreateFileNameByLR(l, r), ios::binary);
//    vector<uint16_t> v(buff.size());
//    in_t.read((char*)v.data(), v.size()*sizeof(uint16_t));
//    in_t.close();
//    ofstream out_t(CreateFileNameByLR(l, r) + "_my_out.txt");
//    for (size_t i = 0; i < v.size(); ++i)
//        out_t << v[i] << "  ";

}

void MergeSortClass::MergeSort(size_t l, size_t r)
{
    if (r - l <= MinBlockSize)
        CreateSortedFile(l, r);
    else
    {
        int c = (l+r)/2;
        MergeSort(l, c);
        MergeSort(c+1, r);

        MergeFiles(CreateFileNameByLR(l, c), CreateFileNameByLR(c+1, r));
    }
}


vector<string> MergeSortClass::Run(const string &file_name, size_t N)
{
    SrcFile = file_name;

    size_t M = pow(10, N);

    cout << "MinBlockSize = " << MinBlockSize << endl;

//    string resFileName = "res_merge_sort.out";
    string resFileName = CreateFileNameByLR(0, M-1);

    std::chrono::time_point<ClockType> TimeStart = ClockType::now();

    MergeSort(0, M-1);

    std::chrono::time_point<ClockType> TimeEnd = ClockType::now();
    double Time = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(TimeEnd - TimeStart).count();
    Time /= 1.0e9;

// Текстовый вывод для отладки
//    ifstream in_t(resFileName, ios::binary);
//    vector<uint16_t> v(M);
//    in_t.read((char*)v.data(), v.size()*sizeof(uint16_t));
//    in_t.close();
//    ofstream out_t(to_string(N) + "_my_out.txt");
//    for (size_t i = 0; i < M; ++i)
//        out_t << v[i] << "  ";


    vector<string> resVec;
    resVec.emplace_back(move(resFileName));
    resVec.emplace_back(to_string(Time));

    return resVec;
}

