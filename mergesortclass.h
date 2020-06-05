#ifndef MERGESORTCLASS_H
#define MERGESORTCLASS_H

#include "itask.h"

#include <string>

std::string CreateFileNameByLR(int l, int r);

std::string MergeFiles(const std::string &file_1, const std::string &file_2);


class MergeSortClass : public ITask
{
private:

    std::string SrcFile;
    size_t MinBlockSize = 1000;

    void MergeSort(size_t l, size_t r);
    void CreateSortedFile(size_t l, size_t r);

public:
    virtual std::vector<std::string> Run(const std::string &file_name, size_t N) override;

    void SetMinBlockSize(size_t _minBlockSize) {MinBlockSize = _minBlockSize;}
};

#endif // MERGESORTCLASS_H
