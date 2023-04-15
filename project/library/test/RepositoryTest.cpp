#include <boost/test/unit_test.hpp>

#include "model/Repository.h"
#include "model/typedefs.h"
#include "model/Client.h"


struct TestSuiteRepositoryFixture {
    const std::string testFirstName = "Jan";
    const std::string testLastName = "Nowak";
    const std::string testPersonalID = "0123456789";

};

// Testy tworzone dla jednego typo, bo reszta zachowuje się tak samo

BOOST_FIXTURE_TEST_SUITE(TestSuiteRepository, TestSuiteRepositoryFixture)

    BOOST_AUTO_TEST_CASE(GetTest) {
        Repository<ClientPtr> cRepo;
        int size = 5;
        ClientPtr clients[size];

        for (int i = 0; i < size; i++) {
            std::ostringstream sout;
            sout << "012345678" << i;
            clients[i] = std::make_shared<Client>(testFirstName, testLastName, sout.str());
            cRepo.add(clients[i]);
        }

        for (int i = 0; i < size; i++) {
            BOOST_TEST(cRepo.get(i) == clients[i]);
        }
    }

    BOOST_AUTO_TEST_CASE(GetTestException) {
        Repository<ClientPtr> cRepo;
        BOOST_REQUIRE_THROW(cRepo.get(1), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(AddTest) {
        Repository<ClientPtr> cRepo;
        int size = 5;
        ClientPtr clients[size];

        for (int i = 0; i < size; i++) {
            std::ostringstream sout;
            sout << "012345678" << i;
            cRepo.add(std::make_shared<Client>(testFirstName, testLastName, sout.str()));
        }

        BOOST_TEST(cRepo.size() == size);
    }

    BOOST_AUTO_TEST_CASE(AddTestException) {
        Repository<ClientPtr> cRepo;
        BOOST_REQUIRE_THROW(cRepo.add(nullptr), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(FindTest) {
        Repository<ClientPtr> cRepo;
        std::string findPersonalID = "looking_id";
        ClientPtr findClient = std::make_shared<Client>(testFirstName, testLastName, findPersonalID);
        cRepo.add(findClient);

        int size = 5;
        for (int i = 0; i < size; i++) {
            std::ostringstream sout;
            sout << "012345678" << i;
            cRepo.add(std::make_shared<Client>(testFirstName, testLastName, sout.str()));
        }

        ClientPredicate predicate = [findPersonalID](const ClientPtr &ptr) {
            return ptr->getClientID() == findPersonalID;
        };

        BOOST_TEST(cRepo.find(predicate) == findClient);
    }

    BOOST_AUTO_TEST_CASE(FindAllTest) {
        Repository<ClientPtr> cRepo;
        int NowakSize = 3;
        int KowalskiSize = 2;
        std::string findLastName = "Kowalski";
        BOOST_TEST_REQUIRE(testFirstName != findLastName);
        for (int i = 0; i < NowakSize; i++) {
            std::ostringstream sout;
            sout << "012345678" << i;
            cRepo.add(std::make_shared<Client>(testFirstName, findLastName, sout.str()));
        }
        for (int i = 0; i < KowalskiSize; i++) {
            std::ostringstream sout;
            sout << "012345678" << i + NowakSize;
            cRepo.add(std::make_shared<Client>(testFirstName, testLastName, sout.str()));
        }

        ClientPredicate predicate = [findLastName](const ClientPtr &ptr) {
            return ptr->getSecondName() == findLastName;
        };

        BOOST_TEST(cRepo.findAll(predicate).size() == NowakSize);
    }

    BOOST_AUTO_TEST_CASE(SizeTest) {
        Repository<ClientPtr> cRepo;
        int size = 5;
        for (int i = 0; i < size; i++) {
            std::ostringstream sout;
            sout << "012345678" << i;
            cRepo.add(std::make_shared<Client>(testFirstName, testLastName, sout.str()));
        }

        BOOST_TEST(cRepo.size() == size);
    }

    BOOST_AUTO_TEST_CASE(RemoveTest) {
        Repository<ClientPtr> cRepo;
        int size = 5;
        ClientPtr clients[size];
        for (int i = 0; i < size; i++) {
            std::ostringstream sout;
            sout << "012345678" << i;
            clients[i] = std::make_shared<Client>(testFirstName, testLastName, sout.str());
            cRepo.add(clients[i]);
        }

        cRepo.remove(clients[2]);
        cRepo.remove(clients[3]);

        BOOST_TEST(cRepo.size() == size - 2);
    }


BOOST_AUTO_TEST_SUITE_END()