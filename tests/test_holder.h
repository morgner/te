#ifndef TEST_HOLDER_H
#define TEST_HOLDER_H

#include "te.h"

#include "cute/cute_base.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

struct TemplateHolder
  {
  explicit TemplateHolder(std::string const & code) :
    templateFile{std::filesystem::temp_directory_path() / "te_tests.tpl"}
    {
    auto templateData = std::ofstream(templateFile);
    ASSERTM("Failed to create template file", templateData);
    templateData.write(code.c_str(), code.size());
    }

  ~TemplateHolder() noexcept(false)
    {
    ASSERTM("Template file has disappeared", std::filesystem::exists(templateFile));
    std::filesystem::remove(templateFile);
    }

  std::filesystem::path file() const
    {
    return templateFile;
    }

  friend TemplateHolder operator""_tpl(char const * data, unsigned long const size);

  private:
    std::filesystem::path const templateFile;
  };

inline TemplateHolder operator""_tpl(char const * data, unsigned long const size)
  {
  return TemplateHolder{{data, size}};
  }

inline auto perform_replacement(TRenderData & data, std::string templ)
  {
  auto oTemplate = TemplateHolder{templ};
  auto oTe = Cte{data, oTemplate.file()};
  auto oStream = std::ostringstream{};
  oStream << oTe;

  return oStream.str();
  }


#endif
