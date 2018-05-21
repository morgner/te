#include "cute/cute_equals.h"

#include "../cute/extensions.h"
#include "../test_holder.h"

#include "te.h"

namespace test_suite
  {

  void test_one_curly_brace_missing_at_the_start()
    {
    auto oData = TRenderData{{"variable", {{"", "replacement"}}}};
    ASSERT_EQUAL("{ variable", perform_replacement(oData, "{ variable }}"));
    }

  void test_both_curly_braces_missing_at_the_start()
    {
    auto oData = TRenderData{{"variable", {{"", "replacement"}}}};
    ASSERT_EQUAL(" variable", perform_replacement(oData, " variable }}"));
    }

  void test_one_curly_brace_missing_at_the_end()
    {
    auto oData = TRenderData{{"variable", {{"", "replacement"}}}};
    ASSERT_EQUAL("", perform_replacement(oData, "{{ variable }"));
    }

  void test_both_curly_braces_missing_at_the_end()
    {
    auto oData = TRenderData{{"variable", {{"", "replacement"}}}};
    ASSERT_EQUAL("", perform_replacement(oData, "{{ variable "));
    }

  auto suite = cutex::NamedSuite {
    "Invalid template syntax",
      {
      CUTE(test_one_curly_brace_missing_at_the_start),
      CUTE(test_both_curly_braces_missing_at_the_start),
      CUTE(test_one_curly_brace_missing_at_the_end),
      CUTE(test_both_curly_braces_missing_at_the_end),
      }
  };

  }
