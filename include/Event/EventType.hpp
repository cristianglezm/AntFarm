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
 * @version 0.1
 */
namespace EventType{
        static constexpr int COLLISION_EVENT = 0;
        static constexpr int TERRAIN_COLLISION = 1;
        static constexpr int CHANGE_OVERTIME = 2;
        static constexpr int CHANGE_NENTITIES = 3;
        static constexpr int CHANGE_COMMAND = 4;
        static constexpr int SELECT_ENTITY = 5;
        static constexpr int OUT_MAP = 6;
        static constexpr int LEVEL_COMPLETE = 7;
        static constexpr int LEVEL_FAILED = 8;
        static constexpr int UPDATE_SCORE = 9;
}
#endif // EVENT_TYPE_HPP