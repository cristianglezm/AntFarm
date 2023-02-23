#include <AppStates/PauseState.hpp>
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
        JsonBox::Value v;
    #if defined ANDROID
        v.loadFromString(std::string(android::readAssetsFile(filename).data()));
    #else
        v.loadFromFile(filename);
    #endif
        if(v["Config"]["font"].getString() != ""){
            font = v["Config"]["font"].getString();
        }
    }
    bool PauseState::update(sf::Time dt){
    	mTextEffectTime += dt;
        if(mTextEffectTime >= sf::seconds(0.5f)){
            mShowText = !mShowText;
            mTextEffectTime = sf::Time::Zero;
        }
        return false;
    }
    bool PauseState::handleEvent(const sf::Event& event){
        *getContext().active = false;
        if(event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseEntered){
            *getContext().active = true;
            requestStackPop();
        }
        return false;
    }
}
