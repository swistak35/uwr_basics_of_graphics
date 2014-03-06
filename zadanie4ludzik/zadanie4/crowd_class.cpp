#include <stdlib.h>
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "graphics_class.hpp"
#include "crowd_class.hpp"

using namespace glm;

#define PI      3.1415

Crowd::Crowd(GraphicsEngine *enginep) {
    engine = enginep;

    delay           = 0.8;
    walker_chances  = 80;
    runner_chances  = 20;
    angle           = 45;

    create_person(vec3(0.0f, 0.0f, 0.0f));
}

void Crowd::draw_people() {
    for(Person* person : people) {
        person->draw(engine->getMVP());
    }
}

void Crowd::apply_physics(double delta_time) {
    delayed_creating(delta_time);

    if (engine->is_view_changed()) {
        engine->observer = people.back();
    }

    for(Person* person : people) {
        person->apply_physics(delta_time);
    }
}

void Crowd::create_walker(float angle, vec3 init_position) {
    Person * newperson = new Person(engine);
    float tallness = (float) (rand() % 40) / 100;

    newperson->move_angle = angle;
    newperson->position = init_position;
    newperson->speed = vec3(4.0f * cos(2*PI*angle/360), 0.0f, 4.0f * sin(2*PI*angle/360));

    people.push_back(newperson);
    std::cout << "Walker created\n";
}

void Crowd::create_runner(float angle, vec3 init_position) {
    Person * newperson = new Person(engine);

    newperson->move_angle          = angle;
    newperson->position            = init_position;
    newperson->speed               = vec3(20.0f * cos(2*PI*angle/360), 0.0f, 20.0f * sin(2*PI*angle/360));
    newperson->arm_max_angle       = 45.0f;
    newperson->arm_speed           = 300.0f;
    newperson->forearm_max_angle   = 45.0f;
    newperson->forearm_speed       = 300.0f;
    newperson->leg_max_angle       = 80.0f;
    newperson->leg_speed           = 500.0f;
    newperson->forearm_angle_offset= 45.0f;

    people.push_back(newperson);
    std::cout << "Runner created\n";
}

void Crowd::create_person(vec3 init_position) {
    int rperson = rand() % 100;
    float rangle = (rand() % angle) - (angle / 2);

    if (0 <= rperson && rperson < walker_chances) {
        create_walker(rangle, init_position);
    } else if (walker_chances <= rperson && rperson < walker_chances + runner_chances) {
        create_runner(rangle, init_position);
    }

}

void Crowd::delayed_creating(double delta_time) {
    time_since_last_created += delta_time;

    if (time_since_last_created > delay) {
        create_person(vec3(0.0, 0.0, -8.0));
        create_person(vec3(0.0, 0.0,  0.0));
        create_person(vec3(0.0, 0.0,  8.0));
        time_since_last_created = 0.0;
    }
}


