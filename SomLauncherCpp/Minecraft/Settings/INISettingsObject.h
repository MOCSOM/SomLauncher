#ifndef SETTINGS_INISETTINGSOBJECT_H_
#define SETTINGS_INISETTINGSOBJECT_H_

#include <QObject>

#include "Setting.h"
#include "INIFile.h"
#include "SettingsObject.h"

/*!
 * \brief A settings object that stores its settings in an INIFile.
 */
class INISettingsObject : public SettingsObject
{
	Q_OBJECT

protected:
	INIFile m_ini;
	QString m_filePath;

public:
	explicit INISettingsObject(const QString& path, QObject* parent = 0);

	/*!
	 * \brief Gets the path to the INI file.
	 * \return The path to the INI file.
	 */
	virtual QString filePath() const;

	/*!
	 * \brief Sets the path to the INI file and reloads it.
	 * \param filePath The INI file's new path.
	 */
	virtual void setFilePath(const QString& filePath);

	bool reload() override;

	void suspendSave() override;
	void resumeSave() override;

protected slots:
	virtual void changeSetting(const Setting& setting, QVariant value) override;
	virtual void resetSetting(const Setting& setting) override;

protected:
	virtual QVariant retrieveValue(const Setting& setting) override;
	void doSave();
};

#endif // !SETTINGS_INISETTINGSOBJECT_H_