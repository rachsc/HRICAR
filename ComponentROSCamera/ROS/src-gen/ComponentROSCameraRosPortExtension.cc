//--------------------------------------------------------------------------
// This file is generated by the SeRoNet Tooling. The SeRoNet Tooling is 
// developed by the SeRoNet Project consortium: 
// http://www.seronet-projekt.de
//
// The ROS Mixed-Port Component is developed by:
// Service Robotics Research Center of Ulm University of Applied Sciences
// Fraunhofer Institute for Manufacturing Engineering and Automation IPA
//
// This code-generator uses infrastructure of the SmartMDSD Toolchain on
// which the SeRoNet Tooling is based on.
//
// CAUTION: 
// This software is a preview for the purpose of technology demonstration. 
// It is experimental and comes with no support. Use at your own risk.
// Please do not modify this file. It will be re-generated
// running the code generator.
//--------------------------------------------------------------------------

#include "ComponentROSCameraRosPortExtension.hh"

// statically create a global PlainOpcUaComponentROSCameraExtension instance
static ComponentROSCameraRosPortExtension ros_port_extension;

ComponentROSCameraRosPortExtension::ComponentROSCameraRosPortExtension()
:	ComponentROSCameraExtension("ComponentROSCameraRosPortExtension")
{
	nh = 0;
	callbacksPtr = 0;
}

ComponentROSCameraRosPortExtension::~ComponentROSCameraRosPortExtension()
{  }

void ComponentROSCameraRosPortExtension::loadParameters(const SmartACE::SmartIniParameter &parameter)
{  }

void ComponentROSCameraRosPortExtension::initialize(ComponentROSCamera *component, int argc, char* argv[])
{
	ros::init(argc, argv, "ComponentROSCamera", ros::init_options::NoSigintHandler);
	nh = new ros::NodeHandle();
	
	callbacksPtr = new ComponentROSCameraRosPortCallbacks();
	
	component->rosPorts = this;
	
	_cam = nh->subscribe("/usb_cam/image_raw", 10, &ComponentROSCameraRosPortCallbacks::_cam_cb, callbacksPtr);
}

int ComponentROSCameraRosPortExtension::onStartup()
{
	return startExtensionThread();
}

int ComponentROSCameraRosPortExtension::extensionExecution()
{
	ros::spin();
	return 0;
}

int ComponentROSCameraRosPortExtension::onShutdown(const std::chrono::steady_clock::duration &timeoutTime)
{
	ros::shutdown();
	return stopExtensionThread(timeoutTime);
}

void ComponentROSCameraRosPortExtension::destroy()
{
	delete nh;
	delete callbacksPtr;
}
