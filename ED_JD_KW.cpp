#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>

using namespace std;

struct Item {
    string name;
    int count;
};

struct Player {
    string name = "Jokubas Dagys";
    string klase = "Pelenu Karys";
    int maxHP = 180;
    int hp = 180;
    int attack = 26;
    int defense = 12;
    int speed = 10;
    int coins = 250;
    int xp = 0;

    bool hasAmulet = false;
    bool hasMap = false;
    bool hasDungeonKey = false;
    bool hasAshFalchion = false;
    bool ashBurstUsed = false;

    int potions = 0;
    int bandages = 0;
    int armorFragments = 0;
    int flameCrystals = 0;
    int achievements = 0;
};

struct Enemy {
    string name;
    string type;
    int hp;
    int maxHP;
    int attack;
    int defense;
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void waitEnter() {
    cout << "\nSpausk ENTER, kad testi...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int askChoice(int minChoice, int maxChoice) {
    int c;
    while (true) {
        cout << "\n> ";
        if (cin >> c && c >= minChoice && c <= maxChoice) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return c;
        }
        cout << "Neteisingas pasirinkimas. Bandyk dar karta.";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void line() {
    cout << "------------------------------------------------------------\n";
}

void header(Player &p, const string &place) {
    clearScreen();
    line();
    cout << "                 PELENU KELIAS - 1 SKYRIUS\n";
    cout << "                 Uzmirsto Kaimo Sauksmas\n";
    line();
    cout << "Vieta: " << place << "\n";
    cout << "HP: " << p.hp << "/" << p.maxHP
         << " | Ataka: " << p.attack
         << " | Gynyba: " << p.defense
         << " | Greitis: " << p.speed
         << " | Monetos: " << p.coins
         << " | XP: " << p.xp << "\n";
    line();
}

void showVillageArt() {
    cout << R"(
        ~ ~ ~        PELENU KAIMAS        ~ ~ ~

              (  )     (   )   (  )
               ||       ||      ||
          ____/  \_____/  \____/  \____
         /   sudeges kaimas ir pelenai  \
        /___________________________ ____\
              |  |   X   |  |   X   |  |
              |__|_______|__|_______|__|

)";
}

void showForestArt() {
    cout << R"(
          TAMUSIS MISKAS

        /\      /\        /\      /\
       //\\    //\\      //\\    //\\
      ///\\\  ///\\\    ///\\\  ///\\\
        ||      ||        ||      ||
        ||   rukas...     ||      ||

)";
}

void showTempleArt() {
    cout << R"(
             APLEISTA SVENTYKLA

              /\              /\
             /  \____________/  \
            /JUODI DEMONU ZENKLAI\
           /______________________\
              ||      ____      ||
              ||     |    |     ||
              ||_____|____|_____||

)";
}

void showFortressArt() {
    cout << R"(
             POZEMINE TVIRTOVE

        ################################
        #  grotos  #  grandines  #    #
        #----------#-------------#----#
        #   lava teka po akmenimis    #
        ################################

)";
}

void showHero(Player &p) {
    header(p, "Herojaus informacija");
    cout << "Vardas: " << p.name << "\n";
    cout << "Klase: " << p.klase << "\n";
    cout << "Istorija: Jaunas kalvis, kurio seima buvo sunaikinta demonu.\n";
    cout << "Tikslas: surasti, kas atsiunte demonus, ir atkersyti.\n\n";
    cout << "Daiktai:\n";
    cout << "- Moros amuletas: " << (p.hasAmulet ? "taip" : "ne") << "\n";
    cout << "- Sulauzytas zemelapis: " << (p.hasMap ? "taip" : "ne") << "\n";
    cout << "- Pozemio raktas: " << (p.hasDungeonKey ? "taip" : "ne") << "\n";
    cout << "- Pelenu Falchionas: " << (p.hasAshFalchion ? "taip" : "ne") << "\n";
    cout << "- HP eliksyrai: " << p.potions << "\n";
    cout << "- Medicininiai tvarsciai: " << p.bandages << "\n";
    cout << "- Sarvu fragmentai: " << p.armorFragments << "\n";
    cout << "- Liepsnos kristalai: " << p.flameCrystals << "\n";
    waitEnter();
}

