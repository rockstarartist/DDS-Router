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
 * @file EchoParticipant.cpp
 */

#ifndef _DDSROUTER_PARTICIPANT_IMPLEMENTATIONS_AUX_COMMONRTPSROUTERPARTICIPANT_HPP_
#define _DDSROUTER_PARTICIPANT_IMPLEMENTATIONS_AUX_COMMONRTPSROUTERPARTICIPANT_HPP_

#include <memory>

#include <fastrtps/rtps/participant/RTPSParticipant.h>
#include <fastrtps/rtps/RTPSDomain.h>

#include <ddsrouter/reader/implementations/rtps/Reader.hpp>
#include <ddsrouter/types/endpoint/DomainId.hpp>
#include <ddsrouter/types/utils.hpp>
#include <ddsrouter/writer/implementations/rtps/Writer.hpp>
#include <ddsrouter/exceptions/InitializationException.hpp>
#include <ddsrouter/participant/implementations/auxiliar/BaseParticipant.hpp>

namespace eprosima {
namespace ddsrouter {
namespace rtps {

template <class ConfigurationType>
CommonRTPSRouterParticipant<ConfigurationType>::CommonRTPSRouterParticipant(
        const ConfigurationType participant_configuration,
        std::shared_ptr<PayloadPool> payload_pool,
        std::shared_ptr<DiscoveryDatabase> discovery_database)
    : BaseParticipant<ConfigurationType>(participant_configuration, payload_pool, discovery_database)
{
    // init_();
}

template <class ConfigurationType>
CommonRTPSRouterParticipant<ConfigurationType>::~CommonRTPSRouterParticipant()
{
    if (rtps_participant_)
    {
        fastrtps::rtps::RTPSDomain::removeRTPSParticipant(rtps_participant_);
    }
}

template <class ConfigurationType>
void CommonRTPSRouterParticipant<ConfigurationType>::onParticipantDiscovery(
        fastrtps::rtps::RTPSParticipant*,
        fastrtps::rtps::ParticipantDiscoveryInfo&& info)
{
    if (info.info.m_guid.guidPrefix != this->rtps_participant_->getGuid().guidPrefix)
    {
        if (info.status == fastrtps::rtps::ParticipantDiscoveryInfo::DISCOVERED_PARTICIPANT)
        {
            logInfo(DDSROUTER_DISCOVERY,
                    "Found in Participant " << this->id_nts_() << " new Participant " << info.info.m_guid << ".");
        }
        else if (info.status == fastrtps::rtps::ParticipantDiscoveryInfo::CHANGED_QOS_PARTICIPANT)
        {
            logInfo(DDSROUTER_DISCOVERY, "Participant " << info.info.m_guid << " changed QoS.");
        }
        else if (info.status == fastrtps::rtps::ParticipantDiscoveryInfo::REMOVED_PARTICIPANT)
        {
            logInfo(DDSROUTER_DISCOVERY, "Participant " << info.info.m_guid << " removed.");
        }
        else
        {
            logInfo(DDSROUTER_DISCOVERY, "Participant " << info.info.m_guid << " dropped.");
        }
    }
}

template <class ConfigurationType>
template<class DiscoveryInfoKind>
Endpoint CommonRTPSRouterParticipant<ConfigurationType>::create_endpoint_from_info_(
        DiscoveryInfoKind& info)
{
    // Parse GUID
    Guid info_guid;
    info_guid = info.info.guid();

    // Parse QoS
    DurabilityKind info_durability_kind = info.info.m_qos.m_durability.durabilityKind();
    ReliabilityKind info_reliability_kind;
    if (info.info.m_qos.m_reliability.kind == fastdds::dds::BEST_EFFORT_RELIABILITY_QOS)
    {
        info_reliability_kind = fastrtps::rtps::BEST_EFFORT;
    }
    else if (info.info.m_qos.m_reliability.kind == fastdds::dds::RELIABLE_RELIABILITY_QOS)
    {
        info_reliability_kind = fastrtps::rtps::RELIABLE;
    }
    else
    {
        utils::tsnh(
            utils::Formatter() <<
                "Invalid ReliabilityQoS value found while parsing DiscoveryInfo for Endpoint creation.");
    }
    QoS info_qos(info_durability_kind, info_reliability_kind);

    // Parse Topic
    RealTopic info_topic(std::string(info.info.topicName()), std::string(info.info.typeName()),
            info.info.topicKind() == eprosima::fastrtps::rtps::TopicKind_t::WITH_KEY);

    // Create Endpoint
    if (std::is_same<DiscoveryInfoKind, fastrtps::rtps::ReaderDiscoveryInfo>::value)
    {
        return Endpoint(EndpointKind::READER, info_guid, info_qos, info_topic);
    }
    else if (std::is_same<DiscoveryInfoKind, fastrtps::rtps::WriterDiscoveryInfo>::value)
    {
        return Endpoint(EndpointKind::WRITER, info_guid, info_qos, info_topic);
    }
    else
    {
        utils::tsnh(utils::Formatter() << "Invalid DiscoveryInfoKind for Endpoint creation.");
        return Endpoint();
    }
}

template <class ConfigurationType>
void CommonRTPSRouterParticipant<ConfigurationType>::onReaderDiscovery(
        fastrtps::rtps::RTPSParticipant*,
        fastrtps::rtps::ReaderDiscoveryInfo&& info)
{
    if (info.info.guid().guidPrefix != this->rtps_participant_->getGuid().guidPrefix)
    {
        Endpoint info_reader = create_endpoint_from_info_<fastrtps::rtps::ReaderDiscoveryInfo>(info);

        if (info.status == fastrtps::rtps::ReaderDiscoveryInfo::DISCOVERED_READER)
        {
            logInfo(DDSROUTER_DISCOVERY,
                    "Found in Participant " << this->id_nts_() << " new Reader " << info.info.guid() << ".");

            this->discovery_database_->push_item_to_queue(std::make_tuple(DatabaseOperation::INSERT, info_reader));
        }
        else if (info.status == fastrtps::rtps::ReaderDiscoveryInfo::CHANGED_QOS_READER)
        {
            logInfo(DDSROUTER_DISCOVERY, "Reader " << info.info.guid() << " changed QoS.");

            this->discovery_database_->push_item_to_queue(std::make_tuple(DatabaseOperation::UPDATE, info_reader));
        }
        else if (info.status == fastrtps::rtps::ReaderDiscoveryInfo::REMOVED_READER)
        {
            logInfo(DDSROUTER_DISCOVERY, "Reader " << info.info.guid() << " removed.");

            info_reader.active(false);
            this->discovery_database_->push_item_to_queue(std::make_tuple(DatabaseOperation::UPDATE, info_reader));
        }
        else
        {
            logInfo(DDSROUTER_DISCOVERY, "Reader " << info.info.guid() << " dropped.");

            info_reader.active(false);
            this->discovery_database_->push_item_to_queue(std::make_tuple(DatabaseOperation::UPDATE, info_reader));
        }
    }
}

template <class ConfigurationType>
void CommonRTPSRouterParticipant<ConfigurationType>::onWriterDiscovery(
        fastrtps::rtps::RTPSParticipant*,
        fastrtps::rtps::WriterDiscoveryInfo&& info)
{
    if (info.info.guid().guidPrefix != this->rtps_participant_->getGuid().guidPrefix)
    {
        Endpoint info_writer = create_endpoint_from_info_<fastrtps::rtps::WriterDiscoveryInfo>(info);

        if (info.status == fastrtps::rtps::WriterDiscoveryInfo::DISCOVERED_WRITER)
        {
            logInfo(DDSROUTER_DISCOVERY,
                    "Found in Participant " << this->id_nts_() << " new Writer " << info.info.guid() << ".");

            this->discovery_database_->push_item_to_queue(std::make_tuple(DatabaseOperation::INSERT, info_writer));
        }
        else if (info.status == fastrtps::rtps::WriterDiscoveryInfo::CHANGED_QOS_WRITER)
        {
            logInfo(DDSROUTER_DISCOVERY, "Writer " << info.info.guid() << " changed QoS.");

            this->discovery_database_->push_item_to_queue(std::make_tuple(DatabaseOperation::UPDATE, info_writer));
        }
        else if (info.status == fastrtps::rtps::WriterDiscoveryInfo::REMOVED_WRITER)
        {
            logInfo(DDSROUTER_DISCOVERY, "Writer " << info.info.guid() << " removed.");

            info_writer.active(false);
            this->discovery_database_->push_item_to_queue(std::make_tuple(DatabaseOperation::UPDATE, info_writer));
        }
        else
        {
            logInfo(DDSROUTER_DISCOVERY, "Writer " << info.info.guid() << " dropped.");

            info_writer.active(false);
            this->discovery_database_->push_item_to_queue(std::make_tuple(DatabaseOperation::UPDATE, info_writer));
        }
    }
}

template <class ConfigurationType>
void CommonRTPSRouterParticipant<ConfigurationType>::create_participant_()
{
    DomainId domain = this->configuration_.domain();
    fastrtps::rtps::RTPSParticipantAttributes params = participant_attributes_();

    logInfo(DDSROUTER_RTPS_PARTICIPANT,
            "Creating Participant in domain " << domain);

    rtps_participant_ = fastrtps::rtps::RTPSDomain::createParticipant(domain(), params, this);
    if (!rtps_participant_)
    {
        throw InitializationException(
                  utils::Formatter() << "Error creating RTPS Participant " << this->id());
    }

    logInfo(DDSROUTER_RTPS_PARTICIPANT,
            "New Participant " << this->configuration_.kind() <<
            " created with id " << this->id() <<
            " in domain " << domain << " with guid " << rtps_participant_->getGuid());
}

template <class ConfigurationType>
std::shared_ptr<IWriter> CommonRTPSRouterParticipant<ConfigurationType>::create_writer_(
        RealTopic topic)
{
    return std::make_shared<Writer>(
        this->id(), topic,
        this->payload_pool_, rtps_participant_);
}

template <class ConfigurationType>
std::shared_ptr<IReader> CommonRTPSRouterParticipant<ConfigurationType>::create_reader_(
        RealTopic topic)
{
    return std::make_shared<Reader>(this->id(), topic, this->payload_pool_, rtps_participant_);
}

template <class ConfigurationType>
fastrtps::rtps::RTPSParticipantAttributes
CommonRTPSRouterParticipant<ConfigurationType>::participant_attributes_() const
{
    fastrtps::rtps::RTPSParticipantAttributes params;
    return params;
}

} /* namespace rtps */
} /* namespace ddsrouter */
} /* namespace eprosima */

#endif /* _DDSROUTER_PARTICIPANT_IMPLEMENTATIONS_AUX_COMMONRTPSROUTERPARTICIPANT_HPP_ */
