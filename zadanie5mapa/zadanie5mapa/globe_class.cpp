#include <iostream>
#include <fstream>
#include <string>

#include "globe_class.hpp"

Globe::Globe(string fname, GraphicsEngine * engine, Observer * observer) {
    this->fname = fname;
    this->engine = engine;
    this->observer = observer;
    load_data();
}

void Globe::load_data() {
    ifstream infile(fname.c_str());

    string line, mapname;
    int tlat, tlng, pos;

    while (getline(infile, line)) {
        if (GLOBE_CLASS_DEBUG) cout << "line: " << line;

        pos = line.find_last_of('/');
        if (pos == -1) pos = 0;
        if (GLOBE_CLASS_DEBUG) cout << " pos: " << pos;

        mapname = line.substr(pos+1);
        if (GLOBE_CLASS_DEBUG) cout << " mapname: " << mapname << endl;

        tlat = stoi(mapname.substr(1, 2));
        tlng = stoi(mapname.substr(4, 3));
        if (GLOBE_CLASS_DEBUG) cout << "tlat: " << tlat << " tlng: " << tlng << endl;

        if (mapname[0] == 'n' || mapname[0] == 'N') {
            tlat += 90;
        } else {
            tlat = 90 - tlat;
        }
        if (mapname[3] == 'w' || mapname[3] == 'W') {
            tlng = 360 - tlng;
        } else {
            // tlng ok
        }

        load_mapdata(line, tlat, tlng);
        maps.push_back(vec2(tlat, tlng));
    }

    engine->update_lod(4);
    vec3 new_position = calculate_center();
    // W trybie 3d chcemy byc skierowani wzrokiem do srodka globu
    if (engine->current_mode == 3) {
        observer->direction = - new_position;
    }
    cout << "Starting position: | " << new_position.x << " | " << new_position.y << " | " << new_position.z << " |\n";
    observer->position = new_position;
    if (engine->current_mode == 2) {
        for (int i = vsize; i < engine->vertices.size(); i++) {
            engine->vertices.at(i).a *= cos(abs(middle.y - 90));
        }
    }
    engine->send_buffers();
    engine->vertices.clear();
}

