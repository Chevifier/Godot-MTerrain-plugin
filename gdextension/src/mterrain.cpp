#include "mterrain.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/world3d.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/reg_ex.hpp>
#include <godot_cpp/classes/reg_ex_match.hpp>

#include "mbrush_manager.h"
#include "navmesh/mnavigation_region_3d.h"
#include "mbrush_layers.h"


void MTerrain::_bind_methods() {
    //ADD_SIGNAL(MethodInfo("finish_updating"));
    //ADD_SIGNAL(MethodInfo("finish_updating_physics"));

    ClassDB::bind_method(D_METHOD("finish_terrain"), &MTerrain::finish_terrain);
    ClassDB::bind_method(D_METHOD("start"), &MTerrain::start);
    ClassDB::bind_method(D_METHOD("create_grid"), &MTerrain::create_grid);
    ClassDB::bind_method(D_METHOD("remove_grid"), &MTerrain::remove_grid);
    ClassDB::bind_method(D_METHOD("restart_grid"), &MTerrain::restart_grid);
    ClassDB::bind_method(D_METHOD("update"), &MTerrain::update);
    ClassDB::bind_method(D_METHOD("finish_update"), &MTerrain::finish_update);
    ClassDB::bind_method(D_METHOD("update_physics"), &MTerrain::update_physics);
    ClassDB::bind_method(D_METHOD("finish_update_physics"), &MTerrain::finish_update_physics);
    ClassDB::bind_method(D_METHOD("get_image_list"), &MTerrain::get_image_list);
    ClassDB::bind_method(D_METHOD("get_image_id", "uniform_name"), &MTerrain::get_image_id);
    ClassDB::bind_method(D_METHOD("save_image","image_index","force_save"), &MTerrain::save_image);
    ClassDB::bind_method(D_METHOD("has_unsave_image"), &MTerrain::has_unsave_image);
    ClassDB::bind_method(D_METHOD("save_all_dirty_images"), &MTerrain::save_all_dirty_images);
    ClassDB::bind_method(D_METHOD("is_finishing_update_chunks"), &MTerrain::is_finish_updating);
    ClassDB::bind_method(D_METHOD("is_finishing_update_physics"), &MTerrain::is_finish_updating_physics);
    ClassDB::bind_method(D_METHOD("get_pixel", "x","y","image_index"), &MTerrain::get_pixel);
    ClassDB::bind_method(D_METHOD("set_pixel", "x","y","color","image_index"), &MTerrain::set_pixel);
    ClassDB::bind_method(D_METHOD("get_height_by_pixel", "x","y"), &MTerrain::get_height_by_pixel);
    ClassDB::bind_method(D_METHOD("set_height_by_pixel", "x","y","value"), &MTerrain::set_height_by_pixel);
    ClassDB::bind_method(D_METHOD("get_closest_height", "world_position"), &MTerrain::get_closest_height);
    ClassDB::bind_method(D_METHOD("get_height", "world_position"), &MTerrain::get_height);
    ClassDB::bind_method(D_METHOD("get_ray_collision_point", "ray_origin","ray_vector","step","max_step"), &MTerrain::get_ray_collision_point);
    
    ClassDB::bind_method(D_METHOD("set_dataDir","dir"), &MTerrain::set_dataDir);
    ClassDB::bind_method(D_METHOD("get_dataDir"), &MTerrain::get_dataDir);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "dataDir"), "set_dataDir", "get_dataDir");
    ClassDB::bind_method(D_METHOD("set_layersDataDir","input"), &MTerrain::set_layersDataDir);
    ClassDB::bind_method(D_METHOD("get_layersDataDir"), &MTerrain::get_layersDataDir);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "layersDataDir"), "set_layersDataDir","get_layersDataDir");

    ClassDB::bind_method(D_METHOD("set_save_generated_normals","value"), &MTerrain::set_save_generated_normals);
    ClassDB::bind_method(D_METHOD("get_save_generated_normals"), &MTerrain::get_save_generated_normals);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "save_generated_normals"), "set_save_generated_normals", "get_save_generated_normals");

    ClassDB::bind_method(D_METHOD("set_grid_create","val"), &MTerrain::set_create_grid);
    ClassDB::bind_method(D_METHOD("get_create_grid"), &MTerrain::get_create_grid);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "create_grid"), "set_grid_create", "get_create_grid");
    ClassDB::bind_method(D_METHOD("get_material"), &MTerrain::get_material);
    ClassDB::bind_method(D_METHOD("set_material", "terrain_material"), &MTerrain::set_material);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "material", PROPERTY_HINT_RESOURCE_TYPE, "ShaderMaterial"), "set_material", "get_material");
    
    ClassDB::bind_method(D_METHOD("set_heightmap_layers", "input"), &MTerrain::set_heightmap_layers);
    ClassDB::bind_method(D_METHOD("get_heightmap_layers"), &MTerrain::get_heightmap_layers);
    ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "heightmap_layers"), "set_heightmap_layers","get_heightmap_layers");

    ClassDB::bind_method(D_METHOD("set_update_chunks_interval","interval"), &MTerrain::set_update_chunks_interval);
    ClassDB::bind_method(D_METHOD("get_update_chunks_interval"), &MTerrain::get_update_chunks_interval);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "update_chunks_interval"), "set_update_chunks_interval", "get_update_chunks_interval");
    
    ClassDB::bind_method(D_METHOD("set_distance_update_threshold","input"), &MTerrain::set_distance_update_threshold);
    ClassDB::bind_method(D_METHOD("get_distance_update_threshold"), &MTerrain::get_distance_update_threshold);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT,"distance_update_threshold"),"set_distance_update_threshold","get_distance_update_threshold");

    ClassDB::bind_method(D_METHOD("set_update_chunks_loop", "val"), &MTerrain::set_update_chunks_loop);
    ClassDB::bind_method(D_METHOD("get_update_chunks_loop"), &MTerrain::get_update_chunks_loop);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "update_chunks_loop"), "set_update_chunks_loop", "get_update_chunks_loop");

    ClassDB::bind_method(D_METHOD("set_update_physics_interval", "val"), &MTerrain::set_update_physics_interval);
    ClassDB::bind_method(D_METHOD("get_update_physics_interval"), &MTerrain::get_update_physics_interval);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "update_physics_interval"), "set_update_physics_interval", "get_update_physics_interval");

    ClassDB::bind_method(D_METHOD("set_update_physics_loop", "val"), &MTerrain::set_update_physics_loop);
    ClassDB::bind_method(D_METHOD("get_update_physics_loop"), &MTerrain::get_update_physics_loop);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "update_physics_loop"), "set_update_physics_loop", "get_update_physics_loop");

    ClassDB::bind_method(D_METHOD("set_physics_update_limit", "val"), &MTerrain::set_physics_update_limit);
    ClassDB::bind_method(D_METHOD("get_physics_update_limit"), &MTerrain::get_physics_update_limit);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "physics_update_limit"), "set_physics_update_limit", "get_physics_update_limit");

    ClassDB::bind_method(D_METHOD("get_terrain_size"), &MTerrain::get_terrain_size);
    ClassDB::bind_method(D_METHOD("set_terrain_size", "size"), &MTerrain::set_terrain_size);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I,"terrain_size"), "set_terrain_size", "get_terrain_size");
    ClassDB::bind_method(D_METHOD("set_offset", "offset"), &MTerrain::set_offset);
    ClassDB::bind_method(D_METHOD("get_offset"), &MTerrain::get_offset);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "offset"), "set_offset", "get_offset");

    ClassDB::bind_method(D_METHOD("set_region_size", "region_size"), &MTerrain::set_region_size);
    ClassDB::bind_method(D_METHOD("get_region_size"), &MTerrain::get_region_size);
    ADD_PROPERTY(PropertyInfo(Variant::INT,"region_size"), "set_region_size", "get_region_size");
    
    
    ClassDB::bind_method(D_METHOD("set_max_range", "max_range"), &MTerrain::set_max_range);
    ClassDB::bind_method(D_METHOD("get_max_range"), &MTerrain::get_max_range);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "max_range"), "set_max_range", "get_max_range");
    ClassDB::bind_method(D_METHOD("set_custom_camera", "camera"), &MTerrain::set_custom_camera);
    ClassDB::bind_method(D_METHOD("set_editor_camera", "camera"), &MTerrain::set_editor_camera);

    
    ClassDB::bind_method(D_METHOD("set_min_size","index"), &MTerrain::set_min_size);
    ClassDB::bind_method(D_METHOD("get_min_size"), &MTerrain::get_min_size);
    ADD_PROPERTY(PropertyInfo(Variant::INT,"min_size",PROPERTY_HINT_ENUM, M_SIZE_LIST_STRING), "set_min_size", "get_min_size");

    ClassDB::bind_method(D_METHOD("set_max_size","index"), &MTerrain::set_max_size);
    ClassDB::bind_method(D_METHOD("get_max_size"), &MTerrain::get_max_size);
    ADD_PROPERTY(PropertyInfo(Variant::INT,"max_size",PROPERTY_HINT_ENUM, M_SIZE_LIST_STRING), "set_max_size", "get_max_size");
    
    ClassDB::bind_method(D_METHOD("set_min_h_scale","index"), &MTerrain::set_min_h_scale);
    ClassDB::bind_method(D_METHOD("get_min_h_scale"), &MTerrain::get_min_h_scale);
    ADD_PROPERTY(PropertyInfo(Variant::INT,"min_h_scale",PROPERTY_HINT_ENUM, M_H_SCALE_LIST_STRING), "set_min_h_scale", "get_min_h_scale");

    ClassDB::bind_method(D_METHOD("set_max_h_scale","index"), &MTerrain::set_max_h_scale);
    ClassDB::bind_method(D_METHOD("get_max_h_scale"), &MTerrain::get_max_h_scale);
    ADD_PROPERTY(PropertyInfo(Variant::INT,"max_h_scale",PROPERTY_HINT_ENUM, M_H_SCALE_LIST_STRING), "set_max_h_scale", "get_max_h_scale");

    ClassDB::bind_method(D_METHOD("set_size_info", "size_info"), &MTerrain::set_size_info);
    ClassDB::bind_method(D_METHOD("get_size_info"), &MTerrain::get_size_info);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "size_info",PROPERTY_HINT_NONE,"",PROPERTY_USAGE_STORAGE), "set_size_info", "get_size_info");

    ClassDB::bind_method(D_METHOD("set_lod_distance", "lod_distance"), &MTerrain::set_lod_distance);
    ClassDB::bind_method(D_METHOD("get_lod_distance"), &MTerrain::get_lod_distance);
    ADD_PROPERTY(PropertyInfo(Variant::PACKED_INT32_ARRAY, "lod_distance",PROPERTY_HINT_NONE,"", PROPERTY_USAGE_STORAGE),"set_lod_distance","get_lod_distance");

    ClassDB::bind_method(D_METHOD("get_pixel_world_pos", "x","y"), &MTerrain::get_pixel_world_pos);
    ClassDB::bind_method(D_METHOD("get_closest_pixel", "world_pos"), &MTerrain::get_closest_pixel);
    ClassDB::bind_method(D_METHOD("set_brush_manager", "brush_manager"), &MTerrain::set_brush_manager);
    ClassDB::bind_method(D_METHOD("draw_height", "brush_pos","radius","brush_id"), &MTerrain::draw_height);
    ClassDB::bind_method(D_METHOD("draw_color","brush_pos","radius","brush_id","index"),&MTerrain::draw_color);

    ClassDB::bind_method(D_METHOD("set_active_layer_by_name","layer_name"), &MTerrain::set_active_layer_by_name);
    ClassDB::bind_method(D_METHOD("add_heightmap_layer","layer_name"), &MTerrain::add_heightmap_layer);
    ClassDB::bind_method(D_METHOD("merge_heightmap_layer"), &MTerrain::merge_heightmap_layer);
    ClassDB::bind_method(D_METHOD("remove_heightmap_layer"), &MTerrain::remove_heightmap_layer);
    ClassDB::bind_method(D_METHOD("toggle_heightmap_layer_visibile"), &MTerrain::toggle_heightmap_layer_visibile);
    ClassDB::bind_method(D_METHOD("get_layer_visibility","input"), &MTerrain::get_layer_visibility);

    ClassDB::bind_method(D_METHOD("update_grass_list"), &MTerrain::update_grass_list);
    ClassDB::bind_method(D_METHOD("terrain_child_changed"), &MTerrain::terrain_child_changed);
    ClassDB::bind_method(D_METHOD("get_region_grid_size"), &MTerrain::get_region_grid_size);
    ClassDB::bind_method(D_METHOD("get_base_size"), &MTerrain::get_base_size);
    ClassDB::bind_method(D_METHOD("get_h_scale"), &MTerrain::get_h_scale);

    ClassDB::bind_method(D_METHOD("set_brush_layers","input"), &MTerrain::set_brush_layers);
    ClassDB::bind_method(D_METHOD("get_brush_layers"), &MTerrain::get_brush_layers);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY,"brush_layers",PROPERTY_HINT_NONE,"",PROPERTY_USAGE_STORAGE),"set_brush_layers","get_brush_layers");
    ClassDB::bind_method(D_METHOD("set_brush_layers_num","input"), &MTerrain::set_brush_layers_num);
    ClassDB::bind_method(D_METHOD("get_brush_layers_num"), &MTerrain::get_brush_layers_num);
    ADD_PROPERTY(PropertyInfo(Variant::INT,"brush_layers_groups_num",PROPERTY_HINT_NONE,"",PROPERTY_USAGE_NONE),"set_brush_layers_num","get_brush_layers_num");
    ClassDB::bind_method(D_METHOD("get_layers_info"), &MTerrain::get_layers_info);
    ClassDB::bind_method(D_METHOD("set_color_layer","index","group_index","brush_name"), &MTerrain::set_color_layer);
    ClassDB::bind_method(D_METHOD("test_function"), &MTerrain::test_function);
}

