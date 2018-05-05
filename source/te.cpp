#include "te.h"

int main()
    {
    TMapS2S const mVariables { {"title", "odb Viewer"}, {"message", "WELCOME"},
                               {"my", "demo"}, {"former-query", "t:Star Trek"},
                               {"static+favicon-icon", "/static/fav.icon"},
                               {"static+style-css", "/static/style.css"} };

    TMapS2V const mVectors   { {"messages", {"hello", "world"}},
                               {"qresults", {"Star Trek", "Star Wars"}} };

    Cte const ote(mVariables, mVectors, "index.html", "../templates/");

    std::cout << ote;
    }

