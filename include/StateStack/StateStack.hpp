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
    class StateStack{
        public:
            enum Action{
                Push,
                Pop,
                Clear,
            };
        public:
            explicit StateStack(AppState::Context context);
            template <typename T>
            void registerState(AppStates::ID stateID);
            void update(sf::Time dt);
            void render();
            void handleEvent(const sf::Event& event);
            void pushState(AppStates::ID stateID);
            void popState();
            void clearStates();
            bool isEmpty() const;
            ~StateStack();
        private:
            AppState::uPtr createState(AppStates::ID stateID);
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
}

#endif // ANT_STATE_STACK_HPP
