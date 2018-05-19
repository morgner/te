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
    output << "{{ chapter-tag-open }}Chapter A{{ chapter-tag-close }}";
    }

  void test_simple_variable_replacement()
    {
    auto buffer = std::ostringstream{};
    TRenderData mVariables{
        { "chapter-tag-open",  {{ "", "<h1>"  }} },
        { "chapter-tag-close", {{ "", "</h1>" }} }
    };

    auto oTe = Cte{mVariables, TemplateName};

    buffer << oTe;

    ASSERT_EQUAL(buffer.str(), "<h1>Chapter A</h1>");
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
