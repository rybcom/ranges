
#pragma once

#include <type_traits>

namespace types
{

	template<typename T>
	using IsNotReference = typename std::enable_if<!std::is_reference<T>::value, void>::type;

	template <typename T, typename Parameter>
	class NamedType 
	{
	public:
		using UnderlyingType = T;


		// constructor
		constexpr NamedType()
		{
			value_ = T{};
		}
		explicit constexpr NamedType(T const& value) : value_(value) {}
		template<typename T_ = T, typename = IsNotReference<T_>>
		explicit constexpr NamedType(T&& value) : value_(std::move(value)) {}

		// get
		constexpr T& get() { return value_; }
		constexpr T const& get() const { return value_; }

		// conversions
		using ref = NamedType<T&, Parameter>;
		operator ref ()
		{
			return ref(value_);
		}

		struct argument
		{
			template<typename U>
			NamedType operator=(U&& value) const
			{
				return NamedType(std::forward<U>(value));
			}
			argument() = default;
			argument(argument const&) = delete;
			argument(argument &&) = delete;
			argument& operator=(argument const&) = delete;
			argument& operator=(argument &&) = delete;
		};

	private:
		T value_;
	};

	template<template<typename T> class StrongType, typename T>
	constexpr StrongType<T> make_named(T const& value)
	{
		return StrongType<T>(value);
	}

}


