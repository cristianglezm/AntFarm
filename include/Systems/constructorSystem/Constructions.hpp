#ifndef CONSTRUCTIONS_H
#define CONSTRUCTIONS_H
#include <Systems/constructorSystem/constructorSystem.hpp>
namespace ant{
    class Constructions{
        public:
            // commands
            static constructorSystem::command tunnel;
            static constructorSystem::command bridge;
            static constructorSystem::command stairs;
            static constructorSystem::command hole;
            // colors
            static sf::Color Grey;
            static sf::Color lightGrey;
            static sf::Color Brown;
            static sf::Color lightBrown;
    };
}
#endif // CONSTRUCTIONS_H
