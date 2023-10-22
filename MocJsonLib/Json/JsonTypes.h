#ifndef JSONTYPES_H_
#define JSONTYPES_H_

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