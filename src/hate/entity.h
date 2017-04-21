#pragma once
#include <vector>

namespace Hate {

	class Entity {
		public:
			Entity();

			~Entity();

			template <class T>
				void get();

			template <class T>
				void add(T component);

			template <class T>
				void remove();

		private:
			std::vector<Component*> components;
	};
}
