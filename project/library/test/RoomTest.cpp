#include <boost/test/unit_test.hpp>

#include "model/Room.h"

BOOST_AUTO_TEST_SUITE(TestSuiteRoom)

    BOOST_AUTO_TEST_CASE(ContructorTest) {
        Room room(100, 11, 2);

        BOOST_TEST(room.getRoomPrice() == 100);
        BOOST_TEST(room.getRoomNumber() == 11);
        BOOST_TEST(room.getRoomCapacity() == 2);
        BOOST_TEST(!room.checkIfArchived());
    }

    BOOST_AUTO_TEST_CASE(ContructorTestExceptions) {
        BOOST_REQUIRE_THROW(Room room(-100, 11, 2), std::logic_error);
        BOOST_REQUIRE_THROW(Room room(100, -11, 2), std::logic_error);
        BOOST_REQUIRE_THROW(Room room(100, 11, -2), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(SettersTest) {
        Room room(100, 11, 2);

        room.setRoomPrice(123);

        BOOST_TEST(room.getRoomPrice() == 123);
    }


    BOOST_AUTO_TEST_CASE(ArchiveTest) {
        Room room(100, 11, 2);

        room.setIsArchive(false);

        BOOST_TEST(room.checkIfArchived());
    }

BOOST_AUTO_TEST_SUITE_END()