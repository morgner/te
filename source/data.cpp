#include "te.h"

int main()
    {
    TMapS2S const  mVariables{ {"title", "odb Viewer"}, {"message", "WELCOME"},
                               {"my", "demo"}, {"former-query", "t:Star Trek"},
                               {"static+favicon-icon", "/static/fav.icon"},
                               {"static+style-css", "/static/style.css"} };

    TMapS2V const mVectors   { {"properties", {"nm9087684", "actor", "director"}},
                               {"linked",     {"Star Treck", "nobody", "couple"}} };

    Cte const ote(mVariables, mVectors, "data.html", "../templates/");

    std::cout << ote;
    }

