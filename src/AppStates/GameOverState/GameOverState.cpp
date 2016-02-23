#include <AppStates/GameOverState/GameOverState.hpp>
#include <Utils/Utility.hpp>
namespace ant{
    GameOverState::GameOverState(StateStack& stack, Context context, std::string msg)
    : AppState(stack,context)
    , mText(){
        loadConfig(Config::CONFIG_FILE);
        mText.setFont(context.assets->getFont(font));
        mText.setString(msg);
        Utils::centerOrigin(mText);
        mText.setPosition(context.window->getView().getSize() / 2.f);
    }
    void GameOverState::render(){
        sf::RenderWindow& window = *getContext().window;
        window.draw(mText);
    }
    void GameOverState::loadConfig(const std::string& filename){
        JsonBox::Value v;
        v.loadFromFile(filename);
        if(v["Config"]["font"].getString() != ""){
            font = v["Config"]["font"].getString();
        }
    }
    bool GameOverState::update(sf::Time dt){
        return false;
    }
    bool GameOverState::handleEvent(const sf::Event& event){
        if(event.type == sf::Event::KeyPressed){
            requestStateClear();
            requestStackPush(AppStates::Menu);
        }
        return false;
    }
}
