#include "mgrass_lod_setting.h"

#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/variant/basis.hpp>
#include<cstdlib>
#include <godot_cpp/variant/utility_functions.hpp>


void MGrassLodSetting::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_seed","input"), &MGrassLodSetting::set_seed);
    ClassDB::bind_method(D_METHOD("get_seed"), &MGrassLodSetting::get_seed);
    ADD_PROPERTY(PropertyInfo(Variant::INT,"seed"),"set_seed","get_seed");
    ClassDB::bind_method(D_METHOD("set_divide","input"), &MGrassLodSetting::set_divide);
    ClassDB::bind_method(D_METHOD("get_divide"), &MGrassLodSetting::get_divide);
    ADD_PROPERTY(PropertyInfo(Variant::INT,"divide"),"set_divide","get_divide");
    ClassDB::bind_method(D_METHOD("set_grass_in_cell","input"), &MGrassLodSetting::set_grass_in_cell);
    ClassDB::bind_method(D_METHOD("get_grass_in_cell"), &MGrassLodSetting::get_grass_in_cell);
    ADD_PROPERTY(PropertyInfo(Variant::INT,"grass_in_cell"),"set_grass_in_cell","get_grass_in_cell");
    ClassDB::bind_method(D_METHOD("set_force_lod_count","input"), &MGrassLodSetting::set_force_lod_count);
    ClassDB::bind_method(D_METHOD("get_force_lod_count"), &MGrassLodSetting::get_force_lod_count);
    ADD_PROPERTY(PropertyInfo(Variant::INT,"force_lod_count"),"set_force_lod_count","get_force_lod_count");
    ClassDB::bind_method(D_METHOD("set_offset","input"), &MGrassLodSetting::set_offset);
    ClassDB::bind_method(D_METHOD("get_offset"), &MGrassLodSetting::get_offset);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3,"offset"),"set_offset","get_offset");
    ClassDB::bind_method(D_METHOD("set_rot_offset","input"), &MGrassLodSetting::set_rot_offset);
    ClassDB::bind_method(D_METHOD("get_rot_offset"), &MGrassLodSetting::get_rot_offset);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3,"rot_offset"),"set_rot_offset","get_rot_offset");
    ClassDB::bind_method(D_METHOD("set_rand_pos_start","input"), &MGrassLodSetting::set_rand_pos_start);
    ClassDB::bind_method(D_METHOD("get_rand_pos_start"), &MGrassLodSetting::get_rand_pos_start);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3,"rand_pos_start"),"set_rand_pos_start","get_rand_pos_start");
    ClassDB::bind_method(D_METHOD("set_rand_pos_end","input"), &MGrassLodSetting::set_rand_pos_end);
    ClassDB::bind_method(D_METHOD("get_rand_pos_end"), &MGrassLodSetting::get_rand_pos_end);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3,"rand_pos_end"),"set_rand_pos_end","get_rand_pos_end");
    ClassDB::bind_method(D_METHOD("set_rand_rot_start","input"), &MGrassLodSetting::set_rand_rot_start);
    ClassDB::bind_method(D_METHOD("get_rand_rot_start"), &MGrassLodSetting::get_rand_rot_start);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3,"rand_rot_start"),"set_rand_rot_start","get_rand_rot_start");
    ClassDB::bind_method(D_METHOD("set_rand_rot_end","input"), &MGrassLodSetting::set_rand_rot_end);
    ClassDB::bind_method(D_METHOD("get_rand_rot_end"), &MGrassLodSetting::get_rand_rot_end);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3,"rand_rot_end"),"set_rand_rot_end","get_rand_rot_end");
    ClassDB::bind_method(D_METHOD("set_uniform_rand_scale_start","input"), &MGrassLodSetting::set_uniform_rand_scale_start);
    ClassDB::bind_method(D_METHOD("get_uniform_rand_scale_start"), &MGrassLodSetting::get_uniform_rand_scale_start);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT,"uniform_rand_scale_start"),"set_uniform_rand_scale_start","get_uniform_rand_scale_start");
    ClassDB::bind_method(D_METHOD("set_uniform_rand_scale_end","input"), &MGrassLodSetting::set_uniform_rand_scale_end);
    ClassDB::bind_method(D_METHOD("get_uniform_rand_scale_end"), &MGrassLodSetting::get_uniform_rand_scale_end);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT,"uniform_rand_scale_end"),"set_uniform_rand_scale_end","get_uniform_rand_scale_end");
    ClassDB::bind_method(D_METHOD("set_rand_scale_start","input"), &MGrassLodSetting::set_rand_scale_start);
    ClassDB::bind_method(D_METHOD("get_rand_scale_start"), &MGrassLodSetting::get_rand_scale_start);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3,"rand_scale_start"),"set_rand_scale_start","get_rand_scale_start");
    ClassDB::bind_method(D_METHOD("set_rand_scale_end","input"), &MGrassLodSetting::set_rand_scale_end);
    ClassDB::bind_method(D_METHOD("get_rand_scale_end"), &MGrassLodSetting::get_rand_scale_end);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3,"rand_scale_end"),"set_rand_scale_end","get_rand_scale_end");
}

