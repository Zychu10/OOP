#include "model/Room.h"
#include "exceptions/ParameterException.h"

Room::Room(int roomPrice, int roomNumber, int roomCapacity) : roomPrice(roomPrice),
                                                              roomNumber(roomNumber),
                                                              roomCapacity(roomCapacity) {

    isArchive = false;

    if (roomPrice <= 0) { throw ParameterException("Nieprawidlowa cena pokoju!"); }
    if (roomNumber <= 0) { throw ParameterException("Nieprawidlowy numer pokoju!"); }
    if (roomCapacity <= 0) { throw ParameterException("Nieprawidlowa pojemnosc pokoju!"); }
}

Room::~Room() {

}

// getters
unsigned int Room::getRoomPrice() const {
    return roomPrice;
}

unsigned int Room::getRoomNumber() const {
    return roomNumber;
}

unsigned int Room::getRoomCapacity() const {
    return roomCapacity;
}

bool Room::checkIfArchived() const {
    return isArchive;
}

// setters
void Room::setRoomPrice(int newBasePrice) {
    if (newBasePrice >= 0) {
        roomPrice = newBasePrice;
    }
}

void Room::setIsArchive(bool status) {
    isArchive = true;
}

// other methods
std::string Room::getInfo() const {
    return "(Room) cena: " + std::to_string(getRoomPrice()) + ", numer: " +
           std::to_string(getRoomNumber()) +
           ", pojemnosc: " + std::to_string(getRoomCapacity()) + ", is archived: " +
           (checkIfArchived() ? "true" : "false");
}
