#ifndef TRUE_FILTER_H
#define TRUE_FILTER_H

#include "StatelessFilter.h"

namespace opov {

class TrueFilter: public StatelessFilter {
public:
	virtual bool filter(const FilterIssue& issue) const {
		return true;
	}
};

}

#endif
