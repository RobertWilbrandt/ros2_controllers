// Copyright 2024 FZI Forschungszentrum Informatik
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
#ifndef TEST_POSE_BROADCASTER_HPP_
#define TEST_POSE_BROADCASTER_HPP_

#include <gmock/gmock.h>

#include <memory>
#include <string>

#include "pose_broadcaster/pose_broadcaster.hpp"

// subclassing and friending so we can access member variables
class FriendPoseBroadcaster : public pose_broadcaster::PoseBroadcaster
{
};

class PoseBroadcasterTest : public ::testing::Test
{
public:
  void SetUp() override;
  void TearDown() override;

protected:
  const std::string sensor_name_ = "pose_sensor";

  std::array<double, 7> sensor_values = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
  hardware_interface::StateInterface pose_position_x_{
    sensor_name_, "position.x", &sensor_values[0]};
  hardware_interface::StateInterface pose_position_y_{
    sensor_name_, "position.y", &sensor_values[1]};
  hardware_interface::StateInterface pose_position_z_{
    sensor_name_, "position.z", &sensor_values[2]};
  hardware_interface::StateInterface pose_orientation_x_{
    sensor_name_, "orientation.x", &sensor_values[3]};
  hardware_interface::StateInterface pose_orientation_y_{
    sensor_name_, "orientation.y", &sensor_values[4]};
  hardware_interface::StateInterface pose_orientation_z_{
    sensor_name_, "orientation.z", &sensor_values[5]};
  hardware_interface::StateInterface pose_orientation_w_{
    sensor_name_, "orientation.w", &sensor_values[6]};

  std::unique_ptr<FriendPoseBroadcaster> pose_broadcaster_;
};

#endif  // TEST_POSE_BROADCASTER_HPP_
