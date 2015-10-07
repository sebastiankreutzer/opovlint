/*
 * test_system.cpp
 *
 *  Created on: Jul 2, 2014
 *      Author: ahueck
 */

#include <TestApp.h>

#include <core/utility/ClangUtil.h>
#include <core/utility/Util.h>
#include <core/module/ASTMatcherModule.h>
#include <core/configuration/JSONConfiguration.h>
#include <modules/ExplicitCast.h>
#include <core/issue/filter/TrueFilter.h>
#include <core/issue/filter/UniqueFilter.h>
#include <core/issue/filter/Filtering.h>

#include <string>
#include <memory>

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>


TEST_CASE("Configuration", "[config]") {
	const std::string file = "test/data/config.json";
	std::unique_ptr<opov::Configuration> config = opov::util::make_unique<opov::JSONConfiguration>();
    SECTION("Simple Parsing") {
    	std::string tmp;
    	REQUIRE_NOTHROW(config->load(file));
    	config->getValue("test", tmp);
    	REQUIRE(tmp == "data");
    	config->getValue("geo", tmp);
    	REQUIRE(tmp == "");
    	config->getValue("geo:type", tmp);
    	REQUIRE(tmp == "Point");
    	std::vector<double> tmpv;
    	config->getVector("geo:coordinates", tmpv);
    	REQUIRE(tmpv.size() == 2);
    	REQUIRE(tmpv[0] == 37.871609);
    }

    SECTION("Parsing Twice") {
    	REQUIRE_NOTHROW(config->load(file));
    	std::string tmp;
    	std::vector<double> tmpv;
    	for (int var = 0; var < 2; ++var) {
        	REQUIRE_NOTHROW(config->load(file));
        	config->getValue("test", tmp);
        	REQUIRE(tmp == "data");
        	config->getValue("geo", tmp);
        	REQUIRE(tmp == "");
        	config->getValue("geo:type", tmp);
        	REQUIRE(tmp == "Point");
        	tmpv.clear();
        	config->getVector("geo:coordinates", tmpv);
        	REQUIRE(tmpv.size() == 2);
        	REQUIRE(tmpv[0] == 37.871609);
		}
    }

    SECTION("Parsing All") {
    	REQUIRE_NOTHROW(config->load(file));
    	std::vector<double> tmpvd;
    	config->getVector("vectors:a", tmpvd);
    	REQUIRE(tmpvd.size() == 2);
    	REQUIRE(tmpvd[0] == 37.871609);
    	REQUIRE(tmpvd[1] == -122.25831);
    	std::vector<int> tmpvi;
    	config->getVector("vectors:b", tmpvi);
    	REQUIRE(tmpvi.size() == 2);
    	REQUIRE(tmpvi[0] == 10);
    	REQUIRE(tmpvi[1] == 20);
    	std::vector<std::string> tmpvs;
    	config->getVector("vectors:c", tmpvs);
    	REQUIRE(tmpvs.size() == 2);
    	REQUIRE(tmpvs[0] == "c_aa");
    	REQUIRE(tmpvs[1] == "c_bb");
    }

    SECTION("Parsing Default Value") {
    	REQUIRE_NOTHROW(config->load(file));
    	std::vector<double> tmpvd;
    	config->getVector("vectors:aaa", tmpvd);
    	REQUIRE(tmpvd.size() == 0);

    	std::string tmp;
    	config->getValue("test_ne", tmp, "la");
    	REQUIRE(tmp == "la");
    	config->getValue("geo_ne", tmp);
    	REQUIRE(tmp == "");
    	config->getValue("geo:type:ne", tmp, "bla");
    	REQUIRE(tmp == "bla");
    }

    SECTION("Parsing Default Lvalue") {
    	REQUIRE_NOTHROW(config->load(file));
    	std::string tmp;
    	std::string def = "lvalue";
    	config->getValue("test_ne", tmp, def);
    	REQUIRE(tmp == "lvalue");
    	config->getValue("geo_ne", tmp, def);
    	REQUIRE(tmp == "lvalue");
    	config->getValue("geo:type:ne", tmp, def);
    	REQUIRE(tmp == "lvalue");
    }
}


TEST_CASE("TransformationHandle", "[thandle]") {
	opov::test::TestApp app(conf);
	app.init();
	app.addModule(new opov::module::ExplicitCast());
	const std::string code = "typedef double scalar; scalar a = 10.0; void container() { int res = 0.0; res = static_cast<double>(a); }";
    SECTION("No transformation state") {
		auto handle = app.getHandler();
		REQUIRE(handle->getIncludeDirectives() == nullptr);
		REQUIRE(handle->getAllReplacements().size() == 0);
    }
    SECTION("Transformation on empty code state") {
		auto handle = app.getHandler();
		app.executeOnCode("");
		REQUIRE(handle->getIncludeDirectives() != nullptr);
		REQUIRE(handle->getAllReplacements().size() == 0);
    }
    SECTION("Transformation on code state") {
		auto handle = app.getHandler();
		app.executeOnCode(code);
		REQUIRE(handle->getIncludeDirectives() != nullptr);
		//REQUIRE(handle->getAllReplacements().size() == 1);
    }
}

// Isolated filtering test cases (does not test system as a whole)
TEST_CASE("Filter", "[filter]") {
	opov::test::TestApp app(conf);
	app.init();

	std::shared_ptr<opov::Issue> issue1 = std::make_shared<opov::Issue>();
	issue1->setModuleName("TestModule1");
	opov::FilterIssue filterIssue1;
	filterIssue1.id = 0;
	filterIssue1.issue = issue1;


	std::shared_ptr<opov::Issue> issue2 = std::make_shared<opov::Issue>();
	issue2->setModuleName("TestModule2");
	opov::FilterIssue filterIssue2;
	filterIssue1.id = 1;
	filterIssue1.issue = issue2;

	std::shared_ptr<opov::Issue> issue1Clone = std::make_shared<opov::Issue>();
	issue1Clone->setModuleName("TestModule1");
	opov::FilterIssue filterIssue1Clone;
	filterIssue1.id = 2;
	filterIssue1.issue = issue1Clone;

	opov::FilterIssueMap map;
	map[0] = filterIssue1;
	map[1] = filterIssue2;
	map[2] = filterIssue1Clone;

	SECTION("Issue hashing") {
		int h1 = issue1->hash();
		int h2 = issue2->hash();
		int h3 = issue1Clone->hash();
		REQUIRE(h1 != h2);
		REQUIRE(h1 == h3);
	}

	SECTION("Accept everything") {
		opov::TrueFilter trueFilter;
		opov::FilterIssueMap result = trueFilter.apply(map);
		REQUIRE(result.size() == 3);
	}

	SECTION("Unique Filter") {
		opov::UniqueFilter uniqueFilter;
		opov::FilterIssueMap result = uniqueFilter.apply(map);
		REQUIRE(result.size() == 2);
	}
}
