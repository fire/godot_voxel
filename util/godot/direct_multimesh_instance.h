#ifndef DIRECT_MULTIMESH_INSTANCE_H
#define DIRECT_MULTIMESH_INSTANCE_H

#include "../array_slice.h"

#include <core/templates/rid.h>
#include <scene/resources/multimesh.h>

class World3D;

// Thin wrapper around RenderingServer multimesh instance API
class DirectMultiMeshInstance {
public:
	DirectMultiMeshInstance();
	~DirectMultiMeshInstance();

	void create();
	void destroy();
	bool is_valid() const;
	void set_world(World3D *world);
	void set_multimesh(Ref<MultiMesh> multimesh);
	Ref<MultiMesh> get_multimesh() const;
	void set_transform(Transform world_transform);
	void set_visible(bool visible);
	void set_material_override(Ref<Material> material);

	static Vector<float> make_transform_3d_bulk_array(ArraySlice<const Transform> transforms);

private:
	RID _multimesh_instance;
	Ref<MultiMesh> _multimesh;
};

#endif // DIRECT_MULTIMESH_INSTANCE_H
