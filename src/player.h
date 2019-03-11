#include "main.h"

#ifndef  Player_H
#define Player_H

class  Player{
public:
    glm::vec3 position;
    Player(double x,double y);
    float velocity;
    void   set_position(double x,double y);
    void draw(glm::mat4 VP);
    void draw_pack(glm::mat4 VP);
    void updatestate();
private:
    VAO *head;
    VAO *body;
    VAO *eye;
    VAO *lips;
    VAO *legs;
    VAO *pack;
};

class firebeam{
public:
    double y;
    int time;
    int time2;
    firebeam(double height);
    void draw(glm::mat4 VP,double x);
private:
    VAO *body;
    VAO *brick;
};

#endif 