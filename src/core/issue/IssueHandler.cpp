/*
 * IssueHandler.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: ahueck
 */

#include <core/issue/IssueHandler.h>

namespace opov {

IssueHandler::IssueHandler() : source(""), issues() {
}

void IssueHandler::addIssue(std::shared_ptr<Issue> issue) {
	TranslationUnitIssues& tunit = issues[source];
	if (tunit.MainSourceFile.empty()) {
		tunit.MainSourceFile = source;
	}
	tunit.Issues.push_back(issue);
}

void IssueHandler::setSource(const std::string& current) {
	source = current;
}

TUIssuesMap& IssueHandler::getAllIssues() {
	return issues;
}

void IssueHandler::clear() {
	source = "";
	issues.clear();
}

IssueHandler::~IssueHandler() {
}

} /* namespace opov */
