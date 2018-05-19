## te Template Language

The te language is a simplyfied Django-Project template language. It is not
planned to implement the whole functionality but some extension may become
their te implemntation

### Basics

During template interpretation not interpretable tags and blocks become removed
as if they hadn't exist. For example. if there is no value for 'variable' the
interpreter will erase the tag:

```
{{ variable }}
```

**If** their is a value, it replaces the whole tag, like here:

```
"{{ variable }}"        => "replacement"
"I say: {{ formula }}!" => "I say: Hello world!"
```

Render-Input is a multimap of string to multimap of string:

```
{"variable" { {"", "replacement"},{"color", "white"} } }
```

interpreted this way

```
"{{ variable }}"        => "replacement"
"{{ variable.color }}"  => "white"
"{{ variable.info }}"   => ""
```

### Loops

```
"{% for variable in dummy %}text{% endif %}"
```
Repeats the enclosed structure as often as 'variable' is found in renderdata. 
This includes 'not' if the variable is not present amongst the delivered data.
renderdata may look like this:

```
{"variable" { {"", "replacement"} } }
{"variable" { {"", "reload"     } } }
{"variable" { {"", "speed"      } } }

"{% for variable in dummy %}{{ variable }}+{% endif %}" => "replacement+reload+speed+"
```

The dummy parameter is for future enhancement and lend from the Django template
language. If can not be left off to ensure syntacial readyness. therefor it makes
sense to give the dummy parameter a sensful name like

```
"{% for variable in variables %}...
```

### Inheritance

```
{% extends "template.name" %}
```

Is a way to isolate layout from content. If this element appearsiin a document,
the content of the document is only be seen as union of blocks:

```
{% block A %}formula{% endblock %}XXX{% block B %}speed{% endblock %}
```

The text beween the matching tags ist kept, the rest will get forogtten. The
blocks can only appear in a template that extends the 'block carrier'. There
the text between the matching tags replaces the text in the embedding template.

```
"{% block A %}formula{% endblock %}" embedet in "{% block A %}blank{% endblock %}" => "formlua"
"{% block A %}{% endblock %}"        embedet in "{% block A %}blank{% endblock %}" => "blank"
"{% block A %}formula{% endblock %}" embedet in "{% block A %}{% endblock %}"      => "formlua"
"{% block A %}{% endblock %}"        embedet in "{% block A %}{% endblock %}"      => ""
```
All other content of the embedet template is ignored in the embeding template.

### if then

The if statement is used to exclude content if it cant be filles. This is used
for cases where prefixes or suffixes are coded in the template:

```
{% if variable %}Size is {{ variable }} meters.{% endif %}
```

If there is no 'variable' the embedding text will also be left off. So this
pattern expants eigther completely or not at all, like this:

```
"{% if variable %}Size is {{ variable }} meters.{% endif %}" => "Size is 3.14 meters."
"{% if variable %}Size is {{ variable }} meters.{% endif %}" => ""
```

### Test suite

```
"{{ variable }}"                  "replacement"
"A {{ variable }} B"              "A replacement B"
"{{ variable }}{{ variable }}"    "replacementreplacement"
"{{ Rariable }}{{ variable }}"    "replacement"
"{{{ variable }}}"                "{replacement}"
"{ {{ variable }} }"              "{ replacement }"
"{{ {{ variable }} }}"            "variable"
```
