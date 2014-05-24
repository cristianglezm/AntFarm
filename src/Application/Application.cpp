#include <Application/Application.hpp>

namespace ant{
    Application::Application()
    : mWindow(sf::VideoMode(Config::screenSize.width,Config::screenSize.height), "AntFarm", sf::Style::Close)
    , mAssets(new AssetManager())
    , mAppStateStack(Context(mWindow,(*mAssets.get()))){
        mAssets->loadAssets(Config::ASSETS_GAME_JSON);
        mStatisticsText.setFont(mAssets->getFont("Outwrite"));
        mStatisticsText.setPosition(5.f, 5.f);
        mStatisticsText.setCharacterSize(10u);

        registerStates();
        mAppStateStack.pushState(AppStates::Title);
    }
    void Application::run(){
        sf::Clock clock;
        sf::Time timeSinceLastUpdate = sf::Time::Zero;
        while(mWindow.isOpen()){
            sf::Time dt = clock.restart();
            timeSinceLastUpdate += dt;
            while(timeSinceLastUpdate > TimePerFrame){
                timeSinceLastUpdate -= TimePerFrame;
                processInput();
                update(TimePerFrame);
                if(mAppStateStack.isEmpty()){
                    mWindow.close();
                }
            }
        render();
        }
    }
    void Application::processInput(){
        sf::Event event;
        while (mWindow.pollEvent(event)){
            mAppStateStack.handleEvent(event);
            if (event.type == sf::Event::Closed){
                mWindow.close();
            }
        }
    }
    void Application::update(sf::Time dt){
        mAppStateStack.update(dt);
    }
    void Application::render(){
        mWindow.clear();
        mAppStateStack.render();
        mWindow.setView(mWindow.getDefaultView());
        mWindow.display();
    }
    void Application::updateStatistics(sf::Time dt){
        mStatisticsUpdateTime += dt;
        mStatisticsNumFrames += 1;
        if (mStatisticsUpdateTime >= sf::seconds(1.0f)){
            mStatisticsText.setString("FPS: " + Utils::toString(mStatisticsNumFrames));
            mStatisticsUpdateTime -= sf::seconds(1.0f);
            mStatisticsNumFrames = 0;
        }
    }
    void Application::registerStates(){
        //mAppStateStack.registerState<TitleState>(AppStates::Title);
        //mAppStateStack.registerState<MenuState>(AppStates::Menu);
        //mAppStateStack.registerState<GameState>(AppStates::Game);
        //mAppStateStack.registerState<PauseState>(AppStates::Pause);
    }
    Application::~Application(){

    }
    const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);
}
