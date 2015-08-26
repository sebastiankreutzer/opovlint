#ifndef STATELESS_FILTER_H
#define STATELESS_FILTER_H

namespace opov {

class StatelessFilter : public IFilter {
    virtual TUIssueMap apply(const TUIssueMap& map);

    virtual bool filter(const Issue& issue);
};

}

#endif STATELESS_FILTER