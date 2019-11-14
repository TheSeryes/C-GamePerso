#include <TestMaps.h>
#include <Engine.h>
#include <DemoMap.h>
#include <MapClimber.h>

void TestMap::Load()
{
    bart::Engine::Instance().GetScene().AddEntity("DemoMap", new DemoMap());
}
