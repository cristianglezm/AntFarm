#ifndef ANT_STATE_STACK_HPP
#define ANT_STATE_STACK_HPP
#include <vector>
#include <utility>
#include <functional>
#include <map>
#include <AppStates/AppStates.hpp>
#include <AppStates/AppState.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

namespace ant{
    /**
     * @brief Clase para almacenar los estados del juego.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class StateStack{
        public:
            /**
             * @brief enumeracion para efectuar acciones.
             */
            enum Action{
                Push,
                Pop,
                Clear,
            };
        public:
            /**
             * @brief Constructor principal
             * @param context AppState::Context contexto de ejecucion.
             */
            explicit StateStack(AppState::Context context);
            /**
             * @brief Registra un estado en la fabrica, el estado tiene que tener 3 argumentos
             * @tparam T clase del estado a crear.
             * @param stateID AppState::ID estado a crear.
             */
            template <typename T>
            void registerState(AppStates::ID stateID);
            /**
             * @brief Registra un estado en la fabrica, el estado tiene que tener 3 argumentos
             * @tparam T clase del estado a crear.
             * @param stateID AppState::ID estado a crear,
             * @param msg std::string mensaje que mostrara el estado.
             */
            template <typename T>
            void registerState(AppStates::ID stateID,std::string msg);
            /**
             * @brief Actualiza los estados que tiene
             * @param dt sf::Time delta time
             */
            void update(sf::Time dt);
            /**
             * @brief Renderiza los estados.
             */
            void render();
            /**
             * @brief maneja la input de los estados(teclado/ raton).
             * @param event sf::Event
             */
            void handleEvent(const sf::Event& event);
            /**
             * @brief Añade un estado al Stack
             * @param stateID AppStates::ID
             */
            void pushState(AppStates::ID stateID);
            /**
             * @brief Elimina el ultimo estado añadido.
             */
            void popState();
            /**
             * @brief Elimina todos los estados.
             */
            void clearStates();
            /**
             * @brief Devuelve si el Stack esta vacio.
             * @return bool
             */
            bool isEmpty() const;
            ~StateStack();
        private:
            /**
             * @brief Crea el estado especificado
             * @param stateID AppStates::ID
             */
            AppState::uPtr createState(AppStates::ID stateID);
            /**
             * @brief Aplica los cambios pendientes al Stack.
             */
            void applyPendingChanges();
        private:
            struct PendingChange{
                explicit PendingChange(Action action, AppStates::ID stateID = AppStates::None);
                Action action;
                AppStates::ID stateID;
            };
        private:
            std::vector<AppState::uPtr>	mStack;
            std::vector<PendingChange> mPendingList;
            AppState::Context mContext;
            std::map<AppStates::ID, std::function<AppState::uPtr()>> mFactories;
        };
        template <typename T>
        void StateStack::registerState(AppStates::ID stateID){
            mFactories[stateID] = [this] (){
                return AppState::uPtr(new T(*this, mContext));
            };
        }
        template <typename T>
        void StateStack::registerState(AppStates::ID stateID,std::string msg){
            mFactories[stateID] = [this,msg] (){
                return AppState::uPtr(new T(*this, mContext,msg));
            };
        }
}

#endif // ANT_STATE_STACK_HPP
