#pragma once
#include <cstdint>
#include <vulkan/vulkan.hpp>
#include "spdlog/spdlog.h"
#include "Configuration.hpp"

class ValidationLayer
{
public:
	static bool checkValidationLayerSupport();
protected:
private:

};