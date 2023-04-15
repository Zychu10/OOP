#include <boost/test/unit_test.hpp>

#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <string>

#include "model/Client.h"
#include "model/Room.h"
#include "model/Rent.h"


namespace pt = boost::posix_time;

struct TestSuiteRentFixture {
    const std::string testFirstName = "Jan";
    const std::string testLastName = "Nowak";
    const std::string testPersonalID = "0123456789";
    const unsigned int testBasePrice = 100;
    const unsigned int testRoomNumber = 12;
    const unsigned int testRoomCapacity = 2;
    ClientPtr testClient;
    RoomPtr testRoom;
    boost::uuids::uuid testId;
    pt::ptime testBeginTime;
    pt::ptime beginTime = pt::not_a_date_time;

    TestSuiteRentFixture() {
        testClient = std::make_shared<Client>(testFirstName, testLastName, testPersonalID);
        testRoom = std::make_shared<Room>(testBasePrice, testRoomNumber, testRoomCapacity);
        boost::uuids::random_generator gen;
        testId = gen();
        testBeginTime = pt::second_clock::local_time();

    }
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRent, TestSuiteRentFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTest) {
        Rent rent(testId, testClient, testRoom, testBeginTime);

        BOOST_TEST(testId == rent.getID());
        BOOST_TEST(testClient == rent.getClient());
        BOOST_TEST(testRoom == rent.getRoom());
        BOOST_TEST(testBeginTime == rent.getBeginTime());
        BOOST_TEST(rent.getEndTime().is_not_a_date_time());
        BOOST_TEST(0 == rent.getFinalRentCost());
    }

    BOOST_AUTO_TEST_CASE(ConstructorTestExceptions) {
        BOOST_REQUIRE_THROW(Rent rent(testId, nullptr, testRoom, testBeginTime), std::logic_error);
        BOOST_REQUIRE_THROW(Rent rent(testId, testClient, nullptr, testBeginTime), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestDefaultBeginTime) {
        Rent rent(testId, testClient, testRoom, testBeginTime);

        BOOST_TEST_REQUIRE(!rent.getBeginTime().is_not_a_date_time());

        pt::ptime now = pt::second_clock::local_time();
        pt::time_period skew = pt::time_period(rent.getBeginTime(), now);

        BOOST_TEST((skew.length().hours() == 0 && skew.length().minutes() == 0));
    }


    BOOST_AUTO_TEST_CASE(EndRentTestEndNow) {
        Rent rent(testId, testClient, testRoom, testBeginTime);

        rent.endRent(testBeginTime);

        pt::time_period skew = pt::time_period(rent.getEndTime(), testBeginTime);

        BOOST_TEST(rent.getEndTime() == testBeginTime);
    }

    BOOST_AUTO_TEST_CASE(EndRentTestEndInFuture) {
        Rent rent(testId, testClient, testRoom, testBeginTime);

        pt::ptime future = testBeginTime + pt::hours(1);

        rent.endRent(future);

        pt::time_period skew = pt::time_period(rent.getEndTime(), future);

        BOOST_TEST(rent.getEndTime() == future);
    }

    BOOST_AUTO_TEST_CASE(EndRentTestEndInPast) {
        Rent rent(testId, testClient, testRoom, testBeginTime);

        pt::ptime past = testBeginTime - pt::hours(1);

        rent.endRent(past);

        BOOST_TEST(rent.getEndTime() == rent.getBeginTime());
    }

    BOOST_AUTO_TEST_CASE(EndRentTestEndRentAlreadyEnded) {
        Rent rent(testId, testClient, testRoom, testBeginTime);

        rent.endRent(testBeginTime);

        pt::ptime future = testBeginTime + pt::hours(1);

        rent.endRent(future);

        BOOST_TEST(rent.getEndTime() == testBeginTime);
    }

    BOOST_AUTO_TEST_CASE(GetDaysTestEndedAfter1h) {
        Rent rent(testId, testClient, testRoom, testBeginTime);

        pt::ptime future1h = testBeginTime + pt::hours(1);

        rent.endRent(future1h);

        BOOST_TEST(rent.getRentDays() == 1);
    }

    BOOST_AUTO_TEST_CASE(GetDaysTestEndedAfter59min) {
        Rent rent(testId, testClient, testRoom, testBeginTime);

        pt::ptime future59min = testBeginTime + pt::minutes(59);

        rent.endRent(future59min);

        BOOST_TEST(rent.getRentDays() == 0);
    }

    BOOST_AUTO_TEST_CASE(CalculateFinalRentCostTestDaysIs0) {
        Rent rent(testId, testClient, testRoom, testBeginTime);

        rent.endRent(testBeginTime);

        BOOST_TEST(rent.getFinalRentCost() == 0);
    }

    BOOST_AUTO_TEST_CASE(CalculateFinalRentCostTest) {
        Rent rent(testId, testClient, testRoom, testBeginTime);

        pt::ptime future1h = testBeginTime + pt::hours(1);

        rent.endRent(future1h);

        // Typ klienta bez zniżki
        BOOST_TEST(rent.getFinalRentCost() == 100);
    }

    BOOST_AUTO_TEST_CASE(RentCostTestPernamentCost) {
        Rent rent(testId, testClient, testRoom, testBeginTime);

        pt::ptime future1h = testBeginTime + pt::hours(1);

        rent.endRent(future1h);

        float before = rent.getFinalRentCost();

        rent.getRoom()->setRoomPrice(123);

        float after = rent.getFinalRentCost();

        BOOST_TEST(before == after);
    }

BOOST_AUTO_TEST_SUITE_END()