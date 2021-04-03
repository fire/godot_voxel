#include "voxel_stream_cache.h"

bool VoxelStreamCache::load_voxel_block(Vector3i position, uint8_t lod_index, Ref<VoxelBuffer> &out_voxels) {
	ERR_FAIL_COND_V(out_voxels.is_null(), false);

	const Lod &lod = _cache[lod_index];
	lod.rw_lock.read_lock();

	if (!lod.blocks.has(position)) {
		// Not in cache, will have to query
		lod.rw_lock.read_unlock();
		return false;

	} else {
		// In cache, serve it

		Ref<VoxelBuffer> vb = lod.blocks[position].voxels;

		// Copying is required since the cache has ownership on its data,
		// and the requests wants us to populate the buffer it provides
		out_voxels->copy_format(**vb);
		out_voxels->copy_from(**vb);
		out_voxels->copy_voxel_metadata(**vb);

		lod.rw_lock.read_unlock();
		return true;
	}
}

void VoxelStreamCache::save_voxel_block(Vector3i position, uint8_t lod_index, Ref<VoxelBuffer> voxels) {
	Lod &lod = _cache[lod_index];
	RWLockWrite wlock(lod.rw_lock);
	if (!lod.blocks.has(position)) {
		// Not cached yet, create an entry
		Block b;
		b.position = position;
		b.lod = lod_index;
		b.voxels = voxels;
		b.has_voxels = true;
		lod.blocks.insert(position, b);
		++_count;

	} else {
		// Cached already, overwrite
		lod.blocks[position].voxels = voxels;
		lod.blocks[position].has_voxels = true;
	}
}

bool VoxelStreamCache::load_instance_block(
		Vector3i position, uint8_t lod_index, Ref<VoxelInstanceBlockData> &out_instances) {

	const Lod &lod = _cache[lod_index];
	lod.rw_lock.read_lock();
	if (!lod.blocks.has(position)) {
		// Not in cache, will have to query
		lod.rw_lock.read_unlock();
		return false;

	} else {
		// In cache, serve it

		if (lod.blocks[position].instances == nullptr) {
			out_instances.unref();

		} else {
			// Copying is required since the cache has ownership on its data
			Ref<VoxelInstanceBlockData> new_block_data;
			new_block_data.instance();
			out_instances = new_block_data;
			lod.blocks[position].instances->copy_to(out_instances);
		}

		lod.rw_lock.read_unlock();
		return true;
	}
}

void VoxelStreamCache::save_instance_block(
		Vector3i position, uint8_t lod_index, Ref<VoxelInstanceBlockData> instances) {

	Lod &lod = _cache[lod_index];
	RWLockWrite wlock(lod.rw_lock);
	if (!lod.blocks.has(position)) {
		// Not cached yet, create an entry
		Block b;
		b.position = position;
		b.lod = lod_index;
		b.instances = instances;
		lod.blocks.insert(position, b);
		++_count;

	} else {
		// Cached already, overwrite
		lod.blocks[position].instances = instances;
	}
}

unsigned int VoxelStreamCache::get_indicative_block_count() const {
	return _count;
}
