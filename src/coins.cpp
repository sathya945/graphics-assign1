#include "coins.h"
#include "main.h"
coins::coins()
{
    r1=0.6;
    GLfloat g_vertex_buffer_data[3600];
     float radians = 0;
        for(int i=0;i<9*360;i+=9){
           g_vertex_buffer_data[i] = r1*cos(radians);
           g_vertex_buffer_data[i+1] = r1*sin(radians);
           g_vertex_buffer_data[i+2] = 0.0f;
           g_vertex_buffer_data[i+3] = r1*cos(radians + (2*M_PI/360));
           g_vertex_buffer_data[i+4] = r1*sin(radians + (2*M_PI/360));
           g_vertex_buffer_data[i+5] = 0.0f;
           g_vertex_buffer_data[i+6] = 0.0f;
           g_vertex_buffer_data[i+7] = 0.0f;
           g_vertex_buffer_data[i+8] = 0.0f;
           radians = radians + (2*M_PI/360);
       }
    this->object2=create3DObject(GL_TRIANGLES,360*3,g_vertex_buffer_data,{192,192,192}, GL_FILL);
    this->object = create3DObject(GL_TRIANGLES,360*3,g_vertex_buffer_data,{255,215,0}, GL_FILL);
}
void coins::draw(glm::mat4 VP,double  x,double y){
    this->position=glm::vec3(x, y, 0);
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
   if(int(x+y)%2==0)draw3DObject(this->object);
    else draw3DObject(this->object2);
}
