#include <AppStates/MenuState/MenuState.hpp>

namespace ant{
    MenuState::MenuState(StateStack& stack, Context context)
    : AppState(stack, context)
    , mOptions()
    , mOptionIndex(0){
        loadConfig(Config::CONFIG_FILE);
        mBackground.setTexture(context.assets->getTexture(strBackground));
        sf::Text playOption;
        playOption.setFont(context.assets->getFont(font));
        playOption.setString("Play");
        Utils::centerOrigin(playOption);
        playOption.setPosition(context.window->getView().getSize() / 2.f);
        mOptions.emplace_back(playOption);
        sf::Text helpOption;
        helpOption.setFont(context.assets->getFont(font));
        helpOption.setString("Help");
        Utils::centerOrigin(helpOption);
        helpOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
        mOptions.emplace_back(helpOption);
        sf::Text exitOption;
        exitOption.setFont(context.assets->getFont(font));
        exitOption.setString("Exit");
        Utils::centerOrigin(exitOption);
        exitOption.setPosition(helpOption.getPosition() + sf::Vector2f(0.f, 30.f));
        mOptions.emplace_back(exitOption);
        sf::Text gameTitle;
        gameTitle.setFont(context.assets->getFont(font));
        gameTitle.setString("AntFarm");
        gameTitle.setCharacterSize(50);
        Utils::centerOrigin(gameTitle);
        gameTitle.setPosition(playOption.getPosition() - sf::Vector2f(0.f, 100.f));
        mOptions.emplace_back(gameTitle);
        updateOptionText();
    }
    void MenuState::render(){
        sf::RenderWindow& window = *getContext().window;
        window.setView(window.getDefaultView());
        window.draw(mBackground);
        for(const auto& text : mOptions){
            window.draw(text);
        }
    }
    bool MenuState::update(sf::Time dt){
        return true;
    }
    bool MenuState::handleEvent(const sf::Event& event){
    #if defined ANDROID
        auto& window = *getContext().window;
        if(event.type == sf::Event::TouchEnded){
            sf::Vector2f pos = static_cast<sf::Vector2f>(window.mapPixelToCoords(sf::Vector2i(event.touch.x, event.touch.y), window.getView()));
            for(const auto& text:mOptions){
                if(text.getGlobalBounds().contains(pos)){
                    if(text.getString() == "Play"){
                        requestStackPop();
                        requestStackPush(AppStates::Game);
                    }else if(text.getString() == "Help"){
                        requestStackPush(AppStates::Help);
                    }else if(text.getString() == "Exit"){
                        requestStackPop();
                    }
                }
            }
        }else if(event.type == sf::Event::KeyReleased){
            if(event.key.code == sf::Keyboard::Escape){
                requestStackPop();
            }
        }else if(event.type == sf::Event::LostFocus){
            requestStackPop();
        }
    #else
        if(event.type != sf::Event::KeyReleased){
            return false;
        }
        if(event.key.code == sf::Keyboard::Return){
            if(mOptionIndex == Play){
                requestStackPop();
                requestStackPush(AppStates::Game);
            }else if(mOptionIndex == Help){
                requestStackPush(AppStates::Help);
            }else if(mOptionIndex == Exit){
                requestStackPop();
            }
        }else if(event.key.code == sf::Keyboard::Up){
            if(mOptionIndex > 0){
                mOptionIndex--;
            }
            else{
                mOptionIndex = mOptions.size() - 2;
            }
            updateOptionText();
        }else if(event.key.code == sf::Keyboard::Down){
            if(mOptionIndex < mOptions.size() - 2){
                mOptionIndex++;
            }else{
                mOptionIndex = 0;
            }
            updateOptionText();
        }
    #endif
        return true;
    }
    void MenuState::loadConfig(const std::string& filename){
        JsonBox::Value v;
    #if defined ANDROID
        v.loadFromString(android::readAssetsFile(filename));
    #else
        v.loadFromFile(filename);
    #endif
        if(v["Config"]["font"].getString() != ""){
            font = v["Config"]["font"].getString();
        }
        if(v["Config"]["MenuScreen"]["background"].getString() != ""){
            strBackground = v["Config"]["MenuScreen"]["background"].getString();
        }
    }
    void MenuState::updateOptionText(){
        if (mOptions.empty()){
            return;
        }
        for(auto& text : mOptions){
            text.setFillColor(sf::Color::White);
        }
        mOptions[mOptionIndex].setFillColor(sf::Color::Red);
    }
}
