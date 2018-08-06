#pragma once

#pragma region value macro
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define CAMERA_OFFSET_Y 200
#define PLAYER_SPEED 500.0f
#define PLAYER_JUMP_FORCE 500.0f
#define PLAYER_JUMP_TIME 0.5f
#define PLAYER_WIDTH 110
#define PLAYER_HEIGHT 172
#define PLAYER_MIRROR SVector2(1.0f, 0.0f)
#define WORLD_BLOCK_ATLAS_WIDTH 26
#define WORLD_BLOCK_ATLAS_HEIGHT 26
#define WORLD_BLOCK_WIDTH 48
#define WORLD_BLOCK_HEIGHT 48
#define GRAVITY_VALUE 9.81f
#define WORLD_WIDTH 3840
#define WORLD_HEIGHT 720
#pragma endregion

#pragma region m2vh
#define FOREGROUND_DISTFACTOR 1.2f
#define GROUND_POSITION 720	// Y-Position of top border
#define WAY_HEIGHT 10
#define NPC_HEIGHT 302
#define NPC_WIDTH 174
#define ITEM_WIDTH 55
#define ITEM_HEIGHT 55
#define INVENTORY_ITEM_OFFSET_X 22
#define INVENTORY_ITEM_OFFSET_Y 17
#define INVENTORY_WIDTH 97
#define INVENTORY_HEIGHT 244
#define MOON_POSITION_Y -50
#define MOON_POSITION_X 850
#pragma endregion


#pragma region function macro
#define LOG_ERROR(TEXT, ERROR)		\
	std::cout << TEXT;				\
	std::cout << " Error: ";		\
	std::cout << ERROR;				\
	std::cout << std::endl;

#define LOG_MESSAGE(TEXT, VALUE)	\
	std::cout << ">> ";		\
	std::cout << TEXT;		\
	std::cout << ": ";		\
	std::cout << VALUE;		\
	std::cout << std::endl;

#pragma endregion