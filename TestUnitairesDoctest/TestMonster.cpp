#include "doctest.h"
#include "monster.h"

TEST_CASE("Tests de la classe monster")
{
    SUBCASE("Test des constructeurs")
    {
        SUBCASE("Test pour le monstre")
        {
            SUBCASE("Test du constructeur")
            {
                monster m{10,10,12.2,10,10};
                REQUIRE_EQ(m.getHp(),10);
                REQUIRE_EQ(m.getStrength(),10);
                REQUIRE_EQ(m.getPercentSkill(),12.2);
                REQUIRE_EQ(m.getX(),10);
                REQUIRE_EQ(m.getY(),10);
            }
            SUBCASE("Test du constructeur par défaut")
            {
                monster m{};
                REQUIRE_EQ(m.getHp(),0);
                REQUIRE_EQ(m.getStrength(),0);
                REQUIRE_EQ(m.getPercentSkill(),0.0);
                REQUIRE_EQ(m.getX(),0);
                REQUIRE_EQ(m.getY(),0);
            }
        }
        SUBCASE("Test pour le monstre voyant")
        {
            SUBCASE("Test du constructeur")
            {
                sightMonster m{10,10,12.2,10,10};
                REQUIRE_EQ(m.getHp(),10);
                REQUIRE_EQ(m.getStrength(),10);
                REQUIRE_EQ(m.getPercentSkill(),12.2);
                REQUIRE_EQ(m.getX(),10);
                REQUIRE_EQ(m.getY(),10);
            }
        }
    }

    SUBCASE("Test du setteur")
    {
        monster m{20,20,20.0,20,20};
        position p{14,14};
        m.set(p);
        REQUIRE_EQ(m.getX(),14);
        REQUIRE_EQ(m.getY(),14);
    }
    SUBCASE("Test du déplacement d'un monstre (méthode moveFrom)")
    {
        monster m{};
        m.moveFrom(10,10);
        REQUIRE_EQ(m.getX(),10);
        REQUIRE_EQ(m.getY(),10);
    }
    SUBCASE("Test d'une attaque")
    {
        SUBCASE("Le monstre est attaqué")
        {
            monster m{20,20,20.0,20,20};
            m.attacked(10);
            REQUIRE_EQ(m.getHp(),10);
        }
    }
}

