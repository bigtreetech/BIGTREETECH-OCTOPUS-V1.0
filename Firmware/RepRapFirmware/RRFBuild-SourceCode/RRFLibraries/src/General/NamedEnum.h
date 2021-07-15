/*
 * NamedEnum.h
 *
 *  Created on: 27 Aug 2018
 *      Author: David
 */

#ifndef SRC_NAMEDENUM_H_
#define SRC_NAMEDENUM_H_

// Plumbing to allow overloaded STRINGLIST macro
#define CAT( A, B ) A ## B
#define SELECT( NAME, NUM ) CAT( NAME ## _, NUM )
#define GET_COUNT( _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, COUNT, ... ) COUNT
#define VA_SIZE( ... ) GET_COUNT( __VA_ARGS__, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 )
#define VA_SELECT( NAME, ... ) SELECT( NAME, VA_SIZE(__VA_ARGS__) )(__VA_ARGS__)

// Macro to turn a list of names into a list of strings
#define STRINGLIST( ... ) VA_SELECT( STRINGLIST, __VA_ARGS__ )
#define STRINGLIST_2(_v1,_v2)																	#_v1,#_v2
#define STRINGLIST_3(_v1,_v2,_v3)																#_v1,#_v2,#_v3
#define STRINGLIST_4(_v1,_v2,_v3,_v4)															#_v1,#_v2,#_v3,#_v4
#define STRINGLIST_5(_v1,_v2,_v3,_v4,_v5)														#_v1,#_v2,#_v3,#_v4,#_v5
#define STRINGLIST_6(_v1,_v2,_v3,_v4,_v5,_v6)													#_v1,#_v2,#_v3,#_v4,#_v5,#_v6
#define STRINGLIST_7(_v1,_v2,_v3,_v4,_v5,_v6,_v7)												#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7
#define STRINGLIST_8(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8)											#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8
#define STRINGLIST_9(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9)										#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9
#define STRINGLIST_10(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10)									#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10
#define STRINGLIST_11(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11)							#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11
#define STRINGLIST_12(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12)						#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12
#define STRINGLIST_13(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13)					#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13
#define STRINGLIST_14(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14)				#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14
#define STRINGLIST_15(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15)		#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15
#define STRINGLIST_16(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16)	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16
#define STRINGLIST_17(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17
#define STRINGLIST_18(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17,_v18) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17,#_v18
#define STRINGLIST_19(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17,_v18,_v19) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17,#_v18,#_v19
#define STRINGLIST_20(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17,_v18,_v19,_v20) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17,#_v18,#_v19,#_v20
#define STRINGLIST_21(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17,_v18,_v19,_v20,_v21) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17,#_v18,#_v19,#_v20,#_v21
#define STRINGLIST_22(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17,_v18,_v19,_v20,_v21,_v22) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17,#_v18,#_v19,#_v20,#_v21,#_v22
#define STRINGLIST_23(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17,_v18,_v19,_v20,_v21,_v22,_v23) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17,#_v18,#_v19,#_v20,#_v21,#_v22,#_v23
#define STRINGLIST_24(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17,_v18,_v19,_v20,_v21,_v22,_v23,_v24) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17,#_v18,#_v19,#_v20,#_v21,#_v22,#_v23,#_v24
#define STRINGLIST_25(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17,_v18,_v19,_v20,_v21,_v22,_v23,_v24,_v25) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17,#_v18,#_v19,#_v20,#_v21,#_v22,#_v23,#_v24,#_v25
#define STRINGLIST_26(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17,_v18,_v19,_v20,_v21,_v22,_v23,_v24,_v25,_v26) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17,#_v18,#_v19,#_v20,#_v21,#_v22,#_v23,#_v24,#_v25,#_v26
#define STRINGLIST_27(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17,_v18,_v19,_v20,_v21,_v22,_v23,_v24,_v25,_v26,_v27) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17,#_v18,#_v19,#_v20,#_v21,#_v22,#_v23,#_v24,#_v25,#_v26,#_v27
#define STRINGLIST_28(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17,_v18,_v19,_v20,_v21,_v22,_v23,_v24,_v25,_v26,_v27,_v28) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17,#_v18,#_v19,#_v20,#_v21,#_v22,#_v23,#_v24,#_v25,#_v26,#_v27,#_v28
#define STRINGLIST_29(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17,_v18,_v19,_v20,_v21,_v22,_v23,_v24,_v25,_v26,_v27,_v28,_v29) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17,#_v18,#_v19,#_v20,#_v21,#_v22,#_v23,#_v24,#_v25,#_v26,#_v27,#_v28,#_v29
#define STRINGLIST_30(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17,_v18,_v19,_v20,_v21,_v22,_v23,_v24,_v25,_v26,_v27,_v28,_v29,_v30) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17,#_v18,#_v19,#_v20,#_v21,#_v22,#_v23,#_v24,#_v25,#_v26,#_v27,#_v28,#_v29,#_v30
#define STRINGLIST_31(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17,_v18,_v19,_v20,_v21,_v22,_v23,_v24,_v25,_v26,_v27,_v28,_v29,_v30,_v31) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17,#_v18,#_v19,#_v20,#_v21,#_v22,#_v23,#_v24,#_v25,#_v26,#_v27,#_v28,#_v29,#_v30,#_v31
#define STRINGLIST_32(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17,_v18,_v19,_v20,_v21,_v22,_v23,_v24,_v25,_v26,_v27,_v28,_v29,_v30,_v31,_v32) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17,#_v18,#_v19,#_v20,#_v21,#_v22,#_v23,#_v24,#_v25,#_v26,#_v27,#_v28,#_v29,#_v30,#_v31,#_v32
#define STRINGLIST_33(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17,_v18,_v19,_v20,_v21,_v22,_v23,_v24,_v25,_v26,_v27,_v28,_v29,_v30,_v31,_v32,_v33) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17,#_v18,#_v19,#_v20,#_v21,#_v22,#_v23,#_v24,#_v25,#_v26,#_v27,#_v28,#_v29,#_v30,#_v31,#_v32,#_v33
#define STRINGLIST_34(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17,_v18,_v19,_v20,_v21,_v22,_v23,_v24,_v25,_v26,_v27,_v28,_v29,_v30,_v31,_v32,_v33,_v34) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17,#_v18,#_v19,#_v20,#_v21,#_v22,#_v23,#_v24,#_v25,#_v26,#_v27,#_v28,#_v29,#_v30,#_v31,#_v32,#_v33,#_v34
#define STRINGLIST_35(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17,_v18,_v19,_v20,_v21,_v22,_v23,_v24,_v25,_v26,_v27,_v28,_v29,_v30,_v31,_v32,_v33,_v34,_v35) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17,#_v18,#_v19,#_v20,#_v21,#_v22,#_v23,#_v24,#_v25,#_v26,#_v27,#_v28,#_v29,#_v30,#_v31,#_v32,#_v33,#_v34,#_v35
#define STRINGLIST_36(_v1,_v2,_v3,_v4,_v5,_v6,_v7,_v8,_v9,_v10,_v11,_v12,_v13,_v14,_v15,_v16,_v17,_v18,_v19,_v20,_v21,_v22,_v23,_v24,_v25,_v26,_v27,_v28,_v29,_v30,_v31,_v32,_v33,_v34,_v35,_v36) \
	#_v1,#_v2,#_v3,#_v4,#_v5,#_v6,#_v7,#_v8,#_v9,#_v10,#_v11,#_v12,#_v13,#_v14,#_v15,#_v16,#_v17,#_v18,#_v19,#_v20,#_v21,#_v22,#_v23,#_v24,#_v25,#_v26,#_v27,#_v28,#_v29,#_v30,#_v31,#_v32,#_v33,#_v34,#_v35,#_v36

