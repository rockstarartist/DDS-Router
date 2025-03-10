// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

/**
 * @file VoidReader.cpp
 */

#include <ddsrouter/reader/implementations/auxiliar/VoidReader.hpp>

namespace eprosima {
namespace ddsrouter {

void VoidReader::enable() noexcept
{
}

void VoidReader::disable() noexcept
{
}

void VoidReader::set_on_data_available_callback(
        std::function<void()>) noexcept
{
}

void VoidReader::unset_on_data_available_callback() noexcept
{
}

ReturnCode VoidReader::take(
        std::unique_ptr<DataReceived>&) noexcept
{
    return ReturnCode::RETCODE_NO_DATA;
}

} /* namespace ddsrouter */
} /* namespace eprosima */
