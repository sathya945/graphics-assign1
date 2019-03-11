#include "player.h"
#include "main.h"
Player::Player(double x,double y){
        float r1=1,r2=1.5;
        this->position = glm::vec3(x, y, 0);
        GLfloat g_vertex_buffer_data[3600];
        velocity=0;
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
        GLfloat g_vertex_buffer_data2[]={
            -0.75,-0.75,0,
            0.75,-0.75,0,
            0,-1.25,0,
             -0.75,-0.75,0,
            0.75,-0.75,0,
            0,-1.75,0,
            0,-1.25,0,
            -0.75,-2.75,0,
            0.75,-2.75,0,
              0,-1.75,0,
            -0.75,-2.75,0,
            0.75,-2.75,0
        };
       float r3=0.15;
       GLfloat temp[3600];
       radians=0;
         for(int i=0;i<9*360;i+=9){
           temp[i] = r3*cos(radians);
           temp[i+1] = r3*sin(radians);
           temp[i+2] = 0.0f;
           temp[i+3] = r3*cos(radians + (2*M_PI/360));
           temp[i+4] = r3*sin(radians + (2*M_PI/360));
           temp[i+5] = 0.0f;
           temp[i+6] = 0.0f;
           temp[i+7] = 0.0f;
           temp[i+8] = 0.0f;
           radians = radians + (2*M_PI/360);
       }
        float r4=0.6;
       GLfloat temp2[3600];
       radians=(240*2*M_PI)/360;
         for(int i=0;i<9*60;i+=9){
           temp2[i] = r4*cos(radians);
           temp2[i+1] = r4*sin(radians);
           temp2[i+2] = 0.0f;
           temp2[i+3] = r4*cos(radians + (2*M_PI/360));
           temp2[i+4] = r4*sin(radians + (2*M_PI/360));
           temp2[i+5] = 0.0f;
           temp2[i+6] = 0.0f;
           temp2[i+7] = 0.0f;
           temp2[i+8] = 0.0f;
           radians = radians + (2*M_PI/360);
       }
    GLfloat temp3[]={
        0,0,0,
        -0.2,-1,0,
        0.2,-1,0
    };

    GLfloat pack_arr[]={
        0,0,0,
        0,0.4,0,
        0.2,0,0,
          0,0.4,0,
        0.2,0,0,
        0.2,0.4,0
    };
    this->legs=create3DObject(GL_TRIANGLES,3,temp3,{173,255,47}, GL_FILL);
    this->lips=create3DObject(GL_TRIANGLES,60*3,temp2,{255,99,71}, GL_FILL);
    this->eye=create3DObject(GL_TRIANGLES,360*3,temp,{255,99,71}, GL_FILL);
    this->head = create3DObject(GL_TRIANGLES, 360*3, g_vertex_buffer_data,{173,255,47}, GL_FILL);
   this->body=create3DObject(GL_TRIANGLES, 12, g_vertex_buffer_data2,{173,255,47}, GL_FILL);
this->pack=create3DObject(GL_TRIANGLES,6,pack_arr,{240,128,128},GL_FILL);
}
void Player::draw(glm::mat4 VP){
            if(velocity>0 || position.y==44)draw_pack(VP);
            Matrices.model = glm::mat4(1.0f);
            glm::mat4 translate = glm::translate (this->position);
            Matrices.model *= (translate);
            glm::mat4 MVP = VP * Matrices.model;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
            draw3DObject(this->head);   
            translate = glm::translate(glm::vec3(-0.4,0.5,0));
            Matrices.model *= (translate);
            MVP = VP * Matrices.model;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
            draw3DObject(this->eye);
            translate = glm::translate(glm::vec3(0.8,0,0));
            Matrices.model *= (translate);
            MVP = VP * Matrices.model;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
            draw3DObject(this->eye);
            translate = glm::translate(glm::vec3(-0.4,0,0));
              Matrices.model *= (translate);
            MVP = VP * Matrices.model;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
            draw3DObject(this->lips);
            translate = glm::translate(glm::vec3(0,-0.25,0));
            Matrices.model *= (translate);
            MVP = VP * Matrices.model;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
            draw3DObject(this->body);
            translate = glm::translate(glm::vec3(0.7,-2.75,0));
            Matrices.model *= (translate);
             MVP = VP * Matrices.model;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
            draw3DObject(this->legs);
              translate = glm::translate(glm::vec3(-1.4,0,0));
            Matrices.model *= (translate);
             MVP = VP * Matrices.model;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
            draw3DObject(this->legs);
}
void Player::draw_pack(glm::mat4 VP){
     Matrices.model = glm::mat4(1.0f);
            glm::mat4 translate = glm::translate (this->position);
            Matrices.model *= (translate*glm::translate(glm::vec3(0,-3,0)));
            glm::mat4 MVP = VP * Matrices.model;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
            draw3DObject(this->pack);

}
void Player::set_position(double x,double y){
    this->position.x+=x;
    this->position.y+=y;
    if(this->position.y<8.5){this->position.y=8.5;this->velocity=0;}
    if(this->position.y>44){this->position.y=44;this->velocity=0;}
    if(this->position.x<1){this->position.x=1;}
}

void Player::updatestate(){
    this->set_position(0,velocity);
    double accleration=0.1;
    if(this->position.y>8.5){
        velocity-=accleration;
    }
    else velocity=0;
}


firebeam::firebeam(double height){
    time=1200;
    time2=300;
    y=height;
   float  w=0.2;
    static GLfloat data[]={
        0,0,0,
        0,w,0,
        72,w,0,
        72,w,0,
        0,0,0,
        72,0,0
    };
    static GLfloat data2[]={
        0,0,0,
        0,1,0,
        1,1,0,
        1,1,0,
        0,0,0,
        1,0,0
    };
    this->body=create3DObject(GL_TRIANGLES,2*3, data,{255,0,0}, GL_FILL);
    this->brick=create3DObject(GL_TRIANGLES,2*3, data2,{139,79,57}, GL_FILL);
}
void firebeam::draw(glm::mat4 VP,double x){
    time--;
    time2--;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (glm::vec3(x-36,y,0));
    Matrices.model*=(translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(time2<0)draw3DObject(this->body);
    translate = glm::translate (glm::vec3(0,-0.4,0));
    Matrices.model*=(translate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->brick);
    translate = glm::translate (glm::vec3(72,0,0));
    Matrices.model*=(translate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->brick);
}