// Function to search the table of names for a match. Returns numNames if not found.
unsigned int NamedEnumLookup(const char *s, const char * const names[], unsigned int numNames) noexcept;

static inline const char *SkipLeadingUnderscore(const char *s) noexcept
{
	return (*s == '_') ? s + 1 : s;
}

// Macro to declare an enumeration with printable value names
// Usage example:
//  NamedEnum(MakeOfCar, ford, vauxhall, bmw);
//  MakeOfCar mycar(MakeOfCar::bmw);
//  myCar = MakeOfCar::ford;
//  if (myCar == MakeOfCar::vauxhall) { ... }
//  printf("%s", myCar.ToString());
//
// If any of the names is a C++ reserved word or starts with a digit, prefix it with a single underscore
// IMPORTANT! If the constructor from string is used then the names must be in alphabetical order (ignoring the leading underscore) because it uses a binary search
#define NamedEnum(_typename, _baseType, _v1, ...) \
class _typename { \
public: \
	typedef _baseType BaseType;																					/* alias for the base type */ \
	enum RawType : BaseType { _v1 = 0, __VA_ARGS__ };															/* underlying enumeration */ \
	static constexpr unsigned int NumValues = VA_SIZE(__VA_ARGS__) + 1;											/* count of members */ \
	_typename(RawType arg) noexcept { v = arg; }																/* constructor */ \
	explicit _typename(BaseType arg) noexcept { v = static_cast<RawType>(arg); }								/* constructor */ \
	explicit _typename(const char *s) noexcept { v = static_cast<RawType>(NamedEnumLookup(s, _names, NumValues)); }	/* constructor from string - NAMES MUST BE ORDERED when using this */ \
	_typename(const _typename& arg) noexcept { v = arg.v; }														/* copy constructor */ \
	bool operator==(_typename arg) const noexcept { return v == arg.v; }										/* equality operator */ \
	bool operator!=(_typename arg) const noexcept { return v != arg.v; }										/* inequality operator */ \
	bool operator>(_typename arg) const noexcept { return v > arg.v; }											/* greater-than operator */ \
	bool operator>=(_typename arg) const noexcept { return v >= arg.v; }										/* greater-than-or-equal operator */ \
	bool operator<(_typename arg) const noexcept { return v < arg.v; }											/* less-than operator */ \
	bool operator<=(_typename arg) const noexcept { return v <= arg.v; }										/* less-than-or-equal operator */ \
	bool operator==(RawType arg) const noexcept { return v == arg; }											/* equality operator */ \
	bool operator!=(RawType arg) const noexcept { return v != arg; }											/* inequality operator */ \
	bool operator>(RawType arg) const noexcept { return v > arg; }												/* greater-than operator */ \
	bool operator>=(RawType arg) const noexcept { return v >= arg; }											/* greater-than-or-equal operator */ \
	bool operator<(RawType arg) const noexcept { return v < arg; }												/* less-than operator */ \
	bool operator<=(RawType arg) const noexcept { return v <= arg; }											/* less-than-or-equal operator */ \
	const _typename& operator=(RawType arg) noexcept { v = arg; return *this; }									/* assignment operator from underlying enum */ \
	const _typename& operator=(_typename arg) noexcept { v = arg.v; return *this; }								/* copy assignment operator */ \
	constexpr RawType RawValue() const noexcept { return v; }													/* return the raw enum value, which we can switch on */ \
	constexpr BaseType ToBaseType() const noexcept { return static_cast<BaseType>(v); }							/* convert to integral base type */ \
	static constexpr BaseType ToBaseType(RawType arg) noexcept { return static_cast<BaseType>(arg); }			/* convert to integral base type */ \
	const char* ToString() const noexcept { return (v < NumValues) ? SkipLeadingUnderscore(_names[v]) : "invalid"; }	/* conversion to C string */ \
	void Assign(BaseType arg) noexcept { v = static_cast<RawType>(arg); }										/* assignment from integral base type */ \
	bool IsValid() const noexcept { return v < NumValues; }														/* check validity */ \
private: \
	RawType v; \
	static constexpr const char* _names[NumValues] = { STRINGLIST(_v1, __VA_ARGS__) }; \
}

#endif /* SRC_NAMEDENUM_H_ */
