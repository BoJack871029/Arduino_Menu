
#include <resource-manager.h>
namespace resource
{
void Manager::addResource(Resource *iResource)
{
    if (_resourceLength > 9)
    {
        return;
    }
    _resources[_resourceLength] = iResource;

    _resourceLength++;
}

bool Manager::hasResource(resource::TYPE iType)
{
    for (int i = 0; i < _resourceLength; ++i)
    {
        if (_resources[i]->_type == iType)
        {
            return true;
        }
    }
    return false;
}

void *Manager::get(int iType)
{
    for (int i = 0; i < _resourceLength; ++i)
    {
        if (_resources[i]->_type == iType)
        {
            return _resources[i]->_value;
        }
    }

    return 0;
}
} // namespace resource