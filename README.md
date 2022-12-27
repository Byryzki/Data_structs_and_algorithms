Tietorakenteeni:
	Päätietorakenteeni oli unordered_map<TownID, std::vector<TownID>> edges. Valitsin tämän, sillä
	se on suhteellisen nopea, mutta myös monipuolinen ja täten taipuu moneen tilanteeseen.
	Olisi ehkä ollut hieman tehokkaampaa säilöä tiet Town rakenteeseen suoraan, mutta olin
	aikeissa tehdä enemmänkin graafialgoritmeja ja erillinen tietorakenne tuntui täten luontevammalta.
	Apurakenteiksi otin std::vector<std::pair<TownID, TownID>> allroads ja std::vector<TownID> path
	, joista allroadsin valitsin lähinnä funktioiden palautusarvojen pakosta. Path -vektori on lähinnä
	ulkoinen varasto graafialgoritmin ajolle.

Olin saavuttamiini tehokkuuksiin ihan tyytyväinen. Vaikka rekursiivisen DFS -algoritmin puhutaan olevan
vakioaikainen, on mielestäni oma toteutukseni neliöllinen. Uskon sen kuitenkin olevan suht tehokas
rekursiivisuutensa ja "ulkoisen" tietorakenteensa ansiosta. Toisaalta en ole täysin varma onko algoritmini
edes pahimmassakaan tapauksessa aivan neliöllinen. Myös erilaiset pakolliset tarkastukset, kuten
kaupunkien olemassa olo söivät tehokkuuden vähintään vakiolliseksi. Tähän apu olisi varmaan ollut
käyttää hajautustauluja. 

* Varsinaiset kooditoteutukset löytyvät kansioista prg1 tai prg2. Tiedostosta DFS.txt löytyy toteuttamani
algoritmi syvyyteenhaulle.