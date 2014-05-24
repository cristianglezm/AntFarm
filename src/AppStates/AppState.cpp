#include <AppStates/AppState.hpp>

namespace ant{
    AppState::Context::Context(sf::RenderWindow& window, AssetManager& assets)
    : window(&window)
    , assets(&assets){}
    AppState::AppState(StateStack& Stack, AppState::Context context)
    : mStack(&Stack)
    , mContext(context){

    }
    void AppState::requestStackPush(AppStates::ID stateID){
        mStack->pushState(stateID);
    }
    void AppState::requestStackPop(){
        mStack->popState();
    }
    void AppState::requestStateClear(){
        mStack->clearStates();
    }
    AppState::Context AppState::getContext() const{
        return mContext;
    }
    AppState::~AppState(){

    }
}
