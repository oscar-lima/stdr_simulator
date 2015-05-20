/******************************************************************************
   STDR Simulator - Simple Two DImensional Robot Simulator
   Copyright (C) 2013 STDR Simulator
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA

Authors:

Oscar Lima Carrion, olima_84@yahoo.com
Ashok Meenakshi, mashoksc@gmail.com
Seguey Alexandrov, sergeyalexandrov@mail.com

Review / Edits:
Manos Tsardoulias, etsardou@gmail.com

About this code:

This class represents a motion model for omnidirectional robot and could be
used to sample the possible pose given the starting pose and the commanded
robot's motion.

The two parameters of the class is standard deviations of translational and
rotational components of the motion.

The motion is decomposed into two translations alond the x axis of the
robot (forward), and along the y axis of the robot (lateral), and one
rotation.

Usage:

@code
  Create motion model with 0.02 and 0.01 stddev
    MotionModel motion_model(0.02, 0.01);
  Set the commanded robot's motion
    motion_model.setMotion(0.5, 0.1, 0.1);
  Sample the possible pose given the starting pose
  Note that it could be repeated multiple times for the same starting
  pose of for different starting poses
    Pose new_pose = motion_model.sample(pose);
******************************************************************************/

#ifndef OMNI_MOTION_CONTROLLER_H
#define OMNI_MOTION_CONTROLLER_H

#include <stdr_robot/motion/motion_controller_base.h>

/**
@namespace stdr_robot
@brief The main namespace for STDR Robot
**/ 
namespace stdr_robot 
{
  
  /**
  @class OmniMotionController
  @brief A class that provides motion controller implementation. \
  Inherits publicly MotionController
  **/ 
  class OmniMotionController : public MotionController 
  {
    
    public:
    
      /**
      @brief Default constructor
      @param pose [const geometry_msgs::Pose2D&] The robot pose
      @param tf [tf::TransformBroadcaster&] A ROS tf broadcaster
      @param n [ros::NodeHandle&] The ROS node handle
      @param name [const std::string&] The robot frame id
      @return void
      **/
      OmniMotionController(
        const geometry_msgs::Pose2D& pose, 
        tf::TransformBroadcaster& tf, 
        ros::NodeHandle& n, 
        const std::string& name);
      
      /**
      @brief Callback for velocity commands
      @param msg [const geometry_msgs::Twist&] The velocity command
      @return void
      **/
      void velocityCallback(const geometry_msgs::Twist& msg);
      
      /**
      @brief Stops the robot
      @return void
      **/
      void stop(void);
      
      /**
      @brief Calculates the motion - updates the robot pose
      @param event [const ros::TimerEvent&] A ROS timer event
      @return void
      **/
      void calculateMotion(const ros::TimerEvent& event);
      
      /**
      @brief Default destructor 
      @return void
      **/
      ~OmniMotionController(void);
  };
}


#endif