#ifndef GAME_H
#define GAME_H
#include <Level/Level.hpp>
#include <EventQueue/EventQueue.hpp>
namespace ant{
    class Game{
        private:
            std::shared_ptr<EventQueue> eventQueue;
            std::shared_ptr<Level> level;
        public:
            Game();
            void run();
            ~Game();
    };
}
#endif // GAME_H
