#pragma once
#include <unordered_map>
#include "component.h"

#define ENTITY
namespace hate {

	// Forward declaration if needed
#ifndef COMPONENT
	class Component;
#endif

	/**
	 * The entity typename holds components witch are
	 * updated by the entity manager. 
	 */
	class Entity {
		public:
			// Creates a new entity.
			Entity();

			// Destroys an entity and all its components.
			~Entity();

			// Returns the component of type if it finds it, null otherwise.
			template <class T>
				T* get();

			// Adds the component to the entity.
			template <class T>
				bool add(T* component);

			// Removes the component from the entity.
			template <class T>
				void remove();

			// Disables a specified component.
			template <class T>
				void disable();

			// Disables all components.
			void disableAll();

			// Enables the component.
			template <class T>
				void enable();

			// Enables all the components.
			void enableAll();
	
			// Toggles the components enabled state.
			template <class T>
				void toggle();
			
			// Toggles all the components.
			void toggleAll();

		private:
			std::unordered_map<std::string, Component*> components;
	};
}

#include "entity.cpp"
