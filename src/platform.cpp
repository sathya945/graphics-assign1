#include "platform.h"
#include "main.h"
Platform::Platform(){
    static const GLfloat data[]={
        0,0,0,
        0,5,0,
        4,5,0,
        0,0,0,
        4,0,0,
        4,5,0
    };
    this->object = create3DObject(GL_TRIANGLES,2*3, data,{139,69,19}, GL_FILL);
}

void Platform::draw(glm::mat4 VP){  
        Matrices.model = glm::mat4(1.0f);
        glm::vec3 position = glm::vec3(4,0, 0);
        glm::mat4 translate = glm::translate (position);
        for(int i=0;i<200;i++){
            glm::mat4 MVP = VP * Matrices.model;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
            draw3DObject(this->object);
         
            Matrices.model*=translate;
        }
        Matrices.model = glm::mat4(1.0f);
        glm::vec3 position1 = glm::vec3(0,45,0);
        glm::mat4 translate1 = glm::translate (position1);
        Matrices.model*=translate1;
        for(int i=0;i<200;i++){
            glm::mat4 MVP = VP * Matrices.model;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
            draw3DObject(this->object);
             Matrices.model*=translate;
        }   
}
Enemy::Enemy(double x,double y,double r,double start_angle,double rotate){
    this->rot=rotate;
    rotation=start_angle;
    double angle=4;
    double radians=(2*M_PI*angle)/360;
    radius=r;
    GLfloat data[18];
    data[0]=r*cos(radians);
    data[1]=r*sin(radians);
    data[2]=0;
    data[3]=-data[0];
    data[4]=-data[1];
    data[5]=0;
    data[6]=data[0];
    data[7]=-data[1];
    data[8]=0;
    data[9]=r*cos(radians);
    data[10]=r*sin(radians);
    data[11]=0;
    data[12]=-data[0];
    data[13]=-data[1];
    data[14]=0;
    data[15]=-data[0];
    data[16]=data[1];
    data[17]=0;
    double  r1=data[1];
    length =2*(r+r1);
    width=2*r1;
    GLfloat g_vertex_buffer_data[3600];
    angle=-90;
    radians = (2*M_PI*angle)/360;;
        for(int i=0;i<9*180;i+=9){
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
    position = glm::vec3(x,y,0);
    this->end = create3DObject(GL_TRIANGLES,180*3,g_vertex_buffer_data,{51,25,0}, GL_FILL);
    this->object=create3DObject(GL_TRIANGLES,6,data,{255,255,0}, GL_FILL);
}
void Enemy::change(double x,double y,double theta){
    this->position.x+=x;
    this->position.y+=y;
    this->rotation+=theta;
}
void Enemy::draw(glm::mat4 VP){
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);
    glm::mat4 rotate=glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate*rotate);
   // Matrices.model= glm::scale(Matrices.model, glm::vec3(1,1, 1));
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    translate = glm::translate(glm::vec3(this->radius,0,0));
    Matrices.model *= (translate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->end);
    translate = glm::translate(glm::vec3(-2*this->radius,0,0));
    Matrices.model *= (translate);
    Matrices.model *=(glm::rotate((float) (  M_PI ), glm::vec3(0, 0, 1  )));
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->end);
    change(0,0,rot);
}
Ballon::Ballon(float x,float y){
    radius=0.4;
    xvel=0.6;
    yvel=1;
    acc=0.1;
    float r1=radius;
    this->position = glm::vec3(x, y, 0);
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
    this->object  = create3DObject(GL_TRIANGLES, 360*3, g_vertex_buffer_data,{135, 206, 235}, GL_FILL);
}
void Ballon::draw(glm::mat4 VP){
       Matrices.model = glm::mat4(1.0f);
            glm::mat4 translate = glm::translate (this->position);
            Matrices.model *= (translate);
            glm::mat4 MVP = VP * Matrices.model;
            glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
            draw3DObject(this->object);
            this->update();
}
void Ballon::update(){
this->position.x+=xvel;
this->position.y+=yvel;
this->yvel-=acc;
}
Boomrang::Boomrang(float x,float y){
            rotation=0;
            xvel=0.1;
            yvel=-0.03;
            acc=0.0002;
             position = glm::vec3(x,y,0);
            float w=0.5;
             float radians = M_PI/2;
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
    radians=M_PI/2;
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
    this->smallhalf=create3DObject(GL_TRIANGLES, 180*3, g_vertex_buffer_data2,{242, 241, 239}, GL_FILL);
    this->bighalf=create3DObject(GL_TRIANGLES, 180*3, g_vertex_buffer_data3,{178,34,34}, GL_FILL);
}
void Boomrang::draw(glm::mat4 VP){
    Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position);
        Matrices.model *= (translate);
        Matrices.model *=glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->bighalf);
        draw3DObject(this->smallhalf);
        update();
}
void Boomrang::update(){
  //  std::cout << position.x << "\n";
    position.x-=xvel;
    position.y+=yvel;
    xvel-=acc;
    if(rotation<180)rotation+=0.25;
}

Powerup::Powerup(float x,float y){
     velocity=0.4;
    acc=0.005;
    xvel=0.2; 
    position = glm::vec3(x,y,0);
    l=1;
    b=0.2;
    rotate=0;
     static const GLfloat data[]={
        l,b,0,
        -l,b,0,
        -l,-b,0,
        l,b,0,
        -l,-b,0,
        l,-b,0
    };
    this->object = create3DObject(GL_TRIANGLES,2*3, data,{255,99,71}, GL_FILL);
}

void Powerup::draw(glm::mat4 VP){
    rotate+=3;
 Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position);
            glm::mat4 rotate=glm::rotate((float) (this->rotate * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate*rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->object);
        MVP*=glm::rotate((float) (90* M_PI / 180.0f), glm::vec3(0, 0, 1));
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->object);
}