MTerrain::MTerrain() {
    lod_distance.append(3);
    lod_distance.append(6);
    lod_distance.append(12);
    lod_distance.append(16);
    lod_distance.append(24);
    connect("tree_exiting", Callable(this, "finish_terrain"));
    recalculate_terrain_config(true);
    grid = memnew(MGrid);
    update_chunks_timer = memnew(Timer);
    update_chunks_timer->set_wait_time(update_chunks_interval);
    update_chunks_timer->set_one_shot(true);
    add_child(update_chunks_timer);
    update_chunks_timer->connect("timeout", Callable(this, "finish_update"));

    update_physics_timer = memnew(Timer);
    update_physics_timer->set_wait_time(update_physics_interval);
    update_physics_timer->set_one_shot(true);
    add_child(update_physics_timer);
    update_physics_timer->connect("timeout", Callable(this, "finish_update_physics"));

    // Grass List update conditions
    connect("ready",Callable(this,"update_grass_list"));
    connect("child_exiting_tree",Callable(this,"terrain_child_changed"));
    connect("child_entered_tree",Callable(this,"terrain_child_changed"));
}

MTerrain::~MTerrain() {
    memdelete(grid);
}


void MTerrain::finish_terrain() {
    if(update_thread_chunks.valid()){
        update_thread_chunks.wait();
    }
}

