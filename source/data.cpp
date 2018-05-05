#include "te.h"

/*
{% block data %}
        <p>{{ class }} : <a href="ni{{ node.id }}">{{ node }}</a></p>
        <p><ul>{% for property in properties %}
               <li><a href="p:{{ property.id }}">{{ property }}</a></li>{% endfor %}
           </ul></p>
{% endblock %}
*/

int main()
    {
    TMapS2S mVariables{ {"title", "odb Viewer"}, {"message", "WELCOME"}, 
                        {"my", "demo"}, {"former-query", "t:Star Trek"}, 
                        {"static+favicon-icon", "/static/fav.icon"}, 
                        {"static+style-css", "/static/style.css"} };

    TMapS2V mVectors  { {"properties", {"nm9087684", "actor", "director"}},
                        {"linked",     {"Star Treck", "nobody", "couple"}} };

    Cte ote(mVariables, mVectors, "data.html", "../templates/");

    std::cout << ote;
    }

