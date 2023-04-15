#ifndef HOTEL_ROOM_H
#define HOTEL_ROOM_H

#include <string>

class Room {
private:
    unsigned int roomPrice;
    const unsigned int roomNumber;
    const unsigned int roomCapacity;
    bool isArchive;

public:
    Room(int roomPrice, int roomNumber, int roomCapacity);

    virtual ~Room();

    // getters
    unsigned int getRoomPrice() const;

    unsigned int getRoomNumber() const;

    unsigned int getRoomCapacity() const;

    bool checkIfArchived() const;

    // setters
    void setRoomPrice(int basePrice);

    void setIsArchive(bool status);

    // other methods
    std::string getInfo() const;
};


#endif //HOTEL_ROOM_H
