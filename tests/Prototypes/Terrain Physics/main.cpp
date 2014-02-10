#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
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
            }
    }
}
float getFPS(const sf::Time& time) {
     return (1000000.0f / time.asMicroseconds());
}


int main()
{
    float counterX=0,counterY=0;
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "AntFarm");
    sf::RectangleShape winBorders{};
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("data/MapNestFrontground.png")){
        return EXIT_FAILURE;
    }
    sf::Texture texture1;
    if(!texture1.loadFromFile("data/MapNestBackground.png")){
        return EXIT_FAILURE;
    }
    sf::Sprite background(texture1);
    sf::Sprite sprite(texture);
    sprite.setPosition(0,0);
    sf::RectangleShape r{};
    sf::View v{};
    bool pressedBtn = false;
    v.setViewport(sf::FloatRect(0,0,5,5));
    sf::View v2{};
    v2.setViewport(sf::FloatRect{0.75f, 0, 0.25f, 0.25f});
    sf::VertexArray particles(sf::Points,sprite.getTextureRect().width * sprite.getTextureRect().height);
    sf::VertexArray liveParticles(sf::Points,sprite.getTextureRect().width * sprite.getTextureRect().height);
    mapParticles(sprite,particles);
    int TextureWidth = sprite.getTextureRect().width;
    int TextureHeight = sprite.getTextureRect().height;

    sf::VertexArray rain(sf::Points,500);
    for(int i=0;i<500;++i){
        rain[i].position = sf::Vector2f(0,0);
        rain[i].color = sf::Color::Red;
    }
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
                            sf::Vector2i position = app.mapCoordsToPixel((sf::Vector2f) sf::Mouse::getPosition(app));
                            system("cls");
                            std::cout << "X: " << position.x << std::endl;
                            std::cout << "Y: " << position.y << std::endl;
                            explode(sprite,(sf::Vector2f)position,60,liveParticles,particles);
                            //explodeCircle(sprite,(sf::Vector2f)position,particles,60);
                    }
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                        liveParticles = particles;
                        particles = sf::VertexArray();
                    }
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::D){
                        sprite.setRotation(sprite.getRotation()+10);
                    }
                    if(event.key.code == sf::Keyboard::A){
                        sprite.setRotation(sprite.getRotation()-10);
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
                        v.setSize(v.getSize().x-10,v.getSize().y-10);
                    }
                    if(event.key.code == sf::Keyboard::Subtract){
                        v.setSize(v.getSize().x+10,v.getSize().y+10);
                    }
                    break;
                }
        }
        //sprite.setPosition(sprite.getPosition().x+(0.3f * sin(sprite.getRotation()* (3.14159265 /180))),
        //                   sprite.getPosition().y+(0.3f * -cos(sprite.getRotation()* (3.14159265 /180))));
        r.setTextureRect((sf::Rect<int>) sprite.getGlobalBounds());
        r.setPosition(sprite.getPosition());
        r.setRotation(sprite.getRotation());
        r.setSize(sf::Vector2f(sprite.getGlobalBounds().width,sprite.getGlobalBounds().height));
        r.setFillColor(sf::Color::Transparent);
        r.setOutlineColor(sf::Color::Red);
        r.setOutlineThickness(5);

        winBorders.setSize((sf::Vector2f)app.getSize()-sf::Vector2f(4,4));
        winBorders.setPosition(2,2);
        winBorders.setFillColor(sf::Color::Transparent);
        winBorders.setOutlineColor(sf::Color::Red);
        winBorders.setOutlineThickness(5);
        /// Hover Mouse to destruct
    sf::Vector2f position = (sf::Vector2f) app.mapCoordsToPixel((sf::Vector2f) sf::Mouse::getPosition(app),v);
    explode(sprite,position,3,liveParticles,particles);
    //explode2(sprite,position,particles);
    std::cout << "\nPosition : " << position.x << "," << position.y << std::endl;
        for(int y=0;y<TextureHeight;++y){
            for(int x=0;x<TextureWidth;++x){
                    if(liveParticles[TextureWidth * y + x].position.y < 400){
                            liveParticles[TextureHeight * y + x].position += sf::Vector2f(0,1);
                    }
            }
        }
        for(int i=0;i<500;++i){
            rain[i].position += sf::Vector2f(0,0.1);
        }


        // Clear screen
        app.clear();
        app.setView(v);
        // Draw the sprite
        app.draw(background);
        //app.draw(r);
        app.draw(winBorders);
        app.draw(particles,&texture);
        app.draw(liveParticles,&texture);
        app.draw(rain);
        // Update the window
        app.display();
        system("cls");
        std::cout << "FPS: " << getFPS(clock.restart());
    }

    return EXIT_SUCCESS;
}

