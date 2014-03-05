#include <iostream>
#include <list>
#include <algorithm>
#include <memory>
class message{
    private:
        std::string str;
    public:
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

std::shared_ptr<message> processMessageSPTR(std::shared_ptr<message> m){
    std::cout << "Function In " << m->getString() << std::endl;
    std::cout << "Function Out " << m->getString() << std::endl;
}
std::unique_ptr<message> processMessageUPTR(std::unique_ptr<message> m){
    std::cout << "Function In " << m->getString() << std::endl;
    std::cout << "Function Out " << m->getString() << std::endl;
    return std::move(m);
}
void shared_ptrExample(){
    std::cout << "Shared Pointer:" << std::endl;
    std::list<std::shared_ptr<message>> l1;
    std::list<std::shared_ptr<message>> l2;
    std::cout << "Creamos Mensaje 1" << std::endl;
    std::shared_ptr<message> spt(new message("Mensaje 1"));
    std::cout << "Referencias del Puntero Compartido: " << spt.use_count() << std::endl;
    std::cout << "Añadimos Mensaje 1 al final de la lista." << std::endl;
    l1.push_back(spt);
    std::cout << "Mensaje 1 Añadido." << std::endl;
    std::cout << "Referencias del Puntero Compartido: " << spt.use_count() << std::endl;
    std::cout << "Obtenemos mensaje" << std::endl;
    std::shared_ptr<message> tmp2;
    for(auto& tmp1 : l1){
        if(tmp1->getString()=="Mensaje 1"){
            tmp2 = tmp1;
        }
    }
    std::cout << "mensaje obtenido " << tmp2->getString() << std::endl;
    std::cout << "Referencias del Puntero Compartido: " << tmp2.use_count() << std::endl;
    {
        std::cout << "Entramos otro Scope" << std::endl;
            std::shared_ptr<message> spt2(new message("Mensaje 2"));
            std::shared_ptr<message> spt3(new message("Mensaje 3"));
            std::cout << "Añadimos Mensaje 2 al frente de la lista." << std::endl;
            l1.push_front(spt2);
            std::cout << "Referencias del Puntero Compartido: " << spt2.use_count() << std::endl;
        std::cout << "Salimos Otro Scope" << std::endl;
    }
    std::cout << "Referencias del Puntero Compartido: " << spt.use_count() << std::endl;
    std::cout << "Process Function Call" << std::endl;
    processMessageSPTR(l1.front());
    std::cout << "Process Function End" << std::endl;
    {
        std::cout << "Copy Message 2" << std::endl;
        std::shared_ptr<message> spt2(l1.front());
        std::cout << "Borramos message 2" << std::endl;
        l1.erase(l1.begin());
        std::cout << "Message 2 Borrado" << std::endl;
        std::cout << "Referencias del Puntero Compartido: " << spt2.use_count() << std::endl;
        std::cout << "Contenido MSG 2 " << spt2->getString() << std::endl;
        std::cout << "añadimos MSG2 a l2 " << std::endl;
        l2.push_back(spt2);
        std::cout << "Referencias del Puntero Compartido: " << spt.use_count() << std::endl;
    }
    std::cout << "Obtenemos Mensaje Lista 2 " << l2.front()->getString() << std::endl;
    std::cout << "Referencias del Puntero Compartido: " << l2.front().use_count() << std::endl;
    std::cout << "Salimos Programa." << std::endl;
}
void unique_ptrExample(){
    std::cout << "Unique Pointer " << std::endl;
    std::list<std::unique_ptr<message>> l1;
    std::list<std::unique_ptr<message>> l2;
    std::cout << "Creamos Mensaje 1" << std::endl;
    std::unique_ptr<message> spt(new message("Mensaje 1"));
    std::cout << "Añadimos Mensaje 1 al final de la lista." << std::endl;
    l1.push_back(std::move(spt));
    std::cout << "Mensaje 1 Añadido." << std::endl;
    std::cout << "Obtenemos mensaje" << std::endl;
    std::unique_ptr<message> tmp2;
    for(auto& tmp1 : l1){
        if(tmp1->getString()=="Mensaje 1"){
            tmp2 = std::move(tmp1);
        }
    }
    std::cout << "mensaje obtenido " << tmp2->getString() << std::endl;
    {
        std::cout << "Entramos otro Scope" << std::endl;
            std::unique_ptr<message> spt2(new message("Mensaje 2"));
            std::unique_ptr<message> spt3(new message("Mensaje 3"));
            spt2 == spt3;
            std::cout << "Añadimos Mensaje 2 al frente de la lista." << std::endl;
            l1.push_front(std::move(spt2));
        std::cout << "Salimos Otro Scope" << std::endl;
    }
    std::cout << "Process Function Call" << std::endl;
    l1.push_front(processMessageUPTR(std::move(l1.front())));
    std::cout << "Process Function End" << std::endl;
    {
        std::cout << "Copy Message 2" << std::endl;
        std::unique_ptr<message> spt2(std::move(l1.front()));
        std::cout << "Borramos message 2" << std::endl;
        l1.erase(l1.begin());
        std::cout << "Message 2 Borrado" << std::endl;
        std::cout << "Contenido MSG 2 " << spt2->getString() << std::endl;
        std::cout << "añadimos MSG2 a l2 " << std::endl;
        l2.push_back(std::move(spt2));
    }
    std::cout << "Obtenemos Mensaje Lista 2 " << l2.front()->getString() << std::endl;
    std::cout << "Salimos Programa." << std::endl;
}
int main(){
    //shared_ptrExample();
    unique_ptrExample();
    return 0;
}

