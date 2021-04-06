/*********************************************************************
 *
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2016,
 *  TU Dortmund - Institute of Control Theory and Systems Engineering.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the institute nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 * 
 * Notes:
 * The following class is derived from a class defined by the
 * g2o-framework. g2o is licensed under the terms of the BSD License.
 * Refer to the base class source for detailed licensing information.
 *
 * Author: Christoph Rösmann, Franz Albers
 *********************************************************************/

#ifndef EDGE_DYNAMICOBSTACLE_H
#define EDGE_DYNAMICOBSTACLE_H

#include <teb_local_planner/g2o_types/vertex_pose.h>
#include <teb_local_planner/g2o_types/vertex_timediff.h>
#include <teb_local_planner/g2o_types/penalties.h>
#include <teb_local_planner/g2o_types/base_teb_edges.h>
#include <teb_local_planner/obstacles.h>
#include <teb_local_planner/teb_config.h>
#include <teb_local_planner/robot_footprint_model.h>

namespace teb_local_planner
{
  
/**
 * @class EdgeDynamicObstacle
 * @brief Edge defining the cost function for keeping a distance from dynamic (moving) obstacles.
 * 
 * The edge depends on two vertices \f$ \mathbf{s}_i, \Delta T_i \f$ and minimizes: \n
 * \f$ \min \textrm{penaltyBelow}( dist2obstacle) \cdot weight \f$. \n
 * \e dist2obstacle denotes the minimum distance to the obstacle trajectory (spatial and temporal). \n
 * \e weight can be set using setInformation(). \n
 * \e penaltyBelow denotes the penalty function, see penaltyBoundFromBelow(). \n
 * @see TebOptimalPlanner::AddEdgesDynamicObstacles
 * @remarks Do not forget to call setTebConfig(), setVertexIdx() and 
 * @warning Experimental
 */  
class EdgeDynamicObstacle : public BaseTebUnaryEdge<2, const Obstacle*, VertexPose>
{
public:
  
  /**
   * @brief Construct edge.
   */    
  EdgeDynamicObstacle() : t_(0)
  {
  }
  
  /**
   * @brief Construct edge and specify the time for its associated pose (neccessary for computeError).
   * @param t_ Estimated time until current pose is reached
   */      
  EdgeDynamicObstacle(double t) : t_(t)
  {
  }
  
  /**
   * @brief Actual cost function
   */   
  void computeError()
  {
    ROS_ASSERT_MSG(cfg_ && _measurement && robot_model_, "You must call setTebConfig(), setObstacle() and setRobotModel() on EdgeDynamicObstacle()");
    const VertexPose* bandpt = static_cast<const VertexPose*>(_vertices[0]);

    //std::cout << std::endl << t_ << std::endl;
    double dist = robot_model_->estimateSpatioTemporalDistance(bandpt->pose(), _measurement, t_);

    _error[0] = penaltyBoundFromBelow(dist, cfg_->obstacles.min_obstacle_dist, cfg_->optim.penalty_epsilon);
    _error[1] = penaltyBoundFromBelow(dist, cfg_->obstacles.dynamic_obstacle_inflation_dist, 0.0);

    //std::cout << "EdgeDynamicObstacle::computeError() dist = " << dist << std::endl;
    //std::cout << "EdgeDynamicObstacle::computeError() _error[0] = " << _error[0] << std::endl;
    //std::cout << "EdgeDynamicObstacle::computeError() _error[1] = " << _error[1] << std::endl;

    ROS_ASSERT_MSG(std::isfinite(_error[0]), "EdgeDynamicObstacle::computeError() _error[0]=%f\n",_error[0]);
  }
  
  
  /**
   * @brief Set Obstacle for the underlying cost function
   * @param obstacle Const pointer to an Obstacle or derived Obstacle
   */     
  void setObstacle(const Obstacle* obstacle)
  {
    _measurement = obstacle;
  }
  
  /**
   * @brief Set pointer to the robot model
   * @param robot_model Robot model required for distance calculation
   */
  void setRobotModel(const BaseRobotFootprintModel* robot_model)
  {
    robot_model_ = robot_model;
  }

