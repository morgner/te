#include "cute/cute_equals.h"

#include "cute/extensions.h"
#include "test_holder.h"

#include "te.h"

namespace test_suite
  {

  void test_if_statement_with_variable_present()
    {
    auto oData = TRenderData{{"variable", {{"", "replacement"}}}};
    ASSERT_EQUAL(
      "replacement",
      perform_replacement(oData, "{% if variable %}{{ variable }}{% endif %}")
    );
    }

  void test_if_statement_without_variable_present()
    {
    auto oData = TRenderData{};
    ASSERT_EQUAL(
      "",
      perform_replacement(oData, "{% if variable %}{{ variable }}{% endif %}")
    );
    }

  void test_for_loop_with_variable_present()
    {
    auto oData = TRenderData{
        {"variable", {{"", "replacement1"}}},
        {"variable", {{"", "replacement2"}}},
    };
    ASSERT_EQUAL(
      "replacement1replacement2",
      perform_replacement(oData, "{% for variable in x %}{{ variable }}{% endif %}")
    );
    }

  void test_for_loop_with_variable_present_and_surrounding_context()
    {
    auto oData = TRenderData{
        {"variable", {{"", "replacement1"}}},
        {"variable", {{"", "replacement2"}}},
    };
    ASSERT_EQUAL(
      " alpha replacement1 omega  alpha replacement2 omega ",
      perform_replacement(oData, "{% for variable in x %} alpha {{ variable }} omega {% endif %}")
    );
    }

  auto suite = cutex::NamedSuite {
    "Control-flow contructs",
      {
      CUTE(test_if_statement_with_variable_present),
      CUTE(test_if_statement_without_variable_present),
      CUTE(test_for_loop_with_variable_present),
      CUTE(test_for_loop_with_variable_present_and_surrounding_context),
      }
  };

  }
