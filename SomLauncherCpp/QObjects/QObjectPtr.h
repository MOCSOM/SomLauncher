#ifndef QOBJECT_QOBJECTPTR_H_
#define QOBJECT_QOBJECTPTR_H_

#include <QObject>

#include <memory>

namespace details
{
	struct DeleteQObjectLater
	{
		void operator()(QObject* obj) const
		{
			obj->deleteLater();
		}
	};
}

template<typename T>
using unique_qobject_ptr = std::unique_ptr<T, details::DeleteQObjectLater>;

template <typename T>
class shared_qobject_ptr
{
public:
	shared_qobject_ptr() {}
	shared_qobject_ptr(T* wrap)
	{
		reset(wrap);
	}
	shared_qobject_ptr(const shared_qobject_ptr<T>& other)
	{
		m_ptr = other.m_ptr;
	}
	template<typename Derived>
	shared_qobject_ptr(const shared_qobject_ptr<Derived>& other)
	{
		m_ptr = other.unwrap();
	}

public:
	void reset(T* wrap)
	{
		using namespace std::placeholders;
		m_ptr.reset(wrap, std::bind(&QObject::deleteLater, _1));
	}
	void reset(const shared_qobject_ptr<T>& other)
	{
		m_ptr = other.m_ptr;
	}
	void reset()
	{
		m_ptr.reset();
	}
	T* get() const
	{
		return m_ptr.get();
	}
	T* operator->() const
	{
		return m_ptr.get();
	}
	T& operator*() const
	{
		return *m_ptr.get();
	}
	operator bool() const
	{
		return m_ptr.get() != nullptr;
	}
	const std::shared_ptr <T> unwrap() const
	{
		return m_ptr;
	}
	bool operator==(const shared_qobject_ptr<T>& other) const {
		return m_ptr == other.m_ptr;
	}
	bool operator!=(const shared_qobject_ptr<T>& other) const {
		return m_ptr != other.m_ptr;
	}

private:
	std::shared_ptr <T> m_ptr;
};

#endif // !QOBJECT_QOBJECTPTR_H_
