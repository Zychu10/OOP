#ifndef HOTEL_CLIENTMANAGER_H
#define HOTEL_CLIENTMANAGER_H

#include "model/typedefs.h"
#include <string>

class ClientManager {
private:
    ClientRepositoryPtr clientRepository;

public:
    ClientManager(const ClientRepositoryPtr &clientRepository);

    virtual ~ClientManager();

    // Tworzy objekt client i zwraca na niego wskaźnik. Jeśli client jest już stworzony zamienia jego pole isArchive na false
    // (jeśli wcześniej było na true) i zwraca wskaźnik ten obiekt
    ClientPtr
    registerClient(const std::string &firstName, const std::string &lastName, const std::string &personalID);

    // ustawia pole isArchive objektu na true
    void unregisterClient(const ClientPtr &client);

    // metoda zwraca nullptr jeśli klient nie istnieje
    const ClientPtr getClient(const std::string &personalID) const;

    // zwraca informacje o wszystkich objektach w repozytorium
    std::string getClientsReport() const;
};


#endif //HOTEL_CLIENTMANAGER_H
