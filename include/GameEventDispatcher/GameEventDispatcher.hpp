#ifndef GAME_EVENT_DISPATCHER_H
#define GAME_EVENT_DISPATCHER_H
#include <Event/Event.hpp>
#include <Event/EventType.hpp>
#include <Subject/Subject.hpp>
namespace ant{
    /**
     *  @brief Clase encargada de processar eventos.
     *  @author Cristian Gonzalez Moreno <Cristian.glez.m@gmail.com>
     *  @version 0.1
     */
    class GameEventDispatcher{
        private:
            Subject onCollision;
            Subject onTransport;
        public:
            GameEventDispatcher();
            inline Subject& OnCollision(){ return onCollision; }
            inline Subject& OnTransport(){ return onTransport; }
            bool DispatchEvent(std::shared_ptr<baseEvent> e);
            ~GameEventDispatcher();
    };
};
#endif // GAME_EVENT_DISPATCHER_H
