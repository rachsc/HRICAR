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
#include "SmartBodyPoseRecognition.hh"
#include "smartTimedTaskTrigger.h"
//FIXME: implement logging
//#include "smartGlobalLogger.hh"

// the ace port-factory is used as a default port-mapping
#include "SmartBodyPoseRecognitionAcePortFactory.hh"

#include "BodyPoseEventServiceOutEventTestHandler.hh"

// initialize static singleton pointer to zero
SmartBodyPoseRecognition* SmartBodyPoseRecognition::_smartBodyPoseRecognition = 0;

// constructor
SmartBodyPoseRecognition::SmartBodyPoseRecognition()
{
	std::cout << "constructor of SmartBodyPoseRecognition\n";
	
	// set all pointer members to NULL
	bodyPoseEventServiceOut = NULL;
	bodyPoseEventServiceOutEventTestHandler = nullptr; 
	bodyPoseQueryServiceAnsw = NULL;
	bodyPoseQueryServiceAnswInputTaskTrigger = NULL;
	bodyPoseQueryServiceAnswHandler = NULL;
	cameraServiceIn = NULL;
	cameraServiceInInputTaskTrigger = NULL;
	cameraServiceInUpcallManager = NULL;
	captureTask = NULL;
	captureTaskTrigger = NULL;
	//coordinationPort = NULL;
	environmentQueryServiceAnsw = NULL;
	environmentQueryServiceAnswInputTaskTrigger = NULL;
	environmentQueryServiceAnswHandler = NULL;
	recognitionTask = NULL;
	recognitionTaskTrigger = NULL;
	//smartBodyPoseRecognitionParams = NULL;
	stateChangeHandler = NULL;
	stateSlave = NULL;
	wiringSlave = NULL;
	param = NULL;
	
	// set default ini parameter values
	connections.component.name = "SmartBodyPoseRecognition";
	connections.component.initialComponentMode = "Neutral";
	connections.component.defaultScheduler = "DEFAULT";
	connections.component.useLogger = false;
	
	connections.bodyPoseEventServiceOut.serviceName = "BodyPoseEventServiceOut";
	connections.bodyPoseEventServiceOut.roboticMiddleware = "ACE_SmartSoft";
	connections.bodyPoseQueryServiceAnsw.serviceName = "BodyPoseQueryServiceAnsw";
	connections.bodyPoseQueryServiceAnsw.roboticMiddleware = "ACE_SmartSoft";
	connections.environmentQueryServiceAnsw.serviceName = "EnvironmentQueryServiceAnsw";
	connections.environmentQueryServiceAnsw.roboticMiddleware = "ACE_SmartSoft";
	connections.cameraServiceIn.initialConnect = false;
	connections.cameraServiceIn.wiringName = "CameraServiceIn";
	connections.cameraServiceIn.serverName = "unknown";
	connections.cameraServiceIn.serviceName = "unknown";
	connections.cameraServiceIn.interval = 1;
	connections.cameraServiceIn.roboticMiddleware = "ACE_SmartSoft";
	connections.captureTask.minActFreq = 0.0;
	connections.captureTask.maxActFreq = 0.0;
	// scheduling default parameters
	connections.captureTask.scheduler = "DEFAULT";
	connections.captureTask.priority = -1;
	connections.captureTask.cpuAffinity = -1;
	connections.recognitionTask.minActFreq = 0.0;
	connections.recognitionTask.maxActFreq = 0.0;
	// scheduling default parameters
	connections.recognitionTask.scheduler = "DEFAULT";
	connections.recognitionTask.priority = -1;
	connections.recognitionTask.cpuAffinity = -1;
	
	// initialize members of OpcUaBackendComponentGeneratorExtension
	
	// initialize members of PlainOpcUaSmartBodyPoseRecognitionExtension
	
	// initialize members of SmartBodyPoseRecognitionROSExtension
	
}

