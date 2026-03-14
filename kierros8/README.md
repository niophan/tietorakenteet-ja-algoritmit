# Tehtävä 4:
Kun int count lisätään luokan private‑osiin, size()‑metodin suoritus nopeutuu, koska sen ei tarvitse enää laskea alkioita läpi koko rakenteen. Se voi vain palauttaa count‑muuttujan arvon, mikä on O(1). Tämä on hyödyllistä vain silloin, kun size()‑kutsuja tehdään usein järjestelmässä.

➕ Etu
size() on välitön ja nopea (O(1)).

➖ Haitta
Jokaisessa metodissa, joka muuttaa alkioiden määrää
(esim. append(), serve(),clear(), empty(), retrieve(), ~destructor, copy(), serve_and_retrieve() ja assignmen operator ), täytyy myös päivittää count oikein. Tämä kasvattaa koodin ylläpito‑ ja virheriskiä:

. Jos joku unohtaa päivittää count, size() antaa väärän tuloksen.
. Rakenteen invariantit voivat rikkoutua.