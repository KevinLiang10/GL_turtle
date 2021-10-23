#ifndef TURTLE_H
#define TURTLE_H
#ifndef _TURTLE_H_INCLUDED_
#define _TURTLE_H_INCLUDED_ 1

#include <vector>

const unsigned int WIDTH = 1000;
const unsigned int HEIGHT = 1000;
const float STEP = 0.001;

struct vertex {
    float x, y, z;
};

class Turtle
{
public:
    vertex v;
    float theta;
    bool down;
    vertex turtleColor;
    
    std::vector<vertex> vertices;


    Turtle();
    ~Turtle();
    void init(float x = 0, float y = 0, float theta = 0);
    void show();
    void forward(float d);
    void right(float theta);
    void left(float theta);
    void setPosition(float x, float y);
    void penup();
    void pendown();
    void color(float r, float g, float b);
    void circle(float radius);
};

#endif
#endif