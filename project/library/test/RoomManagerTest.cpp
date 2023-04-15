#include <boost/test/unit_test.hpp>

#include "managers/RoomManager.h"
#include "model/Repository.h"
#include "model/Room.h"

struct TestSuiteRoomManagerFixture {
    const int testBasePrice = 100;
    const int testRoomNumber = 12;
    const int testRoomCapacity = 2;
    RoomRepositoryPtr testRoomRepository;

    TestSuiteRoomManagerFixture() {
        testRoomRepository = std::make_shared<Repository<RoomPtr>>();
    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRoomManager, TestSuiteRoomManagerFixture)

    BOOST_AUTO_TEST_CASE(ContructorException) {
        BOOST_REQUIRE_THROW(new RoomManager(nullptr), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(RegisterRoomTest) {
        RoomManager roomManager(testRoomRepository);

        RoomPtr testRoom = roomManager.registerRoom(testBasePrice, testRoomNumber, testRoomCapacity);

        BOOST_TEST(testRoom == roomManager.getRoom(testRoomNumber));
    }

    BOOST_AUTO_TEST_CASE(RegisterRoomTestTheSameNumber) {
        RoomManager roomManager(testRoomRepository);

        RoomPtr testRoom1 = roomManager.registerRoom(testBasePrice, testRoomNumber, testRoomCapacity);
        RoomPtr testRoom2 = roomManager.registerRoom(testBasePrice+1, testRoomNumber, testRoomCapacity+1);

        BOOST_TEST(testRoom1 == testRoom2);
    }

    BOOST_AUTO_TEST_CASE(GetRoomTest) {
        RoomManager roomManager(testRoomRepository);

        RoomPtr testRoom = roomManager.registerRoom(testBasePrice, testRoomNumber, testRoomCapacity);

        int size = 5;
        for (int i = 0; i < size; i++) {
            roomManager.registerRoom(testBasePrice, testRoomNumber+i+1, testRoomCapacity);
        }

        BOOST_TEST(roomManager.getRoom(testRoomNumber) == testRoom);
    }

    BOOST_AUTO_TEST_CASE(GetRoomTestNullPtr) {
        RoomManager roomManager(testRoomRepository);

        int size = 5;
        for (int i = 0; i < size; i++) {
            roomManager.registerRoom(testBasePrice, testRoomNumber+i+1, testRoomCapacity);
        }

        BOOST_TEST(roomManager.getRoom(testRoomNumber) == nullptr);
    }

    BOOST_AUTO_TEST_CASE(UnregisterRoomTest) {
        RoomManager roomManager(testRoomRepository);

        RoomPtr testRoom = roomManager.registerRoom(testBasePrice, testRoomNumber, testRoomCapacity);
        roomManager.unregisterRoom(testRoom);

        BOOST_TEST(roomManager.getRoom(testRoomNumber)->checkIfArchived());
    }

BOOST_AUTO_TEST_SUITE_END()