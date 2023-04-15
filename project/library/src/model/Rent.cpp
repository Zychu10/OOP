#include "model/Rent.h"

#include "model/Client.h"
#include "model/Room.h"

#include <cmath>
#include "exceptions/ParameterException.h"
#include "exceptions/LogicException.h"
#include <boost/uuid/uuid_io.hpp>

Rent::Rent(const boost::uuids::uuid &id, const ClientPtr &client, const RoomPtr &room,
           const boost::posix_time::ptime &beginTime)
        : id(id),
          client(client),
          room(room),
          beginTime(beginTime) {

    if (beginTime == boost::posix_time::not_a_date_time) {
        Rent::beginTime = boost::posix_time::second_clock::local_time();
    }
    endTime = boost::posix_time::not_a_date_time;
    finalRentCost = 0;

    if (client == nullptr) { throw ParameterException("Cannot create rent without client!"); }
    if (room == nullptr) { throw ParameterException("Cannot create rent without room!"); }
}

Rent::~Rent() {

}

// getters
const boost::uuids::uuid &Rent::getID() const {
    return id;
}

const ClientPtr &Rent::getClient() const {
    return client;
}

const RoomPtr &Rent::getRoom() const {
    return room;
}

const boost::posix_time::ptime &Rent::getBeginTime() const {
    return beginTime;
}

const boost::posix_time::ptime &Rent::getEndTime() const {
    return endTime;
}

float Rent::getFinalRentCost() const {
    return finalRentCost;
}

// other methods
std::string Rent::getInfo() const {
    std::ostringstream sout;
    sout << "(Rent) rent id: " << id << " " << getClient()->getInfo() << " " << getRoom()->getInfo() << " poczatek wypozyczenia: "
         << beginTime << ", koniec wypozyczenia: " << endTime << ", oplata: " << getFinalRentCost();
    return sout.str();
}

void Rent::endRent(const boost::posix_time::ptime &arg_endTime) {
    if (endTime == boost::posix_time::not_a_date_time) {
        if (arg_endTime == boost::posix_time::not_a_date_time) {
            endTime = boost::posix_time::second_clock::local_time();
        } else {
            if (arg_endTime > beginTime) {
                endTime = arg_endTime;
            } else {
                endTime = beginTime;
            }
        }
        finalRentCost = calculateFinalRentCost();
    }
}

unsigned int Rent::getRentDays() const {
    unsigned int days;
    boost::posix_time::time_period skew = boost::posix_time::time_period(beginTime, endTime);
    days = skew.length().hours() / 24;
    if (skew.length().hours() % 24 >= 1) {
        days++;
    }
    return days;
}

float Rent::calculateFinalRentCost() const {
    float cost = round(100 * getClient()->calculateClientDiscount(getRentDays() * (getRoom()->getRoomPrice()))) / 100;
    if (cost < 0) {
        throw LogicException("Nieprawidlowy koszt wypozyczenia!");
    }
    return cost;
}