#include "doctest.h"
#include "level.h"
#include "curses.h"

TEST_CASE("Test de la classe level")
{
    SUBCASE("Test du constructeur par défaut")
    {
        level l{};
        REQUIRE_EQ(l.getAmulet(),false);
    }
    SUBCASE("Test de la fin d'un niveau")
    {
        level l{};
        REQUIRE_EQ(l.endLevel(),false);
    }
}
