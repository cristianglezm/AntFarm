#ifndef ANT_APPLICATION_HPP
#define ANT_APPLICATION_HPP

#include <Config.hpp>
#include <Utils/String.hpp>
#include <AssetManager/AssetManager.hpp>
#include <AppStateStack/AppStateStack.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace ant{
    class Application{
        public:
            Application();
            void run();
            ~Application();
        private:
            void processInput();
            void update(sf::Time dt);
            void render();
            void updateStatistics(sf::Time dt);
            void registerStates();
        private:
            static const sf::Time TimePerFrame;
            sf::RenderWindow mWindow;
            std::shared_ptr<AssetManager> mAssets;
            AppStateStack mAppStateStack;
            sf::Text mStatisticsText;
            sf::Time mStatisticsUpdateTime;
            std::size_t	mStatisticsNumFrames;
    };
}
#endif // ANT_APPLICATION_HPP
