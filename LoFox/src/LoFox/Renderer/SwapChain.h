#pragma once

#include <vulkan/vulkan.h>

#include "LoFox/Renderer/RenderContext.h"
#include "LoFox/Core/Window.h"

namespace LoFox {

	class SwapChain {

	public:
		SwapChain(Ref<RenderContext> context, Ref<Window> window);
		~SwapChain();

		void Recreate();

		int AcquireNextImageIndex(uint32_t currentFrame);
		void PresentImage(uint32_t imageIndex, VkSemaphore* waitSemaphores);

		void CreateFramebuffers();

		inline VkSwapchainKHR GetSwapChain() { return m_SwapChain; }
		inline VkFramebuffer GetFramebuffer(uint32_t index) { return m_Framebuffers[index]; }

		inline VkFormat GetImageFormat() { return m_ImageFormat; }
		inline VkExtent2D GetExtent() { return m_Extent; }
	private:
		void CleanupSwapChain();
		void CreateSwapChainAndImages();
		void CreateImageViews();
	private:
		Ref<RenderContext> m_Context;
		Ref<Window> m_Window;

		VkSwapchainKHR m_SwapChain;
		std::vector<VkImage> m_Images;
		std::vector<VkImageView> m_ImageViews;
		std::vector<VkFramebuffer> m_Framebuffers;

		VkFormat m_ImageFormat;
		VkExtent2D m_Extent;
	};
}