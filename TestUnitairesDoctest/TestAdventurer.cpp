#include "doctest.h"
#include "adventurer.h"

TEST_CASE("Test de la classe adventurer")
{
    SUBCASE("Test des constructeurs")
    {
        SUBCASE("Test du constructeur par d�faut")
        {
            adventurer a{};
            REQUIRE_EQ(a.getHp(), 0);
            REQUIRE_EQ(a.getStrength(), 0);
            REQUIRE_EQ(a.getArmor(), 0);
            REQUIRE_EQ(a.getSword(), 0);
        }
        SUBCASE("Test du constructeur")
        {
            adventurer a{100,100,100,100};
            REQUIRE_EQ(a.getHp(), 100);
            REQUIRE_EQ(a.getStrength(), 100);
            REQUIRE_EQ(a.getArmor(), 100);
            REQUIRE_EQ(a.getSword(), 100);
        }

    }

    SUBCASE("Test des m�thodes de r�paration des �quipement de l'aventurier")
     {
         SUBCASE("Test de la r�paration de l'�pee avec les pieces")
         {
            adventurer a{20,20,10,10};
            a.increasePurse(1);
            a.repairSword();
            REQUIRE_EQ(a.getSword(),11);
            REQUIRE_EQ(a.getPurse(),0);
         }
         SUBCASE("Test de la r�paration de l'armure avec les pieces")
         {
            adventurer a{20,20,10,10};
            a.increasePurse(1);
            a.repairArmor();
            REQUIRE_EQ(a.getArmor(),11);
            REQUIRE_EQ(a.getPurse(),0);
         }
     }

    SUBCASE("Test de d�placement de l'aventurier")
     {
        adventurer a{};
        a.move(10,10);
        REQUIRE_EQ(a.getX(),10);
        REQUIRE_EQ(a.getY(),10);
     }

     SUBCASE("Test du setteur de position de l'aventurier")
     {
        adventurer a{};
        a.setPos(15,15);
        REQUIRE_EQ(a.getX(),15);
        REQUIRE_EQ(a.getY(),15);
     }

     SUBCASE("Test d'une attaque")
     {
        SUBCASE("Test de la m�thode attacked")
        {
            SUBCASE("Si l'aventurier a encore de l'armure")
            {
                adventurer a{100,50,200,200};
                a.attacked(20);
                REQUIRE_EQ(a.getArmor(),193);
                REQUIRE_EQ(a.getHp(),95);
            }
            SUBCASE("Si l'aventurier n'as plus du tout d'armure")
            {
                adventurer a{100,50,200,0};
                a.increasePurse(100);
                a.attacked(20);
                REQUIRE_EQ(a.getArmor(),93);
                REQUIRE_EQ(a.getPurse(),0);
                REQUIRE_EQ(a.getHp(),95);
            }
            SUBCASE("Test de la mort de l'aventurier")
            {
                adventurer a{1,50,200,0};
                a.attacked(20);
                REQUIRE_EQ(a.getHp(),0);
            }
        }
        SUBCASE("Test de la m�thode kill")
        {
            adventurer a{100,50,200,100};
            a.kill(20);
            REQUIRE_EQ(a.getHp(),100);
            REQUIRE_EQ(a.getStrength(),50);
        }
        SUBCASE("Test de la d�gradation de l'�pee")
        {
            adventurer a{100,50,200,100};
            a.increasePurse(10);
            a.loseSword();
            REQUIRE_EQ(a.getPurse(),10);
        }
     }

    SUBCASE("Test du don de pi�ces � l'aventurier")
    {
        adventurer a{10,10,10,10};
        a.increasePurse(150);
        REQUIRE_EQ(a.getPurse(),150);

    }

}





