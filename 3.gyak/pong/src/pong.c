#include "pong.h"

void init_pong(Pong* pong, int width, int height)
{
    pong->width = width;
    pong->height = height;
    init_pad(&(pong->left_pad), 0, height, RED_THEME);
    init_pad(&(pong->right_pad), width - 50, height, GREEN_THEME);
    init_ball(&(pong->ball), width / 2, height / 2);
}

void update_pong(Pong* pong, double time)
{
    update_pad(&(pong->left_pad), time);
    update_pad(&(pong->right_pad), time);
    update_ball(&(pong->ball), time);
    bounce_ball(pong);
}

void render_pong(Pong* pong)
{
    render_pad(&(pong->left_pad));
    render_pad(&(pong->right_pad));
    render_ball(&(pong->ball));
}

void set_left_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->left_pad), position);
}

void set_left_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->left_pad), speed);
}

void set_right_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->right_pad), position);
}

void set_right_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->right_pad), speed);
}

void set_radius_ball_to(Pong* pong, float radius, float limit_min, float limit_max){
    set_radius_ball(&(pong->ball), radius, limit_min, limit_max);
}


void bounce_ball(Pong* pong)
{
    if (pong->ball.x - pong->ball.radius < 50 && (pong->ball.y- pong->ball.radius<pong->left_pad.y+120 && pong->ball.y > pong->left_pad.y-0)) {
        pong->ball.x = pong->ball.radius + 50;
        pong->ball.speed_x *= -1.2;
        pong->ball.speed_y *= -1.2;
    }
    if (pong->ball.x - pong->ball.radius < -(2 * pong->ball.radius)){
        //pong->left_pad_counter+=1;

		float center_x;
		float center_y;

		center_x = pong->width / 2;
		center_y = pong->height / 2;
		init_ball(&(pong->ball), center_x, center_y);
	}
    
    //jobb pad
    if (pong->ball.x + pong->ball.radius > pong->width - 50 && (pong->ball.y- pong->ball.radius<pong->right_pad.y+120 && pong->ball.y > pong->right_pad.y-0)) {
        pong->ball.x = pong->width - pong->ball.radius - 50;
        pong->ball.speed_x *= -1.2;
        pong->ball.speed_y *= -1.2;
    }


   if (pong->ball.x - pong->ball.radius > pong->width - (2 * pong->ball.radius)){

        //pong->right_pad_counter+=1;
		float center_x;
		float center_y;

		center_x = pong->width / 2;
		center_y = pong->height / 2;
		init_ball(&(pong->ball), center_x, center_y);
        
	}
    
    if (pong->ball.y - pong->ball.radius < 0) {
        pong->ball.y = pong->ball.radius;
        pong->ball.speed_y *= -1;
    }
    if (pong->ball.y + pong->ball.radius > pong->height) {
        pong->ball.y = pong->height - pong->ball.radius;
        pong->ball.speed_y *= -1;
    }
}

void click_ball(Pong* pong, int x, int y){
    move_ball(&(pong->ball), x, y);
}
