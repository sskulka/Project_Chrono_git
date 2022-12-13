/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2006 Erwin Coumans  http://continuousphysics.com/Bullet/

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef BT_SUBSIMPLEX_CONVEX_CAST_H
#define BT_SUBSIMPLEX_CONVEX_CAST_H

#include "cbtConvexCast.h"
#include "cbtSimplexSolverInterface.h"
class cbtConvexShape;

/// cbtSubsimplexConvexCast implements Gino van den Bergens' paper
///"Ray Casting against bteral Convex Objects with Application to Continuous Collision Detection"
/// GJK based Ray Cast, optimized version
/// Objects should not start in overlap, otherwise results are not defined.
class cbtSubsimplexConvexCast : public cbtConvexCast
{
	cbtSimplexSolverInterface* m_simplexSolver;
	const cbtConvexShape* m_convexA;
	const cbtConvexShape* m_convexB;

public:
	cbtSubsimplexConvexCast(const cbtConvexShape* shapeA, const cbtConvexShape* shapeB, cbtSimplexSolverInterface* simplexSolver);

	//virtual ~cbtSubsimplexConvexCast();
	///SimsimplexConvexCast calculateTimeOfImpact calculates the time of impact+normal for the linear cast (sweep) between two moving objects.
	///Precondition is that objects should not penetration/overlap at the start from the interval. Overlap can be tested using cbtGjkPairDetector.
	virtual bool calcTimeOfImpact(
		const cbtTransform& fromA,
		const cbtTransform& toA,
		const cbtTransform& fromB,
		const cbtTransform& toB,
		CastResult& result);
};

#endif  //BT_SUBSIMPLEX_CONVEX_CAST_H
