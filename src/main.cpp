#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

class HelloTriangleApplication {
	public: 
		void run() {
			initWindow();
			initVulkan();
			mainLoop();
			cleanup();
		}

	private: 
		GLFWwindow* window;
		VkInstance instance;

		void initWindow() {
			glfwInit();

			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

			window = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);

		}
		void initVulkan() {
			createInstance();
		}

		void createInstance() {
			VkApplicationInfo appInfo{};
    		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    		appInfo.pApplicationName = "Hello Triangle";
    		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    		appInfo.pEngineName = "No Engine";
    		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    		appInfo.apiVersion = VK_API_VERSION_1_0;

			VkInstanceCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pApplicationInfo = &appInfo;

			uint32_t glfwExtensionCount = 0;
			const char** glfwExtensions;
			glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

			createInfo.enabledExtensionCount = glfwExtensionCount;
			createInfo.ppEnabledExtensionNames = glfwExtensions;

			createInfo.enabledLayerCount = 0;

			VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

			if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
					throw std::runtime_error("failed to create instance!");
					}
		}

		void mainLoop() {
			while (!glfwWindowShouldClose(window)) {
				glfwPollEvents();
			}

		}

		void cleanup() {
			vkDestroyInstance(instance, nullptr);
			glfwDestroyWindow(window);

			glfwTerminate();
		}

	};

	int main() {
		HelloTriangleApplication app;

		try {
			app.run();
		} catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
			return EXIT_FAILURE;
		}

	return EXIT_SUCCESS;
}
