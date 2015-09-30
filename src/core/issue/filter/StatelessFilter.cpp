#include <core/issue/filter/StatelessFilter.h>

namespace opov {

FilterIssueMap StatelessFilter::apply(const FilterIssueMap& map) {

	FilterIssueMap filteredMap;

    for (auto& filterIssue : map) {
    	if (filter(filterIssue.second)) {
    		filteredMap[filterIssue.first] = filterIssue.second;
    	}
    }

    /*
    TUIssuesMap filteredMap;
    for (auto& unit : map) {
        TranslationUnitIssues& filteredUnit = filteredMap[unit.second.MainSourceFile];
        if (filteredUnit.MainSourceFile.empty()) {
        	filteredUnit.MainSourceFile = unit.second.MainSourceFile;
        }
        for (auto& issue : unit.second.Issues) {
            if (filter(*issue)) {
                filteredUnit.Issues.push_back(issue);
            }
        }
        if (!filteredUnit.Issues.empty()) {
            filteredMap.erase(unit.second.MainSourceFile);
        }
    }*/
    return filteredMap;
}

}
