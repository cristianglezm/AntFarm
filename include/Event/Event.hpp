#ifndef EVENT_H
#define EVENT_H
namespace ant{
    class Event{
        private:
            int type;
        public:
            Event(int type);
            void setType(int type);
            inline int getType(){ return type; }
    };
}
#endif // EVENT_H
