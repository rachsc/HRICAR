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

#include "TriggerHandlerCore.hh"


//
// trigger internal handler methods
//

	// handle ADDALGORITHM
	void TriggerHandlerCore::handleCommObjectRecognitionObjects_ObjectRecognitionParameter_ADDALGORITHMCore(const std::string &algorithm)
	{
		this->handleCommObjectRecognitionObjects_ObjectRecognitionParameter_ADDALGORITHM(algorithm);
	}

	// handle ADDOBJECT
	void TriggerHandlerCore::handleCommObjectRecognitionObjects_ObjectRecognitionParameter_ADDOBJECTCore(const std::string &type)
	{
		this->handleCommObjectRecognitionObjects_ObjectRecognitionParameter_ADDOBJECT(type);
	}

	// handle ADDSENSOR
	void TriggerHandlerCore::handleCommObjectRecognitionObjects_ObjectRecognitionParameter_ADDSENSORCore(const ADDSENSORType::sensorType &sensor)
	{
		this->handleCommObjectRecognitionObjects_ObjectRecognitionParameter_ADDSENSOR(sensor);
	}

	// handle BEHAVIOR
	void TriggerHandlerCore::handleCommObjectRecognitionObjects_ObjectRecognitionParameter_BEHAVIORCore(const BEHAVIORType::typeType &type)
	{
		this->handleCommObjectRecognitionObjects_ObjectRecognitionParameter_BEHAVIOR(type);
	}

	// handle CAPTURE
	void TriggerHandlerCore::handleCommObjectRecognitionObjects_ObjectRecognitionParameter_CAPTURECore()
	{
		this->handleCommObjectRecognitionObjects_ObjectRecognitionParameter_CAPTURE();
	}

	// handle DELALGORITHMS
	void TriggerHandlerCore::handleCommObjectRecognitionObjects_ObjectRecognitionParameter_DELALGORITHMSCore()
	{
		this->handleCommObjectRecognitionObjects_ObjectRecognitionParameter_DELALGORITHMS();
	}

	// handle DELOBJECTS
	void TriggerHandlerCore::handleCommObjectRecognitionObjects_ObjectRecognitionParameter_DELOBJECTSCore()
	{
		this->handleCommObjectRecognitionObjects_ObjectRecognitionParameter_DELOBJECTS();
	}

	// handle DELSENSORS
	void TriggerHandlerCore::handleCommObjectRecognitionObjects_ObjectRecognitionParameter_DELSENSORSCore()
	{
		this->handleCommObjectRecognitionObjects_ObjectRecognitionParameter_DELSENSORS();
	}

	// handle RECOGNIZE
	void TriggerHandlerCore::handleCommObjectRecognitionObjects_ObjectRecognitionParameter_RECOGNIZECore(const std::string &viewPointID)
	{
		this->handleCommObjectRecognitionObjects_ObjectRecognitionParameter_RECOGNIZE(viewPointID);
	}

//
// extended trigger internal handler methods
//
