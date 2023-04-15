#include "menu/TerminalMenu.h"

#include <iostream>

#include "exceptions/ParameterException.h"
#include "exceptions/LogicException.h"

#include "managers/ClientManager.h"
#include "managers/RoomManager.h"
#include "managers/RentManager.h"

#include "model/Client.h"
#include "model/Room.h"
#include "model/Rent.h"

using namespace std;

TerminalMenu::TerminalMenu(const ClientManagerPtr &clientManager, const RoomManagerPtr &roomManager,
                           const RentManagerPtr &rentManager) : clientManager(clientManager), roomManager(roomManager),
                                                                rentManager(rentManager) {}

TerminalMenu::~TerminalMenu() {

}

void TerminalMenu::start() {
    cout << "Witaj w hotelu!" << endl;

    bool exit = false;
    while (!exit) {
        cout
                << "**********************************" << endl
                << "1. Zarzadzaj klientami" << endl
                << "2. Zarzadzaj pokojami" << endl
                << "3. Zarzadzaj wynajmem" << endl
                << "0. Zakoncz program" << endl
                << "**********************************" << endl;

        char input;
        cin >> input;

        switch (input) {
            // 1. Zarzadzaj klientami
            case '1':
                client();
                break;

                // 2. Zarzadzaj pokojami
            case '2':
                room();
                break;

                // 3. Zarzadzaj wynajmem
            case '3':
                rent();
                break;

                // 0. Zakoncz program
            case '0':
                exit = true;
                break;

            default:
                cout << "Bledny wybor!" << endl;
                break;
        }
    }
}

void TerminalMenu::client() {
    bool exit = false;
    while (!exit) {
        cout
                << "**********************************" << endl
                << "1. Zarejestruj nowego klienta" << endl
                << "2. Wyswietl informacje o kliencie" << endl
                << "3. Wyswietl informacje o wszystkich klientach" << endl
                << "4. Wyrejestruj klienta" << endl
                << "0. Powrot do menu" << endl
                << "**********************************" << endl;

        char input;
        cin >> input;

        switch (input) {
            // 1. Zarejestruj nowego klienta
            case '1': {
                string firstName, lastName, personalID;
                cout << "Podaj imie: ";
                cin.ignore();
                getline(cin, firstName);
                cout << "Podaj nazwisko: ";
                getline(cin, lastName);
                cout << "Podaj numer pesel: ";
                cin >> personalID;


                try {
                    clientManager->registerClient(firstName, lastName, personalID);
                } catch (ParameterException &e) {
                    cerr << "Parameter error: " << e.what() << endl;
                } catch (LogicException &e) {
                    cerr << "Logic error: " << e.what() << endl;
                }
                break;
            }

                // 2. Wyswietl informacje o kliencie
            case '2': {
                string personalID;
                cout << "Podaj numer pesel klienta: ";
                cin >> personalID;

                ClientPtr client = clientManager->getClient(personalID);
                if (client == nullptr) {
                    cout << "Podany klient nie istnieje!" << endl;
                    break;
                }

                cout << client->getInfo() << endl;
                break;
            }

                // 3. Wyswietl informacje o wszystkich klientach
            case '3':
                cout << clientManager->getClientsReport() << endl;
                break;

                // 4. Wyrejestruj klienta
            case '4': {
                string personalID;
                cout << "Podaj numer pesel klienta: ";
                cin >> personalID;

                try {
                    ClientPtr client = clientManager->getClient(personalID);
                    if (client == nullptr) {
                        cout << "Klient o podanym peselu nie istnieje!" << endl;
                        break;
                    }
                    clientManager->unregisterClient(client);
                } catch (ParameterException &e) {
                    cerr << "Parameter error: " << e.what() << endl;
                } catch (LogicException &e) {
                    cerr << "Logic error: " << e.what() << endl;
                }
                break;
            }

                // 0. Powrot do menu
            case '0':
                exit = true;
                break;

            default:
                cout << "Bledny wybor!" << endl;
                break;
        }
    }
}

