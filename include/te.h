#ifndef __TE_H
#define __TE_H

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


using TMapS2S = std::map<std::string, std::string>;

class CTE
    {
	std::string m_sFilepath;
	std::string m_sPage;

public:

	CTE(TMapS2S & sContent, std::string const & crsFilename, std::string const & crsFilepath)
	    : m_sFilepath(crsFilepath)
	    {
	    std::string s = ReadTemplate(m_sFilepath + crsFilename);

    //+	s = FillLoops(s, sContent);
	    s = FillVariables(s, sContent);

	    std::smatch      sm{};
	    std::regex const reExt("\\{\\%\\s*extends\\s*\"(.*)\"\\s*\\%\\}");
	    std::string      smExt{};
	    std::regex_search(s, sm, reExt);
	    if ( sm.size() > 1 )
		{
		smExt = sm[1];

		TMapS2S mBlocks = GetBlocks(s);

		s = ReadTemplate(smExt);
		s = FillVariables(s, sContent);
		s = FillBlocks(s, mBlocks);
		}
	    m_sPage = std::move(s);
	    }

	friend std::ostream & operator << (std::ostream & ros, CTE const & crTE)
	    {
	    return ros << crTE.m_sPage;
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