void MTerrain::start() {
    create_grid();
}

void MTerrain::create_grid(){
    _chunks = memnew(MChunks);
    _chunks->create_chunks(size_list[min_size_index],size_list[max_size_index],h_scale_list[min_h_scale_index],h_scale_list[max_h_scale_index],size_info);
    grid->set_scenario(get_world_3d()->get_scenario());
    grid->space = get_world_3d()->get_space();
    grid->offset = offset;
    grid->dataDir = dataDir;
    grid->layersDataDir = layersDataDir;
    grid->region_size = region_size;
    grid->heightmap_layers.push_back("background");
    grid->heightmap_layers_visibility.push_back(true);
    grid->heightmap_layers.append_array(heightmap_layers);
    if(material.is_valid()){
        grid->set_material(material);
    }
    grid->lod_distance = lod_distance;
    grid->create(terrain_size.x,terrain_size.y,_chunks);
    get_cam_pos();
    update_uniforms();
    grid->update_regions_uniforms(uniforms);
    grid->update_chunks(cam_pos);
    grid->apply_update_chunks();
    grid->update_physics(cam_pos);
    last_update_pos = cam_pos;
    // Grass Part
    update_grass_list();
    for(int i=0;i<grass_list.size();i++){
        grass_list[i]->init_grass(grid);
        if(grass_list[i]->is_grass_init){
            confirm_grass_list.push_back(grass_list[i]);
            if(grass_list[i]->shape.is_valid()){
                confirm_grass_col_list.push_back(grass_list[i]);
                grass_list[i]->update_physics(cam_pos);
            }
        }
    }

    for(int i=0;i<get_child_count();i++){
        MNavigationRegion3D*  mnav= Object::cast_to<MNavigationRegion3D>(get_child(i));
        if(mnav){
            mnav->init(this,grid);
            if(mnav->is_nav_init && Engine::get_singleton()->is_editor_hint() && mnav->has_data()){
                confirm_nav.push_back(mnav);
                mnav->update_npoints();
                mnav->apply_update_npoints();
            }
        }
    }
    total_update_count = confirm_grass_list.size() + confirm_nav.size();
    if(update_physics_loop){
        update_physics();
    }
    if(update_chunks_loop){
        update();
    }
    if(!grid->has_normals && save_generated_normals){
        int normals_index = get_image_id("normals");
        UtilityFunctions::print("Saving normals");
        save_image(normals_index, true);
    }
}

