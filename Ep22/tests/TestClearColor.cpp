#include "TestClearColor.hpp"

#include "../vendor/imgui/imgui.h"

namespace test{
	TestClearColor::TestClearColor(){
		SetRed(0.03f);
		SetGreen(0.8f);
		SetBlue(0.4f);
		SetAlpha(1.0f);
	}

	TestClearColor::~TestClearColor(){

	}

	void TestClearColor::onUpdate(float deltaTime){

	}

	void TestClearColor::onRender(){
		GLCall(glClearColor(GetRed(), GetGreen(), GetBlue(), GetAlpha()));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColor::onImguiRender(){
		float color[4];
		GetColor(color);

		ImGui::ColorEdit4("Background color:", color);

		SetColor(color);
	}
}
