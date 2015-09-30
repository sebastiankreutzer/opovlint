#ifndef FILTERING_H
#define FILTERING_H

#include <core/issue/IssueHandlerStruct.h>

namespace opov {

class IFilter;

class Filtering {
public:
	Filtering(IFilter* mainFilter);
	~Filtering();

	TUIssuesMap filter(const TUIssuesMap& unfilteredMap);
private:
	IFilter* mainFilter;
};


}

#endif
