#include <iostream>
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
void explode2(sf::Sprite& sprite,sf::Vector2f position,sf::VertexArray& staticParticles,sf::VertexArray& heightMap){
    int spriteHeight = sprite.getTextureRect().height;
    int spriteWidth = sprite.getTextureRect().width;
    int spritePosX = sprite.getTextureRect().left;
    int spritePosY = sprite.getTextureRect().top;
    if((position.x > spritePosX && position.x < spriteWidth)&&(position.y > spritePosY && position.y < spriteHeight)){
            if(heightMap[spriteWidth * position.y + position.x].color == sf::Color::White){
                staticParticles[spriteWidth * position.y + position.x].color.a = 0;
            }
    }
}
void explodeCircle(sf::Sprite& sprite,sf::Vector2f position,sf::VertexArray& staticParticles,int radius,sf::VertexArray& heightMap){
    int x = radius, y = 0;
    int radiusError = 1-x;
  while(x >= y){
    explode2(sprite,sf::Vector2f(x + position.x, y + position.y),staticParticles,heightMap);
    explode2(sprite,sf::Vector2f(y + position.x, x + position.y),staticParticles,heightMap);
    explode2(sprite,sf::Vector2f(-x + position.x, y + position.y),staticParticles,heightMap);
    explode2(sprite,sf::Vector2f(-y + position.x, x + position.y),staticParticles,heightMap);
    explode2(sprite,sf::Vector2f(-x + position.x, -y + position.y),staticParticles,heightMap);
    explode2(sprite,sf::Vector2f(-y + position.x, -x + position.y),staticParticles,heightMap);
    explode2(sprite,sf::Vector2f(x + position.x, -y + position.y),staticParticles,heightMap);
    explode2(sprite,sf::Vector2f(y + position.x, -x + position.y),staticParticles,heightMap);
    y++;
	if(radiusError<0)
		radiusError+=2*y+1;
	else{
		x--;
		radiusError+=2*(y-x+1);
	}
	if(radius > 0){
        --radius;
        explodeCircle(sprite,position,staticParticles,radius,heightMap);
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
void mapImage(sf::Image& image,sf::VertexArray& staticParticles){
    int imageWidth = image.getSize().x;
    int imageHeight = image.getSize().y;
    for(int y = 0;y<imageHeight;++y){
        for(int x = 0;x<imageWidth;++x){
            staticParticles[imageWidth * y + x].color = image.getPixel(x,y);
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
    sf::Image* heightMapImage = new sf::Image();
    if(!heightMapImage->loadFromFile("../../../data/maps/nest/MapNestHeightMap.png")){
        return EXIT_FAILURE;
    }
    sf::Sprite background(texture1);
    sf::Sprite sprite(texture);
    sprite.setPosition(0,0);
    sf::VertexArray particles(sf::Points,sprite.getTextureRect().width * sprite.getTextureRect().height);
    sf::VertexArray heightMap(sf::Points,sprite.getTextureRect().width * sprite.getTextureRect().height);
    mapParticles(sprite,particles);
    mapImage(*heightMapImage,heightMap);
    delete heightMapImage;
    int TextureWidth = sprite.getTextureRect().width;
    int TextureHeight = sprite.getTextureRect().height;

	// Start the game loop
	sf::Time elapsedTime;
	sf::Time lastFrame;
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
                        //sprite.setPosition(sf::Mouse::getPosition(app).x,sf::Mouse::getPosition(app).y);
                            sf::Vector2f position = app.mapPixelToCoords(sf::Mouse::getPosition(app));
                            //explode(sprite,(sf::Vector2f)position,60,liveParticles,particles);
                            explodeCircle(sprite,position,particles,500,heightMap);
                    }
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::D){
                        sprite.setRotation(sprite.getRotation()+10);
                    }
                    if(event.key.code == sf::Keyboard::A){
                        sprite.setRotation(sprite.getRotation()-10);
                    }
                    if(event.key.code == sf::Keyboard::R){
                        mapParticles(sprite,particles);
                    }
                    break;
                }
        }
    /// Hover Mouse to destruct
    sf::Vector2f position = (sf::Vector2f) app.mapPixelToCoords(sf::Mouse::getPosition(app));
    //explode(sprite,position,3,liveParticles,particles);
    explodeCircle(sprite,position,particles,12,heightMap);
        // Clear screen
        app.clear();
        // Draw the sprite
        app.draw(background);
        app.draw(particles,&texture);
        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}

