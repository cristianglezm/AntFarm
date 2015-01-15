#include <Application/Application.hpp>

namespace ant{
    Application::Application()
    : mWindow(std::make_shared<sf::RenderWindow>(sf::VideoMode(Config::screenSize.width,Config::screenSize.height),
                                                "AntFarm", sf::Style::Close))
    , mAssets(std::make_shared<AssetManager>())
    , mStateStack(AppState::Context(mWindow,mAssets)){
        mAssets->loadAssets(Config::ASSETS_GAME_JSON);
        loadConfig(Config::CONFIG_FILE);
        mStatisticsText.setFont(mAssets->getFont(font));
        mStatisticsText.setPosition(Config::screenSize.width-55,Config::screenSize.height-45);
        mStatisticsText.setCharacterSize(25u);
        version.setFont(mAssets->getFont(font));
        version.setCharacterSize(25u);
        version.setPosition(Config::screenSize.width-Config::screenSize.width+5,Config::screenSize.height-50);
        version.setString(Config::VERSION);
        registerStates();
        mStateStack.pushState(AppStates::Title);
    }
    void Application::run(){
        sf::Clock clock;
        sf::Time timeSinceLastUpdate = sf::Time::Zero;
        while(mWindow->isOpen()){
            sf::Time dt = clock.restart();
            timeSinceLastUpdate += dt;
            while(timeSinceLastUpdate > TimePerFrame){
                timeSinceLastUpdate -= TimePerFrame;
                processInput();
                update(TimePerFrame);
                if(mStateStack.isEmpty()){
                    mWindow->close();
                }
            }
        updateStatistics(dt);
        render();
        }
    }
    void Application::loadConfig(const std::string& filename){
        std::fstream file(filename);
        JsonBox::Value v(file);
        if(v["Config"]["font"].getString() != ""){
            font = v["Config"]["font"].getString();
        }
    }
    void Application::processInput(){
        sf::Event event;
        while (mWindow->pollEvent(event)){
            mStateStack.handleEvent(event);
            if (event.type == sf::Event::Closed){
                mWindow->close();
            }
        }
    }
    void Application::update(sf::Time dt){
        mStateStack.update(dt);
    }
    void Application::render(){
        mWindow->clear();
        mStateStack.render();
        mWindow->setView(mWindow->getDefaultView());
        mWindow->draw(mStatisticsText);
        mWindow->draw(version);
        mWindow->display();
    }
    void Application::updateStatistics(sf::Time dt){
        mStatisticsUpdateTime += dt;
        mStatisticsNumFrames += 1;
        if (mStatisticsUpdateTime >= sf::seconds(1.0f)){
            if(mStatisticsNumFrames < 10){
                mStatisticsText.setColor(sf::Color::Red);
            }else if(mStatisticsNumFrames > 59){
                mStatisticsText.setColor(sf::Color::Green);
            }else if(mStatisticsNumFrames < 30){
                mStatisticsText.setColor(sf::Color::Yellow);
            }
            mStatisticsText.setString(Utils::toString(mStatisticsNumFrames));
            mStatisticsUpdateTime -= sf::seconds(1.0f);
            mStatisticsNumFrames = 0;
        }
    }
    void Application::registerStates(){
        mStateStack.registerState<TitleState>(AppStates::Title);
        mStateStack.registerState<MenuState>(AppStates::Menu);
        mStateStack.registerState<GameState>(AppStates::Game);
        mStateStack.registerState<PauseState>(AppStates::Pause);
        mStateStack.registerState<GameOverState>(AppStates::GameFailed,"Game Failed!");
        mStateStack.registerState<GameOverState>(AppStates::GameSucceed,"Game Succeed!");
    }
    const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);
}
