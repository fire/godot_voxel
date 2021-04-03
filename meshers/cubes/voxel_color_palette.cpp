#include "voxel_color_palette.h"

void VoxelColorPalette::set_color(int index, Color color) {
	ERR_FAIL_INDEX(index, static_cast<int>(_colors.size()));
	_colors[index] = Color8(color);
}

Color VoxelColorPalette::get_color(int index) const {
	ERR_FAIL_INDEX_V(index, static_cast<int>(_colors.size()), Color());
	return _colors[index];
}

void VoxelColorPalette::clear() {
	for (size_t i = 0; i < _colors.size(); ++i) {
		_colors[i] = Color8();
	}
}

PackedInt32Array VoxelColorPalette::_b_get_data() const {
	PackedInt32Array colors;
	colors.resize(_colors.size());
	{
		for (size_t i = 0; i < _colors.size(); ++i) {
			colors.ptrw()[i] = _colors[i].to_u32();
		}
	}
	return colors;
}

void VoxelColorPalette::_b_set_data(PackedInt32Array colors) {
	ERR_FAIL_COND(colors.size() > static_cast<int>(_colors.size()));
	for (int i = 0; i < colors.size(); ++i) {
		_colors[i] = Color8::from_u32(colors.ptr()[i]);
	}
}

void VoxelColorPalette::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_color", "color"), &VoxelColorPalette::set_color);
	ClassDB::bind_method(D_METHOD("get_color"), &VoxelColorPalette::get_color);

	ClassDB::bind_method(D_METHOD("set_data", "d"), &VoxelColorPalette::_b_set_data);
	ClassDB::bind_method(D_METHOD("get_data"), &VoxelColorPalette::_b_get_data);

	ADD_PROPERTY(PropertyInfo(Variant::PACKED_INT32_ARRAY, "data"), "set_data", "get_data");

	BIND_CONSTANT(MAX_COLORS);
}
