#include "PCH.h"
#include "UniversalKinematicsAPI.h"
#include "UKProfileSnapshotABI.h"

#include <algorithm>
#include <cstring>
#include <string>

extern "C" __declspec(dllexport) std::uint32_t UK_GetAPIVersion() noexcept
{
    return UniversalKinematics::API::kABIVersion;
}

extern "C" __declspec(dllexport) const UniversalKinematics::SkeletonProfile* UK_GetProfileForActor(RE::Actor* actor) noexcept
{
    return UniversalKinematics::ProfileManager::GetSingleton().GetProfileForActor(actor);
}


namespace
{
    template <std::size_t N>
    void UK_CopyProfileSnapshotString(
        const std::string& source,
        char (&destination)[N]) noexcept
    {
        static_assert(N > 0);
        const auto count = std::min<std::size_t>(source.size(), N - 1);
        if (count != 0) {
            std::memcpy(destination, source.data(), count);
        }
        destination[count] = '\0';
    }
}

// Additive ABI. The legacy UK_GetProfileForActor export above is deliberately
// untouched for existing consumers.
extern "C" __declspec(dllexport) std::uint32_t UK_GetProfileSnapshotV1(
    void* actorRaw,
    UKProfileSnapshotABI::ProfileSnapshotV1* out,
    std::uint32_t outSize) noexcept
{
    using namespace UKProfileSnapshotABI;

    if (!actorRaw || !out || outSize < sizeof(ProfileSnapshotV1)) {
        return 0;
    }

    *out = ProfileSnapshotV1{};
    out->structSize = static_cast<std::uint32_t>(sizeof(ProfileSnapshotV1));
    out->snapshotVersion = kVersion;

    auto* actor = static_cast<RE::Actor*>(actorRaw);
    const auto* profile =
        UniversalKinematics::ProfileManager::GetSingleton().GetProfileForActor(actor);
    if (!profile) {
        return 0;
    }

    out->locomotionMode = static_cast<std::uint8_t>(profile->locomotionMode);
    out->supportModel = static_cast<std::uint8_t>(profile->supportModel);
    out->supportsGrounding = profile->supportsGrounding ? 1u : 0u;

    for (std::size_t i = 0; i < kFootCapacity; ++i) {
        UK_CopyProfileSnapshotString(profile->footBones[i], out->footBones[i]);
    }

    UK_CopyProfileSnapshotString(profile->pelvisNode, out->pelvisNode);
    UK_CopyProfileSnapshotString(profile->chestNode, out->chestNode);

    const auto spineCount =
        std::min<std::size_t>(profile->spineNodes.size(), kSpineCapacity);
    out->spineCount = static_cast<std::uint8_t>(spineCount);
    for (std::size_t i = 0; i < spineCount; ++i) {
        UK_CopyProfileSnapshotString(profile->spineNodes[i], out->spineNodes[i]);
    }

    const auto casterCount =
        std::min<std::size_t>(profile->groundCasters.size(), kGroundCasterCapacity);
    out->groundCasterCount = static_cast<std::uint8_t>(casterCount);
    for (std::size_t i = 0; i < casterCount; ++i) {
        const auto& source = profile->groundCasters[i];
        auto& destination = out->groundCasters[i];

        UK_CopyProfileSnapshotString(source.node, destination.node);
        destination.probeRadius = source.probeRadius;
        destination.verticalOffset = source.verticalOffset;
        destination.forwardBias = source.forwardBias;
        destination.lateralBias = source.lateralBias;
        destination.primarySupport = source.primarySupport ? 1u : 0u;
        destination.countsForStability = source.countsForStability ? 1u : 0u;
        destination.countsForFallDetection = source.countsForFallDetection ? 1u : 0u;
    }

    out->plantLockStrength = profile->plantLockStrength;
    out->maxPelvisDrop = profile->maxPelvisDrop;
    out->maxPelvisLift = profile->maxPelvisLift;
    return 1;
}

