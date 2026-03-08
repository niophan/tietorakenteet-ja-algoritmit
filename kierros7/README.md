```cpp
Error_code Stack::push(Stack_entry item)
{
    Node new_top(item, top_node);
    top_node = new_top;
    return success;
}
```
Tämä ei toimi, koska top_node on osoitin Node*() olioon, joka osoittaa muistissa. Sen sijaan new_top on Node-olio, ei osoitin. Kun top_node = new_top, suoritetaan,ohjelma yritää sijoittaa Node-olion Node* osoittimeen, mikä ei ole sallitua. Kääntäjä antaa virheen, koska tyyppien välillä on ristiriita. 