#pragma once

#include <Windows.h>

//!< Define을 선언

#define D_DESKTOP_WIDTH			GetSystemMetrics(SM_CXSCREEN)							//!< 현재 컴퓨터의 해상도 화면의 width를 가져옴
#define D_DESKTOP_HEIGHT		GetSystemMetrics(SM_CYSCREEN)							//!< 현재 컴퓨터의 해상도 화면의 Height를 가져옴

#define D_WINDOW_WIDTH			1024													//!< 윈도우 창의 넓이
#define D_WINDOW_HEIGHT			768														//!< 윈도우 창의 높이

#define D_WINDOW_POSX			D_DESKTOP_WIDTH / 2	 - D_WINDOW_WIDTH / 2				//!< 윈도우 창이 생성될 때의 위치 (가로)
#define D_WINDOW_POSY			D_DESKTOP_HEIGHT / 2 - D_WINDOW_HEIGHT / 2				//!< 윈도우 창이 생성될 때의 위치 (세로)

#define D_WINDOW_NAME			"first practice"												//!< 윈도우 창 이름

#define D_MAIN_FUNC				CMain::getInstance()									//!< 메인 싱글톤