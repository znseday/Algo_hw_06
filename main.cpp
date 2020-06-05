#include <iostream>

// Цель: Отсортировать миллиард чисел двумя способами: внешней и линейной сортировкой.
// 1. Сгенерировать бинарный файл, который содержит N целых, 16-битных чисел (от 0 до 65535), по 2 байта на каждое число.
// Подобрать N для вашего языка программирования: 1e6, 1e7, 1e8, 1e9 или даже больше.
// 2. Написать алгоритм сортировки слиянием для сортировки файла - внешняя сортировка и замерить время его работы.
// 3. Использовать для сортировки небольших кусков (от 32 до 1024 чисел) другой алгоритм сортировки на выбор (quick, heap, shell) и сравнить время сортировки "комбинированным" алгоритмом.
// 4. Отсортировать числа одним из методов линейной сортировки, написать, какой выбрали:
// а. Блочная сортировка.
// б. Сортировка подсчётом.
// в. Поразрядная сортировка.
// 4. Опубликовать таблицу сравнения быстродействия алгоритмов 2, 3 и 4, сделать выводы.

#include "itask.h"
#include "tester.h"

#include "test_generator.h"

#include "mergesortclass.h"
#include "linearsortclass.h"
#include "stl_sort_wrapper.h"

using namespace std;
namespace fs = std::experimental::filesystem;

int main()
{
//    for (size_t i = 4; i < 10; ++i) // Генерируем основные тесты
//    {
//        GenTestRandom(i);
//        cout << i << " done." << endl;
//    }

//    TestMergeFiles(2, 2);  // проверяем Merge на малых файлах
//    TestMergeFiles(8, 8);
//    TestMergeFiles(10, 20);
//    TestMergeFiles(20, 10);

    MergeSortClass mergeSort;
    Tester testerMergeSort(&mergeSort, "0. MergeSort", fs::current_path().string() + "\\0.random_big_array");
    testerMergeSort.SetMaxTestNumber(7);
    testerMergeSort.RunTasks();

    testerMergeSort.SetMaxTestNumber(8);
    mergeSort.SetMinBlockSize(10000);
    testerMergeSort.RunTasks();

    testerMergeSort.SetMaxTestNumber(10);
    mergeSort.SetMinBlockSize(50000);
    testerMergeSort.RunTasks();

    LinearSortClass linearSort;
    Tester testerLinearSort(&linearSort, "0. CountingSort", fs::current_path().string() + "\\0.random_big_array");
    testerLinearSort.SetMaxTestNumber(10);
    testerLinearSort.RunTasks();

    STL_sort_Wrapper std_sort_Wrapper;
    Tester testerSTL_sort_Wrapper(&std_sort_Wrapper, "0. std::sort", fs::current_path().string() + "\\0.random_big_array");
    testerSTL_sort_Wrapper.SetMaxTestNumber(10);
    testerSTL_sort_Wrapper.RunTasks();

    return 0;
}
