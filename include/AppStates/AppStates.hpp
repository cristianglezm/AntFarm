////////////////////////////////////////////////////////////////
// Copyright 2014 Cristian Glez <Cristian.glez.m@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
////////////////////////////////////////////////////////////////

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
