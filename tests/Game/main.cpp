#include <ComponentTest.hpp>
#include <EntityTest.hpp>
#include <EntityManagerTest.hpp>
#include <EventTest.hpp>
#include <EventQueueTest.hpp>
#include <SystemTest.hpp>
#include <SystemManagerTest.hpp>
#include <QuadtreeTest.hpp>
int main(){
    ComponentTest();
    EntityTest();
    EntityManagerTest();
    EventTest();
    EventQueueTest();
    SystemTest();
    SystemManagerTest();
    QuadtreeTest();
    return 0;
}
