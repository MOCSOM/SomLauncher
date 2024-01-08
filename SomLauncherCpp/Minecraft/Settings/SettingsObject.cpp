#include "SettingsObject.h"

SettingsObject::Lock::Lock(SettingsObjectPtr locked)
	:m_locked(locked)
{
	m_locked->suspendSave();
}

SettingsObject::Lock::~Lock()
{
	m_locked->resumeSave();
}

SettingsObject::SettingsObject(QObject* parent)
	: QObject(parent)
{
}

SettingsObject::~SettingsObject()
{
	m_settings.clear();
}

std::shared_ptr<Setting> SettingsObject::registerOverride(std::shared_ptr<Setting> original, std::shared_ptr<Setting> gate)
{
	if (contains(original->id()))
	{
		qCritical() << QString("Failed to register setting %1. ID already exists.")
			.arg(original->id());
		return nullptr; // Fail
	}
	auto override = std::make_shared<OverrideSetting>(original, gate);
	override->m_storage = this;
	connectSignals(*override);
	m_settings.insert(override->id(), override);
	return override;
}

std::shared_ptr<Setting> SettingsObject::registerPassthrough(std::shared_ptr<Setting> original, std::shared_ptr<Setting> gate)
{
	if (contains(original->id()))
	{
		qCritical() << QString("Failed to register setting %1. ID already exists.")
			.arg(original->id());
		return nullptr; // Fail
	}
	auto passthrough = std::make_shared<PassthroughSetting>(original, gate);
	passthrough->m_storage = this;
	connectSignals(*passthrough);
	m_settings.insert(passthrough->id(), passthrough);
	return passthrough;
}

std::shared_ptr<Setting> SettingsObject::registerSetting(QStringList synonyms, QVariant defVal)
{
	if (synonyms.empty())
	{
		return nullptr;
	}

	if (contains(synonyms.first()))
	{
		qCritical() << QString("Failed to register setting %1. ID already exists.")
			.arg(synonyms.first());
		return nullptr; // Fail
	}

	auto setting = std::make_shared<Setting>(synonyms, defVal);
	setting->m_storage = this;
	connectSignals(*setting);
	m_settings.insert(setting->id(), setting);
	return setting;
}

std::shared_ptr<Setting> SettingsObject::registerSetting(QString id, QVariant defVal)
{
	return registerSetting(QStringList(id), defVal);
}

std::shared_ptr<Setting> SettingsObject::getSetting(const QString& id) const
{
	// Make sure there is a setting with the given ID.
	if (!m_settings.contains(id))
	{
		return nullptr;
	}

	return m_settings[id];
}

QVariant SettingsObject::get(const QString& id) const
{
	auto setting = getSetting(id);
	return (setting ? setting->get() : QVariant());
}

bool SettingsObject::set(const QString& id, QVariant value) const
{
	auto setting = getSetting(id);
	if (!setting)
	{
		qCritical() << QString("Error changing setting %1. Setting doesn't exist.").arg(id);
		return false;
	}
	else
	{
		setting->set(value);
		return true;
	}
}

void SettingsObject::reset(const QString& id) const
{
	auto setting = getSetting(id);
	if (setting)
	{
		setting->reset();
	}
}

bool SettingsObject::contains(const QString& id)
{
	return m_settings.contains(id);
}

bool SettingsObject::reload()
{
	for (auto& setting : m_settings.values())
	{
		setting->set(setting->get());
	}
	return true;
}

void SettingsObject::connectSignals(const Setting& setting) const
{
	//TODO qt compiletime connect
	QObject::connect(&setting, SIGNAL(SettingChanged(const Setting&, QVariant)),
		SLOT(changeSetting(const Setting&, QVariant)));
	QObject::connect(&setting, SIGNAL(SettingChanged(const Setting&, QVariant)),
		SIGNAL(SettingChanged(const Setting&, QVariant)));

	QObject::connect(&setting, SIGNAL(settingReset(Setting)), SLOT(resetSetting(const Setting&)));
	QObject::connect(&setting, SIGNAL(settingReset(Setting)), SIGNAL(settingReset(const Setting&)));
}