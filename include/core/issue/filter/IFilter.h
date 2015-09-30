#ifndef IFILTER_H
#define IFILTER_H

#include "core/issue/filter/FilterIssueStruct.h"
#include "core/issue/Issue.h"

namespace opov {

class IFilter {
public:
    virtual ~IFilter() {};
    virtual FilterIssueMap apply(const FilterIssueMap& map) = 0;
};

}

#endif
