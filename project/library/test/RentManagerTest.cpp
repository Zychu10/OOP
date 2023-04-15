#include <boost/test/unit_test.hpp>

#include "managers/RentManager.h"
#include "model/Repository.h"
#include "model/Rent.h"
#include "model/Client.h"
#include "model/Room.h"
#include <boost/uuid/uuid_generators.hpp>

struct TestSuiteRentManagerFixture {
    const std::string testFirstName = "Jan";
    const std::string testLastName = "Nowak";
    const std::string testPersonalID = "0123456789";
    const unsigned int testBasePrice = 100;
    const unsigned int testRoomNumber = 12;
    const unsigned int testRoomCapacity = 2;
    RentRepositoryPtr testCurrentRents;
    RentRepositoryPtr testArchiveRents;
    ClientPtr testClient;
    RoomPtr testRoom;
    RoomPtr testRoom2;
    boost::posix_time::ptime testTime;

    TestSuiteRentManagerFixture() {
        testCurrentRents = std::make_shared<Repository<RentPtr>>();
        testArchiveRents = std::make_shared<Repository<RentPtr>>();
        testClient = std::make_shared<Client>(testFirstName, testLastName, testPersonalID);
        testRoom = std::make_shared<Room>(testBasePrice, testRoomNumber, testRoomCapacity);
        testRoom2 = std::make_shared<Room>(testBasePrice, testRoomNumber, testRoomCapacity);
        testTime = boost::posix_time::second_clock::local_time();
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRenttManager, TestSuiteRentManagerFixture)

    BOOST_AUTO_TEST_CASE(ContructorException) {
        BOOST_REQUIRE_THROW(new RentManager(nullptr, nullptr), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(RentRoomTest) {
        RentManager rManager(testCurrentRents, testArchiveRents);

        RentPtr testRent = rManager.rentRoom(testClient, testRoom, testTime);

        BOOST_TEST(rManager.getRent(testRoom) == testRent);
    }

    BOOST_AUTO_TEST_CASE(RentRoomTestWhenAlreadyRented) {
        RentManager rManager(testCurrentRents, testArchiveRents);
        RentPtr testRent1 = rManager.rentRoom(testClient, testRoom, testTime);
        BOOST_REQUIRE_THROW(RentPtr testRent2 = rManager.rentRoom(testClient, testRoom, testTime), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(ReturnRoomTest) {
        RentManager rManager(testCurrentRents, testArchiveRents);

        RentPtr testRent = rManager.rentRoom(testClient, testRoom, testTime);
        rManager.returnRoom(testRoom);

        BOOST_TEST(rManager.getRent(testRoom) == nullptr);
    }

    BOOST_AUTO_TEST_CASE(findRoomRentTest) {
        RentManager rManager(testCurrentRents, testArchiveRents);

        RentPtr testRent1 = rManager.rentRoom(testClient, testRoom, testTime);
        RentPtr testRent2 = rManager.rentRoom(testClient, testRoom2, testTime);

        BOOST_TEST(rManager.getRent(testRoom) == testRent1);
    }

    BOOST_AUTO_TEST_CASE(findRoomRentTestNullPtr) {
        RentManager rManager(testCurrentRents, testArchiveRents);

        rManager.rentRoom(testClient, testRoom, testTime);

        BOOST_TEST(rManager.getRent(testRoom2) == nullptr);
    }

    BOOST_AUTO_TEST_CASE(ChangeClientTypeTest) {
        RentManager rManager(testCurrentRents, testArchiveRents);

        BOOST_TEST(testClient->getClientType()->getInfo() == "default");

        RoomPtr expensiveRoom = std::make_shared<Room>(9999, testRoomNumber, testRoomCapacity);

        rManager.rentRoom(testClient, expensiveRoom, testTime - boost::posix_time::hours(2));

        rManager.returnRoom(expensiveRoom);

        BOOST_TEST(testClient->getClientType()->getInfo() == "deluxe");
    }


BOOST_AUTO_TEST_SUITE_END()