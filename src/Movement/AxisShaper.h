/*
 * InputShaper.h
 *
 *  Created on: 20 Feb 2021
 *      Author: David
 */

#ifndef SRC_MOVEMENT_AXISSHAPER_H_
#define SRC_MOVEMENT_AXISSHAPER_H_

#define SUPPORT_DAA		(1)

#include <RepRapFirmware.h>
#include <General/NamedEnum.h>
#include <ObjectModel/ObjectModel.h>
#include "InputShaperPlan.h"

// These names must be in alphabetical order and lowercase
NamedEnum(InputShaperType, uint8_t,
	custom,
#if SUPPORT_DAA
	daa,
#endif
	ei2,
	ei3,
	none,
	zvd,
	zvdd,
);

class DDA;
class BasicPrepParams;
class MoveSegment;

class AxisShaper INHERIT_OBJECT_MODEL
{
public:
	AxisShaper() noexcept;

	float GetFrequency() const noexcept { return frequency; }
	float GetDamping() const noexcept { return zeta; }
	InputShaperType GetType() const noexcept { return type; }
	InputShaperPlan PlanShaping(DDA& dda, BasicPrepParams& params, bool shapingEnabled) const noexcept;

	GCodeResult Configure(GCodeBuffer& gb, const StringRef& reply) THROWS(GCodeException);	// process M593

#if SUPPORT_REMOTE_COMMANDS
	void GetSegments(DDA& dda, const BasicPrepParams& params) const noexcept;
#endif

protected:
	DECLARE_OBJECT_MODEL

private:
	MoveSegment *GetAccelerationSegments(const DDA& dda, const BasicPrepParams& params, InputShaperPlan& plan) const noexcept;
	MoveSegment *GetDecelerationSegments(const DDA& dda, const BasicPrepParams& params, InputShaperPlan& plan) const noexcept;
	MoveSegment *FinishSegments(const DDA& dda, const BasicPrepParams& params, MoveSegment *accelSegs, MoveSegment *decelSegs) const noexcept;
	float GetExtraAccelStartDistance(const DDA& dda) const noexcept;
	float GetExtraAccelEndDistance(const DDA& dda) const noexcept;
	float GetExtraDecelStartDistance(const DDA& dda) const noexcept;
	float GetExtraDecelEndDistance(const DDA& dda) const noexcept;

	static constexpr unsigned int MaxImpulses = 5;
	static constexpr float DefaultFrequency = 40.0;
	static constexpr float DefaultDamping = 0.1;
	static constexpr float DefaultMinimumAcceleration = 10.0;

	float frequency;								// the undamped frequency
	float zeta;										// the damping ratio, see https://en.wikipedia.org/wiki/Damping. 0 = undamped, 1 = critically damped.
	float minimumAcceleration;						// the minimum value that we reduce acceleration to (DAA only)
	float coefficients[MaxImpulses - 1];			// the coefficients of all the impulses, except the last which is 1
	float durations[MaxImpulses - 1];				// the duration in seconds of each impulse except the last
	float totalDuration;							// the total input shaping time in seconds
	float totalShapingClocks;						// the total input shaping time in step clocks
	float clocksLostAtStart, clocksLostAtEnd;		// the acceleration time lost due to input shaping. Multiply by 2 if shaping is used at both the start and end of acceleration.
	float overlappedCoefficients[MaxImpulses - 1][2 * MaxImpulses - 1];
	float overlappedShapingClocks[MaxImpulses - 1];
	float overlappedClocksLost[MaxImpulses - 1];
	float averageAcceleration[MaxImpulses - 1];
	unsigned int numImpulses;						// the total number of impulses
	unsigned int maxOverlap;						// the maximum number of acceleration and deceleration segments that can be overlapped
	InputShaperType type;
};

#endif /* SRC_MOVEMENT_AXISSHAPER_H_ */