void SmartBodyPoseRecognition::addPortFactory(const std::string &name, SmartBodyPoseRecognitionPortFactoryInterface *portFactory)
{
	portFactoryRegistry[name] = portFactory;
}

void SmartBodyPoseRecognition::addExtension(SmartBodyPoseRecognitionExtension *extension)
{
	componentExtensionRegistry[extension->getName()] = extension;
}

SmartACE::SmartComponent* SmartBodyPoseRecognition::getComponentImpl()
{
	return dynamic_cast<SmartBodyPoseRecognitionAcePortFactory*>(portFactoryRegistry["ACE_SmartSoft"])->getComponentImpl();
}

/**
 * Notify the component that setup/initialization is finished.
 * You may call this function from anywhere in the component.
 *
 * Set component's internal lifecycle state automaton (if any) into 
 * Alive mode (from here on the component is ready to provide its services)
 */
void SmartBodyPoseRecognition::setStartupFinished() {
	stateSlave->setWaitState("Alive");
	std::cout << "ComponentDefinition initialization/startup finished." << std::endl;
}


Smart::StatusCode SmartBodyPoseRecognition::connectCameraServiceIn(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	if(connections.cameraServiceIn.initialConnect == false) {
		return Smart::SMART_OK;
	}
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = cameraServiceIn->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->cameraServiceIn->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	cameraServiceIn->subscribe(connections.cameraServiceIn.interval);
	return status;
}


/**
 * First connect ALL client ports contained in this component, then start all services:
 * activate state, push, etc...
 */
Smart::StatusCode SmartBodyPoseRecognition::connectAndStartAllServices() {
	Smart::StatusCode status = Smart::SMART_OK;
	
	status = connectCameraServiceIn(connections.cameraServiceIn.serverName, connections.cameraServiceIn.serviceName);
	if(status != Smart::SMART_OK) return status;
	return status;
}

/**
 * Start all tasks contained in this component.
 */
void SmartBodyPoseRecognition::startAllTasks() {
	// start task CaptureTask
	if(connections.captureTask.scheduler != "DEFAULT") {
		ACE_Sched_Params captureTask_SchedParams(ACE_SCHED_OTHER, ACE_THR_PRI_OTHER_DEF);
		if(connections.captureTask.scheduler == "FIFO") {
			captureTask_SchedParams.policy(ACE_SCHED_FIFO);
			captureTask_SchedParams.priority(ACE_THR_PRI_FIFO_MIN);
		} else if(connections.captureTask.scheduler == "RR") {
			captureTask_SchedParams.policy(ACE_SCHED_RR);
			captureTask_SchedParams.priority(ACE_THR_PRI_RR_MIN);
		}
		captureTask->start(captureTask_SchedParams, connections.captureTask.cpuAffinity);
	} else {
		captureTask->start();
	}
	// start task RecognitionTask
	if(connections.recognitionTask.scheduler != "DEFAULT") {
		ACE_Sched_Params recognitionTask_SchedParams(ACE_SCHED_OTHER, ACE_THR_PRI_OTHER_DEF);
		if(connections.recognitionTask.scheduler == "FIFO") {
			recognitionTask_SchedParams.policy(ACE_SCHED_FIFO);
			recognitionTask_SchedParams.priority(ACE_THR_PRI_FIFO_MIN);
		} else if(connections.recognitionTask.scheduler == "RR") {
			recognitionTask_SchedParams.policy(ACE_SCHED_RR);
			recognitionTask_SchedParams.priority(ACE_THR_PRI_RR_MIN);
		}
		recognitionTask->start(recognitionTask_SchedParams, connections.recognitionTask.cpuAffinity);
	} else {
		recognitionTask->start();
	}
}

/**
 * Start all timers contained in this component
 */
void SmartBodyPoseRecognition::startAllTimers() {
}


