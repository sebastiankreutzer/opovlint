#ifndef AND_FILTER_H
#define AND_FILTER_H

#include "IFilter.h"

namespace opov {
class AndFilter {
public:
	AndFilter(IFilter filter1, IFilter filter2) :
			filter1(filter1), filter2(filter2) // FIXME: Pass as pointers?
	{
	}

	virtual TUIssuesMap apply(const TUIssuesMap& map) {
		TUIssuesMap filter1Map = filter1.apply(map);
		TUIssuesMap filter2Map = filter2.apply(map);
		TUIssuesMap resultMap;
		// TODO
		// Ideas:
		// 1. Generate hashes for every issue of each map and compare them.
		//    Problem: Requirements for the hash function may differ among filters.
		// 2. Assign ID to each issue from the beginning.
		// 3. Only allow stateless filters. This will make filter composition easy, but makes UniqueFilter unusable in conjunction with other filters.

	}
private:
	IFilter filter1;
	IFilter filter2;
};
}

#endif
