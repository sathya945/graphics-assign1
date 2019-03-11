#include "main.h"

#ifndef  PLATFORM_H
#define PLATFORM_H

class  Platform{
public:
    Platform();
    void draw(glm::mat4 VP);
private:
    VAO *object;
};
class Enemy{
public:    
    Enemy(double x,double y,double r,double start_angle,double rotate);
    double radius;
    double width;
    double length;
    double rot;
    double rotation;
    void draw(glm::mat4 VP);
    void change(double x,double y,double theta);
    glm::vec3 position;
private:
    VAO *object;
    VAO *end;
};
class Ballon{
    public:
        Ballon(float x,float y);
        glm::vec3 position;
        float radius;
        float xvel;
        float yvel;
        float acc;
        void draw(glm::mat4 VP);
        void update();
    private:
        VAO *object;
};
class Boomrang{
    public:
        Boomrang(float x,float y);
        glm::vec3 position;
        float xvel;
        float yvel;
        float acc;
        float rotation;
        void draw(glm::mat4 VP);
        void update();
    private:
        VAO *smallhalf;
        VAO *bighalf;
};
class Powerup{
    public:
        Powerup(float x,float y);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        float velocity;
        float acc;
        float xvel;
        float l;
        float rotate;
        float b;
    private:
        VAO *object;

};
#endif 