#pragma once

#include "LoFox/Core/Core.h"

#include <vulkan/vulkan.h>

namespace LoFox {

	class StorageImage {

	public:
		StorageImage(uint32_t width, uint32_t height);
		void Destroy();

		VkDescriptorImageInfo GetDescriptorInfo();

		void TransitionLayout(VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

		static Ref<StorageImage> Create(uint32_t width, uint32_t height);
	private:
		uint32_t m_Width, m_Height;

		VkImage m_Image;
		VkDeviceMemory m_Memory;
		VkImageView m_ImageView;

		VkFormat m_Format;
	};
}