  /**
   * @brief Set all parameters at once
   * @param cfg TebConfig class
   * @param robot_model Robot model required for distance calculation
   * @param obstacle 2D position vector containing the position of the obstacle
   */
  void setParameters(const TebConfig& cfg, const BaseRobotFootprintModel* robot_model, const Obstacle* obstacle)
  {
    cfg_ = &cfg;
    robot_model_ = robot_model;
    _measurement = obstacle;
  }

protected:
  
  const BaseRobotFootprintModel* robot_model_; //!< Store pointer to robot_model
  double t_; //!< Estimated time until current pose is reached
  
public: 
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

};

/**
 * @class EdgeDynamicObstacle
 * @brief Edge defining the cost function for keeping a distance from dynamic (moving) obstacles.
 *
 * The edge depends on two vertices \f$ \mathbf{s}_i, \Delta T_i \f$ and minimizes: \n
 * \f$ \min \textrm{penaltyBelow}( dist2obstacle) \cdot weight \f$. \n
 * \e dist2obstacle denotes the minimum distance to the obstacle trajectory (spatial and temporal). \n
 * \e weight can be set using setInformation(). \n
 * \e penaltyBelow denotes the penalty function, see penaltyBoundFromBelow(). \n
 * @see TebOptimalPlanner::AddEdgesDynamicObstacles
 * @remarks Do not forget to call setTebConfig(), setVertexIdx() and
 * @warning Experimental
 */
class EdgeDynamicObstacle_dynSize : public BaseTebUnaryEdge<2, const Obstacle*, VertexPose>
{
public:

  /**
   * @brief Construct edge.
   */
  EdgeDynamicObstacle_dynSize() : t_(0)
  {
  }

  /**
   * @brief Construct edge and specify the time for its associated pose (neccessary for computeError).
   * @param t_ Estimated time until current pose is reached
   */
  EdgeDynamicObstacle_dynSize(double t) : t_(t)
  {
  }

  /**
   * @brief Actual cost function
   */
  void computeError()
  {
    ROS_ASSERT_MSG(cfg_ && _measurement && robot_model_, "You must call setTebConfig(), setObstacle() and setRobotModel() on EdgeDynamicObstacle()");
    const VertexPose* bandpt = static_cast<const VertexPose*>(_vertices[0]);

    double distPoseToObst = (bandpt->position()-_measurement->getCentroid()).norm();
//    if (distPoseToObst > 30)
//    {
//        distPoseToObst = 30;
//    }
    double dist = robot_model_->estimateSpatioTemporalDistance(bandpt->pose(), _measurement, t_);

    _error[0] = penaltyBoundFromBelow(dist, cfg_->obstacles.min_obstacle_dist+cfg_->obstacles.min_obstacle_dist*distPoseToObst*0.1, cfg_->optim.penalty_epsilon);
    _error[1] = penaltyBoundFromBelow(dist, cfg_->obstacles.dynamic_obstacle_inflation_dist, 0.0);

    //std::cout << "EdgeDynamicObstacle_dynSize::computeError() dist = " << dist << std::endl;
    //std::cout << "EdgeDynamicObstacle_dynSize::computeError() _error[0] = " << _error[0] << std::endl;
    //std::cout << "EdgeDynamicObstacle_dynSize::computeError() _error[1] = " << _error[1] << std::endl;

    ROS_ASSERT_MSG(std::isfinite(_error[0]), "EdgeDynamicObstacle_dynSize::computeError() _error[0]=%f\n",_error[0]);
  }


  /**
   * @brief Set Obstacle for the underlying cost function
   * @param obstacle Const pointer to an Obstacle or derived Obstacle
   */
  void setObstacle(const Obstacle* obstacle)
  {
    _measurement = obstacle;
  }

  /**
   * @brief Set pointer to the robot model
   * @param robot_model Robot model required for distance calculation
   */
  void setRobotModel(const BaseRobotFootprintModel* robot_model)
  {
    robot_model_ = robot_model;
  }

  /**
   * @brief Set all parameters at once
   * @param cfg TebConfig class
   * @param robot_model Robot model required for distance calculation
   * @param obstacle 2D position vector containing the position of the obstacle
   */
  void setParameters(const TebConfig& cfg, const BaseRobotFootprintModel* robot_model, const Obstacle* obstacle)
  {
    cfg_ = &cfg;
    robot_model_ = robot_model;
    _measurement = obstacle;
  }

protected:

