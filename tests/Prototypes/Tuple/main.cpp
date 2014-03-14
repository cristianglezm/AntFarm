#include <iostream>
#include <tuple>
template<typename... Ts>
class Component{
    private:
        long int id;
        std::tuple<Ts...> properties;
    public:
        Component(std::tuple<Ts...> properties,long int id):id(id),properties(properties){}
        void setId(long int id){
            this->id = id;
        }
        long int getId(){
            return id;
        }
        inline std::tuple<Ts...> getProperties(){ return this->properties; }
        ~Component(){}
};
class message{
    private:
        std::string str;
    public:
        message(){}
        message(std::string str){
            this->str = str;
            std::cout << "CTOR "<< str << std::endl;
        }
        void setString(std::string str){
            this->str = str;
        }
        bool operator==(message& m) const{
            std::cout << "me han comparado" << std::endl;
            return (m.getString() == str);
        }
        inline const std::string getString(){ return str; }
        ~message(){
            std::cout << "DTOR "<< str << std::endl;
        }
};
int main(int nargs,char** args){
    std::cout << "Probando Tuple and Templates:" << std::endl;
    std::cout << "Creamos componente con message,int" << std::endl;
    Component<message,int> c1(std::make_tuple(message("TEST MESSAGE FROM TUPLE"),4),3);
    auto properties = c1.getProperties();
    std::cout << "Properties: \n\tprimera: " << std::get<0>(properties).getString()
              << "\n\tsegunda: " << std::get<1>(properties) << std::endl;
    return 0;
}
