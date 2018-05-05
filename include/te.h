#ifndef __TE_H
#define __TE_H

#include <fstream>
#include <iostream>     // std::cout
#include <algorithm>
#include <iterator>
#include <regex>
#include <map>
#include <vector>
#include <utility>      // std::pair

#include <string>       // std::string
#include <streambuf>
#include <sstream>      // std::ostringstream


using TMapS2S = std::map<std::string, std::string>;
using TMapS2V = std::map<std::string, std::vector<std::string>>;
using TLpParm = std::pair<std::string, std::string>;

using namespace std::string_literals; // @suppress("Using directive in header file")

/*

{% for node in nodes %}{% prefix %}<ul>{% end %}
  <li>{{ node }}</li>
{% suffix %}</ul>{% end %}{% end %}
  =>
<ul>
  <li>Star Treck</li>
  <li>Star Wars</li>
</ul>

*/


class Cte
    {
	std::string const m_sFilepath;
	std::string m_sPage;

    public:

	Cte(TMapS2S const & mVariables, TMapS2V & mVLists, std::string const & crsFilename, std::string const & crsFilepath = "")
	    : m_sFilepath(crsFilepath)
	    {
	    std::string s = ReadTemplate(m_sFilepath + crsFilename);

	    s = GetIfs(s, mVLists);
            s = FillLoops(s, mVLists);
	    s = FillVariables(s, mVariables);

	    std::smatch      sm{};
	    std::regex const re(R"(\{\%\s*extends\s*\"(.*)\"\s*\%\})");
	    std::string      sExtend{};
	    std::regex_search(s, sm, re);
	    if ( sm.size() > 1 )
		{
		sExtend = sm[1];

		TMapS2S mBlocks = GetBlocks(s);

		s = ReadTemplate(crsFilepath + sExtend);
	        s = GetIfs(s, mVLists);
                s = FillLoops(s, mVLists);
		s = FillVariables(s, mVariables);
		s = FillBlocks(s, mBlocks);
		}
	    m_sPage = std::move(s);
	    }

	friend std::ostream & operator << (std::ostream & ros, Cte const & crTE)
	    {
	    return ros << crTE.m_sPage;
	    }

        TLpParm SplitLoopParam(std::string const & s) const
            {

	    std::smatch      sm{};
	    std::regex const re(R"(([^\s*]*)\s*in\s*([^\s*]*)\s*\%\})");
	    std::regex_search(s, sm, re);
	    if ( sm.size() > 2 )
		{
		return std::make_pair(sm[1], sm[2]);
		}
            return std::make_pair("", "");
            }

        std::string FillVariables(std::string const & crsPart,
        			  std::string const & crsName,
				  std::string const & crsData) const
            {
            std::regex const re("\\{\\{\\s*"s + crsName + "\\s*\\}\\}"s);
            return std::regex_replace(crsPart, re, crsData);
            }
/*
{% for message in messages %}<div class=flash>{{ message }}</div>{% endfor %}
*/
        std::string FillLoops(std::string const & crsPage, TMapS2V const & mVLists) const
	    {
	    std::ostringstream oss{};

	    std::regex const re(R"(\{\%\s*for\s*|\{\%\s*endfor\s*\%\})");
	    size_t n{0};
	    for (auto it = std::sregex_token_iterator(crsPage.begin(), crsPage.end(), re, -1); it != std::sregex_token_iterator(); ++it)
		{
		if ( ++n & 1 )
		    {
		    oss << *it;
		    }
		else
		    {
		    std::string const si = *it;
		    size_t      const  p = si.find('}')+1;
                    auto        const param  = SplitLoopParam( si.substr(0, p) );
                    if ( mVLists.find(param.second) != mVLists.end() )
                	{
			for ( auto const & a:mVLists.at(param.second) )
			    {
			    oss << FillVariables(si.substr(p), param.first, a);
			    }
                	}
		    }
		}
	    return oss.str();
	    }

	/**
	 * @brief Fills in variales
	 *
	 * @param crsPage The template
	 * @param mData The data to fill in
	 */
	std::string FillVariables(std::string const & crsPage, TMapS2S const & mVariables) const
	    {
	    std::ostringstream oss{};

	    std::regex const re(R"(\{\{\s*|\s*\}\})");
	    size_t n{0};
	    for (auto it = std::sregex_token_iterator(crsPage.begin(), crsPage.end(), re, -1); it != std::sregex_token_iterator(); ++it)
		{
		if ( ++n & 1 )
		    {
		    oss << *it;
		    }
		else
		    {
		    if ( mVariables.find(*it) != mVariables.end() )
			{
			oss << mVariables.at(*it);
			}
		    }
		}
	    return oss.str();
	    }

	/**
	 * @brief Fills the content of the block to their destination
	 *
	 * @param crsPage The input template text
	 * @param mData The variables to fill in
	 */
	std::string FillBlocks(std::string const & crsPage, TMapS2S const & mVariables) const
	    {
	    std::ostringstream oss{};

	    std::regex const re(R"(\{\%\s*block\s*|\{\%\s*endblock\s*\%\})");
	    size_t n{0};
	    for (auto it = std::sregex_token_iterator(crsPage.begin(), crsPage.end(), re, -1); it != std::sregex_token_iterator(); ++it)
		{
		if ( ++n & 1 )
		    {
		    oss << *it;
		    }
		else
		    {
		    std::string const s = *it;
		    size_t      const p = s.find(' ');
		    std::string const k = s.substr(0, p);
		    size_t      const q = s.find('}')+1;
                    if ( mVariables.find(k) != mVariables.end() )
                        {
		        oss << mVariables.at(k);
                        }
                    else
                        {
                        oss << s.substr(q);
                        }
		    }
		}
	    return oss.str();
	    }

	/**
	 * @brief Collects the content of all blocks.
	 *
	 * If a template contains block, all other content can be ignores besides the
	 * function 'extends' to find a shell to put the blocks into
	 *
	 * @param page The template
	 */
	TMapS2S GetBlocks(std::string const & crsPage) const
	    {
	    TMapS2S mResult{};

	    std::regex const re(R"(\{\%\s*block\s*|\{\%\s*endblock\s*\%\})");
	    size_t n{0};
	    for (auto it = std::sregex_token_iterator(crsPage.begin(), crsPage.end(), re, -1); it != std::sregex_token_iterator(); ++it)
		{
		if ( n++ & 1 )
		    {
		    std::string const s = *it;
		    size_t      const p = s.find(' ');
		    size_t      const q = s.find('}');
		    mResult[s.substr(0, p)] = s.substr(q+1);
		    }
		}
	    return std::move(mResult);
	    }

	std::string GetIfs(std::string const & crsPage, TMapS2V const & mVLists) const
	    {
	    std::ostringstream oss{};

	    std::regex const re(R"(\{\%\s*if\s*|\{\%\s*endif\s*\%\})");
	    size_t n{0};
	    for (auto it = std::sregex_token_iterator(crsPage.begin(), crsPage.end(), re, -1); it != std::sregex_token_iterator(); ++it)
		{
		if ( ++n & 1 )
                    {
                    oss << *it;
                    }
                else
		    {
		    std::string const s = *it;
		    size_t      const p = s.find(' ');
		    size_t      const q = s.find('}');
		    if ( mVLists.find(s.substr(0, p)) != mVLists.end() )
                        {
                        oss << s.substr(q+1);
                        }
//                  mResult[s.substr(0, p)] = s.substr(q+1);
		    }
		}
	    return std::move(oss.str());
	    }

	std::string ReadTemplate(std::string const & sFilename) const
	    {
	    std::ifstream f(sFilename);
	    std::string   t((std::istreambuf_iterator<char>(f)),
			     std::istreambuf_iterator<char>());
	    return std::move(t);
	    }

    }; // class CTE

// __TE_H
#endif
