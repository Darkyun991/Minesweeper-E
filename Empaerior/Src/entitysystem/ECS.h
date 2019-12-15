#pragma once
#include "Entity.h"
#include "components/ComponentManager.h"
#include "system/system.h"

namespace Empaerior
{
	class ECS
	{
	public:
		void Init()
		{
			component_manager = std::make_unique<Empaerior::ComponentManager>();
			entity_manager = std::make_unique<Empaerior::EnityManager>();
			system_manager = std::make_unique<Empaerior::SystemManager>();

		}
		//assigns a new id for an entity
		uint64_t create_entity_ID()
		{
			return entity_manager->add_Entity();
		}
		//destroy entity
		void destroy_entity(const uint64_t& id)
		{
			entity_manager->delete_entity(id);
			component_manager->OnEntityDestroyed(id);
			system_manager->OnEntityDestroy(id);

		}

		template<typename T>
		void register_component()
		{
			component_manager->register_component<T>();
		}

		template<typename T>
		void add_component(const uint64_t& entity_id, T component)
		{
			//add the component
			component_manager->add_component<T>(entity_id, component);


			//modify the signature to match the new addition
			std::vector<bool> e_signature = entity_manager->get_signature(entity_id);
			uint64_t component_type = component_manager->get_component_id<T>();
			//while the vector of signature doesn't have elements until the currenjt component we want do add
			//add 0 
			while (e_signature.size() <= component_type)
			{
				e_signature.emplace_back(0);
			}
			//add the new signature
			e_signature[component_type] = 1;
			entity_manager->set_signature(entity_id, e_signature);
			system_manager->OnEntitySignatureChange(entity_id, e_signature);
		}
		template <typename T>
		void remove_component(const uint64_t& entity_id)
		{
			component_manager->remove_component<T>(entity_id);\
			std::vector<bool> e_signature = entity_manager->get_signature(entity_id);
			uint64_t component_type = component_manager->get_component_id<T>();
			e_signature[component_type] = 0;
			system_manager->OnEntitySignatureChange(entity_id, e_signature);
		}

		template <typename T>
		T& get_component(const uint64_t& entity_id)
		{
			return component_manager->get_component<T>(entity_id);
		}

		template <typename T>
		uint64_t get_component_id()
		{
			return component_manager->get_component_id<T>();
		}

		template <typename T>
		std::shared_ptr<T> register_system()
		{
			return system_manager->register_system<T>();
		}

		template <typename T>
		void set_system_signature(std::vector<bool>& signature)
		{
			system_manager->set_signature<T>(signature);
		}





	private:	
		std::unique_ptr<Empaerior::ComponentManager> component_manager;
		std::unique_ptr<Empaerior::EnityManager> entity_manager;
		std::unique_ptr<Empaerior::SystemManager> system_manager;
	};

}