void MTerrain::remove_grid(){
    update_chunks_timer->stop();
    update_physics_timer->stop();
    if(update_thread_chunks.valid()){
        update_thread_chunks.wait();
        finish_updating = true;
    }
    if(update_thread_physics.valid()){
        update_thread_physics.wait();
        finish_updating_physics = true;
    }
    grid->clear();
    for(int i=0;i<confirm_grass_list.size();i++){
        confirm_grass_list[i]->clear_grass();
    }
    confirm_grass_list.clear();
    confirm_grass_col_list.clear();
    for(int i=0;i<get_child_count();i++){
        MNavigationRegion3D*  mnav= Object::cast_to<MNavigationRegion3D>(get_child(i));
        if(mnav){
            mnav->clear();
        }
    }
    confirm_nav.clear();
}

void MTerrain::restart_grid(){
    remove_grid();
    create_grid();
}

void MTerrain::update() {
    ERR_FAIL_COND(!finish_updating);
    ERR_FAIL_COND(!grid->is_created());
    get_cam_pos();
    finish_updating = false;
    // In case -1 is Terrain grid update turn
    if(update_stage==-1){
        last_update_pos = cam_pos;
        update_thread_chunks = std::async(std::launch::async, &MGrid::update_chunks, grid, cam_pos);
        
    }
    else if(update_stage>=0){
        if(update_stage>=confirm_grass_list.size()){
            int index = update_stage - confirm_grass_list.size();
            update_thread_chunks = std::async(std::launch::async, &MNavigationRegion3D::update_npoints, confirm_nav[index]);
        } else {
            update_thread_chunks = std::async(std::launch::async, &MGrass::update_grass, confirm_grass_list[update_stage]);
        }
    }
    update_chunks_timer->start();
}

void MTerrain::finish_update() {
    //UtilityFunctions::print("Finish update stage ", update_stage);
    if(update_stage == -2){
        get_cam_pos();
        float dis = last_update_pos.distance_to(cam_pos);
        if(dis>distance_update_threshold){
            update_stage = -1;
            call_deferred("update");
            return;
        } else {
            update_chunks_timer->start();
        }
    }
    std::future_status status = update_thread_chunks.wait_for(std::chrono::microseconds(1));
    if(status == std::future_status::ready){
        finish_updating = true;
        if(update_stage==-1){
            grid->apply_update_chunks();
            if(confirm_grass_list.size()!=0){
                update_stage++;
                call_deferred("update");
            } else {
                update_stage = -2;
                finish_update();
            }
        }
        else if(update_stage>=0){
            if(update_stage>=confirm_grass_list.size()){
                int index = update_stage - confirm_grass_list.size();
                confirm_nav[index]->apply_update_npoints();
            } else {
                confirm_grass_list[update_stage]->apply_update_grass();
            }
            update_stage++;
            if(update_stage>=total_update_count){
                update_stage = -2;
                finish_update();
            } else {
                call_deferred("update");
            }
        }
    } else {
        update_chunks_timer->start();
    }
}

void MTerrain::update_physics(){
    ERR_FAIL_COND(!finish_updating_physics);
    ERR_FAIL_COND(!grid->is_created());
    get_cam_pos();
    finish_updating_physics = false;
    if(update_stage_physics==-1){
        update_thread_physics = std::async(std::launch::async, &MGrid::update_physics, grid, cam_pos);
    } else if(update_stage_physics>=0){
        update_thread_physics = std::async(std::launch::async, &MGrass::update_physics,confirm_grass_col_list[update_stage_physics], cam_pos);
    }
    update_physics_timer->start();
}

