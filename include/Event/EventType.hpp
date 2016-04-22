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

#ifndef EVENT_TYPE_HPP
#define EVENT_TYPE_HPP
/**
 * @brief Tipos de eventos.
 * @author Cristian Glez <Cristian.glez.m@gmail.com>
 * @version 1.0
 */
namespace EventType{
        enum{
            COLLISION_EVENT,
            TERRAIN_COLLISION,
            CHANGE_OVERTIME,
            CHANGE_NENTITIES,
            CHANGE_COMMAND,
            SELECT_ENTITY,
            OUT_MAP,
            LEVEL_COMPLETE,
            LEVEL_FAILED,
            UPDATE_SCORE
        };
}
#endif // EVENT_TYPE_HPP