#include <map>
#include <core/issue/IssueHandlerStruct.h>
#include <core/issue/filter/UniqueFilter.h>

namespace opov {

UniqueFilter::UniqueFilter() {

}

UniqueFilter::~UniqueFilter() {

}

TUIssuesMap UniqueFilter::apply(const TUIssuesMap& map) {
	std::map<int, int> duplicates;
	TUIssuesMap filteredMap;
	for (auto& unit : map) {
		TranslationUnitIssues& filteredUnit =
				filteredMap[unit.second.MainSourceFile];
		if (filteredUnit.MainSourceFile.empty()) {
			filteredUnit.MainSourceFile = unit.second.MainSourceFile;
		}
		for (auto& issue : unit.second.Issues) {
			int h = issue->hash();
			if (duplicates.find(h) == duplicates.end()) {
				filteredUnit.Issues.push_back(issue);
				duplicates[h] = 0;
			} else {
				duplicates[h]++;
			}
		}
		if (!filteredUnit.Issues.empty()) {
			filteredMap.erase(unit.second.MainSourceFile);
		}
	}
	// TODO: What happens to the meta data?
	return filteredMap;

}

}
