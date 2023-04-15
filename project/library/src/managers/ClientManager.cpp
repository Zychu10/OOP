#include "managers/ClientManager.h"
#include "model/Repository.h"
#include "model/Client.h"
#include "exceptions/ParameterException.h"

ClientManager::ClientManager(const ClientRepositoryPtr &clientRepository) : clientRepository(clientRepository) {
    if (clientRepository == nullptr) { throw ParameterException("Nie mozesz stworzyc clientManagera bez repozytorium"); }
}

ClientManager::~ClientManager() {

}

// Tworzy objekt client i zwraca na niego wskaźnik
ClientPtr ClientManager::registerClient(const std::string &firstName, const std::string &lastName,
                                              const std::string &personalID) {
    ClientPtr clientCheck = getClient(personalID);
    if (clientCheck == nullptr) {
        ClientPtr newClient = std::make_shared<Client>(firstName, lastName, personalID);
        clientRepository->add(newClient);
        return newClient;
    } else {
        clientCheck->setIsArchive(false);      // gdy klient był zarchiwizowany dokonuje się dearchiwizacja
        clientCheck->setFirstName(firstName);            // ustawione zostają nowe dane klienta
        clientCheck->setSecondName(lastName);
        return clientCheck;
    }
}

// ustawia pole isArchive objektu na true
void ClientManager::unregisterClient(const ClientPtr &client) {
    if (client == nullptr) {
        throw ParameterException("Nieprawidlowy ClientPtr!");
    }
    client->setIsArchive(true);
}

// metoda zwraca nullptr jeśli klient nie istnieje
const ClientPtr ClientManager::getClient(const std::string &personalID) const {
    ClientPredicate predicate = [personalID](const ClientPtr ptr) {
        return ptr->getClientID() == personalID;
    };
    return clientRepository->find(predicate);
}

std::string ClientManager::getClientsReport() const {
    return clientRepository->report();
}
