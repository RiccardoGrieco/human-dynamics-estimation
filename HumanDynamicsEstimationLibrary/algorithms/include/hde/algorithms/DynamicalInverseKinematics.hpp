/*
 * Copyright (C) 2021 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * GNU Lesser General Public License v2.1 or any later version.
 */

#ifndef DYNAMICALINVERSEKINEMATICS_HPP
#define DYNAMICALINVERSEKINEMATICS_HPP

#include <iDynTree/Core/VectorDynSize.h>
#include <iDynTree/Core/MatrixDynSize.h>
#include <iDynTree/Model/Model.h>

#include <map>
#include <memory>

namespace hde::algorithms {
    class DynamicalInverseKinematics;
} // namespace hde

class hde::algorithms::DynamicalInverseKinematics
{
private:
    class impl;
    std::unique_ptr<impl> pImpl;

public:

    DynamicalInverseKinematics();
    ~DynamicalInverseKinematics();

    bool setModel(const iDynTree::Model& model);
    bool setFloatingBaseOnFrameNamed(const std::string& floatingBaseFrameName);
    bool setInverseVelocityKinematicsResolutionMode(const std::string& resolutionModeName);
    void setInverseVelocityKinematicsRegularization(const double regularizationWeight);


    bool addPoseAndVelocityTarget(const std::string& linkName,
                                  const iDynTree::Transform& transform,
                                  const iDynTree::Twist& twist,
                                  const double positionTargetWeight = 1.0,
                                  const double rotationTargetWeight = 1.0,
                                  const double linearVelocityWeight = 1.0,
                                  const double angularVelocityWeight = 1.0);
    bool addPoseTarget(const std::string& linkName,
                       const iDynTree::Transform& transform,
                       const double positionTargetWeight = 1.0,
                       const double rotationTargetWeight = 1.0);
    bool addPoseAndVelocityTarget(const std::string& linkName,
                                  const iDynTree::Vector3& position,
                                  const iDynTree::Rotation& rotation,
                                  const iDynTree::Vector3& linearVelocity,
                                  const iDynTree::Vector3& angularVelocity,
                                  const double positionTargetWeight = 1.0,
                                  const double rotationTargetWeight = 1.0,
                                  const double linearVelocityWeight = 1.0,
                                  const double angularVelocityWeight = 1.0);
    bool addPoseTarget(const std::string& linkName,
                       const iDynTree::Vector3& position,
                       const iDynTree::Rotation& rotation,
                       const double positionTargetWeight = 1.0,
                       const double rotationTargetWeight = 1.0);
    bool addPositionAndVelocityTarget(const std::string& linkName,
                                      const iDynTree::Vector3& position,
                                      const iDynTree::Vector3& linearVelocity,
                                      const double positionTargetWeight = 1.0,
                                      const double linearVelocityWeight = 1.0);
    bool addPositionTarget(const std::string& linkName,
                           const iDynTree::Vector3& position,
                           const double positionTargetWeight = 1.0);
    bool addOrientationAndVelocityTarget(const std::string& linkName,
                                         const iDynTree::Rotation& orientation,
                                         const iDynTree::Vector3& angularVelocity,
                                         const double orientationTargetWeight = 1.0,
                                         const double angularVelocityWeight = 1.0);
    bool addOrientationTarget(const std::string& linkName,
                              const iDynTree::Rotation& orientation,
                              const double orientationTargetWeight = 1.0);

    bool setJointConfiguration(const std::string& jointName, const double jointConfiguration);
    bool setJointsConfiguration(const iDynTree::VectorDynSize& jointsConfiguration);
    bool setBasePose(const iDynTree::Transform& baseTransform);
    bool setBasePose(const iDynTree::Vector3& basePosition, const iDynTree::Rotation& baseRotation);
    bool setConfiguration(const iDynTree::Transform& baseTransform,
                          const iDynTree::VectorDynSize& jointsConfiguration);
    bool setConfiguration(const iDynTree::Vector3& basePosition,
                          const iDynTree::Rotation& baseRotation,
                          const iDynTree::VectorDynSize& jointsConfiguration);

    bool getJointsConfigurationSolution(iDynTree::VectorDynSize& jointsConfiguration) const;
    bool getBasePoseSolution(iDynTree::Transform& baseTransform) const;
    bool getBasePoseSolution(iDynTree::Vector3& basePosition, iDynTree::Rotation& baseRotation) const;
    bool getConfigurationSolution(iDynTree::Transform& baseTransform,
                                  iDynTree::VectorDynSize& jointsConfiguration) const;
    bool getConfigurationSolution(iDynTree::Vector3& basePosition,
                                  iDynTree::Rotation& baseRotation,
                                  iDynTree::VectorDynSize& jointsConfiguration) const;
    bool getVelocitySolution(iDynTree::Twist& baseVelocity,
                             iDynTree::VectorDynSize& jointsVelocity) const;
    bool getJointsVelocitySolution(iDynTree::VectorDynSize& jointsVelocity) const;
    bool getBaseVelocitySolution(iDynTree::Twist& baseVelocity) const;
    bool getBaseVelocitySolution(iDynTree::Vector3& linearVelocity,
                                 iDynTree::Vector3& angularVelocity) const;

    void clearProblem();



    // // TODO
    // // addFrameVelocityConstraint
    // // addFrameLinearVelocityConstraint
    // // addFrameAngularVelocityConstraint


    // // TODO
    // bool setCustomBaseVelocityLimit(const iDynTree::VectorDynSize& lowerBound,
    //                                 const iDynTree::VectorDynSize& upperBound);
    // // bool setBaseLinearVelocityLimit();
    // // bool setBaseAngularVelocityLimit();
    // // bool setJointVelocityLimit(std::string jointName, double jointLimit);
    // bool setCustomJointsVelocityLimit(const std::vector<iDynTree::JointIndex>& jointsIndexList,
    //                                   const iDynTree::VectorDynSize& jointsLimitList);
    // bool setCustomConstraintsJointsValues(const std::vector<iDynTree::JointIndex>& jointsIndexList,
    //                                       const iDynTree::VectorDynSize& upperBoundary,
    //                                       const iDynTree::VectorDynSize& lowerBoundary,
    //                                       const iDynTree::MatrixDynSize& customConstraintMatrix,
    //                                       const double k_u,
    //                                       const double k_l);

    // bool setGeneralJointVelocityConstraints(const double jointVelocityLimit);

    // bool setGeneralJointsUpperLowerConstraints(const iDynTree::VectorDynSize& jointUpperLimits,
    //                                            const iDynTree::VectorDynSize& jointLowerLimits);

    // bool updateTarget(const std::string& linkName,
    //                   const iDynTree::Vector3& linearVelocity,
    //                   const iDynTree::Vector3& angularVelocity,
    //                   const double linearWeight = 1.0,
    //                   const double angularWeight = 1.0);
    // bool updateTarget(const std::string& linkName,
    //                   const iDynTree::Twist& twist,
    //                   const double linearWeight = 1.0,
    //                   const double angularWeight = 1.0);
    // bool updateLinearVelocityTarget(const std::string& linkName,
    //                                 const iDynTree::Vector3& linearVelocity,
    //                                 const double linearWeight = 1.0);
    // bool updateAngularVelocityTarget(const std::string& linkName,
    //                                  const iDynTree::Vector3& angularVelocity,
    //                                  const double angularWeight = 1.0);



    // bool solve();

};

#endif // DYNAMICALINVERSEKINEMATICS_HPP