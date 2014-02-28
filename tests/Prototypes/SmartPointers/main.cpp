#include <iostream>
#include <vector>
#include <memory>
class message{
    private:
        std::string str;
    public:
        message(std::string str){
            this->str = str;
            std::cout << "Construimos "<< str << std::endl;
        }
        void setString(std::string str){
            this->str = str;
        }
        inline const std::string getString(){
            return this->str;
        }
        ~message(){
            std::cout << "destruimos "<< str << std::endl;
        }
};
int main(){
    std::vector<message> v1;
    std::vector<std::unique_ptr<message> > v2;
    std::cout << "SmartPointers Test" << std::endl;
    v1.push_back(message("message 1"));
    std::cout << "insertamos " << v1.front().getString() << " a vector 1" << std::endl;
    std::cout << "movemos " << v1.at(0).getString() << " a vector 2" << std::endl;
    std::unique_ptr<message> p1;
    //p1(v1.at(0));
    //v2.push_back(p1);
    v1.at(0).setString("message Modfified");
    v1.erase(v1.begin());
    std::cout <<" vector 1: "<< v1.front().getString() << std::endl;
    return 0;
}

