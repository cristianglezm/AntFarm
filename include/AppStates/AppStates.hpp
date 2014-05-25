#ifndef ANT_APPSTATES_HPP
#define ANT_APPSTATES_HPP
namespace ant{
    /**
     * @brief Tiene los ID de los estados de la aplicacion.
     */
    namespace AppStates{
        /**
         * @brief ID de los estados de la aplicacion.
         */
        enum ID{
            None,
            Title,
            Menu,
            Game,
            Pause,
            GameFailed,
            GameSucceed
        };
    }
}
#endif // ANT_APPSTATES_HPP
