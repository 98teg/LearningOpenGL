#include "../Renderer.hpp"

#ifndef TEST_HPP
#define TEST_HPP

namespace test{

	class Test{
		public:
			Test() {};
			virtual ~Test() {};

			virtual void onUpdate(float deltaTime) {};
			virtual void onRender() {};
			virtual void onImguiRender() {};
	};

}

#endif