void useHealing(Player &p) {
    cout << "\n1) Naudoti HP eliksyra (+35 HP) [" << p.potions << "]";
    cout << "\n2) Naudoti tvarsti (+20 HP) [" << p.bandages << "]";
    cout << "\n0) Atgal";
    int c = askChoice(0, 2);
    if (c == 1) {
        if (p.potions > 0) {
            p.potions--;
            p.hp = min(p.maxHP, p.hp + 35);
            cout << "Jokubas isgeria eliksyra. HP: " << p.hp << "/" << p.maxHP << "\n";
        } else cout << "Neturi eliksyru.\n";
    } else if (c == 2) {
        if (p.bandages > 0) {
            p.bandages--;
            p.hp = min(p.maxHP, p.hp + 20);
            cout << "Jokubas uzsideda tvarsti. HP: " << p.hp << "/" << p.maxHP << "\n";
        } else cout << "Neturi tvarsciu.\n";
    }
}

bool playerDead(Player &p) {
    if (p.hp > 0) return false;
    cout << "\nJokubas krenta ant zemes... bet Moros amuletas trumpai suziba.";
    cout << "\nJis atgauna puse gyvybes. Kelione dar nesibaige.\n";
    p.hp = p.maxHP / 2;
    waitEnter();
    return false;
}

int damageToEnemy(Player &p, Enemy &e, bool heavy, bool ashBurst) {
    int base = p.attack;
    if (heavy) base += 8;
    if (ashBurst) base *= 3;

    if (p.hasAshFalchion && e.type == "demonas") {
        base = base + base / 2;
    }

    int dmg = max(1, base - e.defense);
    int randomBonus = rand() % 5;
    dmg += randomBonus;
    return dmg;
}

bool fight(Player &p, vector<Enemy> enemies, const string &title, bool boss = false, bool gorath = false) {
    p.ashBurstUsed = false;
    int turn = 1;

    while (true) {
        header(p, title);
        cout << "KOVA: " << title << "\n";
        line();
        for (int i = 0; i < (int)enemies.size(); i++) {
            if (enemies[i].hp > 0) {
                cout << i + 1 << ") " << enemies[i].name << " HP: " << enemies[i].hp << "/" << enemies[i].maxHP << "\n";
            }
        }
        line();

        bool allDead = true;
        for (auto &e : enemies) if (e.hp > 0) allDead = false;
        if (allDead) {
            cout << "Pergale! Priesai nugaleti.\n";
            waitEnter();
            return true;
        }

        if (gorath && turn >= 1) {
            cout << "Kingao ugnine aura degina Jokubasa. -2 HP\n";
            p.hp -= 2;
        }

        if (p.hp <= 0) playerDead(p);

        cout << "\nJokubaso veiksmas:\n";
        cout << "1) Greitas smugis\n";
        cout << "2) Sunkus smugis\n";
        cout << "3) Gintis\n";
        cout << "4) Naudoti gydyma\n";
        if (p.hasAshFalchion && !p.ashBurstUsed) {
            cout << "5) Pelenu Pliupsnis (1 karta per kova)\n";
        }

        int maxC = (p.hasAshFalchion && !p.ashBurstUsed) ? 5 : 4;
        int choice = askChoice(1, maxC);
        bool defending = false;
        bool attacked = false;
        bool heavy = false;
        bool ash = false;

        if (choice == 3) {
            defending = true;
            cout << "Jokubas pakelia ginkla ir ruosiasi blokuoti.\n";
        } else if (choice == 4) {
            useHealing(p);
        } else {
            attacked = true;
            heavy = (choice == 2);
            if (choice == 5) {
                ash = true;
                p.ashBurstUsed = true;
                cout << "Pelenu Falchionas uzsiliepsnoja!\n";
            }

            int target = -1;
            for (int i = 0; i < (int)enemies.size(); i++) {
                if (enemies[i].hp > 0) { target = i; break; }
            }

            int dmg = damageToEnemy(p, enemies[target], heavy, ash);
            enemies[target].hp -= dmg;
            cout << "Jokubas smogia priesui " << enemies[target].name << " ir padaro " << dmg << " zalos.\n";

            if (p.hasAshFalchion && (rand() % 100) < 20 && enemies[target].hp > 0) {
                enemies[target].hp -= 3;
                cout << "Priesas uzsidega! Papildoma -3 HP.\n";
            }
        }

        bool allDeadAfter = true;
        for (auto &e : enemies) if (e.hp > 0) allDeadAfter = false;
        if (allDeadAfter) continue;

        cout << "\nPriesu eile:\n";
        for (auto &e : enemies) {
            if (e.hp <= 0) continue;

            int dmg = max(6, e.attack - (p.defense / 3) + (rand() % 7));
            if (defending) dmg /= 2;

            if (gorath && turn % 3 == 0 && e.name.find("Kinga") != string::npos) {
                cout << "Kinga ruosia INFERNO SMUGI!\n";
                dmg = defending ? 10 : 30;
            }

            p.hp -= dmg;
            cout << e.name << " atakuoja. Jokubas gauna " << dmg << " zalos.\n";
        }

        if (boss && title.find("Edvin") != string::npos) {
            for (auto &e : enemies) {
                if (e.name.find("Edvin") != string::npos && e.hp > 0 && e.hp <= 180 && e.defense == 10) {
                    e.defense += 5;
                    e.attack += 4;
                    cout << "\nEdvin apsigaubia tamsos skydu! Jo gynyba ir ataka padideja.\n";
                }
            }
        }

        if (gorath) {
            for (auto &e : enemies) {
                if (e.name.find("Kinga") != string::npos && e.hp > 0 && e.hp <= 350 && e.attack == 30) {
                    e.attack += 10;
                    cout << "\nKingao pyktis sustipreja! Ataka +10.\n";
                }
            }
        }

        if (p.hp <= 0) playerDead(p);
        turn++;
        waitEnter();
    }
}