  const BaseRobotFootprintModel* robot_model_; //!< Store pointer to robot_model
  double t_; //!< Estimated time until current pose is reached

public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

};
    
/**
 * @class EdgeDynamicObstacle_wide
 * @brief Edge defining the cost function for keeping a distance from dynamic (moving) obstacles.
 *
 * The edge depends on config.numberDynamicVertices+1 vertices \f$ \mathbf{s}_i, \Delta T_i \f$ and minimizes: \n
 * \f$ \min \textrm{penaltyBelow}( dist2obstacle) \cdot weight \f$. \n
 * \e dist2obstacle denotes the minimum distance to the obstacle trajectory (spatial and temporal). \n
 * \e weight can be set using setInformation(). \n
 * \e penaltyBelow denotes the penalty function, see penaltyBoundFromBelow(). \n
 * @see TebOptimalPlanner::AddEdgesDynamicObstacles
 * @remarks Do not forget to call setTebConfig(), setVertexIdx() and
 * @warning Experimental
 */
class EdgeDynamicObstacle_wide : public BaseTebMultiEdge<2, const Obstacle*>
{
public:

  /**
   * @brief Construct edge.
   */
  EdgeDynamicObstacle_wide() : t_(0)
  {
  }

  /**
   * @brief Construct edge and specify the time for its associated pose (neccessary for computeError).
   * @param t_ Estimated time until current pose is reached
   */
  EdgeDynamicObstacle_wide(uint8_t n, double t) : t_(t)
  {
      this->resize(n);
  }

  /**
   * @brief Actual cost function
   */
  void computeError()
  {
    ROS_ASSERT_MSG(cfg_ && _measurement && robot_model_, "You must call setTebConfig(), setObstacle() and setRobotModel() on EdgeDynamicObstacle_wide()");

    _error[0] = 0;
    _error[1] = 0;
    for (auto& vertix : _vertices)
    {
        const VertexPose* bandpt = static_cast<const VertexPose*>(vertix);
        double dist = robot_model_->estimateSpatioTemporalDistance(bandpt->pose(), _measurement, t_);

        _error[0] += penaltyBoundFromBelow(dist, cfg_->obstacles.min_obstacle_dist, cfg_->optim.penalty_epsilon);
        _error[1] += penaltyBoundFromBelow(dist, cfg_->obstacles.dynamic_obstacle_inflation_dist, 0.0);
    }

    //std::cout << "EdgeDynamicObstacle_wide::computeError() dist = " << dist << std::endl;
    //std::cout << "EdgeDynamicObstacle_wide::computeError() _error[0] = " << _error[0] << std::endl;
    //std::cout << "EdgeDynamicObstacle_wide::computeError() _error[1] = " << _error[1] << std::endl;

    ROS_ASSERT_MSG(std::isfinite(_error[0]), "EdgeDynamicObstacle_wide::computeError() _error[0]=%f\n",_error[0]);
  }


  /**
   * @brief Set Obstacle for the underlying cost function
   * @param obstacle Const pointer to an Obstacle or derived Obstacle
   */
  void setObstacle(const Obstacle* obstacle)
  {
    _measurement = obstacle;
  }

  /**
   * @brief Set pointer to the robot model
   * @param robot_model Robot model required for distance calculation
   */
  void setRobotModel(const BaseRobotFootprintModel* robot_model)
  {
    robot_model_ = robot_model;
  }

  /**
   * @brief Set all parameters at once
   * @param cfg TebConfig class
   * @param robot_model Robot model required for distance calculation
   * @param obstacle 2D position vector containing the position of the obstacle
   */
  void setParameters(const TebConfig& cfg, const BaseRobotFootprintModel* robot_model, const Obstacle* obstacle)
  {
    cfg_ = &cfg;
    robot_model_ = robot_model;
    _measurement = obstacle;
  }

protected:

