#ifndef FILTERING_H
#define FILTERING_H

#include <core/issue/IssueHandlerStruct.h>

namespace opov {

class IFilter;

class Filtering {
public:
	Filtering(IFilter* mainFilter); // TODO Change to some kind of smart pointer
	~Filtering();

	TUIssuesMap filter(const TUIssuesMap& unfilteredMap);
private:
	IFilter* mainFilter;
};


}

#endif
