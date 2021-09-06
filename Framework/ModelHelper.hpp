#pragma once
#include <tiny_obj_loader.h>
#include "BaseModel.hpp"
#include "spdlog/spdlog.h"

class ModelHelper
{
	static BaseModel::Data loadModel(const char* path);
};