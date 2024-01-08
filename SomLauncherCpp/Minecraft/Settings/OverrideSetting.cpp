#include "OverrideSetting.h"

OverrideSetting::OverrideSetting(std::shared_ptr<Setting> other, std::shared_ptr<Setting> gate)
	: Setting(other->configKeys(), QVariant())
{
	Q_ASSERT(other);
	Q_ASSERT(gate);
	this->m_other = other;
	this->m_gate = gate;
}

QVariant OverrideSetting::defValue() const
{
	return this->m_other->get();
}

QVariant OverrideSetting::get() const
{
	if (isOverriding())
	{
		return Setting::get();
	}
	return this->m_other->get();
}

void OverrideSetting::set(QVariant value)
{
	Setting::set(value);
}

void OverrideSetting::reset()
{
	Setting::reset();
}

bool OverrideSetting::isOverriding() const
{
	return this->m_gate->get().toBool();
}
