////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <array>
#include <string>

#include <math.h>       
#define PI 3.14159265

#include "raycasting_constant.hpp"
#include "player.hpp"

Player player;
sf::Texture murTexture;


sf::RectangleShape generate_map(int i);
bool isCollision(int x, int y);
void line_view(sf::RenderWindow &wi, float nb_dec);

int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Raycasting");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(fps);
    options.antialiasingLevel = 8;

    murTexture.loadFromFile("Wall150.jpg"); // Your texture 
    taille_image = 150; // x*x 

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color(45,255,255)); // Sky


        player.setPosition(player.x,player.y);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            player.angle+= v_angle;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            player.angle-= v_angle;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(!isCollision(player.x+cos(player.angle*PI/180)*vitesse, player.y-sin(player.angle*PI/180)*vitesse)){
                player.x+=cos(player.angle*PI/180)*vitesse;
                player.y-=sin(player.angle*PI/180)*vitesse;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(!isCollision(player.x-cos(player.angle*PI/180)*vitesse,player.y+sin(player.angle*PI/180)*vitesse) ){
                player.x-=cos(player.angle*PI/180)*vitesse;     
                player.y+=sin(player.angle*PI/180)*vitesse;     
            }
        }


        // Floor
        sf::RectangleShape sol({width,height/2});
        sol.setPosition(0,height/2);
        sol.setFillColor(sf::Color(0, 200, 0));
        window.draw(sol);

        // Wall 
        for(float i=0;i<(angle_vision*precision_angle);i++){
            line_view(window,i);     
        }

        //Minimap
        for(int i=0;i<nb_case_w*nb_case_h;i++){
            if(map[i]==1){
                window.draw(generate_map(i));
                
            }
        }
        window.draw(player.forme);
        window.display();
    }

    return 0;
}

sf::RectangleShape generate_map(int i){
    float width_map = width/rate_map;
    float height_map = height/rate_map;
    sf::RectangleShape border(sf::Vector2f(width_map/nb_case_w,height_map/nb_case_h));
    border.setPosition(i%nb_case_w*width_map/nb_case_w,std::floor(i/nb_case_h)*height_map/nb_case_h);
    return border;
}

bool isCollision(int x, int y){
    std::array<int, 4> list_indice{
        (x+rayon*2)/(width/nb_case_w) + (y+rayon*2)/(height/nb_case_h)*nb_case_w,
        x/(width/nb_case_w) + y /(height/nb_case_h)*nb_case_w,
        (x+rayon*2)/(width/nb_case_w) + y /(height/nb_case_h)*nb_case_w,
        x/(width/nb_case_w) + (y+rayon*2)/(height/nb_case_h)*nb_case_w
    };
            
    if( map[list_indice[0]]==1 || map[list_indice[1]]==1||  map[list_indice[2]]==1||  map[list_indice[3]]==1  ){
        return true;
    }
    return false;
}

void line_view(sf::RenderWindow &wi, float nb_dec){
    int d_detect=0;
    bool hit_wall = false;
    float angle_temp = player.angle + angle_vision / 2 - nb_dec/precision_angle ;
    
    sf::RectangleShape line_v({0,1});
    line_v.setFillColor(sf::Color::Red);
    line_v.setPosition((player.x+rayon/2)/rate_map,(player.y+rayon/2)/rate_map);
    line_v.rotate(-angle_temp);

    sf::RectangleShape form_v({0,w_d_d});


    while (!hit_wall){
        int x_detect = player.x+cos(angle_temp*PI/180)*d_detect + rayon;
        int y_detect = player.y-sin(angle_temp*PI/180)*d_detect + rayon;
        if(map[x_detect/(width/nb_case_w) + y_detect /(height/nb_case_h)*nb_case_w]==1){
            hit_wall = true;
            float distance = sqrt(pow(x_detect - player.x,2)+pow(y_detect - player.y,2));
            line_v.setSize({distance/rate_map,1});

            float h_form = 50000/(cos((angle_vision / 2 - nb_dec/precision_angle)*PI/180)*distance);
            form_v.setSize({w_d_d, h_form});
            form_v.setPosition(nb_dec*w_d_d, ( height -  h_form )/2); 

            float brightness = (distance<=dist_tol) ? 1 : dist_tol/distance;

            // Vertical walls are slightly more dark than those are horizontals
            if(
                (map[(x_detect+1)/(width/nb_case_w) + y_detect /(height/nb_case_h)*nb_case_w]==0 ||
                map[(x_detect-1)/(width/nb_case_w) + y_detect /(height/nb_case_h)*nb_case_w]==0 ) &&
                (map[(x_detect)/(width/nb_case_w) + (y_detect+1) /(height/nb_case_h)*nb_case_w]==1 &&
                map[(x_detect)/(width/nb_case_w) + (y_detect-1) /(height/nb_case_h)*nb_case_w]==1 )
            ){
                int light = brightness*200;
                form_v.setFillColor(sf::Color(light,light,light));
                form_v.setTexture(&murTexture);
                form_v.setTextureRect( sf::IntRect( y_detect%(height/nb_case_h)*taille_image/(height/nb_case_h), 0, 1, taille_image ));

            }
            else{
                int light = brightness*255;
                form_v.setFillColor(sf::Color(light,light,light));
                form_v.setTexture(&murTexture);
                form_v.setTextureRect(sf::IntRect(  x_detect%(width/nb_case_w)*taille_image/(width/nb_case_w), 0, 1, taille_image ));
            }

            wi.draw(line_v);
            wi.draw(form_v);
        }
        d_detect++;
    }
}
