#ifndef LT_WINDOW_HPP_019e4aee_c8ab_7c2f_878c_0a6ca34791b8
#define LT_WINDOW_HPP_019e4aee_c8ab_7c2f_878c_0a6ca34791b8
#include <GLFW/glfw3.h>
#include <string>
struct lt_window
{
	const std::string name;
	const unsigned int width, height;
	GLFWwindow* win;
	lt_window(std::string, unsigned int = 640, unsigned int = 480);
	~lt_window();
	GLFWwindow* lt_create_win(const std::string_view);
	bool should_close();
};
#endif /* LT_WINDOW_HPP_019e4aee_c8ab_7c2f_878c_0a6ca34791b8 */
