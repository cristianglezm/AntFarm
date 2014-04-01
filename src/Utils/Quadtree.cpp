#include <Utils/Quadtree.hpp>
#include <Components/ComponentMask.hpp>

namespace ant{
    namespace Utils{
        void Quadtree::split(){
            int subWidth = (int)(bounds.width / 2);
            int subHeight = (int)(bounds.height / 2);
            int x = (int)bounds.left;
            int y = (int)bounds.top;
            nodes[0].reset(new Quadtree((level+1), sf::FloatRect(x + subWidth, y, subWidth, subHeight)));
            nodes[1].reset(new Quadtree((level+1), sf::FloatRect(x, y, subWidth, subHeight)));
            nodes[2].reset(new Quadtree((level+1), sf::FloatRect(x, y + subHeight, subWidth, subHeight)));
            nodes[3].reset(new Quadtree((level+1), sf::FloatRect(x + subWidth, y + subHeight, subWidth, subHeight)));
        }
        int Quadtree::getIndex(Entity* e){
                int index = -1;
                double verticalMidpoint = bounds.left + (bounds.width / 2);
                double horizontalMidpoint = bounds.top + (bounds.height / 2);
                // Object can completely fit within the top quadrants
                auto& properties = e->getComponent(ComponentsMask::COMPONENT_BOUNDS)->getProperties<sf::FloatRect>();
                sf::FloatRect eBounds = std::get<0>(properties);
                bool topQuadrant = (eBounds.top < horizontalMidpoint && eBounds.top + eBounds.height < horizontalMidpoint);
                // Object can completely fit within the bottom quadrants
                bool bottomQuadrant = (eBounds.top > horizontalMidpoint);
                // Object can completely fit within the left quadrants
                if (eBounds.left < verticalMidpoint && eBounds.left + eBounds.width < verticalMidpoint) {
                    if(topQuadrant) {
                        index = 1;
                    }else if(bottomQuadrant) {
                        index = 2;
                    }
                }
                // Object can completely fit within the right quadrants
                else if (eBounds.left > verticalMidpoint) {
                    if (topQuadrant) {
                        index = 0;
                    }else if(bottomQuadrant){
                        index = 3;
                    }
                }
                return index;
        }
        Quadtree::Quadtree(int level){
            this->level = level;
            nodes[0] = nullptr;
            nodes[1] = nullptr;
            nodes[2] = nullptr;
            nodes[3] = nullptr;
        }
        Quadtree::Quadtree(int level,sf::FloatRect bounds){
            this->level = level;
            this->bounds = bounds;
            nodes[0] = nullptr;
            nodes[1] = nullptr;
            nodes[2] = nullptr;
            nodes[3] = nullptr;
        }
        Quadtree::Quadtree(sf::FloatRect bounds){
            this->bounds = bounds;
            this->level = 0;
            nodes[0] = nullptr;
            nodes[1] = nullptr;
            nodes[2] = nullptr;
            nodes[3] = nullptr;
        }
        void Quadtree::insert(Entity* e){
               if (nodes[0] != nullptr) {
                    int index = this->getIndex(e);
                    if (index != -1) {
                        nodes[index]->insert(e);
                        return;
                    }
                }
                entities.push_back(e);

                if(entities.size() > this->MAX_CAPACITY && level < this->MAX_LEVEL){
                    if(nodes[0] == nullptr) {
                        this->split();
                    }
                    std::list<Entity*>::iterator i = entities.begin();
                    while(i != entities.end()){
                        int index = getIndex(*i);
                        if(index != -1){
                            nodes[index]->insert(*i);
                            entities.erase(i++);
                        }else{
                            ++i;
                        }
                    }
                }
        }
        void Quadtree::clear(){
            entities.clear();
            for(int i = 0; i < nodes.size();++i) {
                if(nodes[i] != nullptr){
                    nodes[i]->clear();
                    nodes[i] = nullptr;
                }
            }
        }
        std::list<Entity*> Quadtree::retrieve(std::list<Entity*>& entities,Entity* e){
               int index = this->getIndex(e);
               entities.sort();
               this->entities.sort();
               if (index != -1 && nodes[0] != nullptr) {
                 nodes[index]->retrieve(entities, e);
               }
               entities.merge(this->entities);
               return entities;
        }
        void Quadtree::render(sf::RenderWindow& win){
            for(int i=0;i<nodes.size();++i){
                if(nodes[0] != nullptr){
                    nodes[i]->render(win);
                }
            }
            sf::RectangleShape boundsShape(sf::Vector2f(bounds.width,bounds.height));
            boundsShape.setPosition(bounds.left,bounds.top);
            int b,g,r;
            b = level > 255 ? 255: level+bounds.left;
            g = level > 255 ? 255: level+bounds.top;
            r = level > 255 ? 255: level+(bounds.top+bounds.height);
            if(b> 255 || b <0){b=255;}
            if(g> 255 || g <0){g=255;}
            if(r> 255 || r <0){r=255;}
            sf::Color color(r,b,g,255);
            boundsShape.setOutlineThickness(0.5);
            boundsShape.setFillColor(sf::Color::Transparent);
            boundsShape.setOutlineColor(color);
            win.draw(boundsShape);
        }
        Quadtree::~Quadtree(){

        }
    }
};
