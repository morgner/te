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

struct SimpleReplacementTest001 : FilesystemTemplateTest<SimpleReplacementTest001>
  {
  static constexpr auto TemplateName = "simple_replacement001.tpl";

  void GenerateTemplates()
    {
    auto output = std::ofstream{TemplateName};
    output << "{{ variable }}";
    }

  void test_simple_variable_replacement()
    {
    auto buffer = std::ostringstream{};
    TMapS2M mVariables{
        { "variable", {{ "", "replacement" }} }
    };

    auto oTe = Cte{mVariables, TemplateName};

    buffer << oTe;

    ASSERT_EQUAL(buffer.str(), "replacement");
    }
  };

struct SimpleReplacementTest002 : FilesystemTemplateTest<SimpleReplacementTest002>
  {
  static constexpr auto TemplateName = "simple_replacement002.tpl";

  void GenerateTemplates()
    {
    auto output = std::ofstream{TemplateName};
    output << "before {{ variable }} after";
    }

  void test_simple_variable_replacement()
    {
    auto buffer = std::ostringstream{};
    TMapS2M mVariables{
        { "variable", {{ "", "replacement" }} }
    };

    auto oTe = Cte{mVariables, TemplateName};

    buffer << oTe;

    ASSERT_EQUAL(buffer.str(), "before replacement after");
    }
  };

struct SimpleReplacementTest003 : FilesystemTemplateTest<SimpleReplacementTest003>
  {
  static constexpr auto TemplateName = "simple_replacement003.tpl";

  void GenerateTemplates()
    {
    auto output = std::ofstream{TemplateName};
    output << "{{ variable }}{{ variable }}";
    }

  void test_simple_variable_replacement()
    {
    auto buffer = std::ostringstream{};
    TMapS2M mVariables{
        { "variable", {{ "", "replacement" }} }
    };

    auto oTe = Cte{mVariables, TemplateName};

    buffer << oTe;

    ASSERT_EQUAL(buffer.str(), "replacementreplacement");
    }
  };

struct SimpleReplacementTest004 : FilesystemTemplateTest<SimpleReplacementTest004>
  {
  static constexpr auto TemplateName = "simple_replacement004.tpl";

  void GenerateTemplates()
    {
    auto output = std::ofstream{TemplateName};
    output << "{{ Rariable }}{{ variable }}";
    }

  void test_simple_variable_replacement()
    {
    auto buffer = std::ostringstream{};
    TMapS2M mVariables{
        { "variable", {{ "", "replacement" }} }
    };

    auto oTe = Cte{mVariables, TemplateName};

    buffer << oTe;

    ASSERT_EQUAL(buffer.str(), "replacement");
    }
  };

struct SimpleReplacementTest005 : FilesystemTemplateTest<SimpleReplacementTest005>
  {
  static constexpr auto TemplateName = "simple_replacement005.tpl";

  void GenerateTemplates()
    {
    auto output = std::ofstream{TemplateName};
    output << "{{{ variable }}}";
    }

  void test_simple_variable_replacement()
    {
    auto buffer = std::ostringstream{};
    TMapS2M mVariables{
        { "variable", {{ "", "replacement" }} }
    };

    auto oTe = Cte{mVariables, TemplateName};

    buffer << oTe;

    ASSERT_EQUAL(buffer.str(), "{replacement}");
    }
  };

struct SimpleReplacementTest006 : FilesystemTemplateTest<SimpleReplacementTest006>
  {
  static constexpr auto TemplateName = "simple_replacement006.tpl";

  void GenerateTemplates()
    {
    auto output = std::ofstream{TemplateName};
    output << "{ {{ variable }} }";
    }

  void test_simple_variable_replacement()
    {
    auto buffer = std::ostringstream{};
    TMapS2M mVariables{
        { "variable", {{ "", "replacement" }} }
    };

    auto oTe = Cte{mVariables, TemplateName};

    buffer << oTe;

    ASSERT_EQUAL(buffer.str(), "{ replacement }");
    }
  };

struct SimpleReplacementTest007 : FilesystemTemplateTest<SimpleReplacementTest007>
  {
  static constexpr auto TemplateName = "simple_replacement007.tpl";

  void GenerateTemplates()
    {
    auto output = std::ofstream{TemplateName};
    output << "{{ {{ variable }} }}";
    }

  void test_simple_variable_replacement()
    {
    auto buffer = std::ostringstream{};
    TMapS2M mVariables{
        { "variable", {{ "", "replacement" }} }
    };

    auto oTe = Cte{mVariables, TemplateName};

    buffer << oTe;

    ASSERT_EQUAL(buffer.str(), "variable");
    }
  };

int main(int argc, char const * const * argv)
  {
  auto listener = cute::tap_listener<cute::null_listener>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  auto suite = cute::suite{};

  auto oSimpleReplacementTest001 = SimpleReplacementTest001{};
  auto oSimpleReplacementTest002 = SimpleReplacementTest002{};
  auto oSimpleReplacementTest003 = SimpleReplacementTest003{};
  auto oSimpleReplacementTest004 = SimpleReplacementTest004{};
  auto oSimpleReplacementTest005 = SimpleReplacementTest005{};
  auto oSimpleReplacementTest006 = SimpleReplacementTest006{};
  auto oSimpleReplacementTest007 = SimpleReplacementTest007{};

  suite += CUTE_MEMFUN(oSimpleReplacementTest001, SimpleReplacementTest001, test_simple_variable_replacement);
  suite += CUTE_MEMFUN(oSimpleReplacementTest002, SimpleReplacementTest002, test_simple_variable_replacement);
  suite += CUTE_MEMFUN(oSimpleReplacementTest003, SimpleReplacementTest003, test_simple_variable_replacement);
  suite += CUTE_MEMFUN(oSimpleReplacementTest004, SimpleReplacementTest004, test_simple_variable_replacement);
  suite += CUTE_MEMFUN(oSimpleReplacementTest005, SimpleReplacementTest005, test_simple_variable_replacement);
  suite += CUTE_MEMFUN(oSimpleReplacementTest006, SimpleReplacementTest006, test_simple_variable_replacement);
  suite += CUTE_MEMFUN(oSimpleReplacementTest007, SimpleReplacementTest007, test_simple_variable_replacement);

  return !runner(suite);
  }
