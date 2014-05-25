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
        mOptions.push_back(playOption);
        sf::Text exitOption;
        exitOption.setFont(context.assets->getFont(font));
        exitOption.setString("Exit");
        Utils::centerOrigin(exitOption);
        exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
        mOptions.push_back(exitOption);
        sf::Text gameTitle;
        gameTitle.setFont(context.assets->getFont(font));
        gameTitle.setString("AntFarm");
        gameTitle.setCharacterSize(50);
        Utils::centerOrigin(gameTitle);
        gameTitle.setPosition(playOption.getPosition() - sf::Vector2f(0.f, 100.f));
        mOptions.push_back(gameTitle);
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
        if (event.type != sf::Event::KeyPressed){
            return false;
        }
        if (event.key.code == sf::Keyboard::Return){
            if (mOptionIndex == Play){
                requestStackPop();
                requestStackPush(AppStates::Game);
            }else if (mOptionIndex == Exit){
                requestStackPop();
            }
        }else if (event.key.code == sf::Keyboard::Up){
            if (mOptionIndex > 0){
                mOptionIndex--;
            }
            else{
                mOptionIndex = mOptions.size() - 2;
            }
            updateOptionText();
        }else if (event.key.code == sf::Keyboard::Down){
            if (mOptionIndex < mOptions.size() - 2){
                mOptionIndex++;
            }else{
                mOptionIndex = 0;
            }
            updateOptionText();
        }

        return true;
    }
    void MenuState::loadConfig(const std::string& filename){
        std::fstream file(filename);
        JsonBox::Value v(file);
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
            text.setColor(sf::Color::White);
        }
        mOptions[mOptionIndex].setColor(sf::Color::Red);
    }
}
