#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include "Axis3D.h"
#include "Particle.h"
#include "Projectile.h"
#include "ParticleSystem.h"
#include "GravityForceGenerator.h"

#include "Submarine.h"
#include "Obstacle.h"
#include "Torpedo.h"

std::string density_text = "";
std::string main_Ballast_text = "";
std::string compensation_Ballast_text = "";
std::string quick_Ballast_text = "";



using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

RenderItem* item1 = nullptr;
Axis3D* axis = nullptr;
ParticleSystem* particleSystem = nullptr;
std::vector<Projectile*> projectileVector;
std::list<Particle*> globalList;

Submarine* submarine;

std::vector<Obstacle*> obs;
std::vector<Torpedo*> torpedos;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);


	// Inicialización de Physx
	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	


	// Creamos una escena (PxScene) para definir nuestros sóidos rígidos
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, 0.0f, 0.0f);							// NO HAY GRAVEDAD
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);


	// Creación de los ejes del mundo
	axis = new Axis3D();

	// Generar suelo
	PxRigidStatic* suelo;
	suelo = gPhysics->createRigidStatic(PxTransform({ 0, -100, 0 }));	// Definimos una posición
	PxShape* shape = CreateShape(PxBoxGeometry(1000, 1, 1000));		// Definimos una forma
	suelo->attachShape(*shape);
	gScene->addActor(*suelo);	// Añadimos el elemento a la escena gScene

	// Pintar suelo
	RenderItem* renderSuelo;
	renderSuelo = new RenderItem(shape, suelo, { 0.6, 0.6, 0.6, 1 });


	submarine = new Submarine(PxTransform({ 0, 40, 0 }), 20000, gScene);	// 34557.5

	obs.push_back(new Obstacle({20, 15, 20}, {140, 40, 0}, 100, gScene));
	obs.push_back(new Obstacle({20, 15, 20}, {140, 10, 0}, 100, gScene));
	obs.push_back(new Obstacle({20, 15, 20}, {140, -20, 0}, 100, gScene));
	obs.push_back(new Obstacle({20, 15, 20}, {140, -50, 0}, 100, gScene));
	obs.push_back(new Obstacle({20, 15, 20}, {140, -80, 0}, 100, gScene));
	obs.push_back(new Obstacle({20, 15, 20}, {140, 70, 0}, 100, gScene));
	//obs.push_back(new Obstacle({20, 15, 20}, {140, -60, 0}, 100, gScene));

	RenderItem* agua = new RenderItem(CreateShape(PxBoxGeometry(1000, 0.01, 1000)), new PxTransform(PxVec3(0, 50, 0)), { 0, 0, 1, 0.1 });


	particleSystem = new ParticleSystem(globalList);
	
	//particleSystem->AddGaussianGenerator(Vector3D<>(20, -20, 10), Vector3D<>(1, 0, 0), 30, 5, 1);
	//particleSystem->AddUniformGenerator(Vector3D<>(0, 0, 0), Vector3D<>(-0.4, 1, 0), 10, 5, 1);
	//particleSystem->AddRainGenerator(Vector3D<>(0, 150, 0), 100, 10);

	//particleSystem->Generate2ParticleSpring();
	//particleSystem->GenerateAnchoredSpring();
	
	//particleSystem->GenerateBuoyancyDemo();
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	PxVec3 cameraPos = PxVec3(submarine->rigidBody->getGlobalPose().p) + PxVec3(-120, 80, 0);
	GetCamera()->mEye = cameraPos;
	GetCamera()->mDir = PxVec3(0.80, -0.5, 0).getNormalized();
	//std::cout << GetCamera()->mDir.x << " " << GetCamera()->mDir.y << " " << GetCamera()->mDir.z << "\n";

	gScene->simulate(t);

	submarine->UpdateForces(t);
	submarine->UpdateBallastTanks(t);

	for (auto e : obs) {
		e->UpdateForces(t);
	}

	for (auto e : torpedos) {
		e->UpdateForces(t);
	}

	particleSystem->Update(t);

	for (Projectile* e : projectileVector) e->Integrate(t);

	density_text = "Submarine density: " + std::to_string(submarine->GetDensity());

	main_Ballast_text = "(-N/M+) Main ballast: " + std::to_string(submarine->main_BallastTank.GetWaterPercentage()) + "%";
	if (submarine->main_BallastTank.GetWaterGateOpen()) main_Ballast_text += " (Water OPEN) ";
	if (submarine->main_BallastTank.GetAirGateOpen()) main_Ballast_text += " (Air OPEN) ";
	
	compensation_Ballast_text = "(-J/K+) Comp ballast: " + std::to_string(submarine->compensation_BallastTank.GetWaterPercentage()) + "%";
	if (submarine->compensation_BallastTank.GetWaterGateOpen()) compensation_Ballast_text += " (Water OPEN) ";
	if (submarine->compensation_BallastTank.GetAirGateOpen()) compensation_Ballast_text += " (Air OPEN) ";

	quick_Ballast_text = "(-I/O+) Quick ballast: " + std::to_string(submarine->quick_BallastTank.GetWaterPercentage()) + "%";
	if (submarine->quick_BallastTank.GetWaterGateOpen()) quick_Ballast_text += " (Water OPEN) ";
	if (submarine->quick_BallastTank.GetAirGateOpen()) quick_Ballast_text += " (Air OPEN) ";

	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	delete particleSystem;

	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	gFoundation->release();
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case 'N': 
		submarine->main_BallastTank.SwitchAirGate();
		break;
	case 'M':
		submarine->main_BallastTank.SwitchWaterGate();	
		break;
	case 'J':
		submarine->compensation_BallastTank.SwitchAirGate();
		break;
	case 'K':
		submarine->compensation_BallastTank.SwitchWaterGate();
		break;
	case 'I':
		submarine->quick_BallastTank.SwitchAirGate();
		break;
	case 'O':
		submarine->quick_BallastTank.SwitchWaterGate();
		break;

	// Control del motor
	case 'Q':
		submarine->movementDirection = PxVec3(1, 0, 0);
		break;
	case 'W':
		submarine->movementDirection = PxVec3(2, 0, 0);
		break;
	case 'E':
		submarine->movementDirection = PxVec3(3, 0, 0);
		break;
	case 'A':
		submarine->movementDirection = PxVec3(-1, 0, 0);
		break;
	case 'S':
		submarine->movementDirection = PxVec3(-2, 0, 0);
		break;
	case 'D':
		submarine->movementDirection = PxVec3(-3, 0, 0);
		break;
	case 'X':
		submarine->movementDirection = PxVec3(0, 0, 0);
		break;

	// Torpedos
	case 'F':
	{
		PxVec3 initialPos = submarine->rigidBody->getGlobalPose().p + PxVec3(0, 20, 0);
		torpedos.push_back(new Torpedo(PxTransform(initialPos), 100, gScene, &obs));
		torpedos.back()->movementDirection = PxVec3(50, 0, 0);
		break;
	}
	case 'Z':
	{
		
		Vector3D<> initialPos(GetCamera()->getTransform().p.x, GetCamera()->getTransform().p.y, GetCamera()->getTransform().p.z);
		Vector3D<> initialDir(GetCamera()->getDir().x, GetCamera()->getDir().y, GetCamera()->getDir().z);
		projectileVector.push_back(new Projectile(globalList, 250, 50, 1, 1, initialPos, initialDir));
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}