#ifndef ANT_APPSTATE_STACK_HPP
#define ANT_APPSTATE_STACK_HPP
#include <vector>
#include <utility>
#include <functional>
#include <map>
#include <AppStates/AppState.hpp>
#include <AppStates/AppStates.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

namespace ant{
    class AppStateStack{
        public:
            enum Action{
                Push,
                Pop,
                Clear,
            };
        public:
            explicit AppStateStack(Context context);
            template <typename T>
            void registerState(AppStates::ID stateID);
            void update(sf::Time dt);
            void render();
            void handleEvent(const sf::Event& event);
            void pushState(AppStates::ID stateID);
            void popState();
            void clearStates();
            bool isEmpty() const;
            ~AppStateStack();
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
            Context mContext;
            std::map<AppStates::ID, std::function<AppState::uPtr()>> mFactories;
        };
        template <typename T>
        void AppStateStack::registerState(AppStates::ID stateID){
            mFactories[stateID] = [this] (){
                return AppState::uPtr(new T(*this, mContext));
            };
        }
}
#endif // ANT_APPSTATE_STACK_HPP
