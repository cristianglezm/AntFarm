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

#ifndef STATES_HPP
#define STATES_HPP

#include <bitset>

/**
 * @brief Estados de las entidades
 * @author Cristian Glez <Cristian.glez.m@gmail.com>
 * @version 0.1
 */
namespace States{
    using Mask = std::bitset<32>;
    static constexpr Mask NONE = 0;
    static constexpr Mask GROUND = 1 << 0;
    static constexpr Mask FALLING = 1 << 1;
    static constexpr Mask CLIMBING = 1 << 2;
    static constexpr Mask BUILDING = 1 << 3;
    static constexpr Mask ONFIRE = 1 << 4;
    static constexpr Mask SAVED = 1 << 5;
    static constexpr Mask UNSAVED = 1 << 6;
}

#endif // STATES_HPP
