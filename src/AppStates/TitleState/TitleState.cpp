#include <AppStates/TitleState/TitleState.hpp>
#include <Utils/Utility.hpp>
namespace ant{
    TitleState::TitleState(StateStack& stack, Context context)
    : AppState(stack,context)
    , mText()
    , mShowText(true)
    , mTextEffectTime(sf::Time::Zero){
        loadConfig(Config::CONFIG_FILE);
        mBackgroundSprite.setTexture(context.assets->getTexture(background));
        mText.setFont(context.assets->getFont(font));
        mText.setString("Press any key to start");
        Utils::centerOrigin(mText);
        mText.setPosition(context.window->getView().getSize() / 2.f);
    }
    void TitleState::render(){
        sf::RenderWindow& window = *getContext().window;
        window.draw(mBackgroundSprite);
        if (mShowText){
            window.draw(mText);
        }
    }
    void TitleState::loadConfig(const std::string& filename){
        std::fstream file(filename);
        JsonBox::Value v(file);
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
        if(event.type == sf::Event::KeyPressed){
            requestStackPop();
            requestStackPush(AppStates::Menu);
        }
        return true;
    }
}
