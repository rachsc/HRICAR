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

#ifndef SMARTFACERECOGNITION_ACE_PORTFACTORY_HH_
#define SMARTFACERECOGNITION_ACE_PORTFACTORY_HH_

// include ACE/SmartSoft component implementation
#include "SmartFaceRecognitionImpl.hh"

// include the main component-definition class
#include "SmartFaceRecognitionPortFactoryInterface.hh"

class SmartFaceRecognitionAcePortFactory: public SmartFaceRecognitionPortFactoryInterface
{
private:
	SmartFaceRecognitionImpl *componentImpl;
public:
	SmartFaceRecognitionAcePortFactory();
	virtual ~SmartFaceRecognitionAcePortFactory();

	virtual void initialize(SmartFaceRecognition *component, int argc, char* argv[]) override;
	virtual int onStartup() override;

	virtual Smart::IPushClientPattern<DomainVision::CommVideoImage> * createCameraServiceIn() override;
	
	virtual Smart::IQueryServerPattern<CommObjectRecognitionObjects::CommObjectRecognitionId, CommObjectRecognitionObjects::CommObjectRecognitionEnvironment> * createEnvironmentQueryServiceAnsw(const std::string &serviceName) override;
	virtual Smart::IEventServerPattern<CommBasicObjects::CommVoid, CommObjectRecognitionObjects::CommObjectRecognitionEventResult, CommObjectRecognitionObjects::CommObjectRecognitionEventState> * createFaceEventServiceOut(const std::string &serviceName, std::shared_ptr<Smart::IEventTestHandler<CommBasicObjects::CommVoid, CommObjectRecognitionObjects::CommObjectRecognitionEventResult, CommObjectRecognitionObjects::CommObjectRecognitionEventState>> faceEventServiceOutEventTestHandler) override;
	virtual Smart::IQueryServerPattern<CommObjectRecognitionObjects::CommObjectRecognitionId, CommObjectRecognitionObjects::CommObjectRecognitionObjectProperties> * createFaceQueryServiceAnsw(const std::string &serviceName) override;
	
	// get a pointer to the internal component implementation
	SmartACE::SmartComponent* getComponentImpl();

	virtual int onShutdown(const std::chrono::steady_clock::duration &timeoutTime=std::chrono::seconds(2)) override;
	virtual void destroy() override;
};

#endif /* SMARTFACERECOGNITION_ACE_PORTFACTORY_HH_ */
