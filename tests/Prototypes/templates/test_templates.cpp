#include <cassert>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>
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
class base {
public:
    virtual ~base() = default;
    int id() const {
        return m_id;
    }
    template<typename...T>
    const std::tuple<T...>& virt_data() const;
protected:
    base(int id): m_id(id) {}
private:
    int m_id;
};

template<typename...T>
class derived: public base {
public:
    derived(T...data, int id): base {id}, m_data {std::move(data)...} {}
    const std::tuple<T...>& data() const {
        return m_data;
    }
private:
    std::tuple<T...> m_data;
};

template<typename...T>
const std::tuple<T...>& base::virt_data() const {
    auto& casted = dynamic_cast<const derived<T...>&>(*this);
    return casted.data();
}

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main() {
    std::vector<std::unique_ptr<base>> misc_data;
    misc_data.push_back(make_unique<derived<int, float>>(2, 3.4f, 0));
    misc_data.push_back(make_unique<derived<double>>(43.23, 1));
    misc_data.push_back(make_unique<derived<std::shared_ptr<message>,int,bool>>(std::shared_ptr<message>(new message("TEST")),2,true,4));
    auto data = misc_data.at(0)->virt_data<int, float>();
    assert(data == std::make_tuple(2, 3.4f));
    std::cout << "Obtenemos propiedad " << std::endl;
    auto testComponent = misc_data.at(2)->virt_data<std::shared_ptr<message>,int,bool>();
    std::cout << std::get<0>(testComponent)->getString() << std::endl;
    std::cout << "Cambiamos propiedad local " << std::endl;
    std::get<0>(testComponent)->setString("Changed");
    std::cout << "mostramos propiedad local " << std::endl;
    std::cout << std::get<0>(testComponent)->getString() << std::endl;
    std::cout << "Obtenemos propiedad otra vez " << std::endl;
    auto testComponent1 = misc_data.at(2)->virt_data<std::shared_ptr<message>,int,bool>();
    std::cout << "mostramos propiedad desde otra variable " << std::endl;
    std::cout << std::get<0>(testComponent1)->getString() << std::endl;
}