void MGrassLodSetting::set_seed(int input){
    ERR_FAIL_COND(input<0);
    seed = input;
}
int MGrassLodSetting::get_seed(){
    return seed;
}

void MGrassLodSetting::set_divide(int input){
    ERR_FAIL_COND(input<1);
    divide = input;
}
int MGrassLodSetting::get_divide(){
    return divide;
}

void MGrassLodSetting::set_grass_in_cell(int input){
    ERR_FAIL_COND(input<1);
    grass_in_cell = input;
}
int MGrassLodSetting::get_grass_in_cell(){
    return grass_in_cell;
}

void MGrassLodSetting::set_force_lod_count(int input){
    force_lod_count = input;
}
int MGrassLodSetting::get_force_lod_count(){
    return force_lod_count;
}

void MGrassLodSetting::set_offset(Vector3 input){
    offset = input;
}
Vector3 MGrassLodSetting::get_offset(){
    return offset;
}

void MGrassLodSetting::set_rot_offset(Vector3 input){
    rot_offset = input;
}
Vector3 MGrassLodSetting::get_rot_offset(){
    return rot_offset;
}

void MGrassLodSetting::set_rand_pos_start(Vector3 input){
    rand_pos_start = input;
}
Vector3 MGrassLodSetting::get_rand_pos_start(){
    return rand_pos_start;
}

void MGrassLodSetting::set_rand_pos_end(Vector3 input){
    rand_pos_end = input;
}
Vector3 MGrassLodSetting::get_rand_pos_end(){
    return rand_pos_end;
}

void MGrassLodSetting::set_rand_rot_start(Vector3 input){
    rand_rot_start = input;
}
Vector3 MGrassLodSetting::get_rand_rot_start(){
    return rand_rot_start;
}

void MGrassLodSetting::set_rand_rot_end(Vector3 input){
    rand_rot_end = input;
}
Vector3 MGrassLodSetting::get_rand_rot_end(){
    return rand_rot_end;
}

void MGrassLodSetting::set_uniform_rand_scale_start(float input){
    unifrom_rand_scale_start = input;
}
float MGrassLodSetting::get_uniform_rand_scale_start(){
    return unifrom_rand_scale_start;
}

void MGrassLodSetting::set_uniform_rand_scale_end(float input){
    unifrom_rand_scale_end = input;
}

float MGrassLodSetting::get_uniform_rand_scale_end(){
    return unifrom_rand_scale_end;
}

void MGrassLodSetting::set_rand_scale_start(Vector3 input){
    rand_scale_start = input;
}
Vector3 MGrassLodSetting::get_rand_scale_start(){
    return rand_scale_start;
}

