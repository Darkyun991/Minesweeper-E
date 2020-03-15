#pragma once
#include "Empaerior.h"
#include "defines/Defines.h"
#ifdef EMP_USE_DATA_DUMPS

namespace Empaerior {
	//Theese are debug functions so efficienty is not a pritority
	template <typename T>
	inline Empaerior::string get_data(Empaerior::string name, const T&)
	{
		return "There's no implementation for the specified data type"
	}


	template <>
	inline Empaerior::string get_data<Empaerior::Event_Listener>(Empaerior::string name, const Empaerior::Event_Listener& listener)
	{
		Empaerior::string string = " \nEvent_Listener : " + name + '\n';
		string += "There are " + std::to_string(listener._registeredCallbacks.size()) + " events registered: " + '\n';
		for (auto const& pair : listener._registeredCallbacks) {
			//string += "Event code : " + std::to_string(pair.first) + ' ' + std::to_string(pair.second) +  '\n';
		}
		return string;
	}

	template<>
	inline Empaerior::string get_data<Empaerior::T_E_Component>(Empaerior::string name, const Empaerior::T_E_Component& t_e)
	{
		Empaerior::string string = "\nT_E_Component: " + name + '\n';
		string += "There are " + std::to_string(t_e.functions.size()) + " functions registered :";
		for (Empaerior::u_int i = 0; i < t_e.functions.size(); i++)
		{
			string += std::to_string(i) + "Time : " + std::to_string(t_e.time[i]) + " Elapsed time" + std::to_string(t_e.elapsed_time[i]) + '\n';
		}

		return string;
	}


	template <>
	inline Empaerior::string get_data<Empaerior::Point2f>(Empaerior::string name, const Empaerior::Point2f& point)
	{
		Empaerior::string string = "\nPoint2 : " + name + '\n';
		string += "x: " + std::to_string(point.x) + " y: " + std::to_string(point.y) + '\n';
		return string;
	}


	template<>
	inline Empaerior::string get_data<Empaerior::Float_Rect>(Empaerior::string name, const Empaerior::Float_Rect& rect)
	{
		Empaerior::string string = "\nTransform Rect: " + name + '\n';
		string += "x: " + std::to_string(rect.dimensions.x) + " y: " + std::to_string(rect.dimensions.y) + " w: " + std::to_string(rect.dimensions.w) + " h: " + std::to_string(rect.dimensions.h) + " Angle: " + std::to_string(rect.angle) + '\n';
		return string;
	}

	template<>	
	inline Empaerior::string get_data<Empaerior::Camera>(Empaerior::string name, const Empaerior::Camera& cam)
	{
		Empaerior::string string = "\nCamera : " + name + '\n';
		string += "x: " + std::to_string(cam.rect.x) + " y: " + std::to_string(cam.rect.y) + " w: " + std::to_string(cam.rect.w) + " h: " + std::to_string(cam.rect.h) + '\n';
		return string;
	}

	template<>
	inline Empaerior::string get_data<Empaerior::ECS>(Empaerior::string name, const Empaerior::ECS& ecs)
	{
		Empaerior::string string = "\nECS : " + name + '\n';
		//Entities
		string += "There are: " + std::to_string(ecs.entity_manager->lowest_unallocatedid - ecs.entity_manager->freed_id.size()) + " entities\n";
		//Components
		string += "There are: " + std::to_string(ecs.component_manager->component_containers.size()) + " types of components registered by this ecs:\n";
		for (auto& it : ecs.component_manager->component_containers) {
			string += " * ";
			string += it.first;
			string += '\n';
		}
		string + '\n';

		//Systems
		string += "There are: " + std::to_string(ecs.system_manager->typetosystem.size()) + " systems registered by this ecs:\n";
		for (auto& it : ecs.system_manager->typetosystem) {
			string += " * ";
			string += it.first;
			string += " iterates upon " + std::to_string(it.second->entities_id.size()) + " entities";

			string += '\n';
		}
		string + '\n';

		return string;
	}

	
	


}
#define EMP_DUMP_DATA(a) get_data(#a,a)  

#else

#define EMP_DUMP_DATA(a) 

#endif
