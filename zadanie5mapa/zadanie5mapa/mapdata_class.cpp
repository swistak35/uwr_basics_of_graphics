#include <iostream>
#include <fstream>
#include <string>

#include "mapdata_class.hpp"

Mapdata::Mapdata(string fname, int tlng, int tlat) {
    ifstream file(fname.c_str(), std::ios::in | std::ios::binary);
    lng = tlng;
    lat = tlat;

    if(!file) {
        cout << "Error opening file " << fname << endl;
    } else {
        unsigned char buffer[2];
        for (int i = map_size-1; i >= 0; i--) {
            for (int j = 0; j < map_size; j++) {
                if(!file.read( reinterpret_cast<char*>(buffer), sizeof(buffer) )) {
                    cout << "Error reading file!" << endl;
                }
                heights[j][i] = (buffer[0] << 8) | buffer[1]; // zamieniamy bajty
            }
        }
    }
}
