#ifndef LT_WINDOW_HPP_019e4aee_c8ab_7c2f_878c_0a6ca34791b8
#define LT_WINDOW_HPP_019e4aee_c8ab_7c2f_878c_0a6ca34791b8
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <string>
namespace libtallis
{
	struct window
	{
		std::string name;
		unsigned int width, height;
		bool close;
		GLFWwindow* win;
		VkSurfaceKHR surface;
		window(std::string, unsigned int = 640, unsigned int = 480);
		~window();
		void create_surface(VkInstance);
		bool should_close();

	  private:
		static inline bool glfw_initialized {0}, is_default {0};
		static inline unsigned int num_windows {0};
	};
} /* namespace libtallis */
#endif /* LT_WINDOW_HPP_019e4aee_c8ab_7c2f_878c_0a6ca34791b8 */
