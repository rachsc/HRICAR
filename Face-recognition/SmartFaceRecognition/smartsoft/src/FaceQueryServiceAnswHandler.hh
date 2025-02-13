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
// This file is generated once. Modify this file to your needs. 
// If you want the toolchain to re-generate this file, please 
// delete it before running the code generator.
//--------------------------------------------------------------------------
#ifndef _FACEQUERYSERVICEANSWHANDLER_USER_HH
#define _FACEQUERYSERVICEANSWHANDLER_USER_HH
		
#include "FaceQueryServiceAnswHandlerCore.hh"

class FaceQueryServiceAnswHandler : public FaceQueryServiceAnswHandlerCore
{
protected:
public:
	FaceQueryServiceAnswHandler(IQueryServer *server);
	virtual ~FaceQueryServiceAnswHandler() = default;
	virtual void handleQuery(const QueryId &id, const CommObjectRecognitionObjects::CommObjectRecognitionId& request);
};
#endif
