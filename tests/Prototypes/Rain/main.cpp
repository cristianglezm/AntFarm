#include <SFML/Graphics.hpp>

void explode(sf::Sprite& sprite,sf::Vector2f position,float radius,sf::VertexArray& liveParticles,sf::VertexArray& staticParticles){
    float xPos,yPos;
    int spriteHeight = sprite.getTextureRect().height;
    int spriteWidth = sprite.getTextureRect().width;
    int spritePosX = sprite.getTextureRect().left;
    int spritePosY = sprite.getTextureRect().top;
    for (xPos = position.x - radius;  xPos <= position.x + radius; xPos++) {
            for (yPos = position.y - radius;  yPos <= position.y + radius; yPos++) {
                if (sqrtf(xPos - position.x) + sqrtf(yPos - position.y) <= radius * radius) {
                    if((xPos > spritePosX && xPos < spriteWidth)&&(yPos > spritePosY && yPos < spriteHeight)){
                        liveParticles[spriteWidth * yPos + xPos] = staticParticles[spriteHeight * yPos  + xPos];
                        staticParticles[spriteWidth * yPos + xPos].color.a = 0;
                    }
                }
            }
    }
}
void explode2(sf::Sprite& sprite,sf::Vector2f position,sf::VertexArray& staticParticles){
    int spriteHeight = sprite.getTextureRect().height;
    int spriteWidth = sprite.getTextureRect().width;
    int spritePosX = sprite.getTextureRect().left;
    int spritePosY = sprite.getTextureRect().top;
    if((position.x > spritePosX && position.x < spriteWidth)&&(position.y > spritePosY && position.y < spriteHeight)){
            staticParticles[spriteWidth * position.y + position.x].color.a = 0;
    }
}
void explodeCircle(sf::Sprite& sprite,sf::Vector2f position,sf::VertexArray& staticParticles,int radius){
    int x = radius, y = 0;
    int radiusError = 1-x;
  while(x >= y){
    explode2(sprite,sf::Vector2f(x + position.x, y + position.y),staticParticles);
    explode2(sprite,sf::Vector2f(y + position.x, x + position.y),staticParticles);
    explode2(sprite,sf::Vector2f(-x + position.x, y + position.y),staticParticles);
    explode2(sprite,sf::Vector2f(-y + position.x, x + position.y),staticParticles);
    explode2(sprite,sf::Vector2f(-x + position.x, -y + position.y),staticParticles);
    explode2(sprite,sf::Vector2f(-y + position.x, -x + position.y),staticParticles);
    explode2(sprite,sf::Vector2f(x + position.x, -y + position.y),staticParticles);
    explode2(sprite,sf::Vector2f(y + position.x, -x + position.y),staticParticles);
    y++;
	if(radiusError<0)
		radiusError+=2*y+1;
	else{
		x--;
		radiusError+=2*(y-x+1);
	}
	if(radius > 0){
        --radius;
        explodeCircle(sprite,position,staticParticles,radius);
	}
  }
}
void mapParticles(sf::Sprite& sprite,sf::VertexArray& staticParticles){
    int SpriteWidth = sprite.getGlobalBounds().width;
    int SpriteHeight = sprite.getGlobalBounds().height;
    int spritePosX = sprite.getGlobalBounds().left;
    int spritePosY = sprite.getGlobalBounds().top;
    for(int y=spritePosY;y<SpriteHeight;++y){
            for(int x=spritePosX;x<SpriteWidth;++x){
                staticParticles[SpriteWidth * y + x].position = sf::Vector2f(x,y);
                staticParticles[SpriteWidth * y + x].texCoords = sf::Vector2f(x,y);
                staticParticles[SpriteWidth * y + x].color.a = 255;
            }
    }
}
float getFPS(const sf::Time& time) {
     return (1000000.0f / time.asMicroseconds());
}


int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "AntFarm");

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("../../../data/maps/nest/MapNestFrontground.png")){
        return EXIT_FAILURE;
    }
    sf::Texture texture1;
    if(!texture1.loadFromFile("../../../data/maps/nest/MapNestBackground.png")){
        return EXIT_FAILURE;
    }
    sf::Sprite background(texture1);
    sf::Sprite sprite(texture);
    sprite.setPosition(0,0);
    sf::View v{};
    bool pressedBtn = false;
    v.setViewport(sf::FloatRect(0,0,5,5));
    sf::VertexArray particles(sf::Points,sprite.getTextureRect().width * sprite.getTextureRect().height);
    sf::VertexArray liveParticles(sf::Points,sprite.getTextureRect().width * sprite.getTextureRect().height);
    mapParticles(sprite,particles);
    int TextureWidth = sprite.getTextureRect().width;
    int TextureHeight = sprite.getTextureRect().height;

    sf::VertexArray rain(sf::Points,5000);
    for(int i=0;i<5000;++i){
        rain[i].position = sf::Vector2f(rand()%1+i,0);
        rain[i].color = sf::Color::Blue;
        rain[i].color.a = 255;
    }
	// Start the game loop
	sf::Clock clock;
    while (app.isOpen()){
        // Process events
        sf::Event event;
        while (app.pollEvent(event)){
                switch(event.type){
                case sf::Event::Closed:
                    app.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                            sf::Vector2f position = app.mapPixelToCoords(sf::Mouse::getPosition(app));
                            explodeCircle(sprite,position,particles,60);
                    }
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                        liveParticles = particles;
                        particles = sf::VertexArray();
                    }
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::R){
                        mapParticles(sprite,particles);
                    }
                    if(event.key.code == sf::Keyboard::Left){
                        v.move(-10,0);
                    }
                    if(event.key.code == sf::Keyboard::Right){
                        v.move(10,0);
                    }
                    if(event.key.code == sf::Keyboard::Up){
                        v.move(0,-10);
                    }
                    if(event.key.code == sf::Keyboard::Down){
                        v.move(0,10);
                    }
                    if(event.key.code == sf::Keyboard::Add){
                        v.zoom(0.5);
                    }
                    if(event.key.code == sf::Keyboard::Subtract){
                        v.zoom(1.5);
                    }
                    break;
                }
        }
    /// Hover Mouse to destruct
    sf::Vector2f position = (sf::Vector2f) app.mapPixelToCoords(sf::Mouse::getPosition(app));
    //explode(sprite,position,3,liveParticles,particles);
    explodeCircle(sprite,position,particles,12);
    sf::Image ss();
        for(int i=0;i<5000;++i){
            if(i%5 == 0){
                ///rain[i].position = position - sf::Vector2f(i,i);
                rain[i].position += sf::Vector2f(0,0.5);
            }else{
                rain[i].position += sf::Vector2f(0,1);
                ///rain[i].position = position + sf::Vector2f(i,i);
            }
            if(particles[TextureWidth * rain[i].position.y + rain[i].position.x].color.a == 255){
                rain[i].position.y = 0;
                rain[i].position.x = rand()%1+i;
            }
        }


        // Clear screen
        app.clear();
        //app.setView(v);
        // Draw the sprite
        app.draw(background);
        app.draw(particles,&texture);
        app.draw(rain);
        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}

