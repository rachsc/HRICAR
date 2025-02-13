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
#include "CameraServiceInUpcallManager.hh"

CameraServiceInUpcallManager::CameraServiceInUpcallManager(
	Smart::InputSubject<DomainVision::CommVideoImage> *subject,
	const int &prescaleFactor)
	:	Smart::IInputHandler<DomainVision::CommVideoImage>(subject, prescaleFactor)
{  }
CameraServiceInUpcallManager::~CameraServiceInUpcallManager()
{  }

void CameraServiceInUpcallManager::notify_upcalls(const DomainVision::CommVideoImage &input)
{
	for(auto it=upcalls.begin(); it!=upcalls.end(); it++) {
		(*it)->on_CameraServiceIn(input);
	}
}

void CameraServiceInUpcallManager::attach(CameraServiceInUpcallInterface *upcall)
{
	upcalls.push_back(upcall);
}
void CameraServiceInUpcallManager::detach(CameraServiceInUpcallInterface *upcall)
{
	upcalls.remove(upcall);
}
