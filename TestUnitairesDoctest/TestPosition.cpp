#include "doctest.h"
#include "position.h"

TEST_CASE("Test de la classe position")
{
    SUBCASE("Test des constructeurs")
    {
        SUBCASE("Par défaut")
        {
            position p{};
            REQUIRE_EQ(p.getX(),0);
            REQUIRE_EQ(p.getY(),0);
        }
        SUBCASE("Avec des coordonnées")
        {
            position p{5,5};
            REQUIRE_EQ(p.getX(),5);
            REQUIRE_EQ(p.getY(),5);
        }
        SUBCASE("Avec une position")
        {
            position p{5,5};
            position p2{p};
            REQUIRE_EQ(p.getX(),5);
            REQUIRE_EQ(p.getY(),5);
        }
    }

    SUBCASE("Test des setteurs")
    {
        SUBCASE("Setteur de X")
        {
            position p;
            p.setX(10);
            REQUIRE_EQ(p.getX(),10);
        }

        SUBCASE("Setteur de Y")
        {
            position p;
            p.setY(20);
            REQUIRE_EQ(p.getY(),20);
        }

        SUBCASE("Setteur avec X et Y")
        {
            position p;
            p.set(5,5);
            REQUIRE_EQ(p.getX(),5);
            REQUIRE_EQ(p.getY(),5);
        }

        SUBCASE("Setteur avec une position")
        {
            position p;
            position p1{30,30};
            p.set(p1);
            REQUIRE_EQ(p.getX(),30);
            REQUIRE_EQ(p.getY(),30);
        }
    }

    SUBCASE("Test de la méthode de la méthode moveFrom")
    {
        position p{0,0};
        p.moveFrom(1,18);
        REQUIRE_EQ(p.getX(),1);
        REQUIRE_EQ(p.getY(),18);
    }
}

