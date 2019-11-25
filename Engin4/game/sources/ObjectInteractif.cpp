#include <ObjectInteractif.h>
#include <GameManager.h>

ObjectInteractif::ObjectInteractif()
{
	GameManager::Instance().AddObjectToList(this);
}

void ObjectFactory::Create(const std::string & aName,
						   const bart::Rectangle & aDest,
						   float aAngle, bart::TiledProperties * aProps) const
{
	ObjectInteractif* tNewEntity = new ObjectInteractif();
	tNewEntity->SetPosition(aDest.X, aDest.Y);
	tNewEntity->SetSize(aDest.W, aDest.H);

	bart::Engine::Instance().GetScene().AddEntity(aName, tNewEntity);	
}
