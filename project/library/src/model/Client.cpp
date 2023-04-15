#include "model/Client.h"

#include "exceptions/ParameterException.h"

Client::Client(const std::string &firstName, const std::string &lastName, const std::string &personalID): firstName(firstName), secondName(lastName), clientID(personalID)
                                            {

    isArchive = false;
    clientType = std::make_shared<Default>();
    if (firstName.empty()) { throw ParameterException("Nieprawidłowe imie(nie moze byc puste)!"); }
    if (lastName.empty()) { throw ParameterException("Nieprawidłowe nazwisko(nie moze byc puste)!"); }
    if (personalID.empty()) { throw ParameterException("Nieprawidłowy pesel(nie moze byc puste)!"); }
}

Client::~Client() {

}

// getters
const std::string &Client::getFirstName() const {
    return firstName;
}

const std::string &Client::getSecondName() const {
    return secondName;
}

const std::string &Client::getClientID() const {
    return clientID;
}


const ClientTypePtr &Client::getClientType() const {
    return clientType;
}

// setters
void Client::setFirstName(const std::string &newFirstName) {
    if (!newFirstName.empty()) {
        firstName = newFirstName;
    }
}

void Client::setSecondName(const std::string &newSecondName) {
    if (!newSecondName.empty()) {
        secondName = newSecondName;
    }
}


void Client::setClientType(const ClientTypePtr &newClientType) {
    if (newClientType != nullptr) {
        clientType = newClientType;
    }
}

void Client::setIsArchive(bool status) {
    isArchive = true;
}

// other methods
std::string Client::getInfo() const {
    return "(Client) Imie: " + getFirstName() + ", nazwisko: " + getSecondName() + ", id: " +
            getClientID() + ", typ klienta: " + getClientType()->getInfo() + ", is archived: " +
           (chechIfArchived() ? "true" : "false");
}

bool Client::chechIfArchived() const {
    return isArchive;
}

float Client::calculateClientDiscount(float price) const {
    return clientType->discount(price);
}
