#include "cute/cute.h"
#include "cute/cute_runner.h"
#include "cute/tap_listener.h"

#include "te.h"

#include <fstream>
#include <sstream>

template<typename ConcreteTest>
struct FilesystemTemplateTest
  {
  FilesystemTemplateTest()
    {
    static_cast<ConcreteTest *>(this)->GenerateTemplates();
    }
  };

struct SimpleReplacementTest : FilesystemTemplateTest<SimpleReplacementTest>
  {
  static constexpr auto TemplateNameData = "simple_data.tpl";
  static constexpr auto TemplateNameBase = "simple_base.tpl";

  void GenerateTemplates()
    {
    auto outputData = std::ofstream{TemplateNameData};
    outputData << R"({% extends "simple_base.tpl" %})";
    auto outputBase = std::ofstream{TemplateNameBase};
    outputBase << R"({{ title }})";
    }

  void test_simple_variable_replacement()
    {
    auto buffer = std::ostringstream{};
    TMapS2M mVariables{
        { "title", { { "", "My Blog" }} }
    };

    auto oTe = Cte{mVariables, TemplateNameData};

    buffer << oTe;

    ASSERT_EQUAL(buffer.str(), R"(My Blog)");
    }
  };

int main(int argc, char const * const * argv)
  {
  auto listener = cute::tap_listener<cute::null_listener>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  auto suite = cute::suite{};

  auto oSimpleReplacementTest = SimpleReplacementTest{};
  suite += CUTE_MEMFUN(oSimpleReplacementTest, SimpleReplacementTest, test_simple_variable_replacement);

  return !runner(suite);
  }
