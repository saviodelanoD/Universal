#pragma once

#include "UniversalKinematics.h"

#include <cstdint>

#if defined(UNIVERSAL_KINEMATICS_PROVIDER)
#  define UK_PROVIDER_API __declspec(dllexport)
#else
#  define UK_PROVIDER_API
#endif

namespace UniversalKinematics::API
{
    inline constexpr std::uint32_t kABIVersion = 1;

    using GetAPIVersionFn = std::uint32_t (*)() noexcept;
    using GetProfileForActorFn = const SkeletonProfile* (*)(RE::Actor*) noexcept;
}

extern "C"
{
    UK_PROVIDER_API std::uint32_t UK_GetAPIVersion() noexcept;
    UK_PROVIDER_API const UniversalKinematics::SkeletonProfile* UK_GetProfileForActor(RE::Actor* actor) noexcept;
}

#undef UK_PROVIDER_API

