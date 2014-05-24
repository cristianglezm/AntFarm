#ifndef ANT_APPSTATE_HPP
#define ANT_APPSTATE_HPP
#include <AssetManager/AssetManager.hpp>
#include <AppStates/AppStates.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <memory>
#include <functional>

namespace ant{
    class StateStack;
    class AppState{
        public:
            typedef std::unique_ptr<AppState> uPtr;
            typedef std::shared_ptr<AppState> sPtr;
            struct Context{
                Context(sf::RenderWindow& window, AssetManager& assets);
                sf::RenderWindow* window;
                AssetManager* assets;
            };
        public:
            AppState(StateStack& stack,AppState::Context context);
            virtual void render() = 0;
            virtual bool update(sf::Time dt) = 0;
            virtual bool handleEvent(const sf::Event& event) = 0;
            virtual ~AppState();
        protected:
            void requestStackPush(AppStates::ID stateID);
            void requestStackPop();
            void requestStateClear();
            Context	getContext() const;
        private:
            StateStack* mStack;
            Context	mContext;
    };
}
#include <StateStack/StateStack.hpp>
#endif // ANT_APPSTATE_HPP