void shop(Player &p) {
    while (true) {
        header(p, "Keliaujantis pirklys");
        cout << "Po isdegusiu medziu sedi senas pirklys Dumas.\n";
        cout << "Tyliau... bet jei nori isgyventi, turiu geru daiktu.\n\n";
        cout << "1) HP eliksyras (+60 HP) - 15 monetu\n";
        cout << "2) Didelis HP eliksyras (+120 HP) - 35 monetos\n";
        cout << "3) Stiprus skydas (+8 gynyba) - 60 monetu\n";
        cout << "4) Kario salmas (+5 gynyba, +30 max HP) - 55 monetos\n";
        cout << "5) Kalvio kardas (+18 ataka) - 70 monetu\n";
        cout << "0) Iseiti\n";
        int c = askChoice(0, 5);
        if (c == 0) break;
        if (c == 1 && p.coins >= 15) { p.coins -= 15; p.potions++; cout << "Nupirkai HP eliksyra.\n"; }
        else if (c == 2 && p.coins >= 35) { p.coins -= 35; p.potions += 2; cout << "Nupirkai 2 stiprius eliksyrus.\n"; }
        else if (c == 3 && p.coins >= 60) { p.coins -= 60; p.defense += 8; cout << "Uzdedi stipru skyda. Gynyba +8.\n"; }
        else if (c == 4 && p.coins >= 55) { p.coins -= 55; p.defense += 5; p.maxHP += 30; p.hp += 30; cout << "Uzdedi kario salma.\n"; }
        else if (c == 5 && p.coins >= 70) { p.coins -= 70; p.attack += 18; cout << "Nupirkai kalvio karda. Ataka +18.\n"; }
        else cout << "Nepakanka monetu.\n";
        waitEnter();
    }
}

void restCamp(Player &p, const string &place) {
    header(p, "Poilsio vieta");
    cout << "Pries keliaudamas toliau, Jokubas randa saugia vieta: " << place << ".\n";
    cout << "Jis pailsi, sutvarko sarvus ir pasiruosia kitai kovai.\n\n";
    p.hp = p.maxHP;
    cout << "HP pilnai atkurta: " << p.hp << "/" << p.maxHP << "\n";
    waitEnter();
}

void intro(Player &p) {
    header(p, "Pelenu Kaimas");
    showVillageArt();
    cout << "Jokubas grizta namo po medziokles ir randa kaima deganti.\n";
    cout << "Ore tvyro dumai, namai sugriuve, o gatvese - tik pelenai.\n\n";
    cout << "Purve guli sena zyne Mora. Ji vos kvepuoja.\n\n";
    cout << "Mora: \"Jokubas... jie atejo is misko... demonai su juodais zenklais...\n";
    cout << "Mora: \"Pasieme vaikus... Sventykloje... skubek...\"\n\n";
    cout << "Mora istiesia tau amuleta ir uzmerkia akis.\n";
    p.hasAmulet = true;
    cout << "\nGautas daiktas: Moros amuletas.\n";
    waitEnter();
}

