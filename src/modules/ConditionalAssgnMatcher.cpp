/*
 * ConditionalAssgnMatcher.cpp
 *
 *  Created on: Jun 24, 2014
 *      Author: ahueck
 */

#include <modules/ConditionalAssgnMatcher.h>
#include <core/utility/ClangMatcherExt.h>
#include <core/module/ModuleContext.h>
#include <core/utility/ClangUtil.h>
#include <core/utility/Util.h>
#include <core/configuration/Configuration.h>
#include <core/issue/IssueHandler.h>

namespace opov {
namespace module {

using namespace clang;
using namespace clang::ast_matchers;

ConditionalAssgnMatcher::ConditionalAssgnMatcher() {
  // TODO Auto-generated constructor stub
}

void ConditionalAssgnMatcher::setupOnce(const Configuration* config) {
  config->getValue("global:type", type_s);
}

void ConditionalAssgnMatcher::setupMatcher() {
  // TODO use ofType instead of just typedef?
  StatementMatcher condassign = conditionalOperator(hasDescendant(expr(isTypedef(type_s)))).bind("condassign");
  this->addMatcher(condassign);
}

void ConditionalAssgnMatcher::run(const clang::ast_matchers::MatchFinder::MatchResult& result) {
  const ConditionalOperator* e = result.Nodes.getStmtAs<ConditionalOperator>("condassign");

  auto& sm = context->getSourceManager();
  auto& ihandle = context->getIssueHandler();
  auto& ac = context->getASTContext();
  ihandle.addIssue(sm, ac, e, moduleName(), moduleDescription());
}

std::string ConditionalAssgnMatcher::moduleName() {
  return "ConditionalAssgnMatcher";
}

std::string ConditionalAssgnMatcher::moduleDescription() {
  return "Conditional assignments (?:) are not allowed with ADOL-C.";
}

ConditionalAssgnMatcher::~ConditionalAssgnMatcher() {
}

} /* namespace module */
} /* namespace opov */
