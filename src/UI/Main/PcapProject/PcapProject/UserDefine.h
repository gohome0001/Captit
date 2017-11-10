#pragma once

#include <Windows.h>

//!< Define�� ����

#define D_DESKTOP_WIDTH			GetSystemMetrics(SM_CXSCREEN)							//!< ���� ��ǻ���� �ػ� ȭ���� width�� ������
#define D_DESKTOP_HEIGHT		GetSystemMetrics(SM_CYSCREEN)							//!< ���� ��ǻ���� �ػ� ȭ���� Height�� ������

#define D_WINDOW_WIDTH			1024													//!< ������ â�� ����
#define D_WINDOW_HEIGHT			768														//!< ������ â�� ����

#define D_WINDOW_POSX			D_DESKTOP_WIDTH / 2	 - D_WINDOW_WIDTH / 2				//!< ������ â�� ������ ���� ��ġ (����)
#define D_WINDOW_POSY			D_DESKTOP_HEIGHT / 2 - D_WINDOW_HEIGHT / 2				//!< ������ â�� ������ ���� ��ġ (����)

#define D_WINDOW_NAME			"first practice"												//!< ������ â �̸�

#define D_MAIN_FUNC				CMain::getInstance()									//!< ���� �̱���