void MGrassLodSetting::set_rand_scale_end(Vector3 input){
    rand_scale_end = input;
}
Vector3 MGrassLodSetting::get_rand_scale_end(){
    return rand_scale_end;
}

float MGrassLodSetting::rand_float(float a,float b,int seed){
    srand(seed);
    double r = (sin(double(seed)*3.512+13.23)*2.01*(double)seed);
    if(r<0){
        r*=-1.0;
    }
    r = r - floor(r);
    r = (cos(r*63.341+3.29)*((double)seed+8362.3215));
    if(r<0){
        r*=-1.0;
    }
    r = r - floor(r);
    r = (sin(double(r)*5.312+1.23)*23.01*(double)seed);
    if(r<0){
        r*=-1.0;
    }
    r = r - floor(r);
    double diff = b - a;
    r = r * diff + a;
    return (float)(r);
}



PackedFloat32Array* MGrassLodSetting::generate_random_number(float density,int amount){
    PackedFloat32Array* out = memnew(PackedFloat32Array);
    out->resize(amount * 12);
    for(int i=0;i<amount;i++){
        Vector3 _rand_pos;
        Vector3 _rand_rot;
        Vector3 _rand_scale;
        float uniform_scale;
        int iseed = i*10+seed;
        _rand_pos.x = rand_float(rand_pos_start.x*density,rand_pos_end.x*density,iseed);
        iseed++;
        _rand_pos.y = rand_float(rand_pos_start.y*density,rand_pos_end.y*density,iseed);
        iseed++;
        _rand_pos.z = rand_float(rand_pos_start.z*density,rand_pos_end.z*density,iseed);
        iseed++;
        _rand_rot.x = rand_float(rand_rot_start.x,rand_rot_end.x,iseed);
        iseed++;
        _rand_rot.y = rand_float(rand_rot_start.y,rand_rot_end.y,iseed);
        iseed++;
        _rand_rot.z = rand_float(rand_rot_start.z,rand_rot_end.z,iseed);
        iseed++;
        _rand_scale.x = rand_float(rand_scale_start.x,rand_scale_end.x,iseed);
        iseed++;
        _rand_scale.y = rand_float(rand_scale_start.y,rand_scale_end.y,iseed);
        iseed++;
        _rand_scale.z = rand_float(rand_scale_start.z,rand_scale_end.z,iseed);
        iseed++;
        uniform_scale = rand_float(unifrom_rand_scale_start,unifrom_rand_scale_end,iseed);
        // stage 2
        Basis b;
        b.scale(Vector3(uniform_scale,uniform_scale,uniform_scale));
        b.scale(_rand_scale);
        b.rotate(Vector3(0,1,0),UtilityFunctions::deg_to_rad(rot_offset.y));
        b.rotate(Vector3(1,0,0),UtilityFunctions::deg_to_rad(rot_offset.x));
        b.rotate(Vector3(0,0,1),UtilityFunctions::deg_to_rad(rot_offset.z));
        // Rotation order YXZ
        b.rotate(Vector3(0,1,0),UtilityFunctions::deg_to_rad(_rand_rot.y));
        b.rotate(Vector3(1,0,0),UtilityFunctions::deg_to_rad(_rand_rot.x));
        b.rotate(Vector3(0,0,1),UtilityFunctions::deg_to_rad(_rand_rot.z));


        Vector3 org = offset + _rand_pos;
        Transform3D t(b,org);

        
        int index = i*12;

        out->set(index,t.basis[0][0]);
        out->set(index+1,t.basis[0][1]);
        out->set(index+2,t.basis[0][2]);
        out->set(index+3,t.origin[0]);

        out->set(index+4,t.basis[1][0]);
        out->set(index+5,t.basis[1][1]);
        out->set(index+6,t.basis[1][2]);
        out->set(index+7,t.origin[1]);

        out->set(index+8,t.basis[2][0]);
        out->set(index+9,t.basis[2][1]);
        out->set(index+10,t.basis[2][2]);
        out->set(index+11,t.origin[2]);

    }
    return out;
}