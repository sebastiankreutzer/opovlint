#ifndef IFILTER_H
#define IFILTER_H

#include "core/issue/IssueHandlerStruct.h"
#include "core/issue/Issue.h"

namespace opov {

class IFilter {
public:
    virtual ~IFilter() {};
    virtual TUIssuesMap apply(const TUIssuesMap& map) = 0;
};

}

#endif
