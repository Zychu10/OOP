#include <boost/test/unit_test.hpp>

#include "managers/ClientManager.h"
#include "model/Repository.h"
#include "model/Client.h"


struct TestSuiteClientManagerFixture {
    const std::string testFirstName = "Jan";
    const std::string testLastName = "Nowak";
    const std::string testPersonalID = "0123456789";
    ClientRepositoryPtr testClientRepository;


    TestSuiteClientManagerFixture() {
        testClientRepository = std::make_shared<Repository<ClientPtr>>();
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteClientManager, TestSuiteClientManagerFixture)

    BOOST_AUTO_TEST_CASE(ContructorException) {
        BOOST_REQUIRE_THROW(new ClientManager(nullptr), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(RegisterClientTest) {
        ClientManager cManager(testClientRepository);

        ClientPtr testClient = cManager.registerClient(testFirstName, testLastName, testPersonalID);

        BOOST_TEST(testClient == cManager.getClient(testPersonalID));
    }

    BOOST_AUTO_TEST_CASE(RegisterClientTestTheSameID) {
        ClientManager cManager(testClientRepository);

        ClientPtr testClient1 = cManager.registerClient("Jan", "Nowak", testPersonalID);
        ClientPtr testClient2 = cManager.registerClient("Janusz", "Kowalski", testPersonalID);

        BOOST_TEST_REQUIRE(testClient1 == testClient2);
        BOOST_TEST(testClient1->getFirstName() == "Janusz");
        BOOST_TEST(testClient1->getSecondName() == "Kowalski");
        BOOST_TEST(testClient1->getClientID() == testPersonalID);
        BOOST_TEST(testClient1->chechIfArchived());
    }

    BOOST_AUTO_TEST_CASE(GetClientTest) {
        ClientManager cManager(testClientRepository);

        ClientPtr testClient = cManager.registerClient(testFirstName, testLastName, testPersonalID);

        int size = 5;
        for (int i = 0; i < size; i++) {
            std::ostringstream sout;
            sout << "012345678 " << (i);
            cManager.registerClient("Janusz", "Kowalski", sout.str());
        }

        BOOST_TEST(cManager.getClient(testPersonalID) == testClient);
    }

    BOOST_AUTO_TEST_CASE(GetClientTestNullPtr) {
        ClientManager cManager(testClientRepository);

        int size = 5;
        for (int i = 0; i < size; i++) {
            std::ostringstream sout;
            sout << "012345678 " << (i);
            cManager.registerClient("Janusz", "Kowalski", sout.str());
        }

        BOOST_TEST(cManager.getClient(testPersonalID) == nullptr);
    }

    BOOST_AUTO_TEST_CASE(UnregisterClientTest) {
        ClientManager cManager(testClientRepository);

        ClientPtr client = cManager.registerClient(testFirstName, testLastName, testPersonalID);
        cManager.unregisterClient(client);

        BOOST_TEST(cManager.getClient(testPersonalID)->chechIfArchived());
    }

BOOST_AUTO_TEST_SUITE_END()