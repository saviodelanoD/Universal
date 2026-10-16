#pragma once

#include <RE/Skyrim.h>

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace UniversalKinematics
{
	enum class LocomotionMode : std::uint8_t
	{
		Unspecified = 0,
		GroundedBiped,
		GroundedQuadruped,
		GroundedCrawler,
		GroundedRadial,
		Rolling,
		FlyingGroundCapable,
		FlyingOnly,
		Hovering,
		Swimming,
		Burrowing,
		Static
	};

	enum class GroundSupportModel : std::uint8_t
	{
		Unspecified = 0,
		StandardFeetOnly,
		MultiContactCrawler,
		RadialMultiLeg,
		RollingBody,
		FeetPlusBody,
		FlightOnly,
		HoverOnly,
		SwimOnly
	};

	enum class FallModel : std::uint8_t
	{
		Unspecified = 0,
		StandardUpright,
		LowBodyCrawler,
		RadialDistributed,
		RollingTransform,
		Aerial,
		NoGroundFall
	};

	enum class UpperBodyModel : std::uint8_t
	{
		Unspecified = 0,
		HumanoidHands,
		ForelimbBraced,
		HeadNeckOnly,
		NoMeaningfulUpperBody
	};

	struct GroundCasterPoint
	{
		std::string node{};
		float probeRadius{ 0.0f };
		float verticalOffset{ 0.0f };
		float forwardBias{ 0.0f };
		float lateralBias{ 0.0f };
		bool primarySupport{ false };
		bool countsForStability{ true };
		bool countsForFallDetection{ true };
	};

	struct SkeletonProfile
	{
		// -------------------------------------------------
		// legacy / core
		// -------------------------------------------------
		std::string footBones[4]{};
		std::string pelvisNode{};
		std::vector<std::string> spineNodes{};
		std::string headNode{};

		float bodyLength{ 0.0f };
		float bodyWidth{ 0.0f };
		float bankFactor{ 1.0f };
		float pitchFactor{ 1.0f };
		float strideScale{ 1.0f };

		// -------------------------------------------------
		// locomotion taxonomy / support model
		// -------------------------------------------------
		LocomotionMode locomotionMode{ LocomotionMode::Unspecified };
		GroundSupportModel supportModel{ GroundSupportModel::Unspecified };
		FallModel fallModel{ FallModel::Unspecified };
		UpperBodyModel upperBodyModel{ UpperBodyModel::Unspecified };

		// -------------------------------------------------
		// generic capability layer
		// -------------------------------------------------
		bool supportsGrounding{ true };
		bool supportsStepUp{ true };
		bool supportsStepDown{ true };
		bool supportsSlopeAdaptation{ true };
		bool supportsSupportRecovery{ true };
		bool supportsFallRecovery{ true };
		bool supportsAnatomicalRagdoll{ true };

		bool supportsAirborneLocomotion{ false };
		bool prefersAerialRecovery{ false };

		bool supportsWaterLocomotion{ false };
		bool supportsBurrowingLocomotion{ false };

		bool usesForelimbsAsHands{ false };
		bool isHumanoidLikeUpperBody{ false };

		// -------------------------------------------------
		// ground support / caster model
		// -------------------------------------------------
		std::vector<GroundCasterPoint> groundCasters{};
		std::vector<std::string> bodySupportNodes{};

		std::uint8_t minPrimaryContactsForStable{ 2 };
		std::uint8_t minTotalContactsForStable{ 2 };

		bool allowBodySupportContact{ false };
		bool allowTailSupportContact{ false };
		bool ignoreAirborneFallIfBodySupported{ false };

		float bodySupportProbeHeight{ 0.0f };
		float bodySupportProbeForward{ 0.0f };
		float bodySupportProbeRear{ 0.0f };
		float bodySupportProbeHalfWidth{ 0.0f };

		// -------------------------------------------------
		// upper-body refs
		// -------------------------------------------------
		std::string neckNode{};
		std::string chestNode{};
		std::string clavicleL{};
		std::string clavicleR{};
		std::string upperArmL{};
		std::string upperArmR{};
		std::string forearmL{};
		std::string forearmR{};
		std::string handL{};
		std::string handR{};

		// -------------------------------------------------
		// lower-body chain
		// -------------------------------------------------
		std::string thighL{};
		std::string thighR{};
		std::string calfL{};
		std::string calfR{};
		std::string footL{};
		std::string footR{};
		std::string toeL{};
		std::string toeR{};

		// -------------------------------------------------
		// anatomical measures
		// -------------------------------------------------
		float torsoHeight{ 0.0f };
		float torsoDepth{ 0.0f };
		float shoulderWidth{ 0.0f };
		float neckLength{ 0.0f };
		float headRadius{ 0.0f };
		float armLength{ 0.0f };
		float forearmLength{ 0.0f };
		float handLength{ 0.0f };

		float leftUpperLegLength{ 0.0f };
		float rightUpperLegLength{ 0.0f };
		float leftLowerLegLength{ 0.0f };
		float rightLowerLegLength{ 0.0f };
		float leftLegLength{ 0.0f };
		float rightLegLength{ 0.0f };

		// -------------------------------------------------
		// support base
		// -------------------------------------------------
		float stanceWidth{ 0.0f };
		float stanceLength{ 0.0f };
		float frontTrackWidth{ 0.0f };
		float rearTrackWidth{ 0.0f };
		float supportBaseLength{ 0.0f };

		// -------------------------------------------------
		// correction envelopes
		// -------------------------------------------------
		float maxPelvisDrop{ 0.0f };
		float maxPelvisLift{ 0.0f };
		float maxStepHeight{ 0.0f };
		float maxStepDown{ 0.0f };
		float usableLegReachRatio{ 0.0f };
		float ragdollLegFailureRatio{ 0.0f };
		float supportRecoveryTime{ 0.0f };

		// -------------------------------------------------
		// foot placement
		// -------------------------------------------------
		float footPlantOffsetZ{ 0.0f };
		float footPlantForwardOffset{ 0.0f };
		float toeToHeelLength{ 0.0f };
		float footRadius{ 0.0f };
		float footClearanceMargin{ 0.0f };
		float footLiftBias{ 0.0f };

		// -------------------------------------------------
		// lower-body angular limits
		// -------------------------------------------------
		float maxStablePitchDeg{ 0.0f };
		float maxStableRollDeg{ 0.0f };
		float maxRecoverablePitchDeg{ 0.0f };
		float maxRecoverableRollDeg{ 0.0f };
		float maxBankPerStepDeg{ 0.0f };
		float maxPelvisTiltDeg{ 0.0f };

		// -------------------------------------------------
		// locomotion functional
		// -------------------------------------------------
		float nominalStepLength{ 0.0f };
		float nominalStepHeight{ 0.0f };
		float strideWarpLimit{ 0.0f };
		float swingLiftMax{ 0.0f };
		float swingLiftResponse{ 0.0f };
		float plantLockStrength{ 0.0f };

		float plantAcquireResponse{ 0.0f };
		float plantReleaseResponse{ 0.0f };
		float pelvisSettleResponse{ 0.0f };

		// -------------------------------------------------
		// upper-body sensing/contact
		// -------------------------------------------------
		float avoidanceStartDist{ 0.0f };
		float avoidanceFullDist{ 0.0f };
		float wallBraceStartDist{ 0.0f };
		float wallBraceFullDist{ 0.0f };
		float wallReleaseDist{ 0.0f };
		float sideClearanceMin{ 0.0f };
		float headClearanceMin{ 0.0f };
		float handContactOffset{ 0.0f };

		// -------------------------------------------------
		// upper-body pose limits
		// -------------------------------------------------
		float maxTorsoAvoidYaw{ 0.0f };
		float maxTorsoAvoidPitch{ 0.0f };
		float maxTorsoAvoidRoll{ 0.0f };
		float maxHeadAvoidYaw{ 0.0f };
		float maxHeadAvoidPitch{ 0.0f };
		float maxClavicleLift{ 0.0f };
		float maxShoulderProtract{ 0.0f };
		float maxShoulderRetract{ 0.0f };
		float maxElbowFlex{ 0.0f };
		float maxHandReach{ 0.0f };
		float maxHandSlide{ 0.0f };

		// -------------------------------------------------
		// contribution weights
		// -------------------------------------------------
		float footPlacementWeight{ 0.0f };
		float pelvisCorrectionWeight{ 0.0f };
		float slopeAdaptWeight{ 0.0f };
		float supportRecoveryWeight{ 0.0f };
		float bankStabilizationWeight{ 0.0f };
		float pitchStabilizationWeight{ 0.0f };

		float torsoAvoidWeight{ 0.0f };
		float headAvoidWeight{ 0.0f };
		float clavicleWeight{ 0.0f };
		float upperArmWeight{ 0.0f };
		float forearmWeight{ 0.0f };
		float handPlantWeight{ 0.0f };
		float forearmShieldWeight{ 0.0f };
		float wallSlideWeight{ 0.0f };

		// -------------------------------------------------
		// temporal / hysteresis
		// -------------------------------------------------
		float avoidEnterResponse{ 0.0f };
		float avoidExitResponse{ 0.0f };
		float contactEnterResponse{ 0.0f };
		float contactExitResponse{ 0.0f };
		float reachResponse{ 0.0f };
		float releaseResponse{ 0.0f };
		float contactHoldTime{ 0.0f };
		float contactReacquireDelay{ 0.0f };

		// -------------------------------------------------
		// upper-body capability flags
		// -------------------------------------------------
		bool supportsWallBrace{ false };
		bool supportsForearmShield{ false };
		bool supportsHandPlant{ false };
		bool preferLeftHandForBrace{ false };
		bool preferRightHandForBrace{ false };
	};

	class ProfileManager
	{
	public:
		static ProfileManager& GetSingleton();

		const SkeletonProfile* GetProfileForActor(RE::Actor* actor);
		void InitializeDefaultProfiles();

	private:
		ProfileManager() = default;
		ProfileManager(const ProfileManager&) = delete;
		ProfileManager& operator=(const ProfileManager&) = delete;

		std::unordered_map<RE::FormID, SkeletonProfile> _registry;
	};
}