void MTerrain::finish_update_physics(){
    std::future_status status = update_thread_physics.wait_for(std::chrono::microseconds(1));
    if(status == std::future_status::ready){
        finish_updating_physics = true;
        update_stage_physics++;
        if(update_stage_physics>=confirm_grass_col_list.size()){
            update_stage_physics = -1;
        }
        if(update_physics_loop){
            call_deferred("update_physics");
        }
    } else {
        update_physics_timer->start();
    }
}

bool MTerrain::is_finish_updating(){
    return finish_updating;
}
bool MTerrain::is_finish_updating_physics(){
    return finish_updating_physics;
}

Array MTerrain::get_image_list(){
    return grid->uniforms_id.keys();
}

int MTerrain::get_image_id(String uniform_name){
    if(!grid->is_created()) return -1;
    if(!grid->uniforms_id.has(uniform_name)) return -1;
    return grid->uniforms_id[uniform_name];
}

void MTerrain::save_image(int image_index, bool force_save) {
    ERR_FAIL_COND(!grid->is_created());
    ERR_FAIL_COND(image_index>grid->uniforms_id.keys().size());
    grid->save_image(image_index,force_save);
}

bool MTerrain::has_unsave_image(){
    return grid->has_unsave_image();
}

void MTerrain::save_all_dirty_images(){
    if(grid->is_created()){
        grid->save_all_dirty_images();
    }
}

Color MTerrain::get_pixel(const uint32_t& x,const uint32_t& y, const int32_t& index){
    return grid->get_pixel(x,y,index);
}
void MTerrain::set_pixel(const uint32_t& x,const uint32_t& y,const Color& col,const int32_t& index){
    grid->set_pixel(x,y,col,index);
}
real_t MTerrain::get_height_by_pixel(const uint32_t& x,const uint32_t& y){
    return grid->get_height_by_pixel(x,y);
}
void MTerrain::set_height_by_pixel(const uint32_t& x,const uint32_t& y,const real_t& value){
    grid->set_height_by_pixel(x,y,value);
}

void MTerrain::get_cam_pos() {
    if(custom_camera != nullptr){
        cam_pos = custom_camera->get_global_position();
        return;
    }
    if(editor_camera !=nullptr){
        cam_pos = editor_camera->get_global_position();
        return;
    }
    Viewport* v = get_viewport();
    Camera3D* camera = v->get_camera_3d();
    ERR_FAIL_COND_EDMSG(camera==nullptr, "No camera is detected, If you are in editor activate MTerrain plugin");
    cam_pos = camera->get_global_position();
}

void MTerrain::set_dataDir(String input) {
    dataDir = input;
}

String MTerrain::get_dataDir() {
    return dataDir;
}

void MTerrain::set_layersDataDir(String input){
    layersDataDir = input;
}
String MTerrain::get_layersDataDir(){
    return layersDataDir;
}

void MTerrain::set_create_grid(bool input){
    if(!is_inside_tree()){
        return;
    }
    if(grid->is_created() && !input){
        remove_grid();
        return;
    }
    if(!grid->is_created() && input){
        create_grid();
        return;
    }
}

bool MTerrain::get_create_grid(){
    return grid->is_created();
}


Ref<ShaderMaterial> MTerrain::get_material(){
    return material;
}

void MTerrain::set_material(Ref<ShaderMaterial> m){
    material = m;
}

void MTerrain::set_save_generated_normals(bool input){
    grid->save_generated_normals = input;
    save_generated_normals = input;
}

bool MTerrain::get_save_generated_normals(){
    return save_generated_normals;
}

float MTerrain::get_update_chunks_interval(){
    return update_chunks_interval;
}
void MTerrain::set_update_chunks_interval(float input){
    update_chunks_interval = input;
    if(input < 0.001){
        update_chunks_interval = 0.001;
    }
    update_chunks_timer->set_wait_time(update_chunks_interval);
}

float MTerrain::get_distance_update_threshold(){
    return distance_update_threshold;
}
void MTerrain::set_distance_update_threshold(float input){
    distance_update_threshold = input;
}

void MTerrain::set_update_chunks_loop(bool input) {
    update_chunks_loop = input;
    if(update_chunks_loop && finish_updating){
        update();
    }
}

bool MTerrain::get_update_chunks_loop() {
    return update_chunks_loop;
}

float MTerrain::get_update_physics_interval(){
    return update_physics_interval;
}
void MTerrain::set_update_physics_interval(float input){
    update_physics_interval = input;
    if(input < 0.001){
        update_physics_interval = 0.001;
    }
    update_physics_timer->set_wait_time(update_physics_interval);
}
bool MTerrain::get_update_physics_loop(){
    return update_physics_loop;
}
void MTerrain::set_update_physics_loop(bool input){
    update_physics_loop = input;
    if(update_physics_loop && finish_updating_physics){
        update_physics();
    }
}

void MTerrain::set_physics_update_limit(int32_t input){
    if(input<0){
        grid->physics_update_limit = 0;
    } else {
        grid->physics_update_limit = input;
    }
}
int32_t MTerrain::get_physics_update_limit(){
    return grid->physics_update_limit;
}

Vector2i MTerrain::get_terrain_size(){
    return terrain_size;
}

