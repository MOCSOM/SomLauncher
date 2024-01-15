#include "MSA.h"

MSAInteractive::MSAInteractive(AccountData* data, QObject* parent)
    : AuthFlow(data, parent) 
{
    m_steps.append(std::make_shared<MSAStep>(m_data, MSAStep::Action::Login));
    /*m_steps.append(std::make_shared<XboxUserStep>(m_data));
    m_steps.append(std::make_shared<XboxAuthorizationStep>(m_data, &m_data->xbox_api_token, "http://xboxlive.com", "Xbox"));
    m_steps.append(std::make_shared<XboxAuthorizationStep>(m_data, &m_data->mojangservices_token, "rp://api.minecraftservices.com/", "Mojang"));
    m_steps.append(std::make_shared<LauncherLoginStep>(m_data));
    m_steps.append(std::make_shared<XboxProfileStep>(m_data));
    m_steps.append(std::make_shared<EntitlementsStep>(m_data));
    m_steps.append(std::make_shared<MinecraftProfileStep>(m_data));
    m_steps.append(std::make_shared<GetSkinStep>(m_data));*/
}

MSASilent::MSASilent(AccountData* data, QObject* parent)
    : AuthFlow(data, parent) 
{
    m_steps.append(std::make_shared<MSAStep>(m_data, MSAStep::Action::Refresh));
    /*m_steps.append(std::make_shared<XboxUserStep>(m_data));
    m_steps.append(std::make_shared<XboxAuthorizationStep>(m_data, &m_data->xbox_api_token, "http://xboxlive.com", "Xbox"));
    m_steps.append(std::make_shared<XboxAuthorizationStep>(m_data, &m_data->mojangservices_token, "rp://api.minecraftservices.com/", "Mojang"));
    m_steps.append(std::make_shared<LauncherLoginStep>(m_data));
    m_steps.append(std::make_shared<XboxProfileStep>(m_data));
    m_steps.append(std::make_shared<EntitlementsStep>(m_data));
    m_steps.append(std::make_shared<MinecraftProfileStep>(m_data));
    m_steps.append(std::make_shared<GetSkinStep>(m_data));*/
}
