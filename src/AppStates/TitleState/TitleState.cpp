#include <AppStates/TitleState/TitleState.hpp>
#include <Utils/Utility.hpp>
namespace ant{
    TitleState::TitleState(StateStack& stack, Context context)
    : AppState(stack,context)
    , mTitle()
    , mText()
    , mShowText(true)
    , mTextEffectTime(sf::Time::Zero){
        loadConfig(Config::CONFIG_FILE);
        mBackground.setTexture(context.assets->getTexture(background));
        mText.setFont(context.assets->getFont(font));
        mText.setString("Press any key to start");
        Utils::centerOrigin(mText);
        mText.setPosition(context.window->getView().getSize() / 2.f);
        mTitle.setFont(context.assets->getFont(font));
        mTitle.setString("AntFarm");
        mTitle.setCharacterSize(50);
        Utils::centerOrigin(mTitle);
        mTitle.setPosition(mText.getPosition() - sf::Vector2f(0.f, 100.f));
    }
    void TitleState::render(){
        sf::RenderWindow& window = *getContext().window;
        window.draw(mBackground);
        window.draw(mTitle);
        if (mShowText){
            window.draw(mText);
        }
    }
    void TitleState::loadConfig(const std::string& filename){
        JsonBox::Value v;
    #if defined ANDROID
        v.loadFromString(android::readAssetsFile(filename));
    #else
        v.loadFromFile(filename);
    #endif
        if(v["Config"]["font"].getString() != ""){
            font = v["Config"]["font"].getString();
        }
        if(v["Config"]["TitleScreen"]["background"].getString() != ""){
            background = v["Config"]["TitleScreen"]["background"].getString();
        }
    }
    bool TitleState::update(sf::Time dt){
    	mTextEffectTime += dt;
        if (mTextEffectTime >= sf::seconds(0.5f)){
            mShowText = !mShowText;
            mTextEffectTime = sf::Time::Zero;
        }
        return true;
    }
    bool TitleState::handleEvent(const sf::Event& event){
    #if defined ANDROID
        if(event.type == sf::Event::TouchEnded){
            requestStackPop();
            requestStackPush(AppStates::Menu);
        }else if(event.type == sf::Event::KeyReleased){
            if(event.key.code == sf::Keyboard::Escape){
                requestStackPop();
            }
        }else if(event.type == sf::Event::LostFocus){
            requestStackPop();
        }
    #else
        if(event.type == sf::Event::KeyPressed){
            requestStackPop();
            requestStackPush(AppStates::Menu);
        }
    #endif
        return true;
    }
}
