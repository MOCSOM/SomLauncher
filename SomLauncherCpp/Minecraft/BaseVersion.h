#ifndef MINECRAFT_BASEVERSION_H_
#define MINECRAFT_BASEVERSION_H_

#include <QString>
#include <QMetaType>

#include <memory>

class BaseVersion;

typedef std::shared_ptr<BaseVersion> BaseVersionPtr;

/*!
 * An abstract base class for versions.
 */
class BaseVersion
{
public:
    virtual ~BaseVersion() = default;
    /*!
     * A string used to identify this version in config files.
     * This should be unique within the version list or shenanigans will occur.
     */
    virtual QString descriptor() = 0;

    /*!
     * The name of this version as it is displayed to the user.
     * For example: "1.5.1"
     */
    virtual QString name() = 0;

    /*!
     * This should return a string that describes
     * the kind of version this is (Stable, Beta, Snapshot, whatever)
     */
    virtual QString typeString() const = 0;

    virtual bool operator<(BaseVersion& a);
    virtual bool operator>(BaseVersion& a);
};

Q_DECLARE_METATYPE(BaseVersionPtr)

#endif // !MINECRAFT_BASEVERSION_H_