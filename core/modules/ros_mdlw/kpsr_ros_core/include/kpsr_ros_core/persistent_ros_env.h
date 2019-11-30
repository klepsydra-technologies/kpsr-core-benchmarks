/****************************************************************************
*
*                           Klepsydra Core Modules
*              Copyright (C) 2019-2020  Klepsydra Technologies GmbH
*                            All Rights Reserved.
*
*  This file is subject to the terms and conditions defined in
*  file 'LICENSE.md', which is part of this source code package.
*
*  NOTICE:  All information contained herein is, and remains the property of Klepsydra
*  Technologies GmbH and its suppliers, if any. The intellectual and technical concepts
*  contained herein are proprietary to Klepsydra Technologies GmbH and its suppliers and
*  may be covered by Swiss and Foreign Patents, patents in process, and are protected by
*  trade secret or copyright law. Dissemination of this information or reproduction of
*  this material is strictly forbidden unless prior written permission is obtained from
*  Klepsydra Technologies GmbH.
*
****************************************************************************/

#ifndef PERSISTENT_ROS_ENV_H
#define PERSISTENT_ROS_ENV_H

#include "ros/ros.h"

#include <klepsydra/core/environment.h>
#include <klepsydra/core/yaml_environment.h>

namespace kpsr
{
namespace ros_mdlw
{
/**
 * @brief The PersistentRosEnv class
 *
 * @copyright Klepsydra Technologies 2019-2020.
 *
 * @version 2.0.1
 *
 * @ingroup kpsr-rosstg-composition
 *
 * @details Ros environment that includes a persistent facility to store the properties in a yaml file.
 * This file can then be read on startup. The way this works is that when a property is set through
 * the Klepsydra Environment class, ROS is updated via setParam and also a YAML file as well.
 *
 */
class PersistentRosEnv : public Environment
{
public:
   /**
    * @brief The PersitancePolicy enum. List of persistance policies to save the YAML file.
    */
    enum PersitancePolicy
    {
        NONE = 0,
        ON_GET,
        ON_SET,
        ON_PERSIST
    };

    /**
     * @brief PersistentRosEnv
     * @param nodeHandle
     * @param yamlFileName
     * @param persitancePolicy
     */
    PersistentRosEnv(ros::NodeHandle * nodeHandle, const std::string yamlFileName, const PersitancePolicy persitancePolicy);

    /**
     * @brief getPropertyString
     * @param key
     * @param value
     */
    void getPropertyString(const std::string key, std::string & value);

    /**
     * @brief getPropertyInt
     * @param key
     * @param value
     */
    void getPropertyInt(const std::string key, int & value);

    /**
     * @brief getPropertyFloat
     * @param key
     * @param value
     */
    void getPropertyFloat(const std::string key, float & value);

    /**
     * @brief getPropertyBool
     * @param key
     * @param value
     */
    void getPropertyBool(const std::string key, bool & value);

    /**
     * @brief setPropertyString
     * @param key
     * @param value
     */
    void setPropertyString(const std::string key, const std::string value);

    /**
     * @brief setPropertyInt
     * @param key
     * @param value
     */
    void setPropertyInt(const std::string key, const int & value);

    /**
     * @brief setPropertyFloat
     * @param key
     * @param value
     */
    void setPropertyFloat(const std::string key, const float & value);

    /**
     * @brief setPropertyBool
     * @param key
     * @param value
     */
    void setPropertyBool(const std::string key, const bool & value);

    /**
     * @brief persist YAML file persist method.
     */
    void persist();

private:
    ros::NodeHandle * _nodeHandle;
    YamlEnvironment * _persistentEnv;
    PersitancePolicy _persitancePolicy;

};
}
}
#endif
