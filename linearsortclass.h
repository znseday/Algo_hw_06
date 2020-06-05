#ifndef LINEARSORTCLASS_H
#define LINEARSORTCLASS_H

#include "itask.h"


class LinearSortClass : public ITask
{
public:
    virtual std::vector<std::string> Run(const std::string &file_name, size_t N) override;
};

#endif // LINEARSORTCLASS_H
