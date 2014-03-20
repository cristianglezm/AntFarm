#include <Utils/Quadtree.hpp>
#include <Components/ComponentMask.hpp>
namespace ant{
    namespace Utils{
        void Quadtree::split(){
            int subWidth = (int)(bounds.width / 2);
            int subHeight = (int)(bounds.height / 2);
            int x = (int)bounds.left;
            int y = (int)bounds.top;
            nodes[0].reset(new Quadtree(level+1, sf::FloatRect(x + subWidth, y, subWidth, subHeight)));
            nodes[1].reset(new Quadtree(level+1, sf::FloatRect(x, y, subWidth, subHeight)));
            nodes[2].reset(new Quadtree(level+1, sf::FloatRect(x, y + subHeight, subWidth, subHeight)));
            nodes[3].reset(new Quadtree(level+1, sf::FloatRect(x + subWidth, y + subHeight, subWidth, subHeight)));
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
        int Quadtree::getIndex(Entity* e){
                int index = -1;
                double verticalMidpoint = bounds.left + (bounds.width / 2);
                double horizontalMidpoint = bounds.top + (bounds.height / 2);
                // Object can completely fit within the top quadrants
                auto& properties = e->getComponent(ComponentsMask::COMPONENT_TRANSFORM)->getProperties<sf::FloatRect>();
                sf::FloatRect eBounds = std::get<0>(properties);
                bool topQuadrant = (eBounds.top < horizontalMidpoint && eBounds.top + eBounds.height < horizontalMidpoint);
                // Object can completely fit within the bottom quadrants
                bool bottomQuadrant = (eBounds.top > horizontalMidpoint);
                // Object can completely fit within the left quadrants
                if (eBounds.left < verticalMidpoint && eBounds.top + eBounds.height < verticalMidpoint) {
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
        void Quadtree::insert(Entity* e){
               if (nodes[0] != nullptr) {
                    int index = getIndex(e);
                    if (index != -1) {
                        nodes[index]->insert(e);
                        return;
                    }
                }
                entities.push_back(e);

                if(entities.size() > this->MAX_CAPACITY && level < this->MAX_LEVEL) {
                    if(nodes[0] == nullptr) {
                        this->split();
                    }
                    for(auto entity: entities){
                        int index = getIndex(entity);
                        if(index != -1){
                            entities.remove(e);
                            nodes[index]->insert(e);
                        }
                    }
                }
        }
        void Quadtree::clear(){
            entities.clear();
            for (int i = 0; i < nodes.size();++i) {
                if (nodes[i] != nullptr) {
                    nodes[i]->clear();
                    nodes[i] = nullptr;
                }
            }
        }
        std::list<Entity*> Quadtree::retrieve(std::list<Entity*>* entities,Entity* e){
               int index = getIndex(e);
               entities->sort();
               this->entities.sort();
               if (index != -1 && nodes[0] != nullptr) {
                 nodes[index]->retrieve(entities, e);
               }
               entities->merge(this->entities);
               return *entities;
        }
        Quadtree::~Quadtree(){

        }
    }
};
