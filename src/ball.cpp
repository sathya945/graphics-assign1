#include "ball.h"
#include "main.h"
#include "player.h"

Ball::Ball(float x, float y) {
    radius=0.9;
    velocity=0.4;
    acc=0.005;
    xvel=0.2;
    position = glm::vec3(x, y, 0);
     float radians = 0;
     float r1=1;    
     rotation=0;
    GLfloat g_vertex_buffer_data[3600];
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
    radians = M_PI/2;
    r1=0.5;
    GLfloat g_vertex_buffer_data2[3600];
        for(int i=0;i<9*180;i+=9){
           g_vertex_buffer_data2[i] = r1*cos(radians);
           g_vertex_buffer_data2[i+1] = r1*sin(radians);
           g_vertex_buffer_data2[i+2] = 0.0f;
           g_vertex_buffer_data2[i+3] = r1*cos(radians + (2*M_PI/360));
           g_vertex_buffer_data2[i+4] = r1*sin(radians + (2*M_PI/360));
           g_vertex_buffer_data2[i+5] = 0.0f;
           g_vertex_buffer_data2[i+6] = 0.0f;
           g_vertex_buffer_data2[i+7] = 0.0f;
           g_vertex_buffer_data2[i+8] = 0.0f;
           radians = radians + (2*M_PI/360);
       }
         radians = M_PI/2;
         r1=0.2;
         GLfloat g_vertex_buffer_data3[3600];
        for(int i=0;i<9*180;i+=9){
           g_vertex_buffer_data3[i] = r1*cos(radians);
           g_vertex_buffer_data3[i+1] = r1*sin(radians);
           g_vertex_buffer_data3[i+2] = 0.0f;
           g_vertex_buffer_data3[i+3] = r1*cos(radians + (2*M_PI/360));
           g_vertex_buffer_data3[i+4] = r1*sin(radians + (2*M_PI/360));
           g_vertex_buffer_data3[i+5] = 0.0f;
           g_vertex_buffer_data3[i+6] = 0.0f;
           g_vertex_buffer_data3[i+7] = 0.0f;
           g_vertex_buffer_data3[i+8] = 0.0f;
           radians = radians + (2*M_PI/360);
       }
 //   this->object=create3DObject(GL_TRIANGLES, 360*3, g_vertex_buffer_data,{173,255,47}, GL_FILL);
    this->smallhalf=create3DObject(GL_TRIANGLES, 180*3, g_vertex_buffer_data3,{242, 241, 239}, GL_FILL);

    this->bighalf=create3DObject(GL_TRIANGLES, 180*3, g_vertex_buffer_data2,{255,223,0}, GL_FILL);
}
void Ball::draw(glm::mat4 VP){
            rotation+=3;
            Matrices.model = glm::mat4(1.0f);
            glm::mat4 translate = glm::translate (this->position);
            Matrices.model *= (translate);
             Matrices.model *=glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
            glm::mat4 MVP = VP * Matrices.model;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);    
             translate = glm::translate(glm::vec3(0,0.4,0));
            Matrices.model *= (translate);
            MVP = VP * Matrices.model;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
            draw3DObject(this->bighalf);
            draw3DObject(this->smallhalf);
            translate = glm::translate(glm::vec3(0,-0.7,0));
            Matrices.model *= (translate);
            Matrices.model *=(glm::rotate((float) (  M_PI ), glm::vec3(0, 0, 1  )));
            MVP = VP * Matrices.model;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
            draw3DObject(this->bighalf);
          draw3DObject(this->smallhalf);
}
magent::magent(float x ,float  y){
    position = glm::vec3(x,y,0);
    w=1;
    h=2;
     static const GLfloat data[]={
         0,0,0,
         w,0,0,
         0,h,0,
         0,h,0,
         w,0,0,
         w,h,0
     };
     float radians = M_PI;
    float r1=w;
    GLfloat g_vertex_buffer_data2[3600];
        for(int i=0;i<9*180;i+=9){
           g_vertex_buffer_data2[i] = r1*cos(radians);
           g_vertex_buffer_data2[i+1] = r1*sin(radians);
           g_vertex_buffer_data2[i+2] = 0.0f;
           g_vertex_buffer_data2[i+3] = r1*cos(radians + (2*M_PI/360));
           g_vertex_buffer_data2[i+4] = r1*sin(radians + (2*M_PI/360));
           g_vertex_buffer_data2[i+5] = 0.0f;
           g_vertex_buffer_data2[i+6] = 0.0f;
           g_vertex_buffer_data2[i+7] = 0.0f;
           g_vertex_buffer_data2[i+8] = 0.0f;
           radians = radians + (2*M_PI/360);
       }
    radians=M_PI;
    time=800;
    r1=2*w;
       GLfloat g_vertex_buffer_data3[3600];
        for(int i=0;i<9*180;i+=9){
           g_vertex_buffer_data3[i] = r1*cos(radians);
           g_vertex_buffer_data3[i+1] = r1*sin(radians);
           g_vertex_buffer_data3[i+2] = 0.0f;
           g_vertex_buffer_data3[i+3] = r1*cos(radians + (2*M_PI/360));
           g_vertex_buffer_data3[i+4] = r1*sin(radians + (2*M_PI/360));
           g_vertex_buffer_data3[i+5] = 0.0f;
           g_vertex_buffer_data3[i+6] = 0.0f;
           g_vertex_buffer_data3[i+7] = 0.0f;
           g_vertex_buffer_data3[i+8] = 0.0f;
           radians = radians + (2*M_PI/360);
       }
    this->object=create3DObject(GL_TRIANGLES,6,data,{105,105,105}, GL_FILL);
    this->smallhalf=create3DObject(GL_TRIANGLES, 180*3, g_vertex_buffer_data2,{242, 241, 239}, GL_FILL);
    this->bighalf=create3DObject(GL_TRIANGLES, 180*3, g_vertex_buffer_data3,{178,34,34}, GL_FILL);

}
void magent::draw(glm::mat4 VP){
    time--;
      Matrices.model = glm::mat4(1.0f);
      glm::mat4 translate = glm::translate(this->position);
      Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->bighalf);
    draw3DObject(this->smallhalf);
  translate = glm::translate(glm::vec3(w,0,0));
    Matrices.model *= (translate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    translate = glm::translate(glm::vec3(-3*w,0,0));
    Matrices.model *= (translate);
   MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->object);

}
void magent::update(Player *P){
double x=P->position.x;
double y=P->position.y;
double xx=this->position.x;
double yy=this->position.y;
double dist=(xx-x)*(xx-x)+(yy-y)*(yy-y);
if(dist<500){
    if(dist<1)dist=1;
    P->position.x+=(xx-x)/dist;
    P->position.y+=(yy-y)/dist;
}
}
