#include <core/issue/filter/StatelessFilter.h>

namespace opov {

TUIssuesMap StatelessFilter::apply(const TUIssuesMap& map) {
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
    }
    return filteredMap;
}

}
