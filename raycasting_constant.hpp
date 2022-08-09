const int width = 900;
const int height = 900;
const int rate_map = 5; // mini map is 5x more little than view

const int nb_case_w = 10; // Number of boxes on the width
const int nb_case_h = 10; // Number of boxes on the height
const int vitesse = 15; // Speed player
const int v_angle = 10; // Speed angle
const int angle_vision = 64; // FOV
const int precision_angle = 3; //equals to number of values in 1 degre

sf::RenderWindow window;
sf::ContextSettings options;
const int fps = 30;
const int rayon = 1; // Radius of player (for minimmap)
const int dist_tol = 200; // brightness
float w_d_d = (float) width / (angle_vision*precision_angle);

int taille_image;

std::array<int, nb_case_w*nb_case_h> const map {
    1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,1,
    1,0,0,0,1,1,1,0,0,1,
    1,0,0,0,0,0,1,0,0,1,
    1,0,1,0,0,0,0,0,0,1,
    1,0,1,1,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,1,
    1,0,0,1,1,1,0,0,0,1,
    1,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1
};
