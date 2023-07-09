#pragma once

#include <vulkan/vulkan.h>

#include "LoFox/Core/Window.h"

#include "LoFox/Renderer/Buffer.h"
#include "LoFox/Renderer/Image.h"

#include "LoFox/Renderer/Pipeline.h"
#include "LoFox/Renderer/SwapChain.h"

#include "LoFox/Events/RenderEvent.h"

#include "LoFox/Utils/Time.h"

namespace LoFox {

	class Renderer {

	public:
		static void Init(Ref<Window> window);
		static void Shutdown();

		static void SubmitGraphicsPipeline(GraphicsPipeline pipeline);

		static void StartFrame();
		static void SubmitFrame();

		static void WaitIdle();

		static inline VkFormat GetSwapChainImageFormat() { return m_SwapChain->GetImageFormat(); }
		static inline VkFormat GetSwapChainDepthFormat() { return m_SwapChain->GetDepthImage()->GetFormat(); }
		static inline VkExtent2D GetSwapChainExtent() { return m_SwapChain->GetExtent(); }

		static void OnResize(uint32_t width, uint32_t height) { OnFramebufferResize(FramebufferResizeEvent(width, height)); }
	public:
		static const int MaxFramesInFlight = 1;
	private:
		static void RecordCommandBuffer();
		static void UpdateUniformBuffer(uint32_t currentImage);

		static void CreateImageSampler();

		static void CreateDescriptorPool();
		static void InitPipelines(VkVertexInputBindingDescription vertexBindingDescription, std::vector<VkVertexInputAttributeDescription> vertexAttributeDescriptions);

		static bool OnFramebufferResize(FramebufferResizeEvent& event);
	private:
		static Ref<Window> m_Window;
		static Timer m_Timer;

		static Ref<SwapChain> m_SwapChain;
		static GraphicsPipeline m_GraphicsPipeline;

		static Ref<Image> m_Texture1;

		static std::vector<Ref<Buffer>> m_UniformBuffers;
		static std::vector<void*> m_UniformBuffersMapped;

		static VkSampler m_Sampler;

		static VkDescriptorPool m_DescriptorPool;
		static VkDescriptorSetLayout m_GraphicsDescriptorSetLayout;
		static std::vector<VkDescriptorSet> m_GraphicsDescriptorSets;
	};
}