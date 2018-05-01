#include <fstream>
#include <iostream>     // std::cout
#include <algorithm>
#include <iterator>
#include <regex>
#include <vector>
#include <map>

#include <string>       // std::string
#include <streambuf>
#include <sstream>      // std::ostringstream

using tMapS2S = std::map<std::string, std::string>;

std::string FillVariables(tMapS2S & mData, std::string const & page)
    {
    std::ostringstream oss{};

    std::regex re("\\{\\{\\s*|\\s*\\}\\}");
    size_t n{0};
    for (auto it = std::sregex_token_iterator(page.begin(), page.end(), re, -1); it != std::sregex_token_iterator(); ++it)
        {
        if ( ++n & 1 )
            {
            oss << *it;
            }
        else
            {
            oss << mData[*it];
            }
        }
    return oss.str();
    }

std::string FillBlocks(std::string const & page, tMapS2S & mData)
    {
    std::string result{};
    std::ostringstream const oss{};

    std::regex re("\\{\\%\\s*block\\s*|\\{\\%\\s*endblock\\s*\\%\\}");
    size_t n{0};
    for (auto it = std::sregex_token_iterator(page.begin(), page.end(), re, -1); it != std::sregex_token_iterator(); ++it)
        {
        if ( ++n & 1 )
            {
            std::cout << *it;
            }
        else
            {
            std::string const s = *it;
            size_t      const p = s.find(' ');
            size_t      const q = s.find('}');
            std::cout << mData[s.substr(0, p)]; // << s.substr(q+1);
            }
        }
    return result;
    }


tMapS2S GetBlocks(std::string const & page)
    {
    tMapS2S result;
    std::ostringstream oss;

    std::regex re("\\{\\%\\s*block\\s*|\\{\\%\\s*endblock\\s*\\%\\}");
    size_t n{0};
    for (auto it = std::sregex_token_iterator(page.begin(), page.end(), re, -1); it != std::sregex_token_iterator(); ++it)
        {
        if ( ++n & 1 )
            {
//         std::cout << "+++" << *it << "###";
            }
        else
            {
            std::string const s = *it;
            size_t      const p = s.find(' ');
            size_t      const q = s.find('}');
            result[s.substr(0, p)] = s.substr(q+1);
//          std::cout << "|-" << s.substr(0, p) << "-|" << s.substr(q+1);
            }
        }
    return result;
    }

std::string ReadTemplate(std::string const & sFilename)
    {
    std::ifstream f(sFilename);
    std::string   t((std::istreambuf_iterator<char>(f)),
                     std::istreambuf_iterator<char>());
    return std::move(t);
    }

int main()
    {
    tMapS2S sContent{ {"title", "odb Viewer"}, {"message", "WELCOME"}, {"my", "demo"}, {"former-query", "t:Star Trek"}, {"static+favicon-icon", "/fi"}, {"static+style-css", "/style"} };

    std::string s = ReadTemplate("index.html");
                s = FillVariables(sContent, s);


    std::smatch sm{};
    std::regex  reExt("\\{\\%\\s*extends\\s*\"(.*)\"\\s*\\%\\}");
    std::string smExt{""};
    std::regex_search(s, sm, reExt);
    if ( sm.size() > 1 )
        {
        smExt = sm[1];
//      s = sm.suffix();
        }

    tMapS2S mBlocks = GetBlocks(s);

    s = ReadTemplate(smExt);
    s = FillVariables(sContent, s);
    s = FillBlocks(s, mBlocks);
    }

