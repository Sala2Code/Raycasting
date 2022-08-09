struct Player
{
    void setPosition(float x,float y);

    sf::CircleShape forme;
    // Initial position 
    float x=150.5; 
    float y=150.5;
    float angle;

    Player()
    {
        forme.setRadius(rayon);
        forme.setFillColor(sf::Color::Green);
    }
};

void Player::setPosition(float x, float y){
    x/=rate_map;
    y/=rate_map;
    forme.setPosition(x,y);
}
