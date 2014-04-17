#ifndef COMPONENT_SETTINGS_H
#define COMPONENT_SETTINGS_H
#include <string>
namespace ant{
    /**
     * @brief Clase para la configuracion de los componentes en EntityFactory.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class ComponentSettings{
        public:
            /**
             * @brief Carga la configuracion de la entidad.
             *
             * Carga un fichero json con las propiedades de los componentes
             * las propiedades que no encuentre las pondra por defecto.
             *
             * @param filename std::string nombre del fichero(json) a cargar.
             */
            void loadSettings(const std::string& filename);
        private:
            float Speed;
    };
}
#endif // COMPONENT_SETTINGS_H
