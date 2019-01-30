#include "Test.hpp"

#ifndef TESTCLEARCOLOR_HPP
#define TESTCLEARCOLOR_HPP

namespace test{

	class TestClearColor: public Test{
		private:
			float Color[4];

			inline float GetRed()	const{return Color[0];};
			inline float GetGreen()	const{return Color[1];};
			inline float GetBlue()	const{return Color[2];};
			inline float GetAlpha()	const{return Color[3];};

			inline void  GetColor(float color[4]) const{
				color[0] = GetRed();
				color[1] = GetGreen();
				color[2] = GetBlue();
				color[3] = GetAlpha();
			}

			inline void SetRed(float red)		{Color[0] = red;};
			inline void SetGreen(float green)	{Color[1] = green;};
			inline void SetBlue(float blue)		{Color[2] = blue;};
			inline void SetAlpha(float alpha)	{Color[3] = alpha;};

			inline void SetColor(const float color[4]){
				SetRed(color[0]);
				SetGreen(color[1]);
				SetBlue(color[2]);
				SetAlpha(color[3]);
			}
		public:
			TestClearColor();
			~TestClearColor();

			void OnRender() override;
			void OnImGuiRender() override;
	};

}

#endif
