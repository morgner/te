#include "cute/cute.h"
#include "cute/cute_runner.h"
#include "cute/tap_listener.h"
#include "cute/xml_listener.h"

#include "cute/extensions.h"

#include "test_holder.h"

#include "te.h"

namespace test_suite
  {
  extern cutex::NamedSuite suite;
  }

int main(int argc, char const * const * argv)
  {
  auto xml = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::tap_listener<>>{xml.out};
  auto runner = cute::makeRunner(listener, argc, argv);
  return !test_suite::suite.run_with(runner);
  }
