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
      perform_replacement(oData, "{% for variable in x %}{{ variable }}{% endfor %}")
    );
    }

  void test_for_loop_with_variable_present_wrong_cycle()
    {
    auto oData = TRenderData{
        {"variable", {{"", "replacement1"}}},
        {"variable", {{"", "replacement2"}}},
    };
    ASSERT_EQUAL(
      "replacement1replacement2",
      perform_replacement(oData, "{% for variable in x %}{{ variable }}{% endif %} overlap")
    );
    }

  void test_for_loop_with_variable_multiple_level_present()
    {
    auto oData = TRenderData{
        {"variable", {{"", "replacement1"}, {"is", "A"}}},
        {"variable", {{"", "replacement2"}, {"is", "B"}}},
    };
    ASSERT_EQUAL(
      "replacement1 is A. replacement2 is B. ",
      perform_replacement(oData, "{% for variable in x %}{{ variable }} is {{ variable.is }}. {% endfor %}")
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
      perform_replacement(oData, "{% for variable in x %} alpha {{ variable }} omega {% endfor %}")
    );
    }

  void test_for_loop_with_variable_present_and_surrounding_context_TeX()
    {
    auto oData = TRenderData{
        {"docClass", {{"", "article"}}},
        {"package",  {{"", "[utf8]{inputenc}"}}},
        {"package",  {{"", "[T1]{fontenc}"}}},
        {"package",  {{"", "[german]{babel}"}}},
    };
    ASSERT_EQUAL(R"(  \documentclass{article})"
                 R"()"
                 R"(  \usepackage[utf8]{inputenc})"
                 R"(  \usepackage[T1]{fontenc})"
                 R"(  \usepackage[german]{babel})"
                 R"()"
                 R"(  %--------------------------------------)"
                 R"(  \begin{document})",

      perform_replacement(oData,
	         R"(  \documentclass{{{ docClass }}})"
	         R"()"
	         R"({% if package %}{% for package in x %}  \usepackage{{ package }})"
	         R"({% endfor %}{% endif %})"
	         R"(  %--------------------------------------)"
	         R"(  \begin{document})")
    );
    }

  auto suite = cutex::NamedSuite {
    "Control-flow contructs",
      {
      CUTE(test_if_statement_with_variable_present),
      CUTE(test_if_statement_without_variable_present),
      CUTE(test_for_loop_with_variable_present),
      CUTE(test_for_loop_with_variable_present_wrong_cycle),
      CUTE(test_for_loop_with_variable_multiple_level_present),
      CUTE(test_for_loop_with_variable_present_and_surrounding_context),
      CUTE(test_for_loop_with_variable_present_and_surrounding_context_TeX),
      }
  };

  }