Smart::TaskTriggerSubject* SmartBodyPoseRecognition::getInputTaskTriggerFromString(const std::string &client)
{
	if(client == "CameraServiceIn") return cameraServiceInInputTaskTrigger;
	
	return NULL;
}


void SmartBodyPoseRecognition::init(int argc, char *argv[])
{
	try {
		Smart::StatusCode status;
		
		// load initial parameters from ini-file (if found)
		loadParameter(argc, argv);
		
		// print out the actual parameters which are used to initialize the component
		std::cout << " \nComponentDefinition Initial-Parameters:\n" << COMP->getParameters() << std::endl;
		
		// initializations of OpcUaBackendComponentGeneratorExtension
		
		// initializations of PlainOpcUaSmartBodyPoseRecognitionExtension
		
		// initializations of SmartBodyPoseRecognitionROSExtension
		
		
		// initialize all registered port-factories
		for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
		{
			portFactory->second->initialize(this, argc, argv);
		}
		
		// initialize all registered component-extensions
		for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
		{
			extension->second->initialize(this, argc, argv);
		}
		
		SmartBodyPoseRecognitionPortFactoryInterface *acePortFactory = portFactoryRegistry["ACE_SmartSoft"];
		if(acePortFactory == 0) {
			std::cerr << "ERROR: acePortFactory NOT instantiated -> exit(-1)" << std::endl;
			exit(-1);
		}
		
		// this pointer is used for backwards compatibility (deprecated: should be removed as soon as all patterns, including coordination, are moved to port-factory)
		SmartACE::SmartComponent *component = dynamic_cast<SmartBodyPoseRecognitionAcePortFactory*>(acePortFactory)->getComponentImpl();
		
		std::cout << "ComponentDefinition SmartBodyPoseRecognition is named " << connections.component.name << std::endl;
		
		if(connections.component.useLogger == true) {
			//FIXME: use logging
			//Smart::LOGGER->openLogFileInFolder("data/"+connections.component.name);
			//Smart::LOGGER->startLogging();
		}

		// create event-test handlers (if needed)
		bodyPoseEventServiceOutEventTestHandler = std::make_shared<BodyPoseEventServiceOutEventTestHandler>();
		
		// create server ports
		// TODO: set minCycleTime from Ini-file
		bodyPoseEventServiceOutEventTestHandler = std::make_shared<BodyPoseEventServiceOutEventTestHandler>();
		bodyPoseEventServiceOut = portFactoryRegistry[connections.bodyPoseEventServiceOut.roboticMiddleware]->createBodyPoseEventServiceOut(connections.bodyPoseEventServiceOut.serviceName, bodyPoseEventServiceOutEventTestHandler);
		bodyPoseQueryServiceAnsw = portFactoryRegistry[connections.bodyPoseQueryServiceAnsw.roboticMiddleware]->createBodyPoseQueryServiceAnsw(connections.bodyPoseQueryServiceAnsw.serviceName);
		bodyPoseQueryServiceAnswInputTaskTrigger = new Smart::QueryServerTaskTrigger<CommObjectRecognitionObjects::CommObjectRecognitionId, CommObjectRecognitionObjects::CommObjectRecognitionObjectProperties>(bodyPoseQueryServiceAnsw);
		environmentQueryServiceAnsw = portFactoryRegistry[connections.environmentQueryServiceAnsw.roboticMiddleware]->createEnvironmentQueryServiceAnsw(connections.environmentQueryServiceAnsw.serviceName);
		environmentQueryServiceAnswInputTaskTrigger = new Smart::QueryServerTaskTrigger<CommObjectRecognitionObjects::CommObjectRecognitionId, CommObjectRecognitionObjects::CommObjectRecognitionEnvironment>(environmentQueryServiceAnsw);
		
		// create client ports
		cameraServiceIn = portFactoryRegistry[connections.cameraServiceIn.roboticMiddleware]->createCameraServiceIn();
		
		// create InputTaskTriggers and UpcallManagers
		cameraServiceInInputTaskTrigger = new Smart::InputTaskTrigger<DomainVision::CommVideoImage>(cameraServiceIn);
		cameraServiceInUpcallManager = new CameraServiceInUpcallManager(cameraServiceIn);
		
		// create input-handler
		
		// create request-handlers
		bodyPoseQueryServiceAnswHandler = new BodyPoseQueryServiceAnswHandler(bodyPoseQueryServiceAnsw);
		environmentQueryServiceAnswHandler = new EnvironmentQueryServiceAnswHandler(environmentQueryServiceAnsw);
		
		// create state pattern
		stateChangeHandler = new SmartStateChangeHandler();
		stateSlave = new SmartACE::StateSlave(component, stateChangeHandler);
		status = stateSlave->setUpInitialState(connections.component.initialComponentMode);
		if (status != Smart::SMART_OK) std::cerr << status << "; failed setting initial ComponentMode: " << connections.component.initialComponentMode << std::endl;
		// activate state slave
		status = stateSlave->activate();
		if(status != Smart::SMART_OK) std::cerr << "ERROR: activate state" << std::endl;
		
		wiringSlave = new SmartACE::WiringSlave(component);
		// add client port to wiring slave
		if(connections.cameraServiceIn.roboticMiddleware == "ACE_SmartSoft") {
			//FIXME: this must also work with other implementations
			dynamic_cast<SmartACE::PushClient<DomainVision::CommVideoImage>*>(cameraServiceIn)->add(wiringSlave, connections.cameraServiceIn.wiringName);
		}
		
		// create parameter slave
		param = new SmartACE::ParameterSlave(component, &paramHandler);
		
		
		// create Task CaptureTask
		captureTask = new CaptureTask(component);
		// configure input-links
		// configure task-trigger (if task is configurable)
		if(connections.captureTask.trigger == "PeriodicTimer") {
			// create PeriodicTimerTrigger
			int microseconds = 1000*1000 / connections.captureTask.periodicActFreq;
			if(microseconds > 0) {
				Smart::TimedTaskTrigger *triggerPtr = new Smart::TimedTaskTrigger();
				triggerPtr->attach(captureTask);
				component->getTimerManager()->scheduleTimer(triggerPtr, (void *) 0, std::chrono::microseconds(microseconds), std::chrono::microseconds(microseconds));
				// store trigger in class member
				captureTaskTrigger = triggerPtr;
			} else {
				std::cerr << "ERROR: could not set-up Timer with cycle-time " << microseconds << " as activation source for Task CaptureTask" << std::endl;
			}
		} else if(connections.captureTask.trigger == "DataTriggered") {
			captureTaskTrigger = getInputTaskTriggerFromString(connections.captureTask.inPortRef);
			if(captureTaskTrigger != NULL) {
				captureTaskTrigger->attach(captureTask, connections.captureTask.prescale);
			} else {
				std::cerr << "ERROR: could not set-up InPort " << connections.captureTask.inPortRef << " as activation source for Task CaptureTask" << std::endl;
			}
		} 
		
		// create Task RecognitionTask
		recognitionTask = new RecognitionTask(component);
		// configure input-links
		// configure task-trigger (if task is configurable)
		if(connections.recognitionTask.trigger == "PeriodicTimer") {
			// create PeriodicTimerTrigger
			int microseconds = 1000*1000 / connections.recognitionTask.periodicActFreq;
			if(microseconds > 0) {
				Smart::TimedTaskTrigger *triggerPtr = new Smart::TimedTaskTrigger();
				triggerPtr->attach(recognitionTask);
				component->getTimerManager()->scheduleTimer(triggerPtr, (void *) 0, std::chrono::microseconds(microseconds), std::chrono::microseconds(microseconds));
				// store trigger in class member
				recognitionTaskTrigger = triggerPtr;
			} else {
				std::cerr << "ERROR: could not set-up Timer with cycle-time " << microseconds << " as activation source for Task RecognitionTask" << std::endl;
			}
		} else if(connections.recognitionTask.trigger == "DataTriggered") {
			recognitionTaskTrigger = getInputTaskTriggerFromString(connections.recognitionTask.inPortRef);
			if(recognitionTaskTrigger != NULL) {
				recognitionTaskTrigger->attach(recognitionTask, connections.recognitionTask.prescale);
			} else {
				std::cerr << "ERROR: could not set-up InPort " << connections.recognitionTask.inPortRef << " as activation source for Task RecognitionTask" << std::endl;
			}
		} 
		
		
		// link observers with subjects
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std exception" << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}

// run the component
void SmartBodyPoseRecognition::run()
{
	stateSlave->acquire("init");
	// startup all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->onStartup();
	}
	
	// startup all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->onStartup();
	}
	stateSlave->release("init");
	
	// do not call this handler within the init state (see above) as this handler internally calls setStartupFinished() (this should be fixed in future)
	compHandler.onStartup();
	
	// this call blocks until the component is commanded to shutdown
	stateSlave->acquire("shutdown");
	
	// shutdown all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->onShutdown();
	}
	
	// shutdown all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->onShutdown();
	}
	
	if(connections.component.useLogger == true) {
		//FIXME: use logging
		//Smart::LOGGER->stopLogging();
	}
	
	compHandler.onShutdown();
	
	stateSlave->release("shutdown");
}

