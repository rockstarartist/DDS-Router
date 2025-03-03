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
# Trivial Test #
################

set(TEST_NAME
    TrivialTest)

set(TEST_SOURCES
    TrivialTest.cpp)

set(TEST_LIST
    trivial_void_initialization
    trivial_dummy_initialization
    trivial_communication)

set(TEST_NEEDED_SOURCES
    ../resources/configurations/trivial/trivial_test_dummy_configuration.yaml
    ../resources/configurations/trivial/trivial_test_void_configuration.yaml)

add_blackbox_executable(
    "${TEST_NAME}"
    "${TEST_SOURCES}"
    "${TEST_LIST}"
    "${TEST_NEEDED_SOURCES}")
