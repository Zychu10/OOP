#include "model/ClientType.h"


float Default::discount(float price) const {
    return price;
}

std::string Default::getInfo() const {
    return "default";
}

float Premium::discount(float price) const {
    return 0.85 * price;
}

std::string Premium::getInfo() const {
    return "premium";
}

float Deluxe::discount(float price) const {
    if (price <= 125) return 0.85 * price;
    else if (price <= 250) return 0.8 * price;
    else if (price <= 500) return 0.7 * price;
    else return 0.6 * price;
}

std::string Deluxe::getInfo() const {
    return "deluxe";
}
