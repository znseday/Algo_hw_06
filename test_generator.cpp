#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "test_generator.h"
#include "mergesortclass.h"

using namespace std;

void GenTestRandom(size_t N)
{
    size_t M = pow(10, N);

    ofstream f_in("0.random_big_array\\test." + to_string(N) + ".in", ios::binary);
    if (!f_in)
    {
        cout << "Error" << endl;
        exit(0);
    }

    //cout << "sizeof(size_t) = " << sizeof(size_t) << endl;

    vector<uint16_t> v;
    v.reserve(M);

    for (size_t i = 0; i < M; ++i)
    {
        uint16_t r = rand()*65535ull/RAND_MAX;

//        if (i < 1024)
//            cout << r << endl;

        v.emplace_back(r);
        f_in.write((const char*)&r, sizeof(uint16_t));
    }
    f_in.close();

    sort(v.begin(), v.end());

    ofstream f_out("0.random_big_array\\test." + to_string(N) + ".out", ios::binary);
    f_out.write((const char*)v.data(), v.size()*sizeof(uint16_t));
    f_out.close();

// Текстовый вывод для отладки
//    ofstream out_t(to_string(N) + "_.txt");
//    for (size_t i = 0; i < M; ++i)
//        out_t << v[i] << "  ";
}

void TestMergeFiles(size_t _sizeA, size_t _sizeB)
{
    vector<uint16_t> A, B;
    A.reserve(_sizeA); B.reserve(_sizeB);

    for (size_t i = 0; i < _sizeA; ++i)
        A.emplace_back(rand()%20);

    for (size_t i = 0; i < _sizeB; ++i)
        B.emplace_back(rand()%20);

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    ofstream outA(CreateFileNameByLR(0, _sizeA-1), ios::binary);
    ofstream outB(CreateFileNameByLR(_sizeA, _sizeA+_sizeB-1), ios::binary);

    for (size_t i = 0; i < _sizeA; ++i)
        outA.write((const char*)&A[i], sizeof(uint16_t));

    for (size_t i = 0; i < _sizeB; ++i)
        outB.write((const char*)&B[i], sizeof(uint16_t));

    outA.close();
    outB.close();

    //------------

    ifstream inA(CreateFileNameByLR(0, _sizeA-1), ios::binary);
    ifstream inB(CreateFileNameByLR(_sizeA, _sizeA+_sizeB-1), ios::binary);

    uint16_t a, b, c;

    cout << "A   = ";
    for (size_t i = 0; i < _sizeA; ++i)
    {
        inA.read((char*)&a, sizeof(a));
        cout << setw(3) << a << "  ";
    }
    cout << endl;

    cout << "B   = ";
    for (size_t i = 0; i < _sizeB; ++i)
    {
        inB.read((char*)&b, sizeof(a));
        cout << setw(3) << b << "  ";
    }
    cout << endl;

    inA.close();
    inB.close();

    string res = MergeFiles(CreateFileNameByLR(0, _sizeA-1), CreateFileNameByLR(_sizeA, _sizeA+_sizeB-1));

    ifstream inRes(res, ios::binary);

    cout << "Res = ";
    while (true)
    {
        inRes.read((char*)&c, sizeof(c));
        if (inRes.eof())
            break;

        cout << setw(3) << c << "  ";
    }

    cout << endl << endl;
}
