void MTerrain::set_terrain_size(Vector2i size){
    ERR_FAIL_COND_EDMSG(size.x < 1 || size.y < 1,"Terrain size can not be zero");
    if(size == terrain_size){
        return;
    }
    terrain_size = size;
}


void MTerrain::set_max_range(int32_t input) {
    ERR_FAIL_COND_EDMSG(input<1,"Max range can not be less than one");
    max_range = input;
    grid->max_range = input;
}

int32_t MTerrain::get_max_range() {
    return max_range;
}

void MTerrain::set_editor_camera(Node3D* camera_node){
    editor_camera = camera_node;
}
void MTerrain::set_custom_camera(Node3D* camera_node){
    custom_camera = camera_node;
}

void MTerrain::set_offset(Vector3 input){
    input.y = 0;
    offset = input;
}

Vector3 MTerrain::get_offset(){
    return offset;
}


void MTerrain::set_region_size(int32_t input) {
    ERR_FAIL_COND_EDMSG(input<4,"Region size can not be smaller than 4");
    region_size = input;
}

int32_t MTerrain::get_region_size() {
    return region_size;
}

void MTerrain::update_uniforms() {
    uniforms.clear();
    ERR_FAIL_COND(!material.is_valid());
    ERR_FAIL_COND(!material->get_shader().is_valid());
    Array uniform_list = material->get_shader()->get_shader_uniform_list();
    Ref<RegEx> reg_compression;
    reg_compression.instantiate();
    reg_compression->compile("mterrain_(\\d+)");
    Ref<RegEx> reg_name;
    reg_name.instantiate();
    reg_name->compile("mterrain_\\d*_?(.*)");
    for(int i=0; i<uniform_list.size();i++){
        Dictionary u = uniform_list[i];
        String u_name = u["name"];
        int u_type = u["type"];
        if(u_type==24 && u_name.begins_with("mterrain_")){
            int compression = -1;
            String name;
            Ref<RegExMatch> res = reg_compression->search(u_name);
            if(res.is_valid()){
                PackedStringArray finds = res->get_strings();
                compression = finds[1].to_int();
            }
            res = reg_name->search(u_name);
            if(res.is_valid()){
                PackedStringArray finds = res->get_strings();
                name = finds[1];
            }
            Dictionary uniform_info;
            uniform_info["uniform_name"] = u_name;
            uniform_info["name"] = name;
            uniform_info["compression"] = compression;
            uniforms.append(uniform_info);
        }
    }
}

void MTerrain::recalculate_terrain_config(const bool& force_calculate) {
    if(!is_inside_tree() && !force_calculate){
        return;
    }
    // Calculating max size
    max_size = (int8_t)(max_size_index - min_size_index);
    // Calculating max lod
    max_lod = (int8_t)(max_h_scale_index - min_h_scale_index);
    if(h_scale_list[max_h_scale_index] > size_list[min_size_index]){
        size_info.clear();
        notify_property_list_changed();
        ERR_FAIL_COND("min size is smaller than max h scale");
    }
    size_info.clear();
    size_info.resize(max_size+1);
    for(int i=0;i<size_info.size();i++){
        Array lod;
        lod.resize(max_lod+1);
        for(int j=0;j<lod.size();j++){
            if(j==lod.size()-1){
                lod[j] = true;
                continue;
            }
            lod[j] = i <=j;
        }
        size_info[i] = lod;
    }

    /// Calculating LOD distance
    lod_distance.resize(max_lod);
    int32_t ll = lod_distance[0];
    for(int i=1;i<lod_distance.size();i++){
        if(lod_distance[i] <= ll){
            lod_distance[i] = ll + 1; 
        }
        ll = lod_distance[i];
    }
    notify_property_list_changed();
    for(int i=0;i<grass_list.size();i++){
        grass_list[i]->recalculate_grass_config(max_lod);
    }
}

int MTerrain::get_min_size() {
    return min_size_index;
}

void MTerrain::set_min_size(int index) {
    if(index >= max_size_index){
        return;
    }
    min_size_index = index;
    recalculate_terrain_config(false);
}

int MTerrain::get_max_size() {
    return max_size_index;
}

void MTerrain::set_max_size(int index) {
    if(index <= min_size_index){
        return;
    }
    max_size_index = index;
    recalculate_terrain_config(false);
}

void MTerrain::set_min_h_scale(int index) {
    if(index >= max_h_scale_index){
        return;
    }
    min_h_scale_index = index;
    recalculate_terrain_config(false);
}

int MTerrain::get_min_h_scale() {
    return min_h_scale_index;
}

void MTerrain::set_max_h_scale(int index) {
    if(index <= min_h_scale_index){
        return;
    }
    max_h_scale_index = index;
    recalculate_terrain_config(false);
}

int MTerrain::get_max_h_scale(){
    return max_h_scale_index;
}


void MTerrain::set_size_info(const Array& arr) {
    size_info = arr;
}
Array MTerrain::get_size_info() {
    return size_info;
}

void MTerrain::set_lod_distance(const PackedInt32Array& input){
    lod_distance = input;
}

PackedInt32Array MTerrain::get_lod_distance() {
    return lod_distance;
}

