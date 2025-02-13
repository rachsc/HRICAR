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

#include "SmartBodyPoseRecognitionOpcUaBackendPortFactory.hh"

// include all potentially required pattern implementations
#include <SeRoNetSDK/SeRoNet/OPCUA/Client/PushClient.hpp>
#include <SeRoNetSDK/SeRoNet/OPCUA/Client/EventClient.hpp>
#include <SeRoNetSDK/SeRoNet/OPCUA/Client/QClientOPCUA.hpp>
#include <SeRoNetSDK/SeRoNet/OPCUA/Client/SendClient.hpp>
#include <SeRoNetSDK/SeRoNet/OPCUA/Client/QueryClient.hpp>

#include <SeRoNetSDK/SeRoNet/OPCUA/Server/PushServer.hpp>
#include <SeRoNetSDK/SeRoNet/OPCUA/Server/EventServer.hpp>
#include <SeRoNetSDK/SeRoNet/OPCUA/Server/SendServer.hpp>
#include <SeRoNetSDK/SeRoNet/OPCUA/Server/QueryServer.hpp>

// include referenced CommunicationObject SeRoNetSDK self description implementations
#include "CommBasicObjectsOpcUa/CommVoidOpcUa.hh"
#include "CommObjectRecognitionObjectsOpcUa/CommObjectRecognitionEnvironmentOpcUa.hh"
#include "CommObjectRecognitionObjectsOpcUa/CommObjectRecognitionEventResultOpcUa.hh"
#include "CommObjectRecognitionObjectsOpcUa/CommObjectRecognitionEventStateOpcUa.hh"
#include "CommObjectRecognitionObjectsOpcUa/CommObjectRecognitionIdOpcUa.hh"
#include "CommObjectRecognitionObjectsOpcUa/CommObjectRecognitionObjectPropertiesOpcUa.hh"
#include "DomainVisionOpcUa/CommVideoImageOpcUa.hh"

// create a static instance of the OpcUaBackendPortFactory
static SmartBodyPoseRecognitionOpcUaBackendPortFactory OpcUaBackendPortFactory;

SmartBodyPoseRecognitionOpcUaBackendPortFactory::SmartBodyPoseRecognitionOpcUaBackendPortFactory()
{  
	componentImpl = 0;
	SmartBodyPoseRecognition::instance()->addPortFactory("OpcUa_SeRoNet", this);
}

SmartBodyPoseRecognitionOpcUaBackendPortFactory::~SmartBodyPoseRecognitionOpcUaBackendPortFactory()
{  }

void SmartBodyPoseRecognitionOpcUaBackendPortFactory::initialize(SmartBodyPoseRecognition *component, int argc, char* argv[])
{
	componentImpl = new SeRoNet::Utils::Component(component->connections.component.name);
}

int SmartBodyPoseRecognitionOpcUaBackendPortFactory::onStartup()
{
	if (!component_thread.joinable()) {
    	component_thread = std::thread(&SmartBodyPoseRecognitionOpcUaBackendPortFactory::task_execution, this);
    	return 0;
    }
	return -1;
}

Smart::IPushClientPattern<DomainVision::CommVideoImage> * SmartBodyPoseRecognitionOpcUaBackendPortFactory::createCameraServiceIn()
{
	return new SeRoNet::OPCUA::Client::PushClient<DomainVision::CommVideoImage>(componentImpl);
}


Smart::IEventServerPattern<CommBasicObjects::CommVoid, CommObjectRecognitionObjects::CommObjectRecognitionEventResult, CommObjectRecognitionObjects::CommObjectRecognitionEventState> * SmartBodyPoseRecognitionOpcUaBackendPortFactory::createBodyPoseEventServiceOut(const std::string &serviceName, std::shared_ptr<Smart::IEventTestHandler<CommBasicObjects::CommVoid, CommObjectRecognitionObjects::CommObjectRecognitionEventResult, CommObjectRecognitionObjects::CommObjectRecognitionEventState>> bodyPoseEventServiceOutEventTestHandler)
{
	return new SeRoNet::OPCUA::Server::EventServer<CommBasicObjects::CommVoid, CommObjectRecognitionObjects::CommObjectRecognitionEventResult, CommObjectRecognitionObjects::CommObjectRecognitionEventState>(componentImpl, serviceName, bodyPoseEventServiceOutEventTestHandler);
}

Smart::IQueryServerPattern<CommObjectRecognitionObjects::CommObjectRecognitionId, CommObjectRecognitionObjects::CommObjectRecognitionObjectProperties> * SmartBodyPoseRecognitionOpcUaBackendPortFactory::createBodyPoseQueryServiceAnsw(const std::string &serviceName)
{
	return new SeRoNet::OPCUA::Server::QueryServer<CommObjectRecognitionObjects::CommObjectRecognitionId, CommObjectRecognitionObjects::CommObjectRecognitionObjectProperties>(componentImpl, serviceName);
}

Smart::IQueryServerPattern<CommObjectRecognitionObjects::CommObjectRecognitionId, CommObjectRecognitionObjects::CommObjectRecognitionEnvironment> * SmartBodyPoseRecognitionOpcUaBackendPortFactory::createEnvironmentQueryServiceAnsw(const std::string &serviceName)
{
	return new SeRoNet::OPCUA::Server::QueryServer<CommObjectRecognitionObjects::CommObjectRecognitionId, CommObjectRecognitionObjects::CommObjectRecognitionEnvironment>(componentImpl, serviceName);
}


int SmartBodyPoseRecognitionOpcUaBackendPortFactory::task_execution()
{
	componentImpl->run();
	return 0;
}

int SmartBodyPoseRecognitionOpcUaBackendPortFactory::onShutdown(const std::chrono::steady_clock::duration &timeoutTime)
{
	// stop component-internal infrastructure
	componentImpl->stopRunning();
	// wait on component thread to exit
	if (component_thread.joinable()) {
		// FIXME: don't wait infinetly (use timeoutTime here)
    	component_thread.join();
    }
	return 0;
}

void SmartBodyPoseRecognitionOpcUaBackendPortFactory::destroy()
{
	// clean-up component's internally used resources
	delete componentImpl;
}
