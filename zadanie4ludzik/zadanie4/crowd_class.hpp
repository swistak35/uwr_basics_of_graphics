#ifndef CROWD_CLASS_HPP
#define CROWD_CLASS_HPP

#include <glm/glm.hpp>
#include "person_class.hpp"

using namespace glm;

class Crowd {
public:
    GraphicsEngine * engine;

    std::vector<Person *> people;
    GLfloat delay;
    int walker_chances;
    int runner_chances;
    int angle;
    double time_since_last_created;

    // API
    Crowd(GraphicsEngine * engine);
    void apply_physics(double delta_time);
    void draw_people();
    void create_walker(float angle, vec3 init_position);
    void create_runner(float angle, vec3 init_position);
    void create_person(vec3 init_position);
    void delayed_creating(double delta_time);
};

#endif
