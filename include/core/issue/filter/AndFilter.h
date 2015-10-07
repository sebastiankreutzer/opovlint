#ifndef AND_FILTER_H
#define AND_FILTER_H

#include "IFilter.h"

namespace opov {
class AndFilter: public IFilter {
public:
	AndFilter(IFilter* filter1, IFilter* filter2) :
			filter1(filter1), filter2(filter2)
	{
	}

	~AndFilter() {
		delete filter1;
		delete filter2;
	}

	virtual FilterIssueMap apply(const FilterIssueMap& map) {
		FilterIssueMap filter1Map = filter1->apply(map);
		FilterIssueMap filter2Map = filter2->apply(map);
		TUIssuesMap resultMap;

		for (auto& issue : filter1Map) {
			if (filter2Map.find(issue.first) != filter2Map.end())
				resultMap[issue.first] = issue.second;
		}

		return resultMap;
	}
private:
	IFilter* filter1;
	IFilter* filter2;
};
}

#endif
