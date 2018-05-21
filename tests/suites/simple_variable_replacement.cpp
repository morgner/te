#include "cute/cute_equals.h"

#include "cute/extensions.h"
#include "test_holder.h"

#include "te.h"

namespace test_suite
  {

  void test_simple_variable_replacement()
    {
    auto oData = TRenderData{{"variable", {{"", "replacement"}}}};
    ASSERT_EQUAL(
      "replacement",
      perform_replacement(oData, "{{ variable }}")
    );
    }

  void test_simple_variable_replacement_without_root_value_should_produce_empty_replacement()
    {
    auto oData = TRenderData{{"variable", {{"not_the_root", "replacement"}}}};
    ASSERT_EQUAL(
      "",
      perform_replacement(oData, "")
    );
    }

  void test_simple_variable_replacement_without_replacement_for_variable_should_leave_template_intact()
    {
    auto oData = TRenderData{};
    ASSERT_EQUAL(
      "",
      perform_replacement(oData, "{{ variable }}")
    );
    }

  void test_simple_variable_replacement_with_surrounding_context()
    {
    auto oData = TRenderData{{"variable", {{"", "replacement"}}}};
    ASSERT_EQUAL(
      "before replacement after",
      perform_replacement(oData, "before {{ variable }} after")
    );
    }

  void test_simple_variable_replacement_with_surrounding_context_and_additional_replacement_of_property()
    {
    auto oData = TRenderData{{"variable", {{"", "replacement"}, {"id", "an id for 2"}}}};
    ASSERT_EQUAL(
      "before replacement after an id for 2",
      perform_replacement(oData, "before {{ variable }} after {{ variable.id }}")
    );
    }

  auto suite = cutex::NamedSuite {
    "Simple variable replacement",
      {
      CUTE(test_simple_variable_replacement),
      CUTE(test_simple_variable_replacement_without_root_value_should_produce_empty_replacement),
      CUTE(test_simple_variable_replacement_without_replacement_for_variable_should_leave_template_intact),
      CUTE(test_simple_variable_replacement_with_surrounding_context),
      CUTE(test_simple_variable_replacement_with_surrounding_context_and_additional_replacement_of_property),
      }
  };

  }
