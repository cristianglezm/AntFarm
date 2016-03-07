#include <AppStates/GameState/GameState.hpp>
#include <Event/EventsAlias.hpp>

namespace ant{
    GameState::GameState(StateStack& stack, Context context)
    : AppState(stack,context)
    , win((*context.window))
    , assets(context.assets)
    , gameEventDispatcher(std::make_shared<GameEventDispatcher>())
    , level(std::make_shared<Level>(context.assets,Config::screenSize,gameEventDispatcher))
    , eventQueue(level->getEventQueue(0))
    , currentLevel(0)
    , textScore(){
        loadConfig(Config::CONFIG_FILE);
        totalLevels = level->size();
        gameEventDispatcher->LevelComplete.addObserver(this);
        gameEventDispatcher->LevelFailed.addObserver(this);
        gameEventDispatcher->UpdateScore.addObserver(this);
        GameSpeed = 1;
        score = 0;
        textScore.setFont(context.assets->getFont(font));
        textScore.setPosition(Config::screenSize.width-50,10);
        textScore.setString(Utils::toString(score));
        textScore.setFillColor(sf::Color::Black);
    #if defined ANDROID || WITH_GUI
        loadGUIConf(Config::GUI_FILE);
    #endif
    }
    void GameState::render(){
        level->render(currentLevel,win);
        for(auto i=0u;i<buttons.size();++i){
                win.draw(*buttons[i]);
        }
        win.draw(textScore);
    }
    bool GameState::update(sf::Time dt){
        level->update(currentLevel,dt);
        while(!eventQueue->isEmpty()){
            gameEventDispatcher->DispatchEvent(eventQueue->pop());
        }
        return true;
    }
    bool GameState::handleEvent(const sf::Event& event){
        switch(event.type){
        #if defined ANDROID
            case sf::Event::LostFocus:
                requestStackPush(AppStates::Pause);
                break;
            case sf::Event::TouchEnded:
                if(event.mouseButton.button == sf::Mouse::Left){
                    eventQueue->push(std::make_shared<EventsAlias::select_entity>(EventType::SELECT_ENTITY,
                                    (sf::Vector2i)win.mapPixelToCoords(sf::Vector2i(event.touch.x, event.touch.y), win.getView())));
                    for(auto i=0u;i<buttons.size();++i){
                        auto clickedPos = static_cast<sf::Vector2f>(win.mapPixelToCoords(sf::Vector2i(event.touch.x, event.touch.y),win.getView()));
                        buttons[i]->setScale(sf::Vector2f(1.0f,1.0f));
                        if(buttons[i]->contains(clickedPos)){
                            buttons[i]->setScale(sf::Vector2f(1.1f,1.1f));
                            eventQueue->push(std::make_shared<EventsAlias::change_command>(EventType::CHANGE_COMMAND,
                                                    buttons[i]->getAction()));
                        }
                    }
                }
                break;
            case sf::Event::KeyReleased:
                    if(event.key.code == sf::Keyboard::Escape){
                        requestStackPop();
                    }
                break;
            case sf::Event::MouseLeft:
                    requestStackPush(AppStates::Pause);
                break;
        #else
            case sf::Event::LostFocus:
                requestStackPush(AppStates::Pause);
                break;
            case sf::Event::MouseButtonReleased:
                if(event.mouseButton.button == sf::Mouse::Left){
                    eventQueue->push(std::make_shared<EventsAlias::select_entity>(EventType::SELECT_ENTITY,sf::Mouse::getPosition(win)));
                    for(auto i=0u;i<buttons.size();++i){
                        buttons[i]->setScale(sf::Vector2f(1.0f,1.0f));
                        if(buttons[i]->contains((sf::Vector2f)sf::Mouse::getPosition(win))){
                            buttons[i]->setScale(sf::Vector2f(1.1f,1.1f));
                            eventQueue->push(std::make_shared<EventsAlias::change_command>(EventType::CHANGE_COMMAND,
                                                    buttons[i]->getAction()));
                        }
                    }
                }
                if(event.mouseButton.button == sf::Mouse::Right){
                    eventQueue->push(std::make_shared<EventsAlias::change_command>(EventType::CHANGE_COMMAND,
                                                    Constructions::stop));
                    eventQueue->push(std::make_shared<EventsAlias::select_entity>(EventType::SELECT_ENTITY,
                                                    sf::Mouse::getPosition(win)));
                }
                break;
            case sf::Event::KeyReleased:
                if(event.key.code == sf::Keyboard::Escape){
                    requestStackPop();
                    requestStackPush(AppStates::Menu);
                }
                if(event.key.code == sf::Keyboard::F1){
                    requestStackPush(AppStates::Help);
                }
                if(event.key.code == sf::Keyboard::S){
                    eventQueue->push(std::make_shared<EventsAlias::change_command>(EventType::CHANGE_COMMAND,
                                                    Constructions::stairs));
                }
                if(event.key.code == sf::Keyboard::E){
                    eventQueue->push(std::make_shared<EventsAlias::change_command>(EventType::CHANGE_COMMAND,
                                                    Constructions::explosion));
                }
                if(event.key.code == sf::Keyboard::D){
                    eventQueue->push(std::make_shared<EventsAlias::change_command>(EventType::CHANGE_COMMAND,
                                                    Constructions::downhill));
                }
                if(event.key.code == sf::Keyboard::U){
                    eventQueue->push(std::make_shared<EventsAlias::change_command>(EventType::CHANGE_COMMAND,
                                                    Constructions::uphill));
                }
                if(event.key.code == sf::Keyboard::B){
                    eventQueue->push(std::make_shared<EventsAlias::change_command>(EventType::CHANGE_COMMAND,
                                                    Constructions::bridge));
                }
                if(event.key.code == sf::Keyboard::P){
                    requestStackPush(AppStates::Pause);
                }
                if(event.key.code == sf::Keyboard::T){
                    eventQueue->push(std::make_shared<EventsAlias::change_command>(EventType::CHANGE_COMMAND,
                                                    Constructions::tunnel));
                }
                if(event.key.code == sf::Keyboard::W){
                    eventQueue->push(std::make_shared<EventsAlias::change_command>(EventType::CHANGE_COMMAND,
                                                    Constructions::wall));
                }
                if(event.key.code == sf::Keyboard::H){
                    eventQueue->push(std::make_shared<EventsAlias::change_command>(EventType::CHANGE_COMMAND,
                                                    Constructions::hole));
                }
                if(event.key.code == sf::Keyboard::C){
                    eventQueue->push(std::make_shared<EventsAlias::change_command>(EventType::CHANGE_COMMAND,
                                                    Constructions::climb));
                }
                if(event.key.code == sf::Keyboard::LShift){
                    GameSpeed += 0.1;
                    eventQueue->push(std::make_shared<EventsAlias::change_overtime>(EventType::CHANGE_OVERTIME,sf::seconds(GameSpeed)));
                }
                if(event.key.code == sf::Keyboard::LControl){
                    GameSpeed -= 0.1;
                    eventQueue->push(std::make_shared<EventsAlias::change_overtime>(EventType::CHANGE_OVERTIME,sf::seconds(GameSpeed)));
                }
                break;
            case sf::Event::KeyPressed:
                break;
            #endif
            default:
                break;
        }
        return true;
    }
    void GameState::onNotify(std::shared_ptr<baseEvent> e){
        switch(e->getType()){
            case EventType::LEVEL_COMPLETE:{
                if(currentLevel<(totalLevels-1)){
                    ++currentLevel;
                    eventQueue = level->getEventQueue(currentLevel);
                    gameEventDispatcher = level->getGameEventDispatcher(currentLevel);
                    gameEventDispatcher->LevelComplete.addObserver(this);
                    gameEventDispatcher->LevelFailed.addObserver(this);
                    gameEventDispatcher->UpdateScore.addObserver(this);
                }else if(currentLevel == (totalLevels-1)){
                    requestStackPush(AppStates::GameSucceed);
                }
            }
                break;
            case EventType::LEVEL_FAILED:{
                requestStackPush(AppStates::GameFailed);
            }
                break;
            case EventType::UPDATE_SCORE:{
                score += std::get<0>(e->getAttributes<EventsAlias::update_score>());
                textScore.setString(Utils::toString(score));
            }
                break;
            default:
                break;
        }
    }
    void GameState::loadGUIConf(const std::string& filename){
        JsonBox::Value v;
    #if defined ANDROID
        v.loadFromString(android::readAssetsFile(filename));
    #else
        v.loadFromFile(filename);
    #endif
        if(!v["GUI"]["buttons"].isNull()){
            int size = v["GUI"]["buttons"].getArray().size();
            for(int i=0;i<size;++i){
                sf::Vector2f pos(v["GUI"]["buttons"][size_t(i)]["position"]["x"].getInteger(),
                                 v["GUI"]["buttons"][size_t(i)]["position"]["y"].getInteger());
                sf::Vector2f bSize(v["GUI"]["buttons"][size_t(i)]["scale"]["width"].getInteger(),
                                   v["GUI"]["buttons"][size_t(i)]["scale"]["height"].getInteger());
                sf::Text t;
                if(v["GUI"]["buttons"][size_t(i)]["text"]["font"].getString() != ""){
                    t.setFont(assets->getFont(v["GUI"]["buttons"][size_t(i)]["text"]["font"].getString()));
                }
                t.setString(v["GUI"]["buttons"][size_t(i)]["text"]["string"].getString());
                t.setPosition(pos);
                t.setCharacterSize(v["GUI"]["buttons"][size_t(i)]["text"]["size"].getInteger());
                sf::Sprite sprite;
                sprite.setPosition(pos);
                if(v["GUI"]["buttons"][size_t(i)]["imageID"].getString() != ""){
                    sprite.setTexture(assets->getTexture(v["GUI"]["buttons"][size_t(i)]["imageID"].getString()));
                }
                std::string actionID = v["GUI"]["buttons"][size_t(i)]["action"].getString();
                constructorSystem::command action = [](Entity* e,sf::VertexArray* va,sf::FloatRect bounds){};
                if(actionID == "climb"){
                    action = Constructions::climb;
                }else if(actionID == "dig"){
                    action = Constructions::hole;
                }else if(actionID == "tunnel"){
                    action = Constructions::tunnel;
                }else if(actionID == "stairs"){
                    action = Constructions::stairs;
                }else if(actionID == "wall"){
                    action = Constructions::wall;
                }else if(actionID == "stop"){
                    action = Constructions::stop;
                }else if(actionID == "bridge"){
                    action = Constructions::bridge;
                }else if(actionID == "downhill"){
                    action = Constructions::downhill;
                }else if(actionID == "uphill"){
                    action = Constructions::uphill;
                }else if(actionID == "explosion"){
                    action = Constructions::explosion;
                }
                buttons.emplace_back(std::make_unique<GUI::Button>(pos,sprite,t,action));
            }
        }
    }
    void GameState::loadConfig(const std::string& filename){
        JsonBox::Value v;
    #if defined ANDROID
        v.loadFromString(android::readAssetsFile(filename));
    #else
        v.loadFromFile(filename);
    #endif
        if(v["Config"]["font"].getString() != ""){
            font = v["Config"]["font"].getString();
        }
    }
}
