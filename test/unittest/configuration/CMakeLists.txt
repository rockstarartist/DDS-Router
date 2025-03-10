# Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

################################
# DDSRouter Configuration Test #
################################

set(TEST_NAME ConfigurationTest)

set(TEST_SOURCES
        ConfigurationTest.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/configuration/BaseConfiguration.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/configuration/DDSRouterConfiguration.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/configuration/ParticipantConfiguration.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/exceptions/Exception.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/participant/ParticipantId.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/participant/ParticipantType.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/topic/FilterTopic.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/topic/RealTopic.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/topic/Topic.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/topic/WildcardTopic.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/utils.cpp
    )

set(TEST_LIST
        constructor
        participants_configurations
        real_topics
        allowlist_wildcard
        blocklist_wildcard
        allowlist_and_blocklist
        constructor_fail
        participants_configurations_fail
        real_topics_fail
        allowlist_wildcard_fail
        blocklist_wildcard_fail
    )

set(TEST_EXTRA_LIBRARIES
        fastcdr
        fastrtps
        yaml-cpp
        $<$<BOOL:${WIN32}>:iphlpapi$<SEMICOLON>Shlwapi>
    )

add_unittest_executable(
    "${TEST_NAME}"
    "${TEST_SOURCES}"
    "${TEST_LIST}"
    "${TEST_EXTRA_LIBRARIES}")


##############################
# Address Configuration Test #
##############################

set(TEST_NAME AddressConfigurationTest)

set(TEST_SOURCES
    AddressConfigurationTest.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/exceptions/Exception.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/configuration/implementations/Address_configuration.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/address/Address.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/utils.cpp
    )

set(TEST_LIST
        yaml_port
        yaml_transport_protocol
        yaml_ipv4
        yaml_ipv6
        yaml_dns
        yaml_error_cases
    )

set(TEST_EXTRA_LIBRARIES
        fastcdr
        fastrtps
        yaml-cpp
        $<$<BOOL:${WIN32}>:iphlpapi$<SEMICOLON>Shlwapi>
    )

add_unittest_executable(
    "${TEST_NAME}"
    "${TEST_SOURCES}"
    "${TEST_LIST}"
    "${TEST_EXTRA_LIBRARIES}")
