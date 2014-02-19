
class Component{
    private:
        long int id;
    public:
        Component(long int id){
            this->id = id;
        }
       void setId(long int id){
           this->id = id;
       }
       inline const long getId(){
           return this->id;
       }
};
