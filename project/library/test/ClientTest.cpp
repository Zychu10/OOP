#include <boost/test/unit_test.hpp>

#include "model/Client.h"
#include "model/typedefs.h"

struct TestSuiteClientFixture {
    const std::string testFirstName = "Jan";
    const std::string testLastName = "Nowak";
    const std::string testPersonalID = "0123456789";
    const std::string testFirstName2 = "Janusz";
    const std::string testLastName2 = "Kowalski";
    const std::string testPersonalID2 = "9876543210";



};

BOOST_FIXTURE_TEST_SUITE(TestSuiteClient, TestSuiteClientFixture)

    BOOST_AUTO_TEST_CASE(ContructorTest) {
        Client client(testFirstName, testLastName, testPersonalID);

        BOOST_TEST(client.getFirstName() == testFirstName);
        BOOST_TEST(client.getSecondName() == testLastName);
        BOOST_TEST(client.getClientID() == testPersonalID);
        BOOST_TEST(!client.chechIfArchived());
    }

    BOOST_AUTO_TEST_CASE(ContructorTestExceptions) {
        BOOST_REQUIRE_THROW(Client client("", testLastName, testPersonalID), std::logic_error);
        BOOST_REQUIRE_THROW(Client client(testFirstName, "", testPersonalID), std::logic_error);
        BOOST_REQUIRE_THROW(Client client(testFirstName, testLastName, ""), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(SettersTest) {
        Client client(testFirstName, testLastName, testPersonalID);

        client.setFirstName(testFirstName2);
        BOOST_TEST(client.getFirstName() == testFirstName2);
        client.setFirstName("");
        BOOST_TEST(client.getFirstName() == testFirstName2);

        client.setSecondName(testLastName2);
        BOOST_TEST(client.getSecondName() == testLastName2);
        client.setSecondName("");
        BOOST_TEST(client.getSecondName() == testLastName2);

    }


    BOOST_AUTO_TEST_CASE(ArchiveTest) {
        Client client(testFirstName, testLastName, testPersonalID);

        client.setIsArchive(false);

        BOOST_TEST(client.chechIfArchived());
    }

BOOST_AUTO_TEST_SUITE_END()