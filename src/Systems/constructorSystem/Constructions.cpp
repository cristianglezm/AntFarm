#include <Systems/constructorSystem/Constructions.hpp>

namespace ant{
    constructorSystem::command Constructions::tunnel = [](Entity* e,sf::VertexArray* map,sf::FloatRect bounds){
        if(e->hasComponent(ComponentsMask::COMPONENT_BOUNDS) && e->hasComponent(ComponentsMask::COMPONENT_TRANSFORM)){
            auto& cTrans = e->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                ->getProperties<sf::Vector2f,sf::Vector2f,float>();
            auto& position = std::get<0>(cTrans);
            auto& rotation = std::get<2>(cTrans);
            auto& eBounds = std::get<0>(e->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                            ->getProperties<sf::FloatRect>());
            if(Utils::RectContains(eBounds,Config::screenSize)){
                if(rotation == -90){
                    sf::Vector2f currentPos = sf::Vector2f(position.x+eBounds.width,position.y + eBounds.height);
                    for(int x=currentPos.x;x<(currentPos.x + 10);++x){
                        for(int y=currentPos.y;y>(currentPos.y-eBounds.height);--y){
                            if(Config::screenSize.contains(x,y)){
                                (*map)[bounds.height * x + y].color.a = 0;
                            }
                        }
                    }
                }else if(rotation == 90){
                    sf::Vector2f currentPos = sf::Vector2f(position.x,position.y + eBounds.height);
                    for(int x=currentPos.x;x>(currentPos.x-10);--x){
                        for(int y=currentPos.y;y>(currentPos.y-eBounds.height);--y){
                            if(Config::screenSize.contains(x,y)){
                                (*map)[bounds.height * x + y].color.a = 0;
                            }
                        }
                    }
                }
            }
        }
    };
    constructorSystem::command Constructions::climb = [](Entity* e,sf::VertexArray* map,sf::FloatRect bounds){
        if(e->hasComponent(ComponentsMask::COMPONENT_COUNT)){
            auto& count = std::get<0>(e->getComponent(ComponentsMask::COMPONENT_COUNT)->getProperties<int>());
            if(count == 9){
                count = 20;
            }
            if(count <= 0){
                e->removeState(States::CLIMBING);
            }else{
                e->addState(States::CLIMBING);
            }
        }
    };
    constructorSystem::command Constructions::stop = [](Entity* e,sf::VertexArray* map,sf::FloatRect bounds){
        if(e->hasComponent(ComponentsMask::COMPONENT_COUNT)){
            auto& count = std::get<0>(e->getComponent(ComponentsMask::COMPONENT_COUNT)->getProperties<int>());
            if(count <= 0){
                e->removeState(States::BUILDING);
                e->removeState(States::CLIMBING);
            }
        }
    };
    constructorSystem::command Constructions::wall = [](Entity* e,sf::VertexArray* map,sf::FloatRect bounds){
        if(e->hasComponent(ComponentsMask::COMPONENT_BOUNDS) && e->hasComponent(ComponentsMask::COMPONENT_TRANSFORM)){
            auto& cTrans = e->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                ->getProperties<sf::Vector2f,sf::Vector2f,float>();
            auto& position = std::get<0>(cTrans);
            auto& rotation = std::get<2>(cTrans);
            auto& eBounds = std::get<0>(e->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                            ->getProperties<sf::FloatRect>());
            if(Utils::RectContains(eBounds,Config::screenSize)){
                if(rotation == -90){
                    int j;
                    for(int i=(position.x+eBounds.width);i<(position.x+eBounds.width+10);++i){
                        for(j=(position.y+eBounds.height);j>((position.y+eBounds.height)-50);--j){
                            if(Config::screenSize.contains(i,j)){
                                (*map)[bounds.height * i + j].color = Grey;
                            }
                        }
                        if(Config::screenSize.contains(i,j)){
                            (*map)[bounds.height * i + j].color = lightGrey;
                        }
                    }
                    position.y -= 5;
                    position.x -= 5;
                }else if(rotation == 90){
                    int j;
                    for(int i=position.x;i>(position.x-10);--i){
                        for(j=(position.y+eBounds.height);j>((position.y+eBounds.height)-50);--j){
                            if(Config::screenSize.contains(i,j)){
                                (*map)[bounds.height * i + j].color = Grey;
                            }
                        }
                        if(Config::screenSize.contains(i,j)){
                            (*map)[bounds.height * i + j].color = lightGrey;
                        }
                    }
                    position.y -= 5;
                    position.x += 5;
                }
            }
        }
    };
    constructorSystem::command Constructions::bridge = [](Entity* e,sf::VertexArray* map,sf::FloatRect bounds){
        if(e->hasComponent(ComponentsMask::COMPONENT_BOUNDS) && e->hasComponent(ComponentsMask::COMPONENT_TRANSFORM)){
            auto& cTrans = e->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                ->getProperties<sf::Vector2f,sf::Vector2f,float>();
            auto& position = std::get<0>(cTrans);
            auto& rotation = std::get<2>(cTrans);
            auto& eBounds = std::get<0>(e->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                            ->getProperties<sf::FloatRect>());
            if(Utils::RectContains(eBounds,Config::screenSize)){
                if(rotation == -90){
                    sf::Vector2f currentPos(position.x+eBounds.width,position.y+eBounds.height);
                    for(int x=currentPos.x;x<(currentPos.x+15);++x){
                        for(int i=0;i<2;++i){
                            if(Config::screenSize.contains(x,(currentPos.y-i))){
                                (*map)[bounds.height * x + (currentPos.y-i)].color = Grey;
                            }
                        }
                        if(Config::screenSize.contains(x,currentPos.y)){
                            (*map)[bounds.height * x + currentPos.y].color = Grey;
                        }
                        for(int i=0;i<2;++i){
                            if(Config::screenSize.contains(x,(currentPos.y+i))){
                                (*map)[bounds.height * x + (currentPos.y+i)].color = lightGrey;
                            }
                        }
                    }
                }else if(rotation == 90){
                    sf::Vector2f currentPos(position.x,position.y+eBounds.height);
                    for(int x=currentPos.x;x>(currentPos.x-15);--x){
                        for(int i=0;i<2;++i){
                            if(Config::screenSize.contains(x,(currentPos.y-i))){
                                (*map)[bounds.height * x + (currentPos.y-i)].color = Grey;
                            }
                        }
                        if(Config::screenSize.contains(x,currentPos.y)){
                            (*map)[bounds.height * x + currentPos.y].color = Grey;
                        }
                        for(int i=0;i<2;++i){
                            if(Config::screenSize.contains(x,(currentPos.y+i))){
                                (*map)[bounds.height * x + (currentPos.y+i)].color = lightGrey;
                            }
                        }
                    }
                }
            }
        }
    };
    constructorSystem::command Constructions::stairs = [](Entity* e,sf::VertexArray* map,sf::FloatRect bounds){
        if(e->hasComponent(ComponentsMask::COMPONENT_BOUNDS) && e->hasComponent(ComponentsMask::COMPONENT_TRANSFORM)){
            auto& cTrans = e->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                ->getProperties<sf::Vector2f,sf::Vector2f,float>();
            auto& position = std::get<0>(cTrans);
            auto& rotation = std::get<2>(cTrans);
            auto& eBounds = std::get<0>(e->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                            ->getProperties<sf::FloatRect>());
            if(Utils::RectContains(eBounds,Config::screenSize)){
                if(rotation == -90){
                    int j;
                    for(int i=(position.x+eBounds.width);i<(position.x+eBounds.width+20);++i){
                        for(j=(position.y+eBounds.height);j>((position.y+eBounds.height)-10);--j){
                            if(Config::screenSize.contains(i,j)){
                                (*map)[bounds.height * i + j].color = Grey;
                            }
                        }
                        if(Config::screenSize.contains(i,j)){
                            (*map)[bounds.height * i + j].color = lightGrey;
                        }
                    }
                    position.y -= 10;
                    position.x += 15;
                }else if(rotation == 90){
                    int j;
                    for(int i=position.x;i>(position.x-20);--i){
                        for(j=(position.y+eBounds.height);j>((position.y+eBounds.height)-10);--j){
                            if(Config::screenSize.contains(i,j)){
                                (*map)[bounds.height * i + j].color = Grey;
                            }
                        }
                        if(Config::screenSize.contains(i,j)){
                            (*map)[bounds.height * i + j].color = lightGrey;
                        }
                    }
                    position.y -= 10;
                    position.x -= 15;
                }
            }
        }
    };
    constructorSystem::command Constructions::hole = [](Entity* e,sf::VertexArray* map,sf::FloatRect bounds){
        if(e->hasComponent(ComponentsMask::COMPONENT_BOUNDS) && e->hasComponent(ComponentsMask::COMPONENT_TRANSFORM)){
            auto& cTrans = e->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                ->getProperties<sf::Vector2f,sf::Vector2f,float>();
            auto& position = std::get<0>(cTrans);
            auto& eBounds = std::get<0>(e->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                            ->getProperties<sf::FloatRect>());
            sf::Vector2f currentPos = sf::Vector2f(position.x,
                                                   position.y + eBounds.height);
            if(Utils::RectContains(eBounds,Config::screenSize)){
                for(int x=currentPos.x-10;x<(currentPos.x+eBounds.width+10);++x){
                    for(int y=currentPos.y;y<(currentPos.y+10);++y){
                        if(Config::screenSize.contains(x,y)){
                            (*map)[bounds.height * x + y].color.a = 0;
                        }
                    }
                }
            }
        }
    };
    // Colors
    sf::Color Constructions::Grey(128,128,128,255);
    sf::Color Constructions::lightGrey(192,192,192,255);
    sf::Color Constructions::Brown(128,64,0,255);
    sf::Color Constructions::lightBrown(150,75,0,255);
}
