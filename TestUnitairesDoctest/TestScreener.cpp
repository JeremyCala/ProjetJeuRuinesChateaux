#include "doctest.h"
#include "screener.h"

TEST_CASE("Test de la classe screener")
{
    SUBCASE("Test des constructeurs")
    {
        SUBCASE("Par défaut")
        {
            screener s{};
            REQUIRE_EQ(s.length(),0);
            REQUIRE_EQ(s.width(),0);
        }
        SUBCASE("Avec les dimensions")
        {
            screener s{25,56};
            REQUIRE_EQ(s.length(),25);
            REQUIRE_EQ(s.width(),56);
        }
    }
}
