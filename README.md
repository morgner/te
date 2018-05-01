# te
A minimal template engine

It's a header-only implementation, coding like this:

```cpp
int main()
    {
    TMapS2S mVariables{ {"title", "odb Viewer"}, {"message", "WELCOME"}, 
                        {"my", "demo"}, {"former-query", "t:Star Trek"},
                        {"static+favicon-icon", "/static/te.ico"},
                        {"static+style-css", "/static/style.css"} };

    CTE ote(mVariables, "index.html", "../templates/");

    std::cout << ote;
    }
```
