#include "../Renderer.hpp"

#include <vector>
#include <functional>

#ifndef TEST_HPP
#define TEST_HPP

namespace test{

	class Test{
		public:
			Test() {};
			virtual ~Test() {};

			virtual void OnUpdate(float deltaTime) {};
			virtual void OnRender() {};
			virtual void OnImGuiRender() {};
	};


	class TestMenu : public Test{
		private:
			Test* Current;
			std::vector<std::pair<std::string, std::function<Test*()>>> TestsList;

			inline void SetCurrent(Test* test){Current = test;};
		public:
			TestMenu();

			void OnImGuiRender() override;
			inline Test* GetCurrent() const{return Current;};
			inline bool IsTestSelected() const{return GetCurrent() != nullptr;};
			void DeselecteTest();

			template<typename T>
			void RegisterTest(const std::string& name){
				TestsList.push_back(std::make_pair(name, []() {return new T();}));
			}
	};
}

#endif
