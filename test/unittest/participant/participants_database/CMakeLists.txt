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

#########################
# Participants Database #
#########################

set(TEST_NAME ParticipantsDatabaseTest)

set(TEST_SOURCES
        ParticipantsDatabaseTest.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/exceptions/Exception.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/participant/implementations/auxiliar/VoidParticipant.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/participant/ParticipantsDatabase.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/reader/implementations/auxiliar/VoidReader.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/participant/ParticipantId.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/participant/ParticipantType.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/utils.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/writer/implementations/auxiliar/VoidWriter.cpp
    )

set(TEST_LIST
        add_participant
        empty
        get_participant
        get_participants_ids
        get_participants_map
        pop
        size
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
