/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2009 Erwin Coumans  http://bulletphysics.org

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

///Contains contributions from Disney Studio's

#ifndef BT_OPTIMIZED_BVH_H
#define BT_OPTIMIZED_BVH_H

#include "BulletCollision/BroadphaseCollision/cbtQuantizedBvh.h"

class cbtStridingMeshInterface;

///The cbtOptimizedBvh extends the cbtQuantizedBvh to create AABB tree for triangle meshes, through the cbtStridingMeshInterface.
ATTRIBUTE_ALIGNED16(class)
cbtOptimizedBvh : public cbtQuantizedBvh
{
public:
	BT_DECLARE_ALIGNED_ALLOCATOR();

protected:
public:
	cbtOptimizedBvh();

	virtual ~cbtOptimizedBvh();

	void build(cbtStridingMeshInterface * triangles, bool useQuantizedAabbCompression, const cbtVector3& bvhAabbMin, const cbtVector3& bvhAabbMax);

	void refit(cbtStridingMeshInterface * triangles, const cbtVector3& aabbMin, const cbtVector3& aabbMax);

	void refitPartial(cbtStridingMeshInterface * triangles, const cbtVector3& aabbMin, const cbtVector3& aabbMax);

	void updateBvhNodes(cbtStridingMeshInterface * meshInterface, int firstNode, int endNode, int index);

	/// Data buffer MUST be 16 byte aligned
	virtual bool serializeInPlace(void* o_alignedDataBuffer, unsigned i_dataBufferSize, bool i_swapEndian) const
	{
		return cbtQuantizedBvh::serialize(o_alignedDataBuffer, i_dataBufferSize, i_swapEndian);
	}

	///deSerializeInPlace loads and initializes a BVH from a buffer in memory 'in place'
	static cbtOptimizedBvh* deSerializeInPlace(void* i_alignedDataBuffer, unsigned int i_dataBufferSize, bool i_swapEndian);
};

#endif  //BT_OPTIMIZED_BVH_H
