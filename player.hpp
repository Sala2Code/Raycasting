struct Player
{
    void setPosition(float x,float y);

    sf::CircleShape forme;
    sf::RectangleShape view;
    // Initial position 
    float x=150.5; 
    float y=150.5;
    float angle;

    Player()
    {
        forme.setRadius(rayon);
        forme.setFillColor(sf::Color::Green);

        view.setSize({0,1});
        view.setFillColor(sf::Color::Magenta);
    }
};

void Player::setPosition(float x, float y){
    x/=rate_map;
    y/=rate_map;
    forme.setPosition(x,y);
    view.setPosition(x+rayon/2,y+rayon/2);
}
