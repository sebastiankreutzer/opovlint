/*
 * CSVReporter.h
 *
 *  Created on: May 18, 2014
 *      Author: ahueck
 */

#ifndef CSVREPORTER_H_
#define CSVREPORTER_H_

#include "IssueReporter.h"

//#include <string>

namespace opov {

class CSVReporter : public opov::IssueReporter {
 public:
  CSVReporter();
  virtual void addIssue(const TranslationUnitIssues& issue) override;
  virtual void addIssues(const TUIssuesMap& issues) override;
  virtual ~CSVReporter();

 private:
  void print(const TranslationUnitIssues& issue);
};

}  // namespace opov

#endif /* CSVREPORTER_H_ */
