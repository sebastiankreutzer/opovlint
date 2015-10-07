#ifndef FILTER_ISSUE_STRUCT_H
#define FILTER_ISSUE_STRUCT_H

#include <memory>
#include <map>
#include <core/issue/Issue.h>

namespace opov {

struct FilterIssue {
	int id;
	std::shared_ptr<Issue> issue;

	/*bool operator==(const FilterIssue& rhs) const {
		return id == rhs.id && issue == rhs.issue;
	}*/
};

typedef std::map<int, FilterIssue> FilterIssueMap;

}

#endif