void MTerrain::_get_property_list(List<PropertyInfo> *p_list) const {
    //Adding lod distance property
    PropertyInfo sub_lod(Variant::INT, "LOD distance", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_SUBGROUP);
    p_list->push_back(sub_lod);
    for(int i=0; i<lod_distance.size();i++){
        PropertyInfo p(Variant::INT,"M_LOD_"+itos(i),PROPERTY_HINT_NONE,"",PROPERTY_USAGE_EDITOR);
        p_list->push_back(p);
    }
    //Adding size info property
    for(int size=0;size<size_info.size();size++){
        Array lod_info = size_info[size];
        PropertyInfo sub(Variant::INT, "Size "+itos(size_list[size+min_size_index]), PROPERTY_HINT_NONE, "", PROPERTY_USAGE_SUBGROUP);
        p_list->push_back(sub);
        for(int lod=0;lod<lod_info.size();lod++){
            PropertyInfo p(Variant::BOOL,"SIZE_"+itos(size)+"_LOD_"+itos(lod)+"_HSCALE_"+itos(h_scale_list[lod+min_h_scale_index]),PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR);
            p_list->push_back(p);
        }
    }
    // Brush layers property
    PropertyInfo ccat(Variant::INT, "Brush Layers", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_CATEGORY);
    p_list->push_back(ccat);
    PropertyInfo bln(Variant::INT, "brush_layers_groups_num", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR);
    p_list->push_back(bln);
    for(int i=0;i<brush_layers.size();i++){
        PropertyInfo brl(Variant::OBJECT, "MBL_"+itos(i), PROPERTY_HINT_RESOURCE_TYPE, "MBrushLayers", PROPERTY_USAGE_EDITOR);
        p_list->push_back(brl);
    }
}

real_t MTerrain::get_closest_height(const Vector3& pos) {
    return grid->get_closest_height(pos);
}
real_t MTerrain::get_height(const Vector3& pos){
    return grid->get_height(pos);
}

Ref<MCollision> MTerrain::get_ray_collision_point(Vector3 ray_origin,Vector3 ray_vector,real_t step,int max_step){
    if(!grid->is_created()){
        Ref<MCollision> col;
        col.instantiate();
        return col;
    }
    return grid->get_ray_collision_point(ray_origin,ray_vector,step,max_step);
}

bool MTerrain::_get(const StringName &p_name, Variant &r_ret) const {
    if(p_name.begins_with("SIZE_")){
        PackedStringArray parts = p_name.split("_");
        if(parts.size() != 6){
            return false;
        }
        int64_t size = parts[1].to_int();
        int64_t lod = parts[3].to_int();
        Array lod_info = size_info[size];
        r_ret = lod_info[lod];
        return true;
    }
    if(p_name.begins_with("M_LOD_")){
        int64_t index = p_name.get_slicec('_',2).to_int();
        r_ret = (float)lod_distance[index];
        return true;
    }
    if(p_name.begins_with("MBL_")){
        int64_t index = p_name.get_slicec('_',1).to_int();
        r_ret = brush_layers[index];
        return true;
    }
    return false;
}


bool MTerrain::_set(const StringName &p_name, const Variant &p_value) {
    if(p_name.begins_with("SIZE_")){
        PackedStringArray parts = p_name.split("_");
        if(parts.size() != 6){
            return false;
        }
        int64_t size = parts[1].to_int();
        if(size==0){
            return false;
        }
        int64_t lod = parts[3].to_int();
        Array lod_info = size_info[size];
        lod_info[lod] = p_value;
        size_info[size] = lod_info;
        return true;
    }
    if(p_name.begins_with("M_LOD_")){
        int64_t index = p_name.get_slicec('_',2).to_int();
        int32_t val = p_value;
        if(val<0){
            return false;
        }
        lod_distance[index] = val;
        return true;
    }
    if(p_name.begins_with("MBL_")){
        int64_t index = p_name.get_slicec('_',1).to_int();
        brush_layers[index] = p_value;
        return true;
    }
    return false;
}

Vector2i MTerrain::get_closest_pixel(const Vector3& world_pos){
    return grid->get_closest_pixel(world_pos);
}
void MTerrain::set_brush_manager(Object* input){
    ERR_FAIL_COND(!input->is_class("MBrushManager"));
    MBrushManager* brush_manager = Object::cast_to<MBrushManager>(input);
    grid->set_brush_manager(brush_manager);
}
void MTerrain::draw_height(Vector3 brush_pos,real_t radius,int brush_id){
    if(!grid->is_created()) return;
    grid->draw_height(brush_pos,radius,brush_id);
}

void MTerrain::draw_color(Vector3 brush_pos,real_t radius,String brush_name, String uniform_name){
    if(!grid->is_created()) return;
    MColorBrush* brush = grid->get_brush_manager()->get_color_brush_by_name(brush_name);
    ERR_FAIL_COND(!brush);
    int id = get_image_id(uniform_name);
    ERR_FAIL_COND(id==-1);
    grid->draw_color(brush_pos,radius,brush,id);
}

Vector3 MTerrain::get_pixel_world_pos(uint32_t x,uint32_t y){
    return grid->get_pixel_world_pos(x,y);
}



void MTerrain::set_heightmap_layers(PackedStringArray input){
    heightmap_layers = input;
}
PackedStringArray MTerrain::get_heightmap_layers(){
    return heightmap_layers;
}

void MTerrain::set_active_layer_by_name(String lname){
    ERR_FAIL_COND(!grid->is_created());
    // Zero is always background layer
    if(lname=="background"){
        grid->set_active_layer(0);
    }
    int index = grid->heightmap_layers.find(lname);
    if(index>=0) {
        grid->set_active_layer(index);
        active_layer_name = lname;
    }
}

