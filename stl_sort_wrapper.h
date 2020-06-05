#ifndef STL_SORT_WRAPPER_H
#define STL_SORT_WRAPPER_H

#include "itask.h"


class STL_sort_Wrapper : public ITask
{
public:
    virtual std::vector<std::string> Run(const std::string &file_name, size_t N) override;

};

#endif // STL_SORT_WRAPPER_H
