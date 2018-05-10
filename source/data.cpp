#include "te.h"

int main()
    {
    TMapS2M o{ {"node", { {"", "Mike Miller"},  {"id", "1"}, {"name", "miller"}  } },
               {"node", { {"", "Nora Stands"},  {"id", "2"}, {"name", "stands"}  } },
    //                    node="Mike Miller" node.id="1"  node.name="miller"
               {"title",              { {"", "odb Viewer"}                       } },
               {"message",            { {"", "WELCOME"}                          } },
               {"former-query",       { {"", "t:Star Trek"}                      } },
               {"static+favicon-ico", { {"", "/static/fav.icon"}                 } },
               {"static+style-css",   { {"", "/static/style.css"}                } },
	       {"property",           { {"id", "1"}, {"", "nm9087684"}   } },
	       {"property",           { {"id", "2"}, {"", "actor"}       } },
	       {"property",           { {"id", "3"}, {"", "director"}    } },
	       {"link",               { {"id", "1"}, {"reason", "acted in"}, {"", "Star Treck"} } },
               {"link",               { {"id", "2"}, {"reason", "directed"}, {"", "nobody"} } },
               {"link",               { {"id", "3"}, {"reason", "saw"},      {"", "couple"  } } }
                                                                                         };

    Cte const ote(o, "data.html", "../templates/");

    std::cout << ote;
    }

