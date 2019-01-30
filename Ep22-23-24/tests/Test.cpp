#include "Test.hpp"
#include "../vendor/imgui/imgui.h"

namespace test{
	TestMenu::TestMenu(){
		SetCurrent(nullptr);
	}

	void TestMenu::OnImGuiRender(){
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		for(auto& test : TestsList){
			if(ImGui::Button(test.first.c_str()))
				SetCurrent(test.second());
		}
	}

	void TestMenu::DeselecteTest(){
		delete GetCurrent();
		SetCurrent(nullptr);
	}
}
