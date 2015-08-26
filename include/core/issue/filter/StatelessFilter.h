#ifndef STATELESS_FILTER_H
#define STATELESS_FILTER_H

#include "IFilter.h"

namespace opov {

class StatelessFilter : public IFilter {
public:
    virtual TUIssuesMap apply(const TUIssuesMap& map);
    virtual bool filter(const Issue& issue) const = 0;
};

}

#endif
