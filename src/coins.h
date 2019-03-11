#include "main.h"
#ifndef  coins_H
#define coins_H

class coins{
public:
    coins();
    double r1;
    glm::vec3 position;
    void draw(glm::mat4 VP,double x,double y);
private:
    VAO *object;
    VAO *object2;
};
#endif 