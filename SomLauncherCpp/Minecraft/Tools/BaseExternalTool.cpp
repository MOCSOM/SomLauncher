#include "BaseExternalTool.h"

BaseExternalTool::BaseExternalTool(SettingsObjectPtr settings, InstancePtr instance, QObject* parent)
    : QObject(parent), m_instance(instance), globalSettings(settings)
{
}

BaseDetachedTool::BaseDetachedTool(SettingsObjectPtr settings, InstancePtr instance, QObject* parent)
    : BaseExternalTool(settings, instance, parent)
{
}

void BaseDetachedTool::run()
{
    runImpl();
}

BaseDetachedTool* BaseDetachedToolFactory::createDetachedTool(InstancePtr instance, QObject* parent)
{
    return qobject_cast<BaseDetachedTool*>(createTool(instance, parent));
}