void TerminalMenu::room() {
    bool exit = false;
    while (!exit) {
        cout << "**********************************" << endl
             << "1. Zarejestruj nowy pokoj" << endl
             << "2. Wyswietl informacje o pokoju" << endl
             << "3. Wyswietl informacje o wszystkich pokojach" << endl
             << "4. Wyrejestruj pokoj" << endl
             << "0. Powrot do menu" << endl
             << "**********************************" << endl;

        char input;
        cin >> input;

        switch (input) {
            // 1. Zarejestruj nowy pokoj
            case '1': {
                int basePrice, roomNumber, roomCapacity;
                cout << "Podaj cene: ";
                cin >> basePrice;
                cout << "Podaj numer pokoju: ";
                cin >> roomNumber;
                cout << "Podaj pojemnosc pokoju: ";
                cin >> roomCapacity;

                try {
                    roomManager->registerRoom(basePrice, roomNumber, roomCapacity);
                } catch (ParameterException &e) {
                    cerr << "Parameter error: " << e.what() << endl;
                } catch (LogicException &e) {
                    cerr << "Logic error: " << e.what() << endl;
                }
                break;
            }

                // 2. Wyswietl informacje o pokoju
            case '2': {
                int number;
                cout << "Podaj numer pokoju: ";
                cin >> number;

                RoomPtr room = roomManager->getRoom(number);
                if (room == nullptr) {
                    cout << "Pokoj o podanym numerze nie istnieje!" << endl;
                    return;
                }

                cout << room->getInfo() << endl;
                break;
            }

                // 3. Wyswietl informacje o wszystkich pokojach
            case '3':
                cout << roomManager->getRoomsReport() << endl;
                break;

                // 4. Wyrejestruj pokoj
            case '4': {
                int roomNumber;
                cout << "Podaj numer pokoju: ";
                cin >> roomNumber;

                try {
                    roomManager->unregisterRoom(roomManager->getRoom(roomNumber));
                } catch (ParameterException &e) {
                    cerr << "Parameter error: " << e.what() << endl;
                } catch (LogicException &e) {
                    cerr << "Logic error: " << e.what() << endl;
                }
                break;
            }
                // 0. Powrot do menu
            case '0':
                exit = true;
                break;

            default:
                cout << "Bledny wybor!" << endl;
                break;
        }
    }
}

void TerminalMenu::rent() {
    bool exit = false;
    while (!exit) {
        cout << "**********************************" << endl
             << "1. Wynajmij pokoj" << endl
             << "2. Wyswietl informacje o wynajmnie" << endl
             << "3. Wyswietl informacje o wszystkich obecnych wypozyczeniach" << endl
             << "4. Wyswietl informacje o wszystkich archiwalnych wypozyczeniach" << endl
             << "5. Zakoncz wynajem" << endl
             << "0. Powrot do menu" << endl
             << "**********************************"<< endl;

        char input;
        cin >> input;

        switch (input) {
            // 1. Wynajmij pokoj
            case '1': {
                string personalID;
                int basePrice, roomCapacity;
                cout << "Podaj numer pesel klienta: ";
                cin >> personalID;

                ClientPtr client = clientManager->getClient(personalID);
                if (client == nullptr) {
                    cout << "Klient nie istnieje!" << endl;
                    return;
                }

                cout << "Podaj maksymalna cene za pokoj: ";
                cin >> basePrice;
                cout << "Podaj rozmiar pokoju: ";
                cin >> roomCapacity;

                RoomPtr room = roomManager->getRoom(basePrice, roomCapacity);
                if (room == nullptr) {
                    cout << "Nie znaleziono odpowiedniego pokoju!" << endl;
                    return;
                }

                try {
                    rentManager->rentRoom(client, room);
                } catch (ParameterException &e) {
                    cerr << "Parameter error: " << e.what() << endl;
                } catch (LogicException &e) {
                    cerr << "Logic error: " << e.what() << endl;
                }
                break;
            }

                // 2. Wyswietl informacje o wynajmnie
            case '2': {
                int roomNumber;
                cout << "Podaj numer pesel klienta: ";
                cin >> roomNumber;

                RentPtr rent = rentManager->getRent(roomManager->getRoom(roomNumber));
                if (rent == nullptr) {
                    cout << "Nie znaleziono wynajmu" << endl;
                    return;
                }

                cout << rent->getInfo() << endl;
                break;
            }
                // 3. Wyswietl informacje o wszystkich obecnych wypozyczeniach
            case '3':
                cout << rentManager->getCurrentRentsReport() << endl;
                break;

                // 4. Wyswietl informacje o wszystkich archiwalnych wypozyczeniach
            case '4':
                cout << rentManager->getArchiveRentsReport() << endl;
                break;

                // 5. Zakoncz wynajem
            case '5': {
                int number;
                cout << "Podaj numer pokoju: ";
                cin >> number;

                try {
                    rentManager->returnRoom(roomManager->getRoom(number));
                } catch (ParameterException &e) {
                    cerr << "Parameter error: " << e.what() << endl;
                } catch (LogicException &e) {
                    cerr << "Logic error: " << e.what() << endl;
                }
                break;
            }

                // 0. Powrot do menu
            case '0':
                exit = true;
                break;

            default:
                cout << "Bledny wybor!" << endl;
                break;
        }
    }
}
