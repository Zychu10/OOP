#include "managers/RoomManager.h"
#include "model/Repository.h"
#include "model/Room.h"
#include "exceptions/ParameterException.h"

RoomManager::RoomManager(const RoomRepositoryPtr &roomRepository) : roomRepository(roomRepository) {
    if (roomRepository == nullptr) { throw ParameterException("Nie mozna stworzyc roomManagera bez repozytorium!"); }

}

RoomManager::~RoomManager() {

}

// Tworzy objekt room i zwraca na niego wskaźnik. Jeśli room jest już stworzony zamienia jego pole isArchive na false
// (jeśli wcześniej było na true) i zwraca wskaźnik na ten obiekt
const RoomPtr RoomManager::registerRoom(int basePrice, int roomNumber, int roomCapacity) {
    RoomPtr roomCheck = getRoom(roomNumber);
    if (roomCheck == nullptr) {
        RoomPtr newRoom = std::make_shared<Room>(basePrice, roomNumber, roomCapacity);
        roomRepository->add(newRoom);
        return newRoom;
    } else {
        if (roomCheck->checkIfArchived()) {                // gdy pokój był zarchiwizowany dokonuje się dearchiwizacja
            roomCheck->setIsArchive(false);
        }
        return roomCheck;
    }
}

// ustawia pole isArchive objektu na true
void RoomManager::unregisterRoom(RoomPtr room) {
    if (room == nullptr) {
        throw ParameterException("Invalid room!");
    }
    room->setIsArchive(true);
}

// jeśli pokój nie zostanie znaleziony, zwrócony zostanie nullptr
const RoomPtr RoomManager::getRoom(int roomNumber) const {
    RoomPredicate predicate = [roomNumber](const RoomPtr ptr) {
        return ptr->getRoomNumber() == roomNumber;
    };
    return roomRepository->find(predicate);
}

// zwraca pierwszy dopasoany do parametrów wskaźnik na objekt pokoju
const RoomPtr RoomManager::getRoom(int price, int roomCapacity) const {
    RoomPredicate predicate = [price, roomCapacity](const RoomPtr ptr) {
        return (ptr->getRoomPrice() <= price && ptr->getRoomCapacity() == roomCapacity);
    };
    return roomRepository->find(predicate);
}

std::string RoomManager::getRoomsReport() const {
    return roomRepository->report();
}
