#ifndef HOTEL_RENT_H
#define HOTEL_RENT_H

#include <boost/uuid/uuid.hpp>
#include <boost/date_time.hpp>
#include "model/typedefs.h"

class Rent {
private:
    const boost::uuids::uuid id;
    const ClientPtr client;
    const RoomPtr room;
    boost::posix_time::ptime beginTime;

    boost::posix_time::ptime endTime;
    float finalRentCost;

public:
    Rent(const boost::uuids::uuid &id, const ClientPtr &client, const RoomPtr &room,
         const boost::posix_time::ptime &beginTime = boost::posix_time::not_a_date_time);

    virtual ~Rent();

    // getters
    const boost::uuids::uuid &getID() const;

    const ClientPtr &getClient() const;

    const RoomPtr &getRoom() const;

    const boost::posix_time::ptime &getBeginTime() const;

    const boost::posix_time::ptime &getEndTime() const;

    float getFinalRentCost() const;

    // other methods
    std::string getInfo() const;

    // Zakańcza wypożyczenie i oblicza finalną jego kwotę
    void endRent(const boost::posix_time::ptime &arg_endTime);

    unsigned int getRentDays() const;               // Każdy dzień nalicza się przy wybiciu pierwszej godziny

    float calculateFinalRentCost() const;           // oblicza kosz wynajęcia uzwględniając wszystkie modyfikatory ceny
                                                    // wynik podany jest z z maksymalnie dwoma miejscami po przecinku
};


#endif //HOTEL_RENT_H
