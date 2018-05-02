#include "te.h"

int main()
    {
    TMapS2S mVariables{ {"title", "odb Viewer"}, {"message", "WELCOME"}, 
                        {"my", "demo"}, {"former-query", "t:Star Trek"}, 
                        {"static+favicon-icon", "/static/fav.icon"}, 
                        {"static+style-css", "/static/style.css"} };

    TMapS2V mVectors  { {"messages", {"hello", "world"}},
                        {"qresults", {"Star Trek", "Star Wars"}} };

    CTE ote(mVariables, mVectors, "index.html", "../templates/");

    std::cout << ote;
    }

