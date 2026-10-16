#pragma once

// Universal Kinematics profile snapshot transport.
//
// IMPORTANT:
// This header is intentionally independent from UniversalKinematics.h and
// UniversalKinematicsAPI.h. It contains only fixed-size POD data and therefore
// can cross DLL boundaries built with different CRT / iterator-debug settings.
//
// The legacy UK ABI remains unchanged. Consumers opt into this transport by
// resolving "UK_GetProfileSnapshotV1" with GetProcAddress.

#include <cstdint>
#include <type_traits>

namespace UKProfileSnapshotABI
{
    inline constexpr std::uint32_t kVersion = 1;
    inline constexpr std::uint32_t kBoneNameCapacity = 64;
    inline constexpr std::uint32_t kFootCapacity = 4;
    inline constexpr std::uint32_t kSpineCapacity = 16;
    inline constexpr std::uint32_t kGroundCasterCapacity = 16;

    struct GroundCasterSnapshotV1
    {
        char node[kBoneNameCapacity]{};
        float probeRadius{ 0.0f };
        float verticalOffset{ 0.0f };
        float forwardBias{ 0.0f };
        float lateralBias{ 0.0f };
        std::uint8_t primarySupport{ 0 };
        std::uint8_t countsForStability{ 0 };
        std::uint8_t countsForFallDetection{ 0 };
        std::uint8_t reserved{ 0 };
    };

    struct ProfileSnapshotV1
    {
        std::uint32_t structSize{ sizeof(ProfileSnapshotV1) };
        std::uint32_t snapshotVersion{ kVersion };

        std::uint8_t locomotionMode{ 0 };
        std::uint8_t supportModel{ 0 };
        std::uint8_t supportsGrounding{ 0 };
        std::uint8_t reserved0{ 0 };

        char footBones[kFootCapacity][kBoneNameCapacity]{};
        char pelvisNode[kBoneNameCapacity]{};
        char chestNode[kBoneNameCapacity]{};

        std::uint8_t spineCount{ 0 };
        std::uint8_t groundCasterCount{ 0 };
        std::uint16_t reserved1{ 0 };

        char spineNodes[kSpineCapacity][kBoneNameCapacity]{};
        GroundCasterSnapshotV1 groundCasters[kGroundCasterCapacity]{};

        float plantLockStrength{ 0.0f };
        float maxPelvisDrop{ 0.0f };
        float maxPelvisLift{ 0.0f };
    };

    using GetProfileSnapshotV1Fn =
        std::uint32_t (*)(void* actor, ProfileSnapshotV1* out, std::uint32_t outSize) noexcept;

    static_assert(std::is_standard_layout_v<GroundCasterSnapshotV1>);
    static_assert(std::is_trivially_copyable_v<GroundCasterSnapshotV1>);
    static_assert(std::is_standard_layout_v<ProfileSnapshotV1>);
    static_assert(std::is_trivially_copyable_v<ProfileSnapshotV1>);
}