// clean-up component's resources
void SmartBodyPoseRecognition::fini()
{
	// unlink all observers
	
	// destroy all task instances
	// unlink all UpcallManagers
	// unlink the TaskTrigger
	if(captureTaskTrigger != NULL){
		captureTaskTrigger->detach(captureTask);
		delete captureTask;
	}
	// unlink all UpcallManagers
	// unlink the TaskTrigger
	if(recognitionTaskTrigger != NULL){
		recognitionTaskTrigger->detach(recognitionTask);
		delete recognitionTask;
	}

	// destroy all input-handler

	// destroy InputTaskTriggers and UpcallManagers
	delete cameraServiceInInputTaskTrigger;
	delete cameraServiceInUpcallManager;

	// destroy client ports
	delete cameraServiceIn;

	// destroy server ports
	delete bodyPoseEventServiceOut;
	delete bodyPoseQueryServiceAnsw;
	delete bodyPoseQueryServiceAnswInputTaskTrigger;
	delete environmentQueryServiceAnsw;
	delete environmentQueryServiceAnswInputTaskTrigger;
	// destroy event-test handlers (if needed)
	bodyPoseEventServiceOutEventTestHandler;
	
	// destroy request-handlers
	delete bodyPoseQueryServiceAnswHandler;
	delete environmentQueryServiceAnswHandler;
	
	delete stateSlave;
	// destroy state-change-handler
	delete stateChangeHandler;
	
	// destroy all master/slave ports
	delete wiringSlave;
	delete param;
	

	// destroy all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->destroy();
	}

	// destroy all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->destroy();
	}
	
	// destruction of OpcUaBackendComponentGeneratorExtension
	
	// destruction of PlainOpcUaSmartBodyPoseRecognitionExtension
	
	// destruction of SmartBodyPoseRecognitionROSExtension
	
}

