#ifndef CUTE_EXTENSIONS_H
#define CUTE_EXTENSIONS_H

#include "cute/cute_suite.h"

#include <string>
#include <utility>

namespace cutex
  {

  struct NamedSuite
    {
    NamedSuite(std::string name, cute::suite suite)
      : m_sName{std::move(name)}
      , m_vSuite(std::move(suite))
      {

      }

    template<typename RunnerType>
    bool run_with(RunnerType & runner)
      {
      return runner(m_vSuite, m_sName.c_str());
      }

    private:
      std::string m_sName;
      cute::suite m_vSuite;
    };

  }

#endif
