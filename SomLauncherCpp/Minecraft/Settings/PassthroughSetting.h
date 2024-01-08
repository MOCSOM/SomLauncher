#ifndef SETTINGS_PASSTHROUGHSETTINGS_H_
#define SETTINGS_PASSTHROUGHSETTINGS_H_

#include <QObject>

#include <memory>

#include "Setting.h"

/*!
 * \brief A setting that 'overrides another.' based on the value of a 'gate' setting
 * If 'gate' evaluates to true, the override stores and returns data
 * If 'gate' evaluates to false, the original does,
 */
class PassthroughSetting : public Setting
{
	Q_OBJECT

protected:
	std::shared_ptr<Setting> m_other;
	std::shared_ptr<Setting> m_gate;

public:
	explicit PassthroughSetting(std::shared_ptr<Setting> overriden, std::shared_ptr<Setting> gate);

	virtual QVariant defValue() const;
	virtual QVariant get() const;
	virtual void set(QVariant value);
	virtual void reset();

private:
	bool isOverriding() const;
};

#endif // !SETTINGS_PASSTHROUGHSETTINGS_H_