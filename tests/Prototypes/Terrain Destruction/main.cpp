#include <iostream>
#include <sstream>
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
	if(radiusError<0){
        radiusError+=2*y+1;
	}else{
		x--;
		radiusError+=2*(y-x+1);
	}
  }
  if(radius > 0){
    --radius;
    explodeCircle(sprite,position,staticParticles,radius);
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
std::string toString(int s){
    std::ostringstream oss;
    oss << s;
    return oss.str();
}

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "AntFarm");
    app.setFramerateLimit(0);
    app.setVerticalSyncEnabled(false);
    sf::RectangleShape winBorders{};
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("../../../data/backgrounds/background3.png")){
        return EXIT_FAILURE;
    }
    sf::Texture texture1;
    if(!texture1.loadFromFile("../../../data/backgrounds/background1.png")){
        return EXIT_FAILURE;
    }
    sf::Sprite background(texture1);
    sf::Sprite sprite(texture);
    sprite.setPosition(0,0);

    sf::VertexArray particles(sf::Points,sprite.getTextureRect().width * sprite.getTextureRect().height);
    sf::VertexArray liveParticles(sf::Points,sprite.getTextureRect().width * sprite.getTextureRect().height);
    mapParticles(sprite,particles);

	// Start the game loop
	sf::Time elapsedTime;
	sf::Time lastFrame;
	sf::Clock clock;
	sf::Text fps;
	sf::Font font;
	if(!font.loadFromFile("../../../data/fonts/OLDFAX.ttf")){
        return EXIT_FAILURE;
	}
	fps.setFont(font);
	fps.setCharacterSize(25);
    fps.setPosition(745,550);
    bool running=true;
    while (running){
        // Process events
        int FPS = getFPS(clock.restart());
        /// TODO
        fps.setString(toString(FPS));
        if(FPS < 5){
            fps.setColor(sf::Color::Red);
        }else if(FPS > 50){
            fps.setColor(sf::Color::Green);
        }else if(FPS < 40){
            fps.setColor(sf::Color::Yellow);
        }
        sf::Event event;
        while (app.pollEvent(event)){
                switch(event.type){
                case sf::Event::Closed:
                    running = false;
                    break;
                case sf::Event::MouseButtonPressed:
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        sf::Vector2f position =(sf::Vector2f)app.mapPixelToCoords(sf::Mouse::getPosition(app));
                        //explode(sprite,position,60,liveParticles,particles);
                        explodeCircle(sprite,(sf::Vector2f)position,particles,500);
                    }
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                        liveParticles = particles;
                        particles = sf::VertexArray();
                    }
                    break;
                case sf::Event::KeyPressed:
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                            mapParticles(sprite,particles);
                        }
                    break;
                }
        }
    /// Hover Mouse to destruct
    sf::Vector2f position = (sf::Vector2f) app.mapPixelToCoords(sf::Mouse::getPosition(app));
    //explode(sprite,position,21,liveParticles,particles);
    /// Only One
    //explode2(sprite,position,particles);
    /// Circle
    explodeCircle(sprite,position,particles,16);
        // Clear screen
        app.clear();
        // Draw the sprite
        app.draw(background);
        app.draw(particles,&texture);
        // Update the window
        app.draw(fps);
        app.display();
    }
    app.close();
    return EXIT_SUCCESS;
}

