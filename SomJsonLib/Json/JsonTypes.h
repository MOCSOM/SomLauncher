#ifndef JSONTYPES_H_
#define JSONTYPES_H_

#ifdef SOMJSONDLL_EXPORTS
#define JSONPARCER_API __declspec(dllexport)
#else
#define JSONPARCER_API __declspec(dllimport)
#endif

namespace Json
{
	enum struct JsonTypes
	{
		String,
		Number,
		Bool,
		Array,
		Object,
		Null,
		NotImplemented
	};
}

#endif /*JSONTYPES_H_*/