void SmartBodyPoseRecognition::loadParameter(int argc, char *argv[])
{
	/*
	 Parameters can be specified via command line --filename=<filename> or -f <filename>

	 With this parameter present:
	   - The component will look for the file in the current working directory,
	     a path relative to the current directory or any absolute path
	   - The component will use the default values if the file cannot be found

	 With this parameter absent:
	   - <Name of Component>.ini will be read from current working directory, if found there
	   - $SMART_ROOT/etc/<Name of Component>.ini will be read otherwise
	   - Default values will be used if neither found in working directory or /etc
	 */
	SmartACE::SmartIniParameter parameter;
	std::ifstream parameterfile;
	bool parameterFileFound = false;

	// load parameters
	try
	{
		// if paramfile is given as argument
		if(parameter.tryAddFileFromArgs(argc,argv,"filename", 'f'))
		{
			parameterFileFound = true;
			std::cout << "parameter file is loaded from an argv argument \n";
		} else if(parameter.searchFile("SmartBodyPoseRecognition.ini", parameterfile)) {
			parameterFileFound = true;
			std::cout << "load SmartBodyPoseRecognition.ini parameter file\n";
			parameter.addFile(parameterfile);
		} else {
			std::cout << "WARNING: SmartBodyPoseRecognition.ini parameter file not found! (using default values or command line arguments)\n";
		}
		
		// add command line arguments to allow overwriting of parameters
		// from file
		parameter.addCommandLineArgs(argc,argv,"component");
		
		// initialize the naming service using the command line parameters parsed in the
		// SmartIniParameter class. The naming service parameters are expected to be in
		// the "component" parameter group.
		SmartACE::NAMING::instance()->checkForHelpArg(argc,argv);
		if(parameterFileFound) 
		{
			if(SmartACE::NAMING::instance()->init(parameter.getAllParametersFromGroup("component")) != 0) {
				// initialization of naming service failed
				throw std::logic_error( "<NamingService> Service initialization failed!\nPossible causes could be:\n-> Erroneous configuration.\n-> Naming service not reachable.\n" );
			}
		} else {
			if(SmartACE::NAMING::instance()->init(argc, argv) != 0) {
				// initialization of naming service failed
				throw std::logic_error( "<NamingService> Service initialization failed!\nPossible causes could be:\n-> Erroneous configuration.\n-> Naming service not reachable.\n" );
			}
		}
			
		// print all known parameters
		// parameter.print();
		
		//--- server port // client port // other parameter ---
		// load parameter
		parameter.getString("component", "name", connections.component.name);
		parameter.getString("component", "initialComponentMode", connections.component.initialComponentMode);
		if(parameter.checkIfParameterExists("component", "defaultScheduler")) {
			parameter.getString("component", "defaultScheduler", connections.component.defaultScheduler);
		}
		if(parameter.checkIfParameterExists("component", "useLogger")) {
			parameter.getBoolean("component", "useLogger", connections.component.useLogger);
		}
		
		// load parameters for client CameraServiceIn
		parameter.getBoolean("CameraServiceIn", "initialConnect", connections.cameraServiceIn.initialConnect);
		parameter.getString("CameraServiceIn", "serviceName", connections.cameraServiceIn.serviceName);
		parameter.getString("CameraServiceIn", "serverName", connections.cameraServiceIn.serverName);
		parameter.getString("CameraServiceIn", "wiringName", connections.cameraServiceIn.wiringName);
		parameter.getInteger("CameraServiceIn", "interval", connections.cameraServiceIn.interval);
		if(parameter.checkIfParameterExists("CameraServiceIn", "roboticMiddleware")) {
			parameter.getString("CameraServiceIn", "roboticMiddleware", connections.cameraServiceIn.roboticMiddleware);
		}
		
		// load parameters for server BodyPoseEventServiceOut
		parameter.getString("BodyPoseEventServiceOut", "serviceName", connections.bodyPoseEventServiceOut.serviceName);
		if(parameter.checkIfParameterExists("BodyPoseEventServiceOut", "roboticMiddleware")) {
			parameter.getString("BodyPoseEventServiceOut", "roboticMiddleware", connections.bodyPoseEventServiceOut.roboticMiddleware);
		}
		// load parameters for server BodyPoseQueryServiceAnsw
		parameter.getString("BodyPoseQueryServiceAnsw", "serviceName", connections.bodyPoseQueryServiceAnsw.serviceName);
		if(parameter.checkIfParameterExists("BodyPoseQueryServiceAnsw", "roboticMiddleware")) {
			parameter.getString("BodyPoseQueryServiceAnsw", "roboticMiddleware", connections.bodyPoseQueryServiceAnsw.roboticMiddleware);
		}
		// load parameters for server EnvironmentQueryServiceAnsw
		parameter.getString("EnvironmentQueryServiceAnsw", "serviceName", connections.environmentQueryServiceAnsw.serviceName);
		if(parameter.checkIfParameterExists("EnvironmentQueryServiceAnsw", "roboticMiddleware")) {
			parameter.getString("EnvironmentQueryServiceAnsw", "roboticMiddleware", connections.environmentQueryServiceAnsw.roboticMiddleware);
		}
		
		// load parameters for task CaptureTask
		parameter.getDouble("CaptureTask", "minActFreqHz", connections.captureTask.minActFreq);
		parameter.getDouble("CaptureTask", "maxActFreqHz", connections.captureTask.maxActFreq);
		parameter.getString("CaptureTask", "triggerType", connections.captureTask.trigger);
		if(connections.captureTask.trigger == "PeriodicTimer") {
			parameter.getDouble("CaptureTask", "periodicActFreqHz", connections.captureTask.periodicActFreq);
		} else if(connections.captureTask.trigger == "DataTriggered") {
			parameter.getString("CaptureTask", "inPortRef", connections.captureTask.inPortRef);
			parameter.getInteger("CaptureTask", "prescale", connections.captureTask.prescale);
		}
		if(parameter.checkIfParameterExists("CaptureTask", "scheduler")) {
			parameter.getString("CaptureTask", "scheduler", connections.captureTask.scheduler);
		}
		if(parameter.checkIfParameterExists("CaptureTask", "priority")) {
			parameter.getInteger("CaptureTask", "priority", connections.captureTask.priority);
		}
		if(parameter.checkIfParameterExists("CaptureTask", "cpuAffinity")) {
			parameter.getInteger("CaptureTask", "cpuAffinity", connections.captureTask.cpuAffinity);
		}
		// load parameters for task RecognitionTask
		parameter.getDouble("RecognitionTask", "minActFreqHz", connections.recognitionTask.minActFreq);
		parameter.getDouble("RecognitionTask", "maxActFreqHz", connections.recognitionTask.maxActFreq);
		parameter.getString("RecognitionTask", "triggerType", connections.recognitionTask.trigger);
		if(connections.recognitionTask.trigger == "PeriodicTimer") {
			parameter.getDouble("RecognitionTask", "periodicActFreqHz", connections.recognitionTask.periodicActFreq);
		} else if(connections.recognitionTask.trigger == "DataTriggered") {
			parameter.getString("RecognitionTask", "inPortRef", connections.recognitionTask.inPortRef);
			parameter.getInteger("RecognitionTask", "prescale", connections.recognitionTask.prescale);
		}
		if(parameter.checkIfParameterExists("RecognitionTask", "scheduler")) {
			parameter.getString("RecognitionTask", "scheduler", connections.recognitionTask.scheduler);
		}
		if(parameter.checkIfParameterExists("RecognitionTask", "priority")) {
			parameter.getInteger("RecognitionTask", "priority", connections.recognitionTask.priority);
		}
		if(parameter.checkIfParameterExists("RecognitionTask", "cpuAffinity")) {
			parameter.getInteger("RecognitionTask", "cpuAffinity", connections.recognitionTask.cpuAffinity);
		}
		
		// load parameters for OpcUaBackendComponentGeneratorExtension
		
		// load parameters for PlainOpcUaSmartBodyPoseRecognitionExtension
		
		// load parameters for SmartBodyPoseRecognitionROSExtension
		
		
		// load parameters for all registered component-extensions
		for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
		{
			extension->second->loadParameters(parameter);
		}
		
		paramHandler.loadParameter(parameter);
	
	} catch (const SmartACE::IniParameterError & e) {
		std::cerr << e.what() << std::endl;
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std::exception: " << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}
