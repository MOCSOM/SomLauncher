#include "Mojang.h"

MojangRefresh::MojangRefresh(AccountData* data, QObject* parent)
    : AuthFlow(data, parent) 
{
    /*m_steps.append(new YggdrasilStep(m_data, QString()));
    m_steps.append(new ForcedMigrationStep(m_data));
    m_steps.append(new MinecraftProfileStep(m_data));
    m_steps.append(new MigrationEligibilityStep(m_data));
    m_steps.append(new GetSkinStep(m_data));*/
}

MojangLogin::MojangLogin(AccountData* data, QString password, QObject* parent)
    : AuthFlow(data, parent), m_password(password) 
{
    /*m_steps.append(new YggdrasilStep(m_data, m_password));
    m_steps.append(new ForcedMigrationStep(m_data));
    m_steps.append(new MinecraftProfileStep(m_data));
    m_steps.append(new MigrationEligibilityStep(m_data));
    m_steps.append(new GetSkinStep(m_data));*/
}
