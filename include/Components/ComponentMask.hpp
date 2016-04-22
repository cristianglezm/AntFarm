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

#ifndef COMPONENT_MASK_HPP
#define COMPONENT_MASK_HPP

#include <bitset>

/**
 * @brief tipos de componentes.
 * @author Cristian Glez <Cristian.glez.m@gmail.com>
 * @version 1.0
 */
namespace ComponentsMask{
        using Mask = std::bitset<32>;
        static constexpr Mask COMPONENT_NONE = 0;
        static constexpr Mask COMPONENT_SPRITE = 1 << 0;
        static constexpr Mask COMPONENT_ANIMATION = 1 << 1;
        static constexpr Mask COMPONENT_VELOCITY = 1 << 2;
        static constexpr Mask COMPONENT_TRANSFORM = 1 << 3;
        static constexpr Mask COMPONENT_DESTRUCTABLE = 1 << 4;
        static constexpr Mask COMPONENT_BOUNDS = 1 << 5;
        static constexpr Mask COMPONENT_PASSAGE = 1 << 6;
        static constexpr Mask COMPONENT_OUT = 1 << 7;
        static constexpr Mask COMPONENT_IN = 1 << 8;
        static constexpr Mask COMPONENT_COUNT = 1 << 9;
}
#endif // COMPONENT_MASK_HPP