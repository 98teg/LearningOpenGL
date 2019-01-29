#include "Test.hpp"
#include "../vendor/imgui/imgui.h"

namespace test{
	TestMenu::TestMenu(){
		SetCurrent(nullptr);
	}

	void TestMenu::OnImGuiRender(){
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
