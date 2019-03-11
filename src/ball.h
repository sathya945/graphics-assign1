#include "main.h"
#include "player.h"
#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball(float x, float y);
    glm::vec3 position;
    double radius;
    float rotation;
    void draw(glm::mat4 VP);
    double velocity;
    double xvel;
    double acc;
    void set_position(float x, float y);
private:
    VAO *object;
    VAO *bighalf;
    VAO *smallhalf;
};


class magent{
    public:
    double w;
    int time;
    glm::vec3 position;
    double h;
    magent(float x,float y);
    void draw(glm::mat4 VP);
    void update(Player *P);
    private:
    VAO *object;
    VAO *bighalf;
    VAO *smallhalf;
};

#endif // BALL_H
