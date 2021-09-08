#pragma once

#include <vulkan/vulkan.hpp>

namespace Gyro
{
	namespace Vulkan
	{
		namespace Commands
		{
			class CommandBuffer
			{
			public:
				void Create();
			private:
				VkCommandBuffer buffer;
			};
		}

	}

}
