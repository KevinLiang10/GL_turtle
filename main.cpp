
#include "turtle.h"

int main()
{
    
    Turtle turtle = Turtle();
    turtle.init();
    turtle.color(0, 1, 0);

    for (int i = 0; i < 180; i++)
        {
            turtle.forward(100*4);
            turtle.right(30);
            turtle.forward(20*4);
            turtle.left(60);
            turtle.forward(50*4);
            turtle.right(30);

            turtle.penup();
            turtle.setPosition(0, 0);
            turtle.pendown();

            turtle.right(2);
        }

    turtle.show();

    return 0;
}
