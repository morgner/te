##te Template Language

The te language is a simplyfied Django-Project template language. It is not
planned to implement the whole functionality but some extension may become
their te implemntation

###Basics

During template interpretation not interpretable tags and blocks become removed
as if they hadn't exist. For example. if there is no value for 'variable' the
interpreter will erase the tag:

```
"{{ variable }}" => ""
```

**If** their is a value, it replaces the whole tag, like here:

```
"{{ variable }}"        => "replacement"
"I say: {{ formula }}!" => "I say: Hello world!"
```

Render-Input is a multimap of string and multimap of string:

```
{"variable" { {"", "replacement"},{"color", "white"} } }
```

interpreted this way

```
"{{ variable }}"        => "replacement"
"{{ variable.color }}"  => "white"
"{{ variable.info }}"   => ""
```


###Test suite

```
"{{ variable }}"                  "replacement"
"A {{ variable }} B"              "A replacement B"
"{{ variable }}{{ variable }}"    "replacementreplacement"
"{{ Rariable }}{{ variable }}"    "replacement"
"{{{ variable }}}"                "{replacement}"
"{ {{ variable }} }"              "{ replacement }"
"{{ {{ variable }} }}"            "variable"
```
