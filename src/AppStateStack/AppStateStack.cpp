#include <AppStateStack/AppStateStack.hpp>
#include <cassert>
namespace ant{
    AppStateStack::AppStateStack(Context context)
    : mStack()
    , mPendingList()
    , mContext(context)
    , mFactories(){}
    void AppStateStack::update(sf::Time dt){
        for(auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr){
            if(!(*itr)->update(dt)){
                break;
            }
        }
        applyPendingChanges();
    }
    void AppStateStack::render(){
        for(auto& state : mStack){
            state->render();
        }
    }
    void AppStateStack::handleEvent(const sf::Event& event){
        for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr){
            if (!(*itr)->handleEvent(event)){
                break;
            }
        }
        applyPendingChanges();
    }
    void AppStateStack::pushState(AppStates::ID stateID){
        mPendingList.push_back(PendingChange(Push, stateID));
    }
    void AppStateStack::popState(){
        mPendingList.push_back(PendingChange(Pop));
    }
    void AppStateStack::clearStates(){
        mPendingList.push_back(PendingChange(Clear));
    }
    bool AppStateStack::isEmpty() const{
        return mStack.empty();
    }
    AppState::uPtr AppStateStack::createState(AppStates::ID stateID){
        auto found = mFactories.find(stateID);
        assert(found != mFactories.end());
        return found->second();
    }
    void AppStateStack::applyPendingChanges(){
        for(auto& change: mPendingList){
            switch (change.action){
                case Push:
                    mStack.push_back(createState(change.stateID));
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
    AppStateStack::PendingChange::PendingChange(Action action, States::ID stateID)
    : action(action)
    , stateID(stateID){}
    AppStateStack::~AppStateStack(){

    }
}
