//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain
// The SmartSoft Toolchain has been developed by:
//  
// Service Robotics Research Center
// University of Applied Sciences Ulm
// Prittwitzstr. 10
// 89075 Ulm (Germany)
//
// Information about the SmartSoft MDSD Toolchain is available at:
// www.servicerobotik-ulm.de
//
// Please do not modify this file. It will be re-generated
// running the code generator.
//--------------------------------------------------------------------------

#ifndef SMARTBODYPOSERECOGNITION_OPC_UA_BACKEND_PORTFACTORY_HH_
#define SMARTBODYPOSERECOGNITION_OPC_UA_BACKEND_PORTFACTORY_HH_

// include the main component-definition class
#include "SmartBodyPoseRecognitionPortFactoryInterface.hh"

#include <thread>
#include <chrono>

// include SeRoNetSDK library
#include <SeRoNetSDK/SeRoNet/Utils/Task.hpp>
#include <SeRoNetSDK/SeRoNet/Utils/Component.hpp>

class SmartBodyPoseRecognitionOpcUaBackendPortFactory: public SmartBodyPoseRecognitionPortFactoryInterface
{
private:
	// internal component instance
	SeRoNet::Utils::Component *componentImpl;
	
	// component thread
	std::thread component_thread;
	
	// internal component thread method
	int task_execution();
public:
	SmartBodyPoseRecognitionOpcUaBackendPortFactory();
	virtual ~SmartBodyPoseRecognitionOpcUaBackendPortFactory();

	virtual void initialize(SmartBodyPoseRecognition *component, int argc, char* argv[]) override;
	virtual int onStartup() override;

	virtual Smart::IPushClientPattern<DomainVision::CommVideoImage> * createCameraServiceIn() override;
	
	virtual Smart::IEventServerPattern<CommBasicObjects::CommVoid, CommObjectRecognitionObjects::CommObjectRecognitionEventResult, CommObjectRecognitionObjects::CommObjectRecognitionEventState> * createBodyPoseEventServiceOut(const std::string &serviceName, std::shared_ptr<Smart::IEventTestHandler<CommBasicObjects::CommVoid, CommObjectRecognitionObjects::CommObjectRecognitionEventResult, CommObjectRecognitionObjects::CommObjectRecognitionEventState>> bodyPoseEventServiceOutEventTestHandler) override;
	virtual Smart::IQueryServerPattern<CommObjectRecognitionObjects::CommObjectRecognitionId, CommObjectRecognitionObjects::CommObjectRecognitionObjectProperties> * createBodyPoseQueryServiceAnsw(const std::string &serviceName) override;
	virtual Smart::IQueryServerPattern<CommObjectRecognitionObjects::CommObjectRecognitionId, CommObjectRecognitionObjects::CommObjectRecognitionEnvironment> * createEnvironmentQueryServiceAnsw(const std::string &serviceName) override;
	
	virtual int onShutdown(const std::chrono::steady_clock::duration &timeoutTime=std::chrono::seconds(2)) override;
	virtual void destroy() override;
};

#endif /* SMARTBODYPOSERECOGNITION_SERONET_SDK_PORTFACTORY_HH_ */
