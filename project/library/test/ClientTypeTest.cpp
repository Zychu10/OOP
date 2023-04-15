#include <boost/test/unit_test.hpp>

#include "model/ClientType.h"
#include "model/typedefs.h"

BOOST_AUTO_TEST_SUITE(TestSuiteClientType)

    BOOST_AUTO_TEST_CASE(GetInfoTest) {
        ClientTypePtr clientType = std::make_shared<Default>();
        BOOST_TEST(clientType->getInfo() == "default");

        clientType = std::make_shared<Premium>();
        BOOST_TEST(clientType->getInfo() == "premium");

        clientType = std::make_shared<Deluxe>();
        BOOST_TEST(clientType->getInfo() == "deluxe");
    }

    BOOST_AUTO_TEST_CASE(ApplyDiscountTest) {
        ClientTypePtr clientType = std::make_shared<Deluxe>();
        // deluxe >500 zniżka 40%
        BOOST_TEST(clientType->discount(1000) == 600);

        clientType = std::make_shared<Premium>();
        // premium zniżka 15%
        BOOST_TEST(clientType->discount(1000) == 850);

        clientType = std::make_shared<Default>();
        // default brak zniżki
        BOOST_TEST(clientType->discount(1000) == 1000);
    }

BOOST_AUTO_TEST_SUITE_END()