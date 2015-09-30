#include <map>
#include <core/issue/IssueHandlerStruct.h>
#include <core/issue/filter/UniqueFilter.h>

namespace opov {

UniqueFilter::UniqueFilter() {

}

UniqueFilter::~UniqueFilter() {

}

FilterIssueMap UniqueFilter::apply(const FilterIssueMap& map) {
	std::map<int, int> duplicates;

	FilterIssueMap filteredMap;

	for (auto& filterIssue : map) {
		int h = filterIssue.second.issue->hash();
		if (duplicates.find(h) == duplicates.end()) {
			filteredMap[filterIssue.first] = filterIssue.second;
			duplicates[h] = 0;
		} else {
			duplicates[h]++;
		}
	}

	/*TUIssuesMap filteredMap;
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
	}*/
	// TODO: What happens to the meta data?
	return filteredMap;

}

}
