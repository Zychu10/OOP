#include "managers/RentManager.h"
#include "model/Repository.h"
#include "model/Rent.h"
#include "model/Client.h"
#include <boost/uuid/uuid_generators.hpp>
#include <vector>
#include "exceptions/ParameterException.h"
#include "exceptions/LogicException.h"

RentManager::RentManager(const RentRepositoryPtr &currentRents, const RentRepositoryPtr &archiveRents) : currentRents(
        currentRents), archiveRents(archiveRents) {
    if (currentRents == nullptr) { throw ParameterException("Nie mozesz stworzyc rentManagera bez repozytorium!"); }
    if (archiveRents == nullptr) { throw ParameterException("Nie mozesz stworzyc rentManagera bez repozytorium!"); }
}

RentManager::~RentManager() {

}

// zmiana typu klienta na podawie ile wydał pieniędzy za najem pokoji. (Zliczane są tylko zakończone wypożyczenia)
void RentManager::changeClientType(const ClientPtr &client) const {
    float totalAmount = 0;
    RentPredicate predicate = [client](const RentPtr& ptr) {
        return ptr->getClient() == client;
    };
    // znajdz wszystkie archiwalne wypożyczenia klienta
    std::vector<RentPtr> clientArchiveRents = archiveRents->findAll(predicate);
    for (int i = 0; i < clientArchiveRents.size(); i++) {
        totalAmount += clientArchiveRents[i]->getFinalRentCost();
    }
    if (totalAmount < 500) {
    } else if (totalAmount < 1000) {
        client->setClientType(std::make_shared<Premium>());
    } else {
        client->setClientType(std::make_shared<Deluxe>());
    }
}

// Tworzy objekt rent i zwraca na niego wskaźnik. Jeśli pokój jest już przypisany do wypożecznia zwraca nullptr


RentPtr RentManager::rentRoom(const ClientPtr &client, const RoomPtr &room, const boost::posix_time::ptime &beginTime) {
    if (getRent(room) == nullptr) {
        boost::uuids::random_generator gen;
        RentPtr newRent = std::make_shared<Rent>(gen(), client, room, beginTime);
        currentRents->add(newRent);
        return newRent;
    } else {
        throw LogicException("Pokoj jest wynajety!");

    }
}

// Przenosi objekt room z repozytorium currentRents do archiveRents
void RentManager::returnRoom(const RoomPtr& room) const {
    RentPtr rent = getRent(room);
    if (rent != nullptr) {
        rent->endRent(boost::posix_time::second_clock::local_time());
        archiveRents->add(rent);
        currentRents->remove(rent);
        changeClientType(rent->getClient());
    }
}

// Jeśli wypożyczenie nie zostanie znalezione zwraca nullptr
RentPtr RentManager::getRent(const RoomPtr& room) const {
    RentPredicate predicate = [room](const RentPtr& ptr) {
        return ptr->getRoom() == room;
    };
    return currentRents->find(predicate);
}

std::string RentManager::getCurrentRentsReport() const {
    return currentRents->report();
}

std::string RentManager::getArchiveRentsReport() const {
    return archiveRents->report();
}
