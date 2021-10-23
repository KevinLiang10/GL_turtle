#ifndef _TURTLE
#define _TURTLE


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Turtle{
    protected:
    
    unsigned int SCR_WIDTH;
    unsigned int SCR_HEIGHT;
    std::string turtleName;


    double turtleX = 0.0;
    double turtleY = 0.0;

    public:
    GLFWwindow* window;

    Turtle(unsigned int width = 800, unsigned int height = 600, const char * name = "turtle");
    virtual ~Turtle();

    int getScreenWidth();
    int getScreenHeight();

    void setScreenWidth(int width);
    void setScreenHeight(int height);

    double getTurtleWidth();
    double getTurtleHeight();

    void setTurtleWidth(double width);
    void setTurtleHeight(double height);

    void forward(double length);
    void left(double degree);
    void right(double degree);



    


};

#endif