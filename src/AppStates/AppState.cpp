#include <AppStates/AppState.hpp>

namespace ant{
    Context::Context(sf::RenderWindow& window, AssetManager& assets)
    : window(&window)
    , assets(&assets){}
    AppState::AppState(AppStateStack& Stack, AppState::Context context)
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
    Context	AppState::getContext() const{
        return mContext;
    }
    AppState::~AppState(){

    }
}