void forest(Player &p) {
    header(p, "Tamsusis Miskas");
    showForestArt();
    cout << "Miskas tamsus ir rukantas. Medziai isdege. Keistai tylu.\n";
    waitEnter();

    vector<Enemy> hounds = {
        {"Seseliu Suo", "demonas", 30, 30, 6, 0},
        {"Seseliu Suo", "demonas", 30, 30, 6, 0}
    };
    fight(p, hounds, "Pirmieji Seseliai");
    p.coins += 100;
    p.potions += 2;
    p.xp += 80;

    vector<Enemy> soldiers = {
        {"Demonu Kareivis", "demonas", 45, 45, 9, 3},
        {"Demonu Kareivis", "demonas", 45, 45, 9, 3},
        {"Demonu Kareivis", "demonas", 45, 45, 9, 3}
    };
    fight(p, soldiers, "Patruliai");
    p.coins += 70;
    p.bandages += 2;
    p.hasMap = true;
    p.xp += 130;

    header(p, "Tamsusis Miskas");
    cout << "Ant vieno kareivio randi sulauzyta zemelapi.\n";
    cout << "Jame pazymeta slapta sventykla.\n";
    waitEnter();

    shop(p);
}

void temple(Player &p) {
    header(p, "Apleista Sventykla");
    showTempleArt();
    cout << "Akmeniniai griuvesiai stovi tarp pelenu.\n";
    cout << "Ant sienu juodi demonu zenklai. Ore kvepia siera.\n";
    waitEnter();

    vector<Enemy> watchers = {
        {"Akmeninis Milzinas", "akmuo", 80, 80, 14, 8},
        {"Akmeninis Milzinas", "akmuo", 80, 80, 14, 8}
    };
    fight(p, watchers, "Sventyklos Sargai");
    p.coins += 90;
    p.armorFragments += 1;
    p.xp += 180;

    header(p, "Bosas: Edvin Vaskan");
    cout << "Is tamsos iseina buves sventyklos kunigas. Jos akys dega juoda ugnimi.\n\n";
    cout << "Edvin Vaskan: \"Jokubas Dagys... tu jau mires, tiesiog dar nezinai.\n";
    cout << "Edvin Vaskan: \"Musu Valdovas Koras atgims - ir tavo kaimas buvo tik pradzia.\"\n";
    waitEnter();

    vector<Enemy> serafas = {
        {"Edvin Vaskan", "demonas", 300, 300, 18, 8},
        {"Skeletas", "undead", 50, 50, 8, 2},
        {"Skeletas", "undead", 50, 50, 8, 2}
    };
    fight(p, serafas, "Edvin Vaskan", true);

    p.coins += 150;
    p.hasDungeonKey = true;
    p.xp += 260;

    header(p, "Po pergales");
    cout << "Edvin krenta. Prie jo kuno randi Pozemio Rakta ir Noctis uzrasus.\n";
    cout << "Uzrasuose parasyta: vaikai laikomi pozemineje tvirtoveje.\n";
    waitEnter();
}

void ashFalchion(Player &p) {
    header(p, "Pelenu Skliautas");
    cout << "Jokubas atrakina lobio kambari Pozemio Raktu.\n";
    cout << "Viduje stovi senas altorius. I akmeni ikaltas kardas.\n\n";
    cout << "Tai Pelenu Falchionas - ginklas, nukaltas pries 300 metu.\n";
    cout << "Paskutinis Pelenu Karys juo kovojo su tais paciais demonais.\n";
    waitEnter();

    p.hasAshFalchion = true;
    p.attack += 45;
    p.achievements++;

    header(p, "Ypatingas ginklas");
    cout << "╔══════════════════════════════════════════════╗\n";
    cout << "║        RASTAS YPATINGAS GINKLAS!             ║\n";
    cout << "║        Pelenu Falchionas ikeltas             ║\n";
    cout << "║        i inventoriu. Automatiska             ║\n";
    cout << "║        uzdetas kaip ginklas.                 ║\n";
    cout << "╚══════════════════════════════════════════════╝\n\n";
    cout << "Efektai:\n";
    cout << "- Ataka +45\n";
    cout << "- 20% sansas padegti priesa\n";
    cout << "- Pelenu Pliupsnis: 3x stipresnis smugis karta per kova\n";
    cout << "- +50% zalos pries demonus\n";
    waitEnter();
}

