#include "project.h"
extern st_state state;

void power_on(){

	state.target_angle=state.preset_angle;
	if(state.softstart){
		state.angle=MAX_ANGLE-2*state.speed;
	}else{
		state.angle=state.target_angle;
	}
	state.power=ON; //here we set it on so we dont need to set it on in the interrupt :D
}


void power_off(){
	state.target_angle=MAX_ANGLE;
	if(!state.softstart){
		state.angle=MAX_ANGLE;
	}

//state.power=OFF;
}

void angle_change(int preset_angle){
	state.preset_angle=preset_angle;
	state.target_angle=state.preset_angle;
	if(!state.softstart) state.angle=state.target_angle;

//	state.angle=preset_angle;
}
