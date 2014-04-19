#ifndef QUADTREE_H
#define QUADTREE_H
#include <array>
#include <memory>
#include <list>
#include <Entity/Entity.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>

namespace ant{
    namespace Utils{
        /**
         * @class Quadtree
         * @brief Clase para reducir el numero de test de collisiones.
         * @author Cristian Glez <Cristian.glez.m@gmail.com>
         * @version 0.1
         * @todo posible feature hacer template para poder usar puntos y rectangulos ademas de entidades.
         */
        class Quadtree{
            public:
                typedef std::list<Entity*> list;
                /**
                 * @brief Constructor principal, necesita que se especifique el rectangulo que
                 *        Ocupara.
                 *
                 * @param bounds sf::FloatRect Rectangulo marcando la zona de este quadtree.
                 */
                Quadtree(sf::FloatRect bounds);
                /**
                 * @brief Agrega un puntero a una entidad, la posiciona en el nodo correcto,
                 *        si no cabe en ningun nodo inferior se mantiene en el padre.
                 *
                 * @param e Entity *
                 */
                void insert(Entity* e);
                /**
                 * @brief Limpia el quadtree y sus nodos.
                 *
                 */
                void clear();
                /**
                 * @brief Agrega las entidades del mismo sector que
                 *        la entidad especificada a la lista(la misma entidad especificada es agregada tambien)
                 *
                 * @param entities std::list<Entity*>& lista a la que agregan las entidades del mismo sector de la especificada.
                 * @param e Entity * Entidad a comprobar.
                 * @return std::list<Entity*> lista de entidades
                 */
                std::list<Entity*> retrieve(std::list<Entity*>& entities,Entity* e);
                /**
                 * @brief Metodo para ver las divisiones en la pantalla.
                 * @param win sf::RenderWindow& ventana a la cual dibujar.
                 */
                void render(sf::RenderWindow& win);
                ~Quadtree();
            private:
                const static int MAX_CAPACITY = 100;
                const static int MAX_LEVEL = 1000;
                int level;
                std::array<std::unique_ptr<Quadtree>,4> nodes;
                sf::FloatRect bounds;
                std::list<Entity*> entities;
                /**
                 * @brief Constructor privado para la division de los nodos.
                 * @param level int numero del nivel.
                 * @param bounds sf::FloatRect rectangulo de la division.
                 */
                Quadtree(int level,sf::FloatRect bounds);
                /**
                 * @brief Metodo para dividir el quadtree.
                 *
                 * Inicializa los nodos del quadtree y se empiezan a usar.
                 */
                void split();
                /**
                 * @brief Obtiene el indice(nodo donde esta) de la entidad especificada.
                 * @param e Entity* Entidad para sacar su indice.
                 * @return int devuelve el indice(0-3) -1 si esta en el mismo.
                 */
                int getIndex(Entity* e);
        };
    }
}
#endif
