#ifndef PAGES_BASEPAGECONTAINER_H_
#define PAGES_BASEPAGECONTAINER_H_

#include <QString>

class BasePageContainer
{
public:
	BasePageContainer() = default;
	virtual ~BasePageContainer() = default;

public:
	virtual bool selectPage(QString pageId) = 0;
	virtual void refreshContainer() = 0;
	virtual bool requestClose() = 0;
};

#endif // !PAGES_BASEPAGECONTAINER_H_