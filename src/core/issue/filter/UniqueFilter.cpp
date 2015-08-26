#include "core/issue/IssueHandlerStruct.h"
#include "core/issue/filter/UniqueFilter.h"

namespace opov {

UniqueFilter::UniqueFilter() {

}

UniqueFilter::~UniqueFilter() {

}

TUIssuesMap UniqueFilter::apply(const TUIssuesMap& map) {
    TUIssuesMap filteredMap;
    std::vector<int> hashes;
    for (auto& unit : map) {
        TranslationUnitIssues filteredUnit;
        filteredUnit.MainSourceFile = unit.MainSourceFile;
        for (auto& issue : unit.Issues) {
            int hash = hashIssue(issue);
            if (std::find(hashes.begin(), hashes.end(), hash)) {
                // TODO mark duplicate
            } else {
                filteredUnit.Issues.push_back(issue);
                hashes.push_back(hash);
            }
        }
        if (!filteredUnit.Issues.empty()) {
            filteredMap.insert(filteredUnit);
        }
    }
    return filteredMap;
}

}