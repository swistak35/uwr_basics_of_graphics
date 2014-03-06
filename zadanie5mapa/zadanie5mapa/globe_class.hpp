#ifndef GLOBE_CLASS_HPP
#define GLOBE_CLASS_HPP

#include <iostream>
#include <fstream>
#include <vector>

#include "utils.hpp"
#include "graphics_class.hpp"
#include "observer_class.hpp"

#define RADIUS 1.0
#define DEGREES 0.0008333333333333334


using namespace std;

class Globe {
public:
    string fname;
    int map_size = 1201;
    vector<vec2> maps;
    GraphicsEngine * engine;
    Observer * observer;
    vec2 middle;
    int vsize;

    Globe(string fname, GraphicsEngine * engine, Observer * observer);
private:
    void load_data();
    void load_mapdata(string mapname, int lat, int lng);
    vec3 calculate_center();
};


#endif


