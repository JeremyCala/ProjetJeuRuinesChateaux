#include "doctest.h"
#include "room.h"

TEST_CASE("Tests de la classe room")
{
    SUBCASE("Test du constructeur par défaut")
    {
        room r{};
        REQUIRE_EQ(r.getX(),0);
        REQUIRE_EQ(r.getY(),0);
        REQUIRE_EQ(r.getLength(),0);
        REQUIRE_EQ(r.getWidth(),0);
    }
    SUBCASE("Test du constructeur ")
    {
        room r{4,5,25,50};
        REQUIRE_EQ(r.getX(),4);
        REQUIRE_EQ(r.getY(),5);
        REQUIRE_EQ(r.getLength(),25);
        REQUIRE_EQ(r.getWidth(),50);
    }
}
