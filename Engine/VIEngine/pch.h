//Precompile header file
#pragma once


//STL (Standard Template Library)
#include<memory>
#include<stdint.h>
#include<set>
#include<random>
#include<limits>
#include<vector>
#include<string>
#include<bitset>
#include<cassert>
#include<assert.h>
#include<sstream>
#include<istream>
#include<fstream>
#include<iostream>
#include<algorithm>
#include<functional>
#include<unordered_map>
#include<map>
#include<stack>


template <typename T> using Shared = std::shared_ptr<T>;
template <typename T> using Unique = std::unique_ptr<T>;

#if ON_VI_ENGINE
#if DYNAMIC_BUILD
#ifdef _MSC_VER
#define VI_API __declspec(dllexport)
#else
#define VI_API __attribute__((visibility("default")))

#endif // _MSC_VER
#else
#define VI_API
#endif // DYNAMIC_BUILD

#else
#if DYNAMIC_IMPORT
#ifdef _MSC_VER
#define VI_API __declspec(dllimport)
#else
#define VI_API
#endif // _MSC_VER
#else
#define VI_API
#endif //DYNAMIC_IMPORT
#endif // ON_VI_ENGINE

// Runtime assert
#define VI_ASSERT assert

// Static assert
#if defined(__lang__) || defined(__gcc__)
#define VI_STATIC_ASSERT _Static_assert
#else
#define VI_STATIC_ASSERT static_assert
#endif

#if defined(__lang__) || defined(__gcc__)
#define VI_FORCE_INLINE __attribute__((allways_inline)) inline
#define VI_NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
#define VI_FORCE_INLINE __forceinline
#define VI_NOINLINE __declspec(noinline)
#else
#define VI_FORCE_INLINE inline
#define VI_NOINLINE 
#endif

#define VI_FREE_MEMORY(memory) if (memory != nullptr) {delete memory; memory = nullptr;}

#define BIND_EVENT_FUNCTION(function)[this](auto&... args)->decltype(auto)\
{return this->function(std::forward<decltype(args)>(args)...);}

#define INVALID_ID 0

namespace VIEngine {
	using UUID = size_t;
	UUID VI_API GetUUID();


	template<typename T>
	UUID VI_API GetTypeUUID() {
		static UUID uuid = GetUUID();
		return uuid;
	}
}