void fortress(Player &p) {
    header(p, "Pozemine Tvirtove");
    showFortressArt();
    cout << "Pozeminis labirintas pilnas grotų, grandiniu ir lavos upeliu.\n";
    cout << "Tolumoje girdisi vaiku balsai.\n";
    waitEnter();

    vector<Enemy> guards = {
        {"Liepsnos Sargas", "demonas", 60, 60, 16, 5},
        {"Liepsnos Sargas", "demonas", 60, 60, 16, 5},
        {"Liepsnos Sargas", "demonas", 60, 60, 16, 5},
        {"Liepsnos Sargas", "demonas", 60, 60, 16, 5}
    };
    fight(p, guards, "Tvirtoves Apsauga");
    p.coins += 40;
    p.flameCrystals += 2;
    p.xp += 200;

    if (p.hasDungeonKey) ashFalchion(p);

    header(p, "Bosas: Kinga Wysocka");
    cout << "Ant lavos sosto sedi demone Kinga Wysocka.\n\n";
    cout << "Kinga: \"Tu atradai Pelenu Falchiona... Idomu.\n";
    cout << "Kinga: \"Paskutinis jo savininkas irgi mane, kad gali mus sustabdyti.\n";
    cout << "Kinga: \"Jo kaulai puosia mano sosta.\"\n";
    waitEnter();

    vector<Enemy> gorath = {
        {"Kinga Wysocka", "demonas", 450, 450, 24, 12},
        {"Liepsnos Sargas", "demonas", 60, 60, 16, 5},
        {"Liepsnos Sargas", "demonas", 60, 60, 16, 5},
        {"Liepsnos Sargas", "demonas", 60, 60, 16, 5}
    };
    fight(p, gorath, "Kinga Wysocka", true, true);

    p.coins += 300;
    p.xp += 350;
    p.achievements += 2;

    header(p, "Kingao pabaiga");
    cout << "Kinga krenta ant keliu...\n";
    cout << "Kinga: \"Tu... nezinai... ko esi dalis... Koras... jau... pabudo...\"\n";
    cout << "Kinga virsta pelenais.\n\n";
    cout << "Gauta: 300 monetu, Kingao Sirdis, pasiekimas - Vaikai islaisvinti.\n";
    waitEnter();
}

void ending(Player &p) {
    header(p, "1 Skyriaus pabaiga");
    cout << "Jokubas isveda vaikus is tvirtoves.\n";
    cout << "Prie isejimo jo laukia paslaptingas keliautojas su kapisonu - Vex.\n\n";
    cout << "Vex: \"Neblogai, kalvi. Kinga buvo tik sargas.\n";
    cout << "Vex: \"Koras - tai kas kita. Jei nori zinoti kur jis - eik paskui mane.\"\n\n";
    cout << "Jokubas ziuri atgal i degancio kaimo krypti. Tada seka Vexa.\n\n";

    cout << "╔══════════════════════════════════════════════╗\n";
    cout << "║             1 SKYRIUS BAIGTAS!               ║\n";
    cout << "║                                              ║\n";
    cout << "║  XP gauta:      " << p.xp << "               ║\n";
    cout << "║  Monetos:       " << p.coins << "            ║\n";
    cout << "║  Pasiekimai:    " << p.achievements << "     ║\n";
    cout << "║  Istorija tesiasi 2 skyriuje...              ║\n";
    cout << "╚══════════════════════════════════════════════╝\n";
    waitEnter();
}

void mainMenu(Player &p) {
    while (true) {
        header(p, "Pagrindinis meniu");
        cout << "1) Pradeti 1 skyriu\n";
        cout << "2) Herojaus informacija\n";
        cout << "3) Instrukcija\n";
        cout << "0) Iseiti\n";
        int c = askChoice(0, 3);
        if (c == 0) exit(0);
        if (c == 2) showHero(p);
        if (c == 3) {
            header(p, "Instrukcija");
            cout << "Tai tekstine RPG kova konsolėje.\n";
            cout << "Rinkis skaicius meniu, kovok su priesais ir sek istorija.\n";
            cout << "Gintis naudinga pries stiprias atakas.\n";
            cout << "Parduotuveje gali nusipirkti eliksyru ir apsaugos.\n";
            waitEnter();
        }
        if (c == 1) break;
    }
}

int main() {
    srand((unsigned)time(nullptr));
    Player player;

    mainMenu(player);
    intro(player);
    shop(player);
    forest(player);
    temple(player);
    restCamp(player, "sventyklos rusys");
    shop(player);
    fortress(player);
    ending(player);

    return 0;
}
