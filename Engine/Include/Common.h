#pragma once

#include <iostream>
#include <bitset>

#ifdef BUILD_DLL
	#define EXTERN extern
#else
	#define EXTERN
#endif

#define COMPONENT(name) struct name : public Component<name>

#ifdef PLATFORM_WINDOWS
	#ifdef BUILD_DLL
		#define API __declspec(dllexport)
	#else
		#define API __declspec(dllimport)
	#endif
#else
	#define API
#endif

#ifdef BUILD_DEBUG
	#define LOG(message) std::cout << "  " << message << "\n"
	#define LOG_WARNING(message) std::cout << "- " << message << "\n"
	#define LOG_ERROR(message) std::cout << "! " << message << "\n"
#else
	#define LOG(message)
	#define LOG_WARNING(message)
	#define LOG_ERROR(message)
#endif

#define LOG_ALWAYS(message) std::cout << "  " << message << "\n"

typedef uint8_t int_componentID;	// Max component count = 256
typedef uint16_t int_entityID;		// Max entity count = 65536

constexpr uint32_t GetMaxComponentID()
{
	uint32_t value = 1;

	for (int i = 0; i < sizeof(int_componentID) * 8; i++)
	{
		value *= 2;
	}

	return value;
}

typedef std::bitset<GetMaxComponentID()> componentKey;