void Globe::load_mapdata(string mapname, int lat, int lng) {
    if (DEBUG) cout << "Loading map " << mapname << endl;
    ifstream file(mapname.c_str(), std::ios::in | std::ios::binary);
    short heights[map_size][map_size];

    if(!file) {
        cout << "Error opening file: " << mapname << endl;
    } else {
        unsigned char buffer[2];
        for (int i = map_size-1; i >= 0; i--) {
            for (int j = 0; j < map_size; j++) {
                if(!file.read( reinterpret_cast<char*>(buffer), sizeof(buffer) )) {
                    cout << "Error reading file: " << mapname << endl;
                }
                heights[j][i] = (buffer[0] << 8) | buffer[1]; // zamieniamy bajty
            }
        }
    }

    // ponizsze ladowanie mozna przeniesc wyzej
    GLfloat tmpa, tmpb;
    GLfloat tmph;
    GLfloat tlat, tlng;
    vsize = engine->vertices.size();

    for (int j = 0; j < map_size; j++) {
        for (int i = 0; i < map_size; i++) {
            if (engine->current_mode == 3) {
                tmpa = lat + j * DEGREES;
                tmpb = lng + i * DEGREES;
                tmph = GLfloat (heights[i][j]);
            } else {
                tmpa = lng * 1200 + i;
                tmpb = lat * 1200 + j;
//                tmpa = lng * ANGLES;
//                tmpb = log(tan((lat * ANGLES) / 2));

                tmph = GLfloat (heights[i][j]);
                if (i % 1201 == 0 && j % 1201 == 0) cout << "V(" << tmpa << ", " << tmpb << ", " << tmph << ") [" << lng << ", " << lat << "]\n";
            }

            engine->vertices.push_back({
                tmpa, tmpb, tmph
            });
        }
    }

    // tworzenie trójkątów
    for (int l = 0; l < LODS; l++) {
        int inc;
        if (STRICTER_LOD) {
            inc = pow(2.0,float(l));
        } else {
            int inc = l+1;
        }

        int last = ((map_size - inc) / inc) * inc;

        for (int i = 0; i < map_size-inc; i += inc) {
            for (int j = 0; j < map_size-inc; j += inc) {
//                engine->indices_points[l].push_back(engine->vertices.size() - 1);
                engine->indices_triangles[l].push_back(vsize + i * map_size + j);
                engine->indices_triangles[l].push_back(vsize + i * map_size + j + inc);
                engine->indices_triangles[l].push_back(vsize + (i+inc) * map_size + j);

                engine->indices_triangles[l].push_back(vsize + i * map_size + j + inc);
                engine->indices_triangles[l].push_back(vsize + (i+inc) * map_size + j);
                engine->indices_triangles[l].push_back(vsize + (i+inc) * map_size + j + inc);
            }

            // jesli to nie jest ostatnie i
            if (i + inc < map_size - inc) {
                engine->indices_triangles[l].push_back(vsize + i * map_size + last);
                engine->indices_triangles[l].push_back(vsize + i * map_size + 1200);
                engine->indices_triangles[l].push_back(vsize + (i+inc) * map_size + last);

                engine->indices_triangles[l].push_back(vsize + i * map_size + 1200);
                engine->indices_triangles[l].push_back(vsize + (i+inc) * map_size + last);
                engine->indices_triangles[l].push_back(vsize + (i+inc) * map_size + 1200);
            }
        }

        for (int j = 0; j < map_size-inc; j += inc) {
            engine->indices_triangles[l].push_back(vsize + last * map_size + j);
            engine->indices_triangles[l].push_back(vsize + last * map_size + j + inc);
            engine->indices_triangles[l].push_back(vsize + 1200 * map_size + j);

            engine->indices_triangles[l].push_back(vsize + last * map_size + j + inc);
            engine->indices_triangles[l].push_back(vsize + 1200 * map_size + j);
            engine->indices_triangles[l].push_back(vsize + 1200 * map_size + j + inc);
        }

        engine->indices_triangles[l].push_back(vsize + last * map_size + last);
        engine->indices_triangles[l].push_back(vsize + last * map_size + 1200);
        engine->indices_triangles[l].push_back(vsize + 1200 * map_size + last);

        engine->indices_triangles[l].push_back(vsize + last * map_size + 1200);
        engine->indices_triangles[l].push_back(vsize + 1200 * map_size + last);
        engine->indices_triangles[l].push_back(vsize + 1200 * map_size + 1200);
    }
}

vec3 Globe::calculate_center() {
    int left = 360, right = 0, top = 0, bottom = 180;

    for (int i = 0; i < maps.size(); i++) {
        vec2 current = maps.at(i);
        if (current.y + 1 > right) {
            right = current.y + 1;
        }
        if (current.y < left) {
            left = current.y;
        }
        if (current.x > top) {
            top = current.x;
        }
        if (current.x + 1< bottom) {
            bottom = current.x + 1;
        }
    }

    middle = vec2(float(left + right) / 2, float(top + bottom) / 2);
    cout << "Middle: " << middle.x << " | " << middle.y << "\n";

    if (engine->current_mode == 3) {
        GLfloat x,y,z;
        x = 11.0 * sin(middle.y * ANGLES) * cos(middle.x * ANGLES);
        y = 11.0 * sin(middle.y * ANGLES) * sin(middle.x * ANGLES);
        z = 11.0 * cos(middle.y * ANGLES);
        return vec3(x,y,z);
    } else {
//        return vec3(middle.x * ANGLES * 100, log(tan((middle.y * ANGLES) / 2)) * 100, 2.0);
        return vec3(middle.x * 1.2 * cos(abs(middle.y - 90)), middle.y * 1.2, 2.0);
    }

}
