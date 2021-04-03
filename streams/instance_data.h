#ifndef VOXEL_INSTANCE_DATA_H
#define VOXEL_INSTANCE_DATA_H

#include "../util/array_slice.h"
#include <core/math/transform.h>
#include "core/object/reference.h"

// Stores data to pass around until it either gets saved or turned into actual instances
struct VoxelInstanceBlockData : public Reference {
	GDCLASS(VoxelInstanceBlockData, Reference);
public:
	struct InstanceData {
		Transform transform;
	};

	struct LayerData {
		uint16_t id;
		float scale_min;
		float scale_max;
		std::vector<InstanceData> instances;
	};

	float position_range;
	std::vector<LayerData> layers;

	void copy_to(Ref<VoxelInstanceBlockData> &dst) const {
		// It's all POD so it should work for now
		dst = this;
	}
};

void serialize_instance_block_data(const Ref<VoxelInstanceBlockData> &src, std::vector<uint8_t> &dst);
bool deserialize_instance_block_data(Ref<VoxelInstanceBlockData> &dst, ArraySlice<const uint8_t> src);

#endif // VOXEL_INSTANCE_DATA_H
