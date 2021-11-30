#include "global.hpp"
#include "PlaceClass.hpp"

place::place(bool ifp, bool ih, string n, string co, int p, string o, bool h, int hotcos, int ren, int hotrent, int hourent){
    ifplace = ifp;
    hotel = ih;
    name = n;
    color = co;
    price = p;
    owner = o;
    house = h;
    hotelprice = hotcos;
    rent = ren;
    hotelrent = hotrent;
    houserent = hourent;
};
