#include "Setting.h"

Setting::Setting(QStringList synonyms, QVariant defVal)
	: QObject(), m_synonyms(synonyms), m_defVal(defVal)
{
}

QString Setting::id() const
{
	return this->m_synonyms.first();
}

QStringList Setting::configKeys() const
{
	return this->m_synonyms;
}

QVariant Setting::get() const
{
	SettingsObject* sbase = this->m_storage;
	if (!sbase)
	{
		return defValue();
	}
	else
	{
		QVariant test = sbase->retrieveValue(*this);
		if (!test.isValid())
			return defValue();
		return test;
	}
}

QVariant Setting::defValue() const
{
	return this->m_defVal;
}

void Setting::set(QVariant value)
{
	emit SettingChanged(*this, value);
}

void Setting::reset()
{
	emit settingReset(*this);
}