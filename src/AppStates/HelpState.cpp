#include <AppStates/HelpState.hpp>

namespace ant{
    HelpState::HelpState(StateStack& stack, Context context)
    : AppState(stack,context)
    , mText(){
        loadConfig(Config::CONFIG_FILE);
        mText.setFont(context.assets->getFont(font));
        std::ostringstream help;
    #if defined ANDROID
        help << "HELP\n" <<
                "\tUse the buttons and click the ants to make them do that action.\n\n";
    #else
        help << "HELP\n" <<
                "\tKEYS:\n" <<
                "\t\tw -> wall: The selected ant Will build a wall.\n\n" <<
                "\t\ts -> stairs: The selected ant will build a stair.\n\n" <<
                "\t\te -> explode: The selected ant will explode.\n\n" <<
                "\t\td -> down: The selected ant will dig a stair going down.\n\n" <<
                "\t\tu -> up: The selected ant will dig a stair going up.\n\n" <<
                "\t\tc -> climb: The selected ant will climb walls.\n\n" <<
                "\t\tmouse right: The selected ant will stop doing whatever it was doing.\n\n" <<
                "\t\tmouse left: Selects the ant.\n\n" <<
                "\t\th -> Hole: The selected ant will dig down.\n\n" <<
                "\t\tp -> Pause: Pauses the game.\n\n" <<
                "\t\tesc -> return to main menu.\n\n" <<
                "\t\tF1 -> This menu.\n\n";
    #endif
        mText.setString(help.str());
        mText.setPosition({0,20});
        mText.setCharacterSize(18);
    }
    void HelpState::render(){
        sf::RenderWindow& window = *getContext().window;
        window.clear(sf::Color::Black);
        window.draw(mText);
    }
    void HelpState::loadConfig(const std::string& filename){
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
    bool HelpState::update([[maybe_unused]] sf::Time dt){
        return false;
    }
    bool HelpState::handleEvent(const sf::Event& event){
    #if defined ANDROID
        if(event.type == sf::Event::TouchEnded){
            requestStackPop();
        }
    #else
        if(event.type == sf::Event::KeyReleased){
            requestStackPop();
        }
    #endif
        return false;
    }
}