bool MTerrain::get_layer_visibility(String lname){
    ERR_FAIL_COND_V(!grid->is_created(),false);
    // Zero is always background layer
    if(lname=="background"){
        return true;
    }
    int index = grid->heightmap_layers.find(lname);
    if(index>0) {
        return grid->heightmap_layers_visibility[index];
    }
    return false;
}

void MTerrain::add_heightmap_layer(String lname){
    ERR_FAIL_COND_EDMSG(heightmap_layers.find(lname)!=-1,"Layer name must be unique");
    heightmap_layers.push_back(lname);
    ERR_FAIL_COND(!grid->is_created());
    grid->heightmap_layers.push_back(lname);
    grid->add_heightmap_layer(lname);
    UtilityFunctions::print("Adding new layers ");
    UtilityFunctions::print(grid->heightmap_layers);
}

void MTerrain::merge_heightmap_layer(){
    ERR_FAIL_COND(!grid->is_created());
    ERR_FAIL_COND_EDMSG(grid->active_heightmap_layer == 0,"Can't merge background layer");
    grid->merge_heightmap_layer();
    int index = heightmap_layers.find(active_layer_name);
    if(index>=0){
        heightmap_layers.remove_at(index);
    }
}

void MTerrain::remove_heightmap_layer(){
    ERR_FAIL_COND(!grid->is_created());
    ERR_FAIL_COND_EDMSG(active_layer_name=="background", "Can not remove background layer");
    grid->remove_heightmap_layer();
    int index = heightmap_layers.find(active_layer_name);
    if(index>=0){
        heightmap_layers.remove_at(index);
    }
}

void MTerrain::toggle_heightmap_layer_visibile(){
    ERR_FAIL_COND(!grid->is_created());
    ERR_FAIL_COND_EDMSG(active_layer_name=="background", "Can not Hide background layer");
    grid->toggle_heightmap_layer_visibile();
}

void MTerrain::terrain_child_changed(Node* n){
    if(!is_ready){
        return;
    }
    if(n->is_class("MGrass")){
        MGrass* g = Object::cast_to<MGrass>(n);
        if(grass_list.find(g)==-1){
            update_grass_list();
        }
    }
}

void MTerrain::update_grass_list(){
    // Grass part
    grass_list.clear(); // First make sure grass list is clear
    int child_count = get_child_count();
    for(int i=0;i<child_count;i++){
        if("MGrass" == get_child(i)->get_class()){
            MGrass* g = Object::cast_to<MGrass>(get_child(i));
            grass_list.push_back(g);
            g->recalculate_grass_config(max_h_scale_index - min_h_scale_index);
        }
    }
    is_ready = true;
    /// Finish initlaztion start update
}

Vector2i MTerrain::get_region_grid_size(){
    return Vector2i(grid->get_region_grid_size().x,grid->get_region_grid_size().z);
}

int32_t MTerrain::get_base_size(){
    return size_list[min_size_index];
}
float MTerrain::get_h_scale(){
    return h_scale_list[min_h_scale_index];
}

#include <godot_cpp/classes/file_access.hpp>

struct Foo
{
    String name = "foo zad";
    int dis;
    friend bool operator<(const Foo& c1,Foo& c2){
        return c1.dis<c2.dis;
    }
    friend bool operator>(const Foo& c1,Foo& c2){
        return c1.dis>c2.dis;
    }
};


void MTerrain::set_brush_layers(Array input){
    brush_layers = input;
}
Array MTerrain::get_brush_layers(){
    return brush_layers;
}
void MTerrain::set_brush_layers_num(int input){
    ERR_FAIL_COND(input<0);
    brush_layers.resize(input);
    notify_property_list_changed();
}
int MTerrain::get_brush_layers_num(){
    return brush_layers.size();
}

Array MTerrain::get_layers_info(){
    Array info;
    for(int i=0;i<brush_layers.size();i++){
        Ref<MBrushLayers> layers = brush_layers[i];
        if(layers.is_valid()){
            Dictionary dic;
            dic["title"]=layers->layers_title;
            dic["index"]=i;
            dic["uniform"]=layers->uniform_name;
            dic["brush_name"]=layers->brush_name;
            dic["info"]=layers->get_layers_info();
            info.push_back(dic);
        }
    }
    return info;
}

void MTerrain::set_color_layer(int index,int group_index,String brush_name){
    ERR_FAIL_COND(!grid->is_created());
    ERR_FAIL_COND(!grid->get_brush_manager());
    MColorBrush* brush = grid->get_brush_manager()->get_color_brush_by_name(brush_name);
    ERR_FAIL_COND(!brush);
    Ref<MBrushLayers> bl = brush_layers[group_index];
    bl->set_layer(index,brush);
}

void MTerrain::test_function(){
    uint32_t x = 0;
    uint32_t y = 0;
    int id = get_image_id("splatmap");
    MImage* img = grid->get_image_by_pixel(x,y,id);
    UtilityFunctions::print("--------------------Test function");
    Color c(0.1,0.2,0.3,1);
    img->set_pixel(1,2,c);
    Color o = img->get_pixel(1,2);
    UtilityFunctions::print("o color ",o);
    float red = img->get_pixel_in_channel(1,2,0);
    UtilityFunctions::print("red ",red);
}