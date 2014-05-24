#ifndef ANT_APPSTATE_HPP
#define ANT_APPSTATE_HPP
#include <AssetManager/AssetManager.hpp>
#include <AppStates/AppStates.hpp>
#include <AppStateStack/AppStateStack.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <memory>

namespace ant{
    class AppStateStack;
    struct Context{
        Context(sf::RenderWindow& window, AssetManager& assets);
        sf::RenderWindow* window;
        AssetManager* assets;
    };
    class AppState{
        public:
            typedef std::unique_ptr<AppState> uPtr;
            typedef std::shared_ptr<AppState> sPtr;
        public:
            AppState(AppStateStack& Stack,Context context);
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
            AppStateStack* mStack;
            Context	mContext;
    };
}
#endif // ANT_APPSTATE_HPP
