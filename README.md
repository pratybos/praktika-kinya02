
PROJEKTO APRAŠYMAS
==================

„Pelenu Kelias“ - tai tekstinis RPG žaidimas, sukurtas naudojant C++ programavimo kalbą.

Žaidimo metu žaidėjas:

* keliauja per skirtingas vietoves,
* kovoja su demonais,
* renka daiktus,
* stiprina savo veikėją,
* naudoja gydymo priemones,
* susiduria su bosais.

ŽAIDIMO TAISYKLĖS
=================

Žaidimas valdomas įvedant skaičius konsolėje.

Kovų metu galima pasirinkti:

1. Greitą smūgį
2. Sunkų smūgį
3. Gynybą
4. Gydymą
5. Specialų gebėjimą (jeigu atrakintas)

Žaidėjas turi:

* gyvybes (HP),
* ataką,
* gynybą,
* greitį,
* monetas,
* XP taškus.

Po kovų gaunami:

* XP,
* monetos,
* nauji daiktai.

Žaidėjas gali pirkti geresnius daiktus parduotuvėje ir stiprinti savo veikėją.


KAIP PALEISTI PROGRAMĄ
======================

Programa gali būti paleidžiama naudojant:

* CLion
* Visual Studio
* CodeBlocks

Norint paleisti programą, reikia:

* Atidaryti projektą.
* Paleisti „Run“ mygtuką.
* Programa automatiškai susikompiliuos ir pasileis konsolėje.

MENIU PUNKTAI
=============

1. Pradėti 1 skyrių
   Pradedama pagrindinė istorija.

2. Herojaus informacija
   Parodoma:

* statistika,
* inventorius,
* turimi daiktai,
* veikėjo istorija.

3. Instrukcija
   Trumpai paaiškinamas žaidimo valdymas ir taisyklės.

4. Išeiti
   Uždaroma programa.


GENERATORIUS
============

Žaidime naudojamas atsitiktinių skaičių generatorius.

Jis naudojamas:

* papildomai žalai,
* padegimo efektams,
* priešų smūgių variacijoms.

Naudojamos funkcijos:

* rand()
* srand(time(nullptr))


PARDUOTUVĖ
==========

Kelionės metu žaidėjas gali apsilankyti parduotuvėje.

Galima nusipirkti:

* HP eliksyrus,
* šalmus,
* skydus,
* ginklus.

Pirkimai pagerina veikėjo statistiką:

* HP,
* ataką,
* gynybą.

NAUDOJAMAS FAILO FORMATAS
=========================

Projektui planuojama naudoti CSV formatą.

CSV pavyzdys:

Vardas,XP,Monetos,Pasiekimai
Jokubas Dagys,1200,540,3
Edvinas,980,410,2


NAUDOTOS TECHNOLOGIJOS
======================

* C++
* Konsolinė aplikacija
* iostream
* vector
* string
* algorithm
* ctime


PROJEKTO STRUKTŪRA
==================

/project-folder
│
├── main.cpp
├── README.txt
└── assets/


AUTORIUS
========

Projektą sukūrė:
Jokūbas_Dagys Kinga_Wysocka Edvin_Vaskan

Vilniaus kolegija
Elektronikos ir informatikos fakultetas
