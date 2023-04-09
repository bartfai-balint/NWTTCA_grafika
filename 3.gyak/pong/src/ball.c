#include "ball.h"

#include <GL/gl.h>

#include <math.h>

void move_ball(Ball* ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
}

void init_ball(Ball* ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
    ball->radius = 50;
    ball->speed_x = 500;
    ball->speed_y = 500;
    move_ball(ball, x, y);
    //ball->rotation = 0;
    //ball->rotation_speed=300;
}

void update_ball(Ball* ball, double time)
{
    ball->x += ball->speed_x * time;
    ball->y += ball->speed_y * time;
    //ball->rotation += ball->rotation_speed * time;
}

void render_ball(Ball* ball)
{
    double angle;
    double x;
    double y;

    glPushMatrix();
    glTranslatef(ball->x, ball->y, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.9, 0.8);
    glVertex2f(0, 0);
    angle = 0;
    while (angle < 2.0 * M_PI + 1) {
        x = cos(angle) * ball->radius;
        y = sin(angle) * ball->radius;
        glVertex2f(x, y);
        angle += 0.8;
    }
    glEnd();
    glPopMatrix();

    //set ball radius
    
    void set_radius_ball(Ball* ball, float radius, float limit_min, float limit_max){
        if(radius < limit_min){
            ball->radius = limit_min;
        }else if (radius > limit_max){
            ball->radius = limit_max;
        }else{
            ball->radius = radius;
        }  
    }
    
}