  const BaseRobotFootprintModel* robot_model_; //!< Store pointer to robot_model
  double t_; //!< Estimated time until current pose is reached

public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

};
    
/**
 * @class EdgeDynamicObstacle_fullTEB
 * @brief Edge defining the cost function for keeping a distance from dynamic (moving) obstacles.
 *
 * The edge depends on config.numberDynamicVertices+1 vertices \f$ \mathbf{s}_i, \Delta T_i \f$ and minimizes: \n
 * \f$ \min \textrm{penaltyBelow}( dist2obstacle) \cdot weight \f$. \n
 * \e dist2obstacle denotes the minimum distance to the obstacle trajectory (spatial and temporal). \n
 * \e weight can be set using setInformation(). \n
 * \e penaltyBelow denotes the penalty function, see penaltyBoundFromBelow(). \n
 * @see TebOptimalPlanner::AddEdgesDynamicObstacles
 * @remarks Do not forget to call setTebConfig(), setVertexIdx() and
 * @warning Experimental
 */
class EdgeDynamicObstacle_fullTEB : public BaseTebMultiEdge<1, const Obstacle*>
{
public:

  /**
   * @brief Construct edge.
   */
  EdgeDynamicObstacle_fullTEB()
  {
  }

  /**
   * @brief Construct edge and specify the time for its associated pose (neccessary for computeError).
   * @param t_ Estimated time until current pose is reached
   */
  EdgeDynamicObstacle_fullTEB(uint8_t n)
  {
      this->resize(n);
      timeDiff = std::vector<double>(n, 0);
  }

  /**
   * @brief Actual cost function
   */
  void computeError()
  {
    ROS_ASSERT_MSG(cfg_ && _measurement && robot_model_, "You must call setTebConfig(), setObstacle() and setRobotModel() on EdgeDynamicObstacle_fullTEB()");

    _error[0] = 0;
    //_error[1] = 0;
    for (int i=0; i<_vertices.size(); ++i)
    //for (auto& vertix : _vertices)
    {
        const VertexPose* bandpt = static_cast<const VertexPose*>(_vertices[i]);
        double dist = robot_model_->estimateSpatioTemporalDistance(bandpt->pose(), _measurement, timeDiff[i]);

        _error[0] += penaltyBoundFromBelow(dist, cfg_->obstacles.min_obstacle_dist, cfg_->optim.penalty_epsilon);
        //_error[1] += penaltyBoundFromBelow(dist, cfg_->obstacles.dynamic_obstacle_inflation_dist, 0.0);

//        double new_error0 = penaltyBoundFromBelow(dist, cfg_->obstacles.min_obstacle_dist, cfg_->optim.penalty_epsilon);
//        double new_error1 = penaltyBoundFromBelow(dist, cfg_->obstacles.dynamic_obstacle_inflation_dist, 0.0);
//        if (new_error0 > _error[0])
//        {
//            _error[0] = new_error0;
//            _error[1] = new_error1;
//        }
    }

    //std::cout << "EdgeDynamicObstacle_fullTEB::computeError() dist = " << dist << std::endl;
    //std::cout << "EdgeDynamicObstacle_fullTEB::computeError() _error[0] = " << _error[0] << std::endl;
    //std::cout << "EdgeDynamicObstacle_fullTEB::computeError() _error[1] = " << _error[1] << std::endl;

    ROS_ASSERT_MSG(std::isfinite(_error[0]), "EdgeDynamicObstacle_fullTEB::computeError() _error[0]=%f\n",_error[0]);
  }


  /**
   * @brief Set Obstacle for the underlying cost function
   * @param obstacle Const pointer to an Obstacle or derived Obstacle
   */
  void setObstacle(const Obstacle* obstacle)
  {
    _measurement = obstacle;
  }

  /**
   * @brief Set pointer to the robot model
   * @param robot_model Robot model required for distance calculation
   */
  void setRobotModel(const BaseRobotFootprintModel* robot_model)
  {
    robot_model_ = robot_model;
  }

  /**
   * @brief Set all parameters at once
   * @param cfg TebConfig class
   * @param robot_model Robot model required for distance calculation
   * @param obstacle 2D position vector containing the position of the obstacle
   */
  void setParameters(const TebConfig& cfg, const BaseRobotFootprintModel* robot_model, const Obstacle* obstacle)
  {
    cfg_ = &cfg;
    robot_model_ = robot_model;
    _measurement = obstacle;
  }

  /**
   * @brief Set the timeDiff value for one vertex
   * @param t TimeDiff value
   */
  void setTimeDiff(const uint8_t i, const double t)
  {
    timeDiff[i] = t;
  }

protected:

