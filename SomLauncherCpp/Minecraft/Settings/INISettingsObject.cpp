#include "INISettingsObject.h"

INISettingsObject::INISettingsObject(const QString& path, QObject* parent)
	: SettingsObject(parent)
{
	this->m_filePath = path;
	this->m_ini.loadFile(path);
}

QString INISettingsObject::filePath() const
{
	return this->m_filePath;
}

void INISettingsObject::setFilePath(const QString& filePath)
{
	this->m_filePath = filePath;
}

bool INISettingsObject::reload()
{
	return this->m_ini.loadFile(this->m_filePath) && SettingsObject::reload();
}

void INISettingsObject::suspendSave()
{
	this->m_suspendSave = true;
}

void INISettingsObject::resumeSave()
{
	this->m_suspendSave = false;
	if (this->m_doSave)
	{
		this->m_ini.saveFile(this->m_filePath);
	}
}

void INISettingsObject::changeSetting(const Setting& setting, QVariant value)
{
	if (contains(setting.id()))
	{
		// valid value -> set the main config, remove all the sysnonyms
		if (value.isValid())
		{
			auto list = setting.configKeys();
			this->m_ini.set(list.takeFirst(), value);
			for (auto& iter : list)
				this->m_ini.remove(iter);
		}
		// invalid -> remove all (just like resetSetting)
		else
		{
			for (auto& iter : setting.configKeys())
				this->m_ini.remove(iter);
		}
		doSave();
	}
}

void INISettingsObject::resetSetting(const Setting& setting)
{
	// if we have the setting, remove all the synonyms. ALL OF THEM
	if (contains(setting.id()))
	{
		for (auto& iter : setting.configKeys())
			this->m_ini.remove(iter);
		doSave();
	}
}

QVariant INISettingsObject::retrieveValue(const Setting& setting)
{
	// if we have the setting, return value of the first matching synonym
	if (contains(setting.id()))
	{
		for (auto& iter : setting.configKeys())
		{
			if (this->m_ini.contains(iter))
				return this->m_ini[iter];
		}
	}
	return QVariant();
}

void INISettingsObject::doSave()
{
	if (this->m_suspendSave)
	{
		this->m_doSave = true;
	}
	else
	{
		this->m_ini.saveFile(this->m_filePath);
	}
}