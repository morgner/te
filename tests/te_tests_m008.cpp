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
  static constexpr auto TemplateName = "simple_replacement.tpl";

  void GenerateTemplates()
    {
    auto output = std::ofstream{TemplateName};
    output << R"({% for f1 in x %}{{ f1.id }}{% endfor %})";
    }

  void test_simple_variable_replacement()
    {
    auto buffer = std::ostringstream{};
    TMapS2M mVariables{
        { "f1", { { "id", "H" }} },
        { "f1", { { "id", "E" }} },
        { "f1", { { "id", "L" }} },
        { "f1", { { "id", "L" }} },
        { "f1", { { "id", "O" }} },
        { "f1", { { "id", " " }} },
        { "f1", { { "id", "t" }} },
        { "f1", { { "id", "e" }} },
        { "f2", { { "id", "A" }} },
        { "f2", { { "id", "B" }} },
        { "f2", { { "id", "C" }} }
    };

    auto oTe = Cte{mVariables, TemplateName};

    buffer << oTe;

    ASSERT_EQUAL(buffer.str(), R"(HELLO te)");
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
