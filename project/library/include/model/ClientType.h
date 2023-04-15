#ifndef HOTEL_CLIENTTYPE_H
#define HOTEL_CLIENTTYPE_H

#include <string>

class ClientType {
public:
    virtual float discount(float price) const = 0;
    virtual std::string getInfo() const = 0;
};

class Default : public ClientType {
public:
    float discount(float price) const override;
    std::string getInfo() const override;
};

class Premium : public ClientType {
public:
    float discount(float price) const override;
    std::string getInfo() const override;
};

class Deluxe : public ClientType {
public:
    float discount(float price) const override;
    std::string getInfo() const override;

};


#endif //HOTEL_CLIENTTYPE_H