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

################
# DDS Test WAN #
################

set(TEST_NAME
    DDSTestWAN)

set(TEST_SOURCES
    DDSTestWAN.cpp
    ${PROJECT_SOURCE_DIR}/test/blackbox/ddsrouter_core/dds/types/HelloWorld/HelloWorld.cxx
    ${PROJECT_SOURCE_DIR}/test/blackbox/ddsrouter_core/dds/types/HelloWorld/HelloWorldPubSubTypes.cxx
    ${PROJECT_SOURCE_DIR}/test/blackbox/ddsrouter_core/dds/types/HelloWorldKeyed/HelloWorldKeyed.cxx
    ${PROJECT_SOURCE_DIR}/test/blackbox/ddsrouter_core/dds/types/HelloWorldKeyed/HelloWorldKeyedPubSubTypes.cxx)

set(TEST_LIST
    end_to_end_WAN_communication_UDPv4
    end_to_end_WAN_communication_UDPv6
    end_to_end_WAN_communication_TCPv4
    end_to_end_WAN_communication_TCPv6
    end_to_end_WAN_communication_TLSv4
    end_to_end_WAN_communication_TLSv6)

set(TEST_NEEDED_SOURCES
    # UDPv4
    ../../resources/configurations/dds/WAN/UDP/IPv4/server.yaml
    ../../resources/configurations/dds/WAN/UDP/IPv4/client.yaml
    ../../resources/configurations/dds/WAN/UDP/IPv4/server-client-A.yaml
    ../../resources/configurations/dds/WAN/UDP/IPv4/server-client-B.yaml
    # UDPv6
    ../../resources/configurations/dds/WAN/UDP/IPv6/server.yaml
    ../../resources/configurations/dds/WAN/UDP/IPv6/client.yaml
    ../../resources/configurations/dds/WAN/UDP/IPv6/server-client-A.yaml
    ../../resources/configurations/dds/WAN/UDP/IPv6/server-client-B.yaml
    # TCPv4
    ../../resources/configurations/dds/WAN/TCP/IPv4/server.yaml
    ../../resources/configurations/dds/WAN/TCP/IPv4/client.yaml
    ../../resources/configurations/dds/WAN/TCP/IPv4/server-client-A.yaml
    ../../resources/configurations/dds/WAN/TCP/IPv4/server-client-B.yaml
    # TCPv6
    ../../resources/configurations/dds/WAN/TCP/IPv6/server.yaml
    ../../resources/configurations/dds/WAN/TCP/IPv6/client.yaml
    ../../resources/configurations/dds/WAN/TCP/IPv6/server-client-A.yaml
    ../../resources/configurations/dds/WAN/TCP/IPv6/server-client-B.yaml
    # TLSv4
    ../../resources/configurations/dds/WAN/TLS/IPv4/server.yaml
    ../../resources/configurations/dds/WAN/TLS/IPv4/client.yaml
    ../../resources/configurations/dds/WAN/TLS/IPv4/server-client-A.yaml
    ../../resources/configurations/dds/WAN/TLS/IPv4/server-client-B.yaml
    # TLSv6
    ../../resources/configurations/dds/WAN/TLS/IPv6/server.yaml
    ../../resources/configurations/dds/WAN/TLS/IPv6/client.yaml
    ../../resources/configurations/dds/WAN/TLS/IPv6/server-client-A.yaml
    ../../resources/configurations/dds/WAN/TLS/IPv6/server-client-B.yaml
    # TLS security files
    ../../resources/configurations/dds/WAN/TLS/security/ca.crt
    ../../resources/configurations/dds/WAN/TLS/security/ddsrouter.crt
    ../../resources/configurations/dds/WAN/TLS/security/ddsrouter.key
    ../../resources/configurations/dds/WAN/TLS/security/dh_params.pem)

set(TEST_EXTRA_HEADERS
    ${PROJECT_SOURCE_DIR}/test/blackbox/ddsrouter_core/dds/types/HelloWorld
    ${PROJECT_SOURCE_DIR}/test/blackbox/ddsrouter_core/dds/types)

add_blackbox_executable(
    "${TEST_NAME}"
    "${TEST_SOURCES}"
    "${TEST_LIST}"
    "${TEST_NEEDED_SOURCES}"
    "${TEST_EXTRA_HEADERS}"
    "${TEST_XFAIL_FILES}")

# Set flaky tests as xfail
add_xfail_label(${CMAKE_CURRENT_SOURCE_DIR}/TEST_XFAIL.list)
