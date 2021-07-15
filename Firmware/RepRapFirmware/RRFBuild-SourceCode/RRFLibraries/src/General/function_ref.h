/// An efficient, type-erasing, non-owning reference to a callable. This is intended for use as
/// the type of a function parameter that is not used after the function in question returns.
///
/// This class does not own the callable, so it is not in general safe to store a function_ref.

// This is a cut-down version of the implementation from LLVM

#ifndef GENERAL_FUNCTION_REF_H
#define GENERAL_FUNCTION_REF_H

#include <type_traits>
#include <functional>

template<typename Fn> class function_ref;

template<typename Ret, typename ...Params>
class function_ref<Ret(Params...)>
{
	Ret (*callback)(void *callable, Params ...params);
	void *callable;

	template<typename Callable> static Ret callback_fn(void *callable2, Params ...params)
	{
		return (*reinterpret_cast<Callable*>(callable2))(std::forward<Params>(params)...);
	}

public:
	template <typename Callable> function_ref(Callable &&callable2,
				typename std::enable_if<!std::is_same<typename std::remove_reference<Callable>::type, function_ref>::value>::type * = nullptr)
	   : callback(callback_fn<typename std::remove_reference<Callable>::type>),
		 callable(reinterpret_cast<void *>(&callable2)) {}

	/// Creates a function_ref which refers to the same callable as rhs
    constexpr function_ref(const function_ref<Ret(Params...)> &rhs) noexcept = default;

    /// Call the stored callable with the given arguments
	Ret operator()(Params ...params) const
	{
		return callback(callable, std::forward<Params>(params)...);
	}
};

#endif /* GENERAL_FUNCTION_REF_H */