  const BaseRobotFootprintModel* robot_model_; //!< Store pointer to robot_model
  std::vector<double> timeDiff; //!< Estimated time until current pose is reached

public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

};

/**
 * @class EdgeDynamicObstacle_time
 * @brief Edge defining the cost function for keeping a distance from dynamic (moving) obstacles.
 *
 * The edge depends on config.numberDynamicVertices+1 vertices \f$ \mathbf{s}_i, \Delta T_i \f$ and minimizes: \n
 * \f$ \min \textrm{penaltyBelow}( dist2obstacle) \cdot weight \f$. \n
 * \e dist2obstacle denotes the minimum distance to the obstacle trajectory (spatial and temporal). \n
 * \e weight can be set using setInformation(). \n
 * \e penaltyBelow denotes the penalty function, see penaltyBoundFromBelow(). \n
 * @see TebOptimalPlanner::AddEdgesDynamicObstacles
 * @remarks Do not forget to call setTebConfig(), setVertexIdx() and
 * @warning Experimental
 */
class EdgeDynamicObstacle_time : public BaseTebMultiEdge<2, const Obstacle*>
{
public:

  /**
   * @brief Construct edge.
   */
  EdgeDynamicObstacle_time()
  {
  }

  /**
   * @brief Construct edge and specify the time for its associated pose (neccessary for computeError).
   * @param t_ Estimated time until current pose is reached
   */
  EdgeDynamicObstacle_time(uint8_t n)
  {
      this->resize(n);
  }

  /**
   * @brief Actual cost function
   */
  void computeError()
  {
    ROS_ASSERT_MSG(cfg_ && _measurement && robot_model_, "You must call setTebConfig(), setObstacle() and setRobotModel() on EdgeDynamicObstacle_time()");

    double time = 0;
    for(int i=1; i<_vertices.size(); ++i)
    {
        const VertexTimeDiff* timediff = static_cast<const VertexTimeDiff*>(_vertices[i]);
        time += timediff->dt();
    }
    //std::cout << std::endl << time << std::endl;
    const VertexPose* bandpt = static_cast<const VertexPose*>(_vertices[0]);
    double dist = robot_model_->estimateSpatioTemporalDistance(bandpt->pose(), _measurement, time);

    double t = time/(_vertices.size()-1);
    _error[0] = penaltyBoundFromBelow(dist, cfg_->obstacles.min_obstacle_dist, cfg_->optim.penalty_epsilon);
    _error[1] = -penaltyBoundFromBelowDerivative(dist, cfg_->obstacles.min_obstacle_dist, cfg_->optim.penalty_epsilon)*(1/t);

    //inflation:
    //_error[1] = penaltyBoundFromBelow(dist, cfg_->obstacles.dynamic_obstacle_inflation_dist, 0.0);

    //std::cout << "EdgeDynamicObstacle_time::computeError() _error[0] = " << _error[0] << std::endl;
    //_error[0] = _error[0]/time;
    //std::cout << "EdgeDynamicObstacle_time::computeError() dist = " << dist << " t = " << t << std::endl;
    //std::cout << "EdgeDynamicObstacle_time::computeError() _error[0] = " << _error[0] << std::endl;
    //std::cout << "EdgeDynamicObstacle_time::computeError() _error[1] = " << _error[1] << std::endl;

    ROS_ASSERT_MSG(std::isfinite(_error[0]), "EdgeDynamicObstacle_time::computeError() _error[0]=%f\n",_error[0]);
  }


  /**
   * @brief Set Obstacle for the underlying cost function
   * @param obstacle Const pointer to an Obstacle or derived Obstacle
   */
  void setObstacle(const Obstacle* obstacle)
  {
    _measurement = obstacle;
  }

  /**
   * @brief Set pointer to the robot model
   * @param robot_model Robot model required for distance calculation
   */
  void setRobotModel(const BaseRobotFootprintModel* robot_model)
  {
    robot_model_ = robot_model;
  }

  /**
   * @brief Set all parameters at once
   * @param cfg TebConfig class
   * @param robot_model Robot model required for distance calculation
   * @param obstacle 2D position vector containing the position of the obstacle
   */
  void setParameters(const TebConfig& cfg, const BaseRobotFootprintModel* robot_model, const Obstacle* obstacle)
  {
    cfg_ = &cfg;
    robot_model_ = robot_model;
    _measurement = obstacle;
  }

protected:

  const BaseRobotFootprintModel* robot_model_; //!< Store pointer to robot_model

public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

};

} // end namespace

#endif
