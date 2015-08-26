#include "core/issue/filter/StatelessFilter.h"

namespace opov {

TUIssuesMap UniqueFilter::apply(const TUIssuesMap& map) {
    TUIssuesMap filteredMap;
    for (auto& unit : map) {
        TranslationUnitIssues filteredUnit;
        filteredUnit.MainSourceFile = unit.MainSourceFile;
        for (auto& issue : unit.Issues) {
            if (filter(issue)) {
                filteredUnit.Issues.push_back(issue);
            }
        }
        if (!filteredUnit.Issues.empty()) {
            filteredMap.insert(filteredUnit);
        }
    }
    return filteredMap;
}

}