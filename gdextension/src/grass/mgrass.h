#ifndef MGRASS
#define MGRASS

#define BUFFER_STRID_FLOAT 12
#define BUFFER_STRID_BYTE 48

#include <mutex>

#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/templates/vset.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/physics_server3d.hpp>
#include <godot_cpp/classes/shape3d.hpp>
#include "mgrass_data.h"
#include "mgrass_lod_setting.h"
#include "../mpixel_region.h"
#include "../mbound.h"
#include <godot_cpp/variant/utility_functions.hpp>

#include "mgrass_chunk.h"

using namespace godot;

class MGrid;

struct MGrassPhysics
{
    RID physic_body;
    MGrassPhysics(RID shape_rid,RID space_rid, Transform3D transform_3d){
        physic_body = PhysicsServer3D::get_singleton()->body_create();
        PhysicsServer3D::get_singleton()->body_set_mode(physic_body,PhysicsServer3D::BODY_MODE_STATIC);
        PhysicsServer3D::get_singleton()->body_set_space(physic_body,space_rid);
        PhysicsServer3D::get_singleton()->body_set_state(physic_body,PhysicsServer3D::BODY_STATE_TRANSFORM,transform_3d);
        PhysicsServer3D::get_singleton()->body_add_shape(physic_body,shape_rid);
    }
    ~MGrassPhysics(){
        PhysicsServer3D::get_singleton()->free_rid(physic_body);
    }
};



class MGrass : public Node3D {
    GDCLASS(MGrass,Node3D);
    private:
    int64_t update_id;
    std::mutex update_mutex;
    uint64_t final_count=0;
    int grass_count_limit=9000000;
    float nav_obstacle_radius=1.0;

    protected:
    static void _bind_methods();

    public:
    bool active = true;
    bool is_grass_init = false;
    RID scenario;
    RID space;
    Ref<MGrassData> grass_data;
    MGrid* grid = nullptr;
    //int grass_in_cell=1;
    uint32_t base_grid_size_in_pixel;
    uint32_t grass_region_pixel_width; // Width or Height both are equal
    uint32_t grass_region_pixel_size; // Total pixel size for each region
    uint32_t region_grid_width;
    uint32_t width;
    uint32_t height;
    MPixelRegion grass_pixel_region;
    MBound grass_bound_limit;
    int lod_count;
    int min_grass_cutoff=1;
    Array lod_settings;
    Array materials;
    Array meshes;
    Vector<Ref<MGrassLodSetting>> settings;
    Ref<MGrassLodSetting> default_lod_setting;
    Vector<RID> material_rids;
    Vector<RID> meshe_rids;
    Vector<PackedFloat32Array*> rand_buffer_pull;
    HashMap<int64_t,MGrassChunk*> grid_to_grass;
    Vector<MGrassChunk*> to_be_visible;
    VSet<int>* dirty_points_id;
    Vector3 shape_offset;
    Ref<Shape3D> shape;
    MBound physics_search_bound;
    MBound last_physics_search_bound;
    HashMap<uint64_t,MGrassPhysics*> physics;
    float collision_radius=64;

    MGrass();
    ~MGrass();
    void init_grass(MGrid* _grid);
    void clear_grass();
    void update_grass();
    void update_dirty_chunks();
    void apply_update_grass();
    void cull_out_of_bound();
    void create_grass_chunk(int grid_index,MGrassChunk* grass_chunk=nullptr);
    void recalculate_grass_config(int max_lod);

    void set_grass_by_pixel(uint32_t px, uint32_t py, bool p_value);
    bool get_grass_by_pixel(uint32_t px, uint32_t py);
    Vector2i get_closest_pixel(Vector3 pos);
    void draw_grass(Vector3 brush_pos,real_t radius,bool add);
    void set_active(bool input);
    bool get_active();
    void set_grass_data(Ref<MGrassData> d);
    Ref<MGrassData> get_grass_data();
    void set_grass_count_limit(int input);
    int get_grass_count_limit();
    //void set_grass_in_cell(int input);
    //int get_grass_in_cell();
    void set_min_grass_cutoff(int input);
    int get_min_grass_cutoff();
    void set_lod_settings(Array input);
    Array get_lod_settings();
    void set_meshes(Array input);
    Array get_meshes();
    void set_materials(Array input);
    Array get_materials();

    int64_t get_count();

    void set_collision_radius(float input);
    float get_collision_radius();
    void set_shape_offset(Vector3 input);
    Vector3 get_shape_offset();
    void set_shape(Ref<Shape3D> input);
    Ref<Shape3D> get_shape();
    void set_nav_obstacle_radius(float input);
    float get_nav_obstacle_radius();
    void update_physics(Vector3 cam_pos);
    void remove_all_physics();
    PackedVector3Array get_physic_positions(Vector3 cam_pos,float radius);


    void _get_property_list(List<PropertyInfo> *p_list) const;
    bool _get(const StringName &p_name, Variant &r_ret) const;
    bool _set(const StringName &p_name, const Variant &p_value);


    godot::Error save_grass_data();

    void test_function();

};
#endif