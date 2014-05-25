#include <AppStates/GameState/GameState.hpp>

namespace ant{
    GameState::GameState(StateStack& stack, Context context)
    : AppState(stack,context)
    , win((*context.window))
    , assets(context.assets)
    , gameEventDispatcher(new GameEventDispatcher())
    , level(new Level(context.assets,Config::screenSize,gameEventDispatcher))
    , eventQueue(level->getEventQueue())
    , currentLevel(0){
        loadConfig(Config::CONFIG_FILE);
        totalLevels = level->size();
        self.reset(this);
        gameEventDispatcher->LevelComplete.addObserver(self);
        gameEventDispatcher->LevelFailed.addObserver(self);
        GameSpeed = 1;
        loadGUIConf(Config::GUI_FILE);
    }
    void GameState::render(){
        level->render(currentLevel,win);
        for(unsigned int i=0;i<buttons.size();++i){
                win.draw(*buttons[i]);
        }
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
            case sf::Event::LostFocus:
                requestStackPush(AppStates::Pause);
            break;
            case sf::Event::MouseButtonReleased:
                if(event.mouseButton.button == sf::Mouse::Left){
                    eventQueue->push(std::shared_ptr<baseEvent>(
                            new Event<sf::Vector2i>(EventType::SELECT_ENTITY,
                                                    sf::Mouse::getPosition(win)))
                                 );
                    for(unsigned int i=0;i<buttons.size();++i){
                        if(buttons[i]->contains((sf::Vector2f)sf::Mouse::getPosition(win))){
                            eventQueue->push(std::shared_ptr<baseEvent>(
                            new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                    buttons[i]->getAction()
                                                    ))
                                 );
                        }
                    }
                }
                if(event.mouseButton.button == sf::Mouse::Right){
                    eventQueue->push(std::shared_ptr<baseEvent>(
                            new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                    Constructions::stop
                                                    ))
                                 );
                    eventQueue->push(std::shared_ptr<baseEvent>(
                            new Event<sf::Vector2i>(EventType::SELECT_ENTITY,
                                                    sf::Mouse::getPosition(win)))
                                 );
                }
                break;
            case sf::Event::KeyReleased:
                if(event.key.code == sf::Keyboard::Escape){
                    requestStackPop();
                    requestStackPush(AppStates::Menu);
                }
                if(event.key.code == sf::Keyboard::S){
                    eventQueue->push(std::shared_ptr<baseEvent>(
                            new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                    Constructions::stairs
                                                    ))
                                 );
                }
                if(event.key.code == sf::Keyboard::D){
                    eventQueue->push(std::shared_ptr<baseEvent>(
                            new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                    Constructions::downhill
                                                    ))
                                 );
                }
                if(event.key.code == sf::Keyboard::U){
                    eventQueue->push(std::shared_ptr<baseEvent>(
                            new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                    Constructions::uphill
                                                    ))
                                 );
                }
                if(event.key.code == sf::Keyboard::B){
                    eventQueue->push(std::shared_ptr<baseEvent>(
                            new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                    Constructions::bridge
                                                    ))
                                 );
                }
                if(event.key.code == sf::Keyboard::P){
                    requestStackPush(AppStates::Pause);
                }
                if(event.key.code == sf::Keyboard::T){
                    eventQueue->push(std::shared_ptr<baseEvent>(
                            new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                    Constructions::tunnel
                                                    ))
                                 );
                }
                if(event.key.code == sf::Keyboard::W){
                    eventQueue->push(std::shared_ptr<baseEvent>(
                            new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                    Constructions::wall
                                                    ))
                                 );
                }
                if(event.key.code == sf::Keyboard::H){
                    eventQueue->push(std::shared_ptr<baseEvent>(
                            new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                    Constructions::hole
                                                    ))
                                 );
                }
                if(event.key.code == sf::Keyboard::C){
                    eventQueue->push(std::shared_ptr<baseEvent>(
                            new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                    Constructions::climb
                                                    ))
                                 );
                }
                if(event.key.code == sf::Keyboard::LShift){
                    GameSpeed += 0.1;
                    eventQueue->push(std::shared_ptr<baseEvent>(
                            new Event<sf::Time>(EventType::CHANGE_OVERTIME,sf::seconds(GameSpeed)))
                                 );
                }
                if(event.key.code == sf::Keyboard::LControl){
                    GameSpeed -= 0.1;
                    eventQueue->push(std::shared_ptr<baseEvent>(
                            new Event<sf::Time>(EventType::CHANGE_OVERTIME,sf::seconds(GameSpeed)))
                                 );
                }
                break;
            case sf::Event::KeyPressed:
                break;
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
                }else if(currentLevel == (totalLevels-1)){
                    requestStackPush(AppStates::GameSucceed);
                }
            }
                break;
            case EventType::LEVEL_FAILED:{
                requestStackPush(AppStates::GameFailed);
            }
                break;
        }
    }
    void GameState::loadGUIConf(const std::string& filename){
        std::fstream file(filename);
        JsonBox::Value v(file);
        if(!v["GUI"]["buttons"].isNull()){
            int size = v["GUI"]["buttons"].getArray().size();
            for(int i=0;i<size;++i){
                sf::Vector2f pos(v["GUI"]["buttons"][size_t(i)]["position"]["x"].getInt(),
                                 v["GUI"]["buttons"][size_t(i)]["position"]["y"].getInt());
                sf::Vector2f bSize(v["GUI"]["buttons"][size_t(i)]["size"]["width"].getInt(),
                                   v["GUI"]["buttons"][size_t(i)]["size"]["height"].getInt());
                sf::Text t;
                if(v["GUI"]["buttons"][size_t(i)]["text"]["font"].getString() != ""){
                    t.setFont(assets->getFont(v["GUI"]["buttons"][size_t(i)]["text"]["font"].getString()));
                }
                t.setString(v["GUI"]["buttons"][size_t(i)]["text"]["string"].getString());
                t.setPosition(pos);
                t.setCharacterSize(v["GUI"]["buttons"][size_t(i)]["text"]["size"].getInt());
                sf::Sprite sprite;
                sprite.setPosition(pos);
                if(v["GUI"]["buttons"][size_t(i)]["imageID"].getString() != ""){
                    sprite.setTexture(assets->getTexture(v["GUI"]["buttons"][size_t(i)]["imageID"].getString()));
                }
                std::string actionID = v["GUI"]["buttons"][size_t(i)]["action"].getString();
                constructorSystem::command action;
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
                }
                buttons.push_back(Utils::makeUniquePtr<GUI::Button>(pos,bSize,sprite,t,action));
            }
        }
    }
    void GameState::loadConfig(const std::string& filename){
        std::fstream file(filename);
        JsonBox::Value v(file);
        if(v["Config"]["font"].getString() != ""){
            font = v["Config"]["font"].getString();
        }
    }
    GameState::~GameState(){
        // liberamos recursos.

    }
}
