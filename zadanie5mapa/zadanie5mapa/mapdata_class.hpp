#ifndef MAPDATA_CLASS_HPP
#define MAPDATA_CLASS_HPP

#include <fstream>
#include "utils.hpp"

using namespace std;

class Mapdata {
public:
    int map_size = 1201;
    short heights[1201][1201] = { { 0 } };
    int lng;
    int lat;
    Mapdata(string fname, int lng, int lat);
};


#endif

