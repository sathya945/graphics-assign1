#include "main.h"
#include "timer.h"
#include "ball.h"
#include "platform.h"
#include "player.h"
#include "coins.h"
#include <complex>
#include <unistd.h>
#include "score.h"

using namespace std;

typedef complex<double> Point; 

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
vector <pair<double,double>> coinsmap;
int ti=-1;
VAO *ring_smallhalf;
VAO *ring_bighalf;
int lives=2;
int revivetime=0;
int time_set=150;
vector <Boomrang> ene2;
bool collisoncheck=true;
vector <Enemy> enemies1;
vector <firebeam> laser_ene;
vector <magent> attr_p;
vector <Ball> coinBall;
vector <Ballon> bullets;
vector <Powerup> arr_power;
int windowheight,windowwidth;
/**************************
* Customizable functions *
**************************/
float changex=0;
int score=0;
float playervelocity=0;
float screen_zoom = 0.1, screen_center_x = 0, screen_center_y = -15;
float camera_rotation_angle = 0;
void draw_ring(glm::mat4 VP,float x,float y);
Timer t60(1.0 / 60);
void initenemies1();
void ring();
void ring_player(Player *P1);
void collect_lives(Player *P);
void boomcollision(Player *P);
void BIG_coins(Player *P1);
void initlaser();
void initlives(Player *P);
void init_ene2(Player *P1);
void initmagnet(Player *P1);
void lasercollision(Player *P1);
void collectcoins(Player *P1);
bool check_collision(double x1,double y1,double x2,double y2,double r);
void collision_enemie1(Player *P1);
void kill_enemies();
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw(Platform Bottom,Player* P1) {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
 //   glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
   // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
   // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
  //  Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!

    double distance=P1->position.x-40;
    if(distance<0)distance=0;       
    Matrices.view = glm::lookAt(glm::vec3(40+distance,40, 3), glm::vec3(40+distance,40, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
    // Scene render
BIG_coins(P1);
draw_ring(VP,66,20);
ring_player(P1);
  Bottom.draw(VP);  
  coins Draw_coins=coins();
  coins *addr=&Draw_coins;
  for(int i=0;i<laser_ene.size();i++){
      laser_ene[i].draw(VP,distance+40);
      if(laser_ene[i].time<0){
          laser_ene.erase(laser_ene.begin()+i);
          i--;
      }
  }
  for(int i=0;i<ene2.size();i++){
      ene2[i].draw(VP);
  }
  for(int i=0;i<coinsmap.size();i++){
      addr->draw(VP,coinsmap[i].first,coinsmap[i].second);
  }
  for(int i=0;i<enemies1.size();i++){
     enemies1[i].draw(VP);
}
  for (int i=0;i<coinBall.size();i++){
      coinBall[i].draw(VP);
  }
  for(int i=0;i<attr_p.size();i++){
      attr_p[i].draw(VP);
      attr_p[i].update(P1);
      if(attr_p[i].time<0){
          attr_p.clear();
      }
  }
  for(int i=0;i<arr_power.size();i++){
      arr_power[i].draw(VP);
  }
  for(int i=0;i<bullets.size();i++){
      bullets[i].draw(VP);
      if(bullets[i].yvel<-1 || bullets[i].position.y>44){bullets.erase(bullets.begin()+i);i--;}
  }
    Bottom.draw(VP);  
    if(revivetime<1 || revivetime%3==0)
        P1->draw(VP);
if(revivetime<1){
    collision_enemie1(P1);
    lasercollision(P1);
    boomcollision(P1);
}
    collectcoins(P1);
    kill_enemies();
    collect_lives(P1);
    float xx=distance+10;
    float yy=43;
    int temp_score=score;
    for(int i=0;i<4;i++){
        Score temp=Score(xx,yy);
        temp.draw(VP,temp_score%10);
        temp_score/=10;
        xx-=2.4;
}
Score temp=Score(distance+13,yy);
temp.draw(VP,lives);
}

void collect_lives(Player *P){
for(int i=0;i<arr_power.size();i++){ 
    float x=arr_power[i].position.x;
    float y=arr_power[i].position.y;
    float xx=P->position.x;
    float yy=P->position.y;
    if(check_collision(x,y,xx,yy,2)|| check_collision(x,y,xx,yy-2,2.7)){
        lives++;
        arr_power.erase(arr_power.begin()+i);
        i--;
    }
}

for (int i=0;i<arr_power.size();i++){
        arr_power[i].velocity-=arr_power[i].acc;
        arr_power[i].position.x+=arr_power[i].xvel;
        if(arr_power[i].position.y<6){
            arr_power[i].position.y=6;
            arr_power[i].velocity=arr_power[i].velocity*-1;
        }
         arr_power[i].position.y+=arr_power[i].velocity;
    }
}

void boomcollision(Player *P){
for(int i=0;i<ene2.size();i++){ 
    float x=ene2[i].position.x;
    float y=ene2[i].position.y;
    float xx=P->position.x;
    float yy=P->position.y;
    float r=0.5;
    if(check_collision(x,y,xx,yy,1.5)|| check_collision(x,y,xx,yy-2,2.2)){
        lives--;
        revivetime=time_set;
        break;
    }
}
}

Point rotate(Point P, Point Q, double theta) 
{ 
    return (P) * polar(1.0, theta) +  Q; 
}
void lasercollision(Player *P1){
      double y=P1->position.y;
      for(int i=0;i<laser_ene.size();i++){
          double yy=laser_ene[i].y;
          if(laser_ene[i].time2>0)continue;
          if((y-4.5<yy && yy <y+1)||( y-4.5<yy+0.2 && yy+0.2<y+1) ){
              lives--;
              revivetime=time_set;
              break;
          }
      }
}
void BIG_coins(Player *P1){

int num=rand()%3000;
    if(2996<num){
    coinBall.push_back(Ball(P1->position.x-10,20));
    //cout<<"djnjd"<<endl;
    }

double x=P1->position.x;
double y=P1->position.y;
for (int i=0;i<coinBall.size();i++){
    double xx=coinBall[i].position.x;
    double yy=coinBall[i].position.y;
    double r=coinBall[i].radius;
     if(check_collision(x,y,xx,yy,r+1)|| check_collision(x,y-2,xx,yy,1.7)){
            score+=100;
            coinBall.erase(coinBall.begin()+i);
            continue;
     }
     if(xx-x > 60 || x-xx>60 ){
            coinBall.erase(coinBall.begin()+i);
            continue;
     }
 }
for (int i=0;i<coinBall.size();i++){
        coinBall[i].velocity-=coinBall[i].acc;
        coinBall[i].position.x+=coinBall[i].xvel;
        if(coinBall[i].position.y<6){
            coinBall[i].position.y=6;
            coinBall[i].velocity=coinBall[i].velocity*-1;
        }
         coinBall[i].position.y+=coinBall[i].velocity;
    }
}
bool circle_rectangle(Point l1,Point l2,Point P1,double radius){
    double a = imag(l1) -imag(l2); 
    double b = real(l2) - real(l1); 
    double c = -a*(real(l2))-b*imag(l2);
    double x1=real(P1),y1=imag(P1);
    double temp=-(a*x1+b*y1+c)/(a*a+b*b);
    double x=a*temp+x1;
    double y=b*temp+y1;
    if((temp*temp*(a*a+b*b))< radius*radius){
        if((real(l1)<=x && x<=real(l2)) ||(real(l2)<=x && x<=real(l1))) {
            if(real(l1)-real(l2)<0.000000001){
                if(((imag(l1)<=y && y<=imag(l2)) ||(imag(l2)<=y && y<=imag(l1))))
                    return true;
                return false;
            }
                cout <<real(l1) << " point " <<imag(l1) <<endl <<real(l2) <<" point " << imag(l2) << endl << real(P1) << " " << imag(P1) << endl;
                cout << x << " foot " << y<< endl;
                cout << a << " " << b << " " <<c << endl;
                return true;
        }
    }
        return false;
}
void collision_enemie1(Player *P1){
double x=P1->position.x;
double y=P1->position.y;

Point headcen(x,y);
for(int i=0;i<enemies1.size();i++){
    double a=(enemies1[i].rotation*M_PI)/180.0;
    double l=enemies1[i].length;
    double b=enemies1[i].width;
    Point cen(enemies1[i].position.x,enemies1[i].position.y);
    Point l1=Point(l/2.0,b/2.0);
    Point l2=Point(l/2.0,-b/2.0);
    Point l3=Point(-l/2.0,-b/2.0);
    Point l4=Point(-l/2.0,b/2.0);
    l1=rotate(l1,cen,a);
    l2=rotate(l2,cen,a);
    l3=rotate(l3,cen,a);
    l4=rotate(l4,cen,a);
    if(circle_rectangle(l1,l2,headcen,1)||circle_rectangle(l2,l3,headcen,1)||circle_rectangle(l3,l4,headcen,1)||circle_rectangle(l4,l1,headcen,1)){
    lives--;
        revivetime=time_set;
        break;
    }
    headcen=Point(x,y-2);
    if(circle_rectangle(l1,l2,headcen,1.7)||circle_rectangle(l2,l3,headcen,1.7)||circle_rectangle(l3,l4,headcen,1.7)||circle_rectangle(l4,l1,headcen,1.7)){
        lives--;
        revivetime=time_set;
        break;
    }
}
}


void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    screen_zoom+=yoffset/100;
     if(screen_zoom<0.01)screen_zoom=0.1;
     if(screen_zoom>1)screen_zoom=0.1;
}


void tick_input(GLFWwindow *window,Player *P1) {   
    if(revivetime>0)revivetime--;
    ti--;
    initlaser();
    initlives(P1);
    initmagnet(P1);
    init_ene2(P1);
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up=glfwGetKey(window, GLFW_KEY_UP);
    int space=glfwGetKey(window,GLFW_KEY_SPACE);
    glfwSetScrollCallback(window, scroll_callback);
    if (left) {
     P1->set_position(-0.5,0);
    }
    if(right){
        P1->set_position(0.5,0);        
    }
    if(up){
        P1->velocity=1;
    }
    if(space){

      if(ti<0) { bullets.push_back(Ballon(P1->position.x + 0.2,P1->position.y +1.5));
      ti=60;
      }
    }
    P1->updatestate();
}

void collectcoins(Player *P1){
        coins Draw_coins=coins();
        coins *addr=&Draw_coins;
        double coin_radius=addr->r1;
        double x1=P1->position.x,x2,y2;
        double y1=P1->position.y;
      for(int i=0;i<coinsmap.size();i++){
          x2=coinsmap[i].first;
          y2=coinsmap[i].second;
          if(check_collision(x1,y1,x2,y2,coin_radius+1) || check_collision(x1,y1-2,x2,y2,coin_radius+1.5)){
              coinsmap.erase(coinsmap.begin()+i);
              if(int(x2+y2)%2==0)score+=10;
              else score+=5;

              i--;
          }
      }
}
bool check_collision(double x1,double y1,double x2,double y2,double r){
        return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<r*r;
}
/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");



    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1920;
    int height = 1080;

    window = initGLFW(width, height);
    initGL (window, width, height);
    Platform Bottom =Platform();
    Player P1=Player(9.0,8.5);
    initcoins();
    ring();
    initlaser();
    initenemies1();
    while (!glfwWindowShouldClose(window)) {
     glfwGetWindowSize( window,&windowwidth, &windowheight );
     reset_screen();
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw(Bottom,&P1);
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
      //      tick_elements();
           tick_input(window,&P1);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
        if(lives<1)    quit(window);
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + (4.0*windowheight/windowwidth) / screen_zoom;
    float bottom = screen_center_y - (4.0*windowheight/windowwidth)/ screen_zoom;
    float left   = screen_center_x - (4.0) / screen_zoom;
    float right  = screen_center_x + (4.0) / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

void horcoins(double x,double y,int n){
    for(int i=0;i<n;i++)
        {
            coinsmap.push_back(make_pair(x,y));
            x+=1.4;
        }
}   
void initcoins(){
    horcoins(40,40,5);
    horcoins(41.5,42,3);
    horcoins(43,44,1);
    for(int i=0;i<90;i++){
        horcoins(rand()%100+20,rand()%40+7,rand()%6);
    }
}
void initenemies1(){
    Enemy laser_1=Enemy(26,36,7,0.0,0.0);
    enemies1.push_back(laser_1);
    enemies1.push_back(Enemy(45,20,6,90.0,2.0));
    for(int i=0;i<10;i++){
       int  x=rand()%150+20;
       int  y=rand()%35+12;
    enemies1.push_back(Enemy(x,y,3+rand()%4,rand()%360,rand()%3));
    }
}
void initlaser(){
    int num=rand()%3000;
    if(2996<num){
        laser_ene.push_back(firebeam(rand()%39+6));
    }
}
void initmagnet(Player *P1){
int num=rand()%3000;
    if(2996<num && attr_p.size()==0){
    attr_p.push_back(magent(P1->position.x-10+rand()%20,rand()%30+9));
    }
}

void kill_enemies(){
 for(int j=0;j<bullets.size();j++){
     int collide=0;
     float r=bullets[j].radius;
     Point headcen(bullets[j].position.x,bullets[j].position.y);
    for(int i=0;i<enemies1.size();i++){
    double a=(enemies1[i].rotation*M_PI)/180.0;
    double l=enemies1[i].length;
    double b=enemies1[i].width;
    Point cen(enemies1[i].position.x,enemies1[i].position.y);
    Point l1=Point(l/2.0,b/2.0);
    Point l2=Point(l/2.0,-b/2.0);
    Point l3=Point(-l/2.0,-b/2.0);
    Point l4=Point(-l/2.0,b/2.0);
    l1=rotate(l1,cen,a);
    l2=rotate(l2,cen,a);
    l3=rotate(l3,cen,a);
    l4=rotate(l4,cen,a);
    if(circle_rectangle(l1,l2,headcen,r)||circle_rectangle(l2,l3,headcen,r)||circle_rectangle(l3,l4,headcen,r)||circle_rectangle(l4,l1,headcen,r)){
        collide=1;
        enemies1.erase(enemies1.begin()+i);
        break;
    }
 }
 if(collide==1){
     bullets.erase(bullets.begin()+j);
     j--;
 }
}
}
void init_ene2(Player *P){
int num=rand()%3000;
    if(2995<num && attr_p.size()==0){
    ene2.push_back(Boomrang(P->position.x+rand()%10+10,rand()%6+37));
    }
}

void initlives(Player *P){
int num=rand()%3000;
    if(2996<num ){
    arr_power.push_back(Powerup(P->position.x-10,20));
    }   
}
void ring(){
    float w=7;
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
    r1=w+0.3;
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
    ring_smallhalf=create3DObject(GL_TRIANGLES, 180*3, g_vertex_buffer_data2,{242, 241, 239}, GL_FILL);
    ring_bighalf=create3DObject(GL_TRIANGLES, 180*3, g_vertex_buffer_data3,{178,34,34}, GL_FILL);
}
void draw_ring(glm::mat4 VP,float x,float y){
       Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (glm::vec3(x,y,0));
        Matrices.model *= (translate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(ring_bighalf);
        draw3DObject(ring_smallhalf);
}
void ring_player(Player *P1){
    float y=P1->position.y-3.5;
    float x=P1->position.x-1;
    if(check_collision(x,y,66,20,7.3) && y <20){
        if((x-66)*(x-66)<49){
        P1->position.y=20-sqrt(49-(x-66)*(x-66))+3.7;}
        P1->velocity=0;
    }
}