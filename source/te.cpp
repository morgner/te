#include "te.h"

int main()
    {
    TMapS2S mVariables{ {"title", "odb Viewer"}, {"message", "WELCOME"}, {"my", "demo"}, {"former-query", "t:Star Trek"}, {"static+favicon-icon", "/fi"}, {"static+style-css", "/style"} };
    CTE ote(mVariables, "index.html", "../templates/");

    std::cout << ote;
    }

