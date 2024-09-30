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
#include "test_pose_broadcaster.hpp"

#include <memory>
#include <utility>
#include <vector>

#include "geometry_msgs/msg/pose_stamped.hpp"
#include "hardware_interface/loaned_state_interface.hpp"
#include "rclcpp/executor.hpp"
#include "rclcpp/executors.hpp"
#include "rclcpp/utilities.hpp"

using hardware_interface::LoanedStateInterface;

void PoseBroadcasterTest::SetUp()
{
  pose_broadcaster_ = std::make_unique<FriendPoseBroadcaster>();

  const auto result = pose_broadcaster_->init(
    "test_pose_broadcaster", "", 0, "", pose_broadcaster_->define_custom_node_options());
  ASSERT_EQ(result, controller_interface::return_type::OK);

  std::vector<LoanedStateInterface> state_ifs;
  state_ifs.emplace_back(pose_position_x_);
  state_ifs.emplace_back(pose_position_y_);
  state_ifs.emplace_back(pose_position_z_);
  state_ifs.emplace_back(pose_orientation_x_);
  state_ifs.emplace_back(pose_orientation_y_);
  state_ifs.emplace_back(pose_orientation_z_);
  state_ifs.emplace_back(pose_orientation_w_);

  pose_broadcaster_->assign_interfaces({}, std::move(state_ifs));
}

void PoseBroadcasterTest::TearDown() { pose_broadcaster_.reset(); }

TEST_F(PoseBroadcasterTest, SensorName_InterfaceNames_NotSet) {}

int main(int argc, char * argv[])
{
  ::testing::InitGoogleMock(&argc, argv);
  rclcpp::init(argc, argv);

  int result = RUN_ALL_TESTS();
  rclcpp::shutdown();

  return result;
}
