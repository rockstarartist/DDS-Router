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

######################
# Discovery Database #
######################

set(TEST_NAME DiscoveryDatabaseTest)

set(TEST_SOURCES
        DiscoveryDatabaseTest.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/dynamic/DiscoveryDatabase.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/exceptions/Exception.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/endpoint/Endpoint.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/endpoint/QoS.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/ReturnCode.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/topic/RealTopic.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/topic/Topic.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/utils.cpp
        ${PROJECT_SOURCE_DIR}/test/TestUtils/test_utils.cpp
    )

set(TEST_LIST
    topic_exists
    endpoint_exists
    add_endpoint
    update_endpoint
    erase_endpoint
    get_endpoint
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
        "${TEST_EXTRA_LIBRARIES}"
    )
