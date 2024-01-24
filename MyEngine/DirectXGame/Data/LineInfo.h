#pragma once
#include "DirectXGame/Math/Vector3.h"
#include "DirectXGame/Data/RenderItem.h"

struct LineInfo {
	Vector3 startPos;
	Vector3 endPos;

	RenderItem renderItem;
};