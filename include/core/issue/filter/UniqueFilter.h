#ifndef UNIQUE_FILTER_H
#define UNIQUE_FILTER_H

#include "IFilter.h"

namespace opov {

class UniqueFilter: public IFilter {
public:
	UniqueFilter();
	virtual ~UniqueFilter();

	virtual TUIssuesMap apply(const TUIssuesMap& map) override;
};

}

#endif
