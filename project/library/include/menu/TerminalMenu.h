#ifndef HOTEL_TERMINALMENU_H
#define HOTEL_TERMINALMENU_H

#include "model/typedefs.h"

class TerminalMenu {
private:
    ClientManagerPtr clientManager;
    RoomManagerPtr roomManager;
    RentManagerPtr rentManager;

public:

    TerminalMenu(const ClientManagerPtr &clientManager, const RoomManagerPtr &roomManager,
                 const RentManagerPtr &rentManager);

    virtual ~TerminalMenu();

    void start();

    void client();

    void room();

    void rent();
};


#endif //HOTEL_TERMINALMENU_H
