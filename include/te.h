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

using namespace std::string_literals;

class CTE
    {
	std::string m_sFilepath;
	std::string m_sPage;

public:

	CTE(TMapS2S & sContent, TMapS2V & sLists, std::string const & crsFilename, std::string const & crsFilepath)
	    : m_sFilepath(crsFilepath)
	    {
	    std::string s = ReadTemplate(m_sFilepath + crsFilename);

            s = FillLoops(s, sLists);
	    s = FillVariables(s, sContent);

	    std::smatch      sm{};
	    std::regex const reExt("\\{\\%\\s*extends\\s*\"(.*)\"\\s*\\%\\}");
	    std::string      smExt{};
	    std::regex_search(s, sm, reExt);
	    if ( sm.size() > 1 )
		{
		smExt = sm[1];

		TMapS2S mBlocks = GetBlocks(s);

		s = ReadTemplate(crsFilepath + smExt);
                s = FillLoops(s, sLists);
		s = FillVariables(s, sContent);
		s = FillBlocks(s, mBlocks);
		}
	    m_sPage = std::move(s);
	    }

	friend std::ostream & operator << (std::ostream & ros, CTE const & crTE)
	    {
	    return ros << crTE.m_sPage;
	    }

        TLpParm SplitLoopParam(std::string s)
            {
	    std::smatch      sm{};
	    std::regex const re("([^\\s*]*)\\s*in\\s*([^\\s*]*)\\s*\\%\\}");
	    std::string      s1{};
	    std::string      s2{};
	    std::regex_search(s, sm, re);
	    if ( sm.size() > 1 )
		{
		s1 = sm[1];
		s2 = sm[2];
		}
            return std::make_pair(s1, s2);
            }

	std::string FillVariables(std::string const & crsPart, std::string const & crsName, std::string const & crsData)
            {
            std::regex const re("\\{\\{\\s*"s + crsName + "\\s*\\}\\}"s);
            return std::regex_replace(crsPart, re, crsData);
            }
/*
{% for message in messages %}<div class=flash>WELCOME</div>
                {% endfor %}
*/
	std::string FillLoops(std::string const & crsPage, TMapS2V & sLists)
	    {
	    std::ostringstream oss{};

	    std::regex const re("\\{\\%\\s*for\\s*|\\{\\%\\s*endfor\\s*\\%\\}");
	    size_t n{0};
	    for (auto it = std::sregex_token_iterator(crsPage.begin(), crsPage.end(), re, -1); it != std::sregex_token_iterator(); ++it)
		{
		if ( ++n & 1 )
		    {
		    oss << *it;
//		    std::cout << "1---------1" << *it;
		    }
		else
		    {
		    //oss << mData[*it];
		    std::string si = *it;
                    TLpParm p = SplitLoopParam( si.substr(0, si.find('}')+1) );
//		    std::cout << "2---------2" << *it; // message in messages %}...
                    std::string so = si.substr(si.find('}')+1);
                    for ( auto & a:sLists[p.second] )
                        {
	                oss << FillVariables(so, p.first, a);
//	                std::cout << FillVariables(so, p.first, a);
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
	std::string FillVariables(std::string const & crsPage, TMapS2S & mData)
	    {
	    std::ostringstream oss{};

	    std::regex const re("\\{\\{\\s*|\\s*\\}\\}");
	    size_t n{0};
	    for (auto it = std::sregex_token_iterator(crsPage.begin(), crsPage.end(), re, -1); it != std::sregex_token_iterator(); ++it)
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

	/**
	 * @brief Fills the content of the block to their destination
	 *
	 * @param crsPage The input template text
	 * @param mData The variables to fill in
	 */
	std::string FillBlocks(std::string const & crsPage, TMapS2S & mData)
	    {
	    std::ostringstream oss{};

	    std::regex const re("\\{\\%\\s*block\\s*|\\{\\%\\s*endblock\\s*\\%\\}");
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
		    oss << mData[s.substr(0, p)];
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
	TMapS2S GetBlocks(std::string const & crsPage)
	    {
	    TMapS2S mResult{};

	    std::regex const re("\\{\\%\\s*block\\s*|\\{\\%\\s*endblock\\s*\\%\\}");
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

	std::string ReadTemplate(std::string const & sFilename)
	    {
	    std::ifstream f(sFilename);
	    std::string   t((std::istreambuf_iterator<char>(f)),
			     std::istreambuf_iterator<char>());
	    return std::move(t);
	    }

    }; // class CTE

// __TE_H
#endif
