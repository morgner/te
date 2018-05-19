#include "te.h"

int main()
    {
/*
    TMapS2M o;
    TSubMap u;
    u.emplace("", "person");
    u.emplace("id", "0");
    o.emplace("prop", u );
    u.clear();

    u.emplace("", "actor");
    u.emplace("id", "1");
    o.emplace("prop", u );
    u.clear();

    u.emplace("", "movie");
    u.emplace("id", "2");
    o.emplace("prop", u );
    u.clear();
*/
    TRenderData o{ {"node", { {"", "Mike Miller"},  {"id", "1"}, {"name", "miller"}  } },
               {"node", { {"", "Nora Stands"},  {"id", "2"}, {"name", "stands"}  } },
    //                    node="Mike Miller" node.id="1"  node.name="miller"
               {"title",              { {"", "odb Viewer"}                       } },
               {"my",                 { {"", "demo"}, {"pk", "demo-private"}     } },
               {"message",            { {"", "WELCOME"}                          } },
               {"former-query",       { {"", "t:Star Trek"}                      } },
               {"static+favicon-ico", { {"", "/static/fav.icon"}                 } },
               {"static+style-css",   { {"", "/static/style.css"}                } },
	       {"properties", { {"", "nm9087684"},  {"", "actor"},  {"", "director"} } },
	       {"linked",     { {"", "Star Treck"}, {"", "nobody"}, {"", "couple"  } } }
                                                                                        };
/*
    for (auto & a:o)
	{
	std::cout << a.first << ", [";
	for (auto & b:a.second)
	    {
	    std::cout << "(" << b.first << ", " << b.second << ") ";
	    }
	std::cout << "]\n";
	}
*/

    Cte const ote(o, "index.html", "../templates/");

    std::cout << ote;
    }

