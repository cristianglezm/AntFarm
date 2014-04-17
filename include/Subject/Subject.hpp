#ifndef SUBJECT_H
#define SUBJECT_H
#include <list>
#include <memory>
#include <Observer/Observer.hpp>
namespace ant{
    /**
     * @brief Tema al cual se suscriben los observadores Observer.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class Subject{
        public:
            /**
             * @brief Constructor por defecto.
             */
            Subject();
            /**
             * @brief A�ade un observador.
             * @param o std::shared_ptr<Observer>
             */
            void addObserver(std::shared_ptr<Observer> o);
            /**
             * @brief Elimina el primer observador que coincida.
             * @param o std::shared_ptr<Observer> observador a eliminar.
             */
            void removeObserver(std::shared_ptr<Observer> o);
            /**
             * @brief Notifica a los Observadores que esten en suscritos a este tema.
             * @param e std::shared_ptr<baseEvent> evento que se envia.
             */
            void notifyObservers(std::shared_ptr<baseEvent> e);
            ~Subject();
        private:
            std::list<std::shared_ptr<Observer> > Observers;
    };
}
#endif // SUBJECT_H
