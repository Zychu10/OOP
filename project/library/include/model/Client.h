#ifndef HOTEL_CLIENT_H
#define HOTEL_CLIENT_H

#include <string>
#include "model/ClientType.h"
#include "model/typedefs.h"

class Client {
private:
    std::string firstName;
    std::string secondName;
    const std::string clientID;
    bool isArchive;
    ClientTypePtr clientType;

public:
    Client(const std::string &firstName, const std::string &lastName, const std::string &personalID);

    virtual ~Client();

    // getters
    const std::string &getFirstName() const;

    const std::string &getSecondName() const;

    const std::string &getClientID() const;

    bool chechIfArchived() const;

    const ClientTypePtr &getClientType() const;

    void setIsArchive(bool status);

    // setters
    void setFirstName(const std::string &newFirstName);

    void setSecondName(const std::string &newSecondName);

    void setClientType(const ClientTypePtr &newClientType);

    // other methods
    std::string getInfo() const;

    float calculateClientDiscount(float price) const;


};


#endif //HOTEL_CLIENT_H
