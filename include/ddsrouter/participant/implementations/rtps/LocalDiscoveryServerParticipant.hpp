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
 * @file LocalDiscoveryServerParticipant.hpp
 */

#ifndef _DDSROUTER_PARTICIPANT_IMPLEMENTATIONS_AUX_LOCALDISCOVERYSERVERPARTICIPANT_HPP_
#define _DDSROUTER_PARTICIPANT_IMPLEMENTATIONS_AUX_LOCALDISCOVERYSERVERPARTICIPANT_HPP_

#include <ddsrouter/configuration/DiscoveryServerParticipantConfiguration.hpp>
#include <ddsrouter/participant/implementations/rtps/DiscoveryServerParticipant.hpp>

namespace eprosima {
namespace ddsrouter {
namespace rtps {

/**
 * TODO
 */
class LocalDiscoveryServerParticipant
    : public DiscoveryServerParticipant<DiscoveryServerParticipantConfiguration>
{
public:

    LocalDiscoveryServerParticipant(
            const ParticipantConfiguration& participant_configuration,
            std::shared_ptr<PayloadPool> payload_pool,
            std::shared_ptr<DiscoveryDatabase> discovery_database);
};

} /* namespace rtps */
} /* namespace ddsrouter */
} /* namespace eprosima */

#endif /* _DDSROUTER_PARTICIPANT_IMPLEMENTATIONS_AUX_LOCALDISCOVERYSERVERPARTICIPANT_HPP_ */
