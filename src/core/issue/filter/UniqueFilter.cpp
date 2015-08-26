#include <core/issue/IssueHandlerStruct.h>
#include <core/issue/filter/UniqueFilter.h>

namespace opov {

UniqueFilter::UniqueFilter() {

}

UniqueFilter::~UniqueFilter() {

}

TUIssuesMap UniqueFilter::apply(const TUIssuesMap& map) {
	std::vector<int> hashes;
	TUIssuesMap filteredMap;
	for (auto& unit : map) {
		TranslationUnitIssues& filteredUnit =
				filteredMap[unit.second.MainSourceFile];
		if (filteredUnit.MainSourceFile.empty()) {
			filteredUnit.MainSourceFile = unit.second.MainSourceFile;
		}
		for (auto& issue : unit.second.Issues) {
			int h = issue->hash();
			auto result = std::find(hashes.begin(), hashes.end(), h);
			if (result == hashes.end()) {
				filteredUnit.Issues.push_back(issue);
				hashes.push_back(h);
			} else {
				// TODO mark duplicate
			}
		}
		if (!filteredUnit.Issues.empty()) {
			filteredMap.erase(unit.second.MainSourceFile);
		}
	}
	return filteredMap;

}

}
