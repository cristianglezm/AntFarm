#include <Systems/constructorSystem/Constructions.hpp>

namespace ant{
    constructorSystem::command Constructions::tunnel = [](Entity* e,sf::VertexArray* map,sf::FloatRect bounds){
        if(e->hasComponent(ComponentsMask::COMPONENT_BOUNDS) && e->hasComponent(ComponentsMask::COMPONENT_TRANSFORM)){
            auto& cTrans = e->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                ->getProperties<ComponentsAlias::transform>();
            auto& position = std::get<0>(cTrans);
            auto& rotation = std::get<2>(cTrans);
            auto& eBounds = std::get<0>(e->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                            ->getProperties<ComponentsAlias::bounds>());
            if(Utils::RectContains(eBounds,Config::screenSize)){
                if(rotation == -90){
                    sf::Vector2f currentPos = sf::Vector2f(position.x+eBounds.width,position.y + eBounds.height);
                    for(int x=currentPos.x;x<(currentPos.x + 20);++x){
                        for(int y=currentPos.y-1;y>(currentPos.y-eBounds.height-5);--y){
                            if(Config::screenSize.contains(x,y)){
                                if((*map)[bounds.height * x + y].color.a == 255){
                                    (*map)[bounds.height * x + y].color.a = 0;
                                }
                            }
                        }
                    }
                }else if(rotation == 90){
                    sf::Vector2f currentPos = sf::Vector2f(position.x,position.y + eBounds.height);
                    for(int x=currentPos.x;x>(currentPos.x - 20);--x){
                        for(int y=currentPos.y-1;y>(currentPos.y-eBounds.height-5);--y){
                            if(Config::screenSize.contains(x,y)){
                                if((*map)[bounds.height * x + y].color.a == 255){
                                    (*map)[bounds.height * x + y].color.a = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    };
    constructorSystem::command Constructions::uphill = [](Entity* e,sf::VertexArray* map,sf::FloatRect bounds){
        if(e->hasComponent(ComponentsMask::COMPONENT_BOUNDS) && e->hasComponent(ComponentsMask::COMPONENT_TRANSFORM)){
            auto& cTrans = e->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                ->getProperties<ComponentsAlias::transform>();
            auto& position = std::get<0>(cTrans);
            auto& rotation = std::get<2>(cTrans);
            auto& eBounds = std::get<0>(e->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                            ->getProperties<ComponentsAlias::bounds>());
            if(Utils::RectContains(eBounds,Config::screenSize)){
                if(rotation == -90){
                    sf::Vector2f currentPos = sf::Vector2f(position.x+eBounds.width,position.y + eBounds.height);
                    for(int x=currentPos.x;x<(currentPos.x + 10);++x){
                        for(int y=currentPos.y-5;y>(currentPos.y-eBounds.height-20);--y){
                            if(Config::screenSize.contains(x,y)){
                                if((*map)[bounds.height * x + y].color.a == 255){
                                    (*map)[bounds.height * x + y].color.a = 0;
                                }
                            }
                        }
                    }
                    position.y -=12;
                    position.x +=5;
                }else if(rotation == 90){
                    sf::Vector2f currentPos = sf::Vector2f(position.x,position.y + eBounds.height);
                    for(int x=currentPos.x;x>(currentPos.x-10);--x){
                        for(int y=currentPos.y-5;y>(currentPos.y-eBounds.height-20);--y){
                            if(Config::screenSize.contains(x,y)){
                                if((*map)[bounds.height * x + y].color.a == 255){
                                    (*map)[bounds.height * x + y].color.a = 0;
                                }
                            }
                        }
                    }
                    position.y -=12;
                    position.x -=5;
                }
                Constructions::tunnel(e,map,bounds);
            }
        }
    };
    constructorSystem::command Constructions::downhill = [](Entity* e,sf::VertexArray* map,sf::FloatRect bounds){
        if(e->hasComponent(ComponentsMask::COMPONENT_BOUNDS) && e->hasComponent(ComponentsMask::COMPONENT_TRANSFORM)){
            auto& cTrans = e->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                ->getProperties<ComponentsAlias::transform>();
            auto& position = std::get<0>(cTrans);
            auto& rotation = std::get<2>(cTrans);
            auto& eBounds = std::get<0>(e->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                            ->getProperties<ComponentsAlias::bounds>());
            if(Utils::RectContains(eBounds,Config::screenSize)){
                if(rotation == -90){
                    sf::Vector2f currentPos = sf::Vector2f(position.x+eBounds.width,position.y + eBounds.height);
                    for(int x=currentPos.x;x<(currentPos.x + 10);++x){
                        for(int y=currentPos.y+5;y>(currentPos.y-eBounds.height-20);--y){
                            if(Config::screenSize.contains(x,y)){
                                if((*map)[bounds.height * x + y].color.a == 255){
                                    (*map)[bounds.height * x + y].color.a = 0;
                                }
                            }
                        }
                    }
                    position.y +=12;
                    position.x +=8;
                }else if(rotation == 90){
                    sf::Vector2f currentPos = sf::Vector2f(position.x,position.y + eBounds.height);
                    for(int x=currentPos.x;x>(currentPos.x-10);--x){
                        for(int y=currentPos.y+5;y>(currentPos.y-eBounds.height-20);--y){
                            if(Config::screenSize.contains(x,y)){
                                if((*map)[bounds.height * x + y].color.a == 255){
                                    (*map)[bounds.height * x + y].color.a = 0;
                                }
                            }
                        }
                    }
                    position.y +=12;
                    position.x -=8;
                }
                Constructions::tunnel(e,map,bounds);
            }
        }
    };
    constructorSystem::command Constructions::climb = [](Entity* e,sf::VertexArray* map,sf::FloatRect bounds){
        if(e->hasComponent(ComponentsMask::COMPONENT_COUNT)){
            auto& count = std::get<0>(e->getComponent(ComponentsMask::COMPONENT_COUNT)->getProperties<ComponentsAlias::count>());
            if(count == 9){
                count = 10;
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
            auto& count = std::get<0>(e->getComponent(ComponentsMask::COMPONENT_COUNT)->getProperties<ComponentsAlias::count>());
            if(count <= 0){
                e->removeState(States::BUILDING);
                e->removeState(States::CLIMBING);
            }
        }
    };
    constructorSystem::command Constructions::wall = [](Entity* e,sf::VertexArray* map,sf::FloatRect bounds){
        if(e->hasComponent(ComponentsMask::COMPONENT_BOUNDS) && e->hasComponent(ComponentsMask::COMPONENT_TRANSFORM)){
            auto& cTrans = e->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                ->getProperties<ComponentsAlias::transform>();
            auto& position = std::get<0>(cTrans);
            auto& rotation = std::get<2>(cTrans);
            auto& eBounds = std::get<0>(e->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                            ->getProperties<ComponentsAlias::bounds>());
            if(Utils::RectContains(eBounds,Config::screenSize)){
                if(rotation == -90){
                    int j;
                    for(int i=(position.x+eBounds.width);i<(position.x+eBounds.width+10);++i){
                        for(j=(position.y+eBounds.height);j>((position.y+eBounds.height)-50);--j){
                            if(Config::screenSize.contains(i,j)){
                                if((*map)[bounds.height * i + j].color.a == 0){
                                    (*map)[bounds.height * i + j].color = Grey;
                                }
                            }
                        }
                        if(Config::screenSize.contains(i,j)){
                            if((*map)[bounds.height * i + j].color.a == 0){
                                (*map)[bounds.height * i + j].color = lightGrey;
                            }
                        }
                    }
                    position.y -= 5;
                    position.x -= 5;
                }else if(rotation == 90){
                    int j;
                    for(int i=position.x;i>(position.x-10);--i){
                        for(j=(position.y+eBounds.height);j>((position.y+eBounds.height)-50);--j){
                            if(Config::screenSize.contains(i,j)){
                                if((*map)[bounds.height * i + j].color.a == 0){
                                    (*map)[bounds.height * i + j].color = Grey;
                                }
                            }
                        }
                        if(Config::screenSize.contains(i,j)){
                            if((*map)[bounds.height * i + j].color.a == 0){
                                (*map)[bounds.height * i + j].color = lightGrey;
                            }
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
                                ->getProperties<ComponentsAlias::transform>();
            auto& position = std::get<0>(cTrans);
            auto& rotation = std::get<2>(cTrans);
            auto& eBounds = std::get<0>(e->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                            ->getProperties<ComponentsAlias::bounds>());
            if(Utils::RectContains(eBounds,Config::screenSize)){
                if(rotation == -90){
                    sf::Vector2f currentPos(position.x+eBounds.width,position.y+eBounds.height);
                    for(int x=currentPos.x;x<(currentPos.x+15);++x){
                        for(int i=0;i<2;++i){
                            if(Config::screenSize.contains(x,(currentPos.y-i))){
                                if((*map)[bounds.height * x + (currentPos.y-i)].color.a == 0){
                                    (*map)[bounds.height * x + (currentPos.y-i)].color = Grey;
                                }
                            }
                        }
                        if(Config::screenSize.contains(x,currentPos.y)){
                            if((*map)[bounds.height * x + (currentPos.y)].color.a == 0){
                                (*map)[bounds.height * x + currentPos.y].color = Grey;
                            }
                        }
                        for(int i=0;i<2;++i){
                            if(Config::screenSize.contains(x,(currentPos.y+i))){
                                if((*map)[bounds.height * x + (currentPos.y+i)].color.a == 0){
                                    (*map)[bounds.height * x + (currentPos.y+i)].color = lightGrey;
                                }
                            }
                        }
                    }
                }else if(rotation == 90){
                    sf::Vector2f currentPos(position.x,position.y+eBounds.height);
                    for(int x=currentPos.x;x>(currentPos.x-15);--x){
                        for(int i=0;i<2;++i){
                            if(Config::screenSize.contains(x,(currentPos.y-i))){
                                if((*map)[bounds.height * x + (currentPos.y-i)].color.a == 0){
                                    (*map)[bounds.height * x + (currentPos.y-i)].color = Grey;
                                }
                            }
                        }
                        if(Config::screenSize.contains(x,currentPos.y)){
                            if((*map)[bounds.height * x + currentPos.y].color.a == 0){
                                (*map)[bounds.height * x + currentPos.y].color = Grey;
                            }
                        }
                        for(int i=0;i<2;++i){
                            if(Config::screenSize.contains(x,(currentPos.y+i))){
                                if((*map)[bounds.height * x + (currentPos.y+i)].color.a ==0){
                                    (*map)[bounds.height * x + (currentPos.y+i)].color = lightGrey;
                                }
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
                                ->getProperties<ComponentsAlias::transform>();
            auto& position = std::get<0>(cTrans);
            auto& rotation = std::get<2>(cTrans);
            auto& eBounds = std::get<0>(e->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                            ->getProperties<ComponentsAlias::bounds>());
            if(Utils::RectContains(eBounds,Config::screenSize)){
                if(rotation == -90){
                    int j;
                    for(int i=(position.x+eBounds.width);i<(position.x+eBounds.width+20);++i){
                        for(j=(position.y+eBounds.height);j>((position.y+eBounds.height)-10);--j){
                            if(Config::screenSize.contains(i,j)){
                                if((*map)[bounds.height * i + j].color.a == 0){
                                    (*map)[bounds.height * i + j].color = Grey;
                                }
                            }
                        }
                        if(Config::screenSize.contains(i,j)){
                            if((*map)[bounds.height * i + j].color.a == 0){
                                (*map)[bounds.height * i + j].color = lightGrey;
                            }
                        }
                    }
                    position.y -= 10;
                    position.x += 15;
                }else if(rotation == 90){
                    int j;
                    for(int i=position.x;i>(position.x-20);--i){
                        for(j=(position.y+eBounds.height);j>((position.y+eBounds.height)-10);--j){
                            if(Config::screenSize.contains(i,j)){
                                if((*map)[bounds.height * i + j].color.a == 0){
                                    (*map)[bounds.height * i + j].color = Grey;
                                }
                            }
                        }
                        if(Config::screenSize.contains(i,j)){
                            if((*map)[bounds.height * i + j].color.a == 0){
                                (*map)[bounds.height * i + j].color = lightGrey;
                            }
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
                                ->getProperties<ComponentsAlias::transform>();
            auto& position = std::get<0>(cTrans);
            auto& eBounds = std::get<0>(e->getComponent(ComponentsMask::COMPONENT_BOUNDS)
                                            ->getProperties<ComponentsAlias::bounds>());
            sf::Vector2f currentPos = sf::Vector2f(position.x,
                                                   position.y + eBounds.height);
            if(Utils::RectContains(eBounds,Config::screenSize)){
                for(int x=currentPos.x-10;x<(currentPos.x+eBounds.width+10);++x){
                    for(int y=currentPos.y-1;y<(currentPos.y+10);++y){
                        if(Config::screenSize.contains(x,y)){
                            if((*map)[bounds.height * x + y].color.a == 255){
                                (*map)[bounds.height * x + y].color.a = 0;
                            }
                        }
                    }
                }
            }
        }
    };
    constructorSystem::command Constructions::explosion = [](Entity* e, sf::VertexArray* map,sf::FloatRect bounds){
        auto rm = [map,bounds](const sf::Vector2f& pos){
            if(bounds.contains(pos)){
                if((*map)[bounds.height * pos.x + pos.y].color.a == 255){
                    (*map)[bounds.height * pos.x + pos.y].color.a = 0;
                }
            }
        };
        if(e->hasComponent(ComponentsMask::COMPONENT_TRANSFORM)){
            auto& cTrans = e->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                ->getProperties<ComponentsAlias::transform>();
            auto& position = std::get<0>(cTrans);
            std::function<void(int,const sf::Vector2f&)> explode;
            explode = [&rm,&explode](int radius,const sf::Vector2f& pos){
                int x = radius, y = 0;
                int radiusError = 1-x;
                while(x >= y){
                    rm(sf::Vector2f(x + pos.x, y + pos.y));
                    rm(sf::Vector2f(y + pos.x, x + pos.y));
                    rm(sf::Vector2f(-x + pos.x, y + pos.y));
                    rm(sf::Vector2f(-y + pos.x, x + pos.y));
                    rm(sf::Vector2f(-x + pos.x, -y + pos.y));
                    rm(sf::Vector2f(-y + pos.x, -x + pos.y));
                    rm(sf::Vector2f(x + pos.x, -y + pos.y));
                    rm(sf::Vector2f(y + pos.x, -x + pos.y));
                    ++y;
                    if(radiusError<0){
                        radiusError+=2*y+1;
                    }else{
                        --x;
                        radiusError+=2*(y-x+1);
                    }
                }
                if(radius > 0){
                    explode(--radius,pos);
                }
            };
            explode(40,position);
            e->addState(States::UNSAVED);
        }
    };
    // Colors
    sf::Color Constructions::Grey(128,128,128,255);
    sf::Color Constructions::lightGrey(192,192,192,255);
    sf::Color Constructions::Brown(128,64,0,255);
    sf::Color Constructions::lightBrown(150,75,0,255);
}
