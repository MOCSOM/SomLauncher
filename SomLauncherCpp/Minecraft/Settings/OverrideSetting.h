#ifndef SETTINGS_OVERRIDESETTINGS_H_
#define SETTINGS_OVERRIDESETTINGS_H_

#include <QObject>

#include <memory>

#include "Setting.h"

/*!
 * \brief A setting that 'overrides another.'
 * This means that the setting's default value will be the value of another setting.
 * The other setting can be (and usually is) a part of a different SettingsObject
 * than this one.
 */
class OverrideSetting : public Setting
{
	Q_OBJECT

protected:
	std::shared_ptr<Setting> m_other;
	std::shared_ptr<Setting> m_gate;

public:
	explicit OverrideSetting(std::shared_ptr<Setting> overriden, std::shared_ptr<Setting> gate);

	virtual QVariant defValue() const;
	virtual QVariant get() const;
	virtual void set(QVariant value);
	virtual void reset();

private:
	bool isOverriding() const;
};

#endif // !SETTINGS_OVERRIDESETTINGS_H_