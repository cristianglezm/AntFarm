#include <queue>
#include <iostream>

int main(int nargs,char** args){
    std::queue<int> q;
    std::deque<int> d;
    d.push_back(32);
    q.push(20);
    q.push(24);

    std::cout << q.front() << std::endl;
    if(!q.empty()){
            q.pop();
    }
    std::cout << q.front() << std::endl;
    if(!q.empty()){
            q.pop();
    }
    std::cout << q.front() << std::endl;
    if(!q.empty()){
            q.pop();
    }
    std::cout << q.front() << std::endl;
}
