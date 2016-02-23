#include <StateStack/StateStack.hpp>
#include <cassert>
namespace ant{
    StateStack::StateStack(AppState::Context context)
    : mStack()
    , mPendingList()
    , mContext(context)
    , mFactories(){}
    void StateStack::update(sf::Time dt){
        for(auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr){
            if(!(*itr)->update(dt)){
                break;
            }
        }
        applyPendingChanges();
    }
    void StateStack::render(){
        for(auto& state : mStack){
            state->render();
        }
    }
    void StateStack::handleEvent(const sf::Event& event){
        for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr){
            if (!(*itr)->handleEvent(event)){
                break;
            }
        }
        applyPendingChanges();
    }
    void StateStack::pushState(AppStates::ID stateID){
        mPendingList.emplace_back(PendingChange(Push, stateID));
    }
    void StateStack::popState(){
        mPendingList.emplace_back(PendingChange(Pop));
    }
    void StateStack::clearStates(){
        mPendingList.emplace_back(PendingChange(Clear));
    }
    bool StateStack::isEmpty() const{
        return mStack.empty();
    }
    AppState::uPtr StateStack::createState(AppStates::ID stateID){
        auto found = mFactories.find(stateID);
        assert(found != mFactories.end());
        return found->second();
    }
    void StateStack::applyPendingChanges(){
        for(auto& change: mPendingList){
            switch(change.action){
                case Push:
                    mStack.emplace_back(createState(change.stateID));
                    break;
                case Pop:
                    mStack.pop_back();
                    break;
                case Clear:
                    mStack.clear();
                    break;
            }
        }
        mPendingList.clear();
    }
    StateStack::PendingChange::PendingChange(Action action, AppStates::ID stateID)
    : action(action)
    , stateID(stateID){}
}
