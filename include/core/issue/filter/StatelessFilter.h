#ifndef STATELESS_FILTER_H
#define STATELESS_FILTER_H

#include "IFilter.h"

namespace opov {

class StatelessFilter : public IFilter {
public:
	virtual ~StatelessFilter() {};
    virtual FilterIssueMap apply(const FilterIssueMap& map);
    virtual bool filter(const FilterIssue& issue) const = 0;
};

}

#endif
