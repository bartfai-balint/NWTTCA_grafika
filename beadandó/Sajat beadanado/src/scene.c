#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>
#include <math.h>

void init_scene(Scene* scene,Camera* camera)
{
    scene->rotation = 0.0;
    scene->key_roation = 0.0;
    scene->light = 0.0;
    

    load_model(&(scene->T34), "assets/models/t34obj.obj");
  
    load_model(&(scene->t55), "assets/models/t552.obj");
    scene->texture_id = load_texture("assets/textures/t55camo.jpg");

    //scene->texture_T34 = load_texture("assets/textures/rudy.jpg");

    load_model(&(scene->bmp), "assets/models/bmp3.obj");
    scene->texture_bmp = load_texture("assets/textures/anyad.jpg");

    load_model(&(scene->house), "assets/models/House.obj");
    scene->texture_house = load_texture("assets/textures/House.jpg");

    load_model(&(scene->key), "assets/models/ak472.obj");
    scene->texture_ak = load_texture("assets/textures/ak47.jpg");
    scene->texture_key = load_texture("assets/textures/grey.jpg");

    load_model(&(scene->table), "assets/models/table.obj");
    scene->texture_table = load_texture("assets/textures/table.jpg");

    load_model(&(scene->movingKey.MoveKey), "assets/models/camera2.obj");

    scene->texture_help = load_texture("assets/textures/help.jpg");


    scene->material.ambient.red = 1;
    scene->material.ambient.green = 1;
    scene->material.ambient.blue = 1;

    scene->material.diffuse.red = 1; 
    scene->material.diffuse.green = 1; 
    scene->material.diffuse.blue = 1;

    scene->material.specular.red = 1;
    scene->material.specular.green = 1;
    scene->material.specular.blue = 1;

    scene->material.shininess = 50; 

    scene->mat_T34.ambient.red = 0.309278;
    scene->mat_T34.ambient.green = 0.309278;
    scene->mat_T34.ambient.blue = 0.309278;

    scene->mat_T34.diffuse.red = 0.17868; //1 volt
    scene->mat_T34.diffuse.green = 0.17868; //1 volt
    scene->mat_T34.diffuse.blue = 0.17868;

    scene->mat_T34.specular.red = 0.5;
    scene->mat_T34.specular.green = 0.5;
    scene->mat_T34.specular.blue = 0.5;//0 mind 3

    scene->mat_T34.shininess = 50; 
}

void set_lighting(const Scene* scene)
{
   float b;
    b = scene->light / 255 ;
    float ambient_light[] = { b, b, b, b };
    float diffuse_light[] = { b, b, b, b };
    float specular_light[] = { b, b, b, b };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}


void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void set_material2(const Material* mat_T34)
{
    float ambient_material_color[] = {
        mat_T34->ambient.red,
        mat_T34->ambient.green,
        mat_T34->ambient.blue
    };

    float diffuse_material_color[] = {
        mat_T34->diffuse.red,
        mat_T34->diffuse.green,
        mat_T34->diffuse.blue
    };

    float specular_material_color[] = {
        mat_T34->specular.red,
        mat_T34->specular.green,
        mat_T34->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(mat_T34->shininess));
}

void update_scene(Scene* scene, Camera* camera,double elapsed_time)
{
    scene->movingKey.position.x = camera->position.x;
    scene->movingKey.position.y = camera->position.y;
   

    scene->rotation += 0.5 ;
    scene->key_roation += 3;
}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    //set_material2(&(scene->mat_T34));
    set_lighting(scene);
    draw_origin();
    draw_T34(scene);
    draw_house(scene);
    draw_table(scene);
    draw_ak(scene);
    draw_t55(scene);
    draw_bmp(scene);
    draw_key_move(scene);
}


void draw_t55(const Scene* scene){
    glPushMatrix();
    glTranslatef(1.5, 1, 0.35);
    glRotatef(90, 1, 0, 0);
    glRotatef(scene->rotation, 0, 1, 0);
    glScalef(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id);
    set_material(&(scene->material));
    draw_model(&(scene->t55));
    glPopMatrix();
}

void draw_T34(const Scene* scene){
    glPushMatrix();
    glTranslatef(4.5, 1, 0.05);
    glRotatef(90, 1, 0, 0);
    glRotatef(scene->rotation, 0, 1, 0);
    glScalef(0.05, 0.05, 0.05);
    set_material(&(scene->material));
    draw_model(&(scene->T34));
    glPopMatrix();
}

void draw_bmp(const Scene* scene){
    glPushMatrix();
    glTranslatef(-1.5, 1, 0.05);
    glRotatef(90, 1, 0, 0);
    glRotatef(scene->rotation, 0, 1, 0);
    glScalef(0.2, 0.2, 0.2);
    glBindTexture(GL_TEXTURE_2D, scene->texture_bmp);
    set_material(&(scene->material));
    draw_model(&(scene->bmp));
    glPopMatrix();
}


void draw_house(const Scene* scene){
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.15, 0.15, 0.15);
    glBindTexture(GL_TEXTURE_2D, scene->texture_house);
    set_material(&(scene->material));
    draw_model(&(scene->house));
    glPopMatrix();
}

void draw_table(const Scene* scene){
    glPushMatrix();
    glTranslatef(0, -1, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->texture_table);
    set_material(&(scene->material));
    draw_model(&(scene->table));
    glPopMatrix();
}

void draw_ak(const Scene* scene){
    glPushMatrix();
    glTranslatef(0, -1, 0.5);
    glRotatef(90, 1, 0, 0);
    glRotatef(scene->key_roation, 0, 1, 0);
    glScalef(0.05, 0.05, 0.05);
    glBindTexture(GL_TEXTURE_2D, scene->texture_ak);
    set_material(&(scene->material));
    draw_model(&(scene->key));
    glPopMatrix();
}

void draw_key_move(const Scene* scene){
    float x,y;
    x = scene->movingKey.position.x + 0.1;
    y = scene->movingKey.position.y + 0.06; 
    glBindTexture(GL_TEXTURE_2D, scene->texture_key);
    glPushMatrix();
    glTranslatef(x, y, 0.9);
    glRotatef(90, 1, 0, 0);
    glScalef(0.02, 0.02, 0.02);
    draw_model(&(scene->movingKey));
    glPopMatrix();
}

void Key_up(Scene* scene, int a, Camera* camera){
    int c = a;
    if(c == 1){
        scene->movingKey.position.x = camera->position.x;
        scene->movingKey.position.y = camera->position.y;
        scene->movingKey.position.z = camera->position.z;
    }
}

void set_sun_brightness_inc(Scene* scene, float b)
{
   scene->light += b;

    if(scene->light > 255.0){
        scene->light = 255.0;
    }
    if(scene->light < 0.0){
        scene->light = 0.0;
    }
}

void show_help(GLuint help_texture) {
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, help_texture);

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3d(-2, 1.5, -3);
        glTexCoord2f(1, 0);
        glVertex3d(2, 1.5, -3);
        glTexCoord2f(1, 1);
        glVertex3d(2, -1.5, -3);
        glTexCoord2f(0, 1);
        glVertex3d(-2, -1.5, -3);
    glEnd();


    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}