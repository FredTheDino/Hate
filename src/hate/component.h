#pragma once
#include <string>
#include <iostream>

#define _COMPONENT_
namespace hate {
	// Forward declaration if needed
#ifndef _ENTITY_
	class Entity;
#endif

	/**
	 * A component can be attatched to an entity.
	 * Components handle the the functionallity and data,
	 * their only requirement is that they extend the base
	 * component in someway, and have a unique key.
	 */
	class Component {
		friend Entity;
		public:
			// Creates a new component.
			Component() {};

			// Delets this component.
			virtual ~Component() {};

			/**
			 * Returns the key for this component type.
			 * Each component type MUST have a unique key. You set this by
			 * overriding this function when you write the component.
			 * 
			 * You can make 2 or more components that share key, if you only want
			 * one of them to be able to be added to an entity at a time. 
			 *
			 * @return the key for this component type.
			 */
			std::string getKey() { return ""; };

			/**
			 * Initalizes the component, here you should check that all
			 * other components needed by this component are present.
			 */
			virtual void init() {};

			/**
			 * Updates the entity, this is called once per frame.
			 */
			virtual void update(double delta) {};	

			void enable() { enabled = true; }

			void disable() { enabled = false; }

			// Toggles the enabled state of the component.
			void toggle() { enabled = !enabled; }

			void setEnabled(bool state) { enabled = state; }

			bool isEnabled() { return enabled; }

		protected:
			/**
			 * Sets the parent of the compoent.
			 * A component cna only have one parent, and this parent should never change.
			 *
			 * @param parent the parent of this entity.
			 */
			void setParent(Entity* parent) {
				this->parent = parent;
			}

		private:	
			// The parent of this entity
			Entity* parent;

			// If the component is enabled or not
			bool enabled;





	};
}
