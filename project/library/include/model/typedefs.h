#ifndef HOTEL_TYPEDEFS_H
#define HOTEL_TYPEDEFS_H

#include <memory>
#include <functional>

// model
class Client;
class Room;
class Rent;
class ClientType;
template<class T>
class Repository;

// client types
class Default;
class Premium;
class Deluxe;

// managers
class ClientManager;
class RoomManager;
class RentManager;

// model smart pointers
typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<Room> RoomPtr;
typedef std::shared_ptr<Rent> RentPtr;
typedef std::shared_ptr<ClientType> ClientTypePtr;

// repositories smart pointers
typedef std::shared_ptr<Repository<ClientPtr>> ClientRepositoryPtr;
typedef std::shared_ptr<Repository<RoomPtr>> RoomRepositoryPtr;
typedef std::shared_ptr<Repository<RentPtr>> RentRepositoryPtr;

// predicates
typedef std::function<bool(ClientPtr)> ClientPredicate;
typedef std::function<bool(RoomPtr)> RoomPredicate;
typedef std::function<bool(RentPtr)> RentPredicate;

// managars smart pointers
typedef std::shared_ptr<ClientManager> ClientManagerPtr;
typedef std::shared_ptr<RoomManager> RoomManagerPtr;
typedef std::shared_ptr<RentManager> RentManagerPtr;


#endif //HOTEL_TYPEDEFS_H
