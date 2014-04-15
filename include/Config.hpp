#ifndef ANT_CONFIG_H
#define ANT_CONFIG_H
#include <string>
namespace ant{
    /**
     * Clase de configuracion con constantes de ficheros.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class Config{
        private:
        public:
            static const std::string VERSION;
            static const std::string ASSETS_GAME_JSON;
    };
}
#endif // CONFIG_H
