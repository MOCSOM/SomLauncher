#include "PassthroughSetting.h"

PassthroughSetting::PassthroughSetting(std::shared_ptr<Setting> other, std::shared_ptr<Setting> gate)
	: Setting(other->configKeys(), QVariant())
{
	Q_ASSERT(other);
	this->m_other = other;
	this->m_gate = gate;
}

QVariant PassthroughSetting::defValue() const
{
	if (isOverriding())
	{
		return this->m_other->get();
	}
	return this->m_other->defValue();
}

QVariant PassthroughSetting::get() const
{
	if (isOverriding())
	{
		return Setting::get();
	}
	return this->m_other->get();
}

void PassthroughSetting::set(QVariant value)
{
	if (isOverriding())
	{
		Setting::set(value);
	}
	this->m_other->set(value);
}

void PassthroughSetting::reset()
{
	if (isOverriding())
	{
		Setting::reset();
	}
	this->m_other->reset();
}

bool PassthroughSetting::isOverriding() const
{
	if (!this->m_gate)
	{
		return false;
	}
	return this->m_gate->get().toBool();
}
