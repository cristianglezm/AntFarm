#include <AppStates/PauseState/PauseState.hpp>
namespace ant{
    PauseState::PauseState(StateStack& stack, Context context)
    : AppState(stack,context)
    , mText()
    , mShowText(true)
    , mTextEffectTime(sf::Time::Zero){
        loadConfig(Config::CONFIG_FILE);
        mText.setFont(context.assets->getFont(font));
        mText.setString("PAUSE");
        Utils::centerOrigin(mText);
        mText.setPosition(context.window->getView().getSize() / 2.f);
    }
    void PauseState::render(){
        sf::RenderWindow& window = *getContext().window;
        if (mShowText){
            window.draw(mText);
        }
    }
    void PauseState::loadConfig(const std::string& filename){
        std::fstream file(filename);
        JsonBox::Value v(file);
        if(v["Config"]["font"].getString() != ""){
            font = v["Config"]["font"].getString();
        }
    }
    bool PauseState::update(sf::Time dt){
    	mTextEffectTime += dt;
        if (mTextEffectTime >= sf::seconds(0.5f)){
            mShowText = !mShowText;
            mTextEffectTime = sf::Time::Zero;
        }
        return false;
    }
    bool PauseState::handleEvent(const sf::Event& event){
        if(event.type == sf::Event::KeyReleased){
            requestStackPop();
        }
        return false;
    }
}
