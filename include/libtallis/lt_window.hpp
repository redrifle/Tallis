#ifndef LT_WINDOW_HPP_019e4aee_c8ab_7c2f_878c_0a6ca34791b8
#define LT_WINDOW_HPP_019e4aee_c8ab_7c2f_878c_0a6ca34791b8
#include <GLFW/glfw3.h>

class lt_window
{
  private:
	const char* name;
	const unsigned int width, height;
	GLFWwindow* win;

  public:
	lt_window(const char*, unsigned int, unsigned int);
	~lt_window();
	GLFWwindow* lt_create_win(const char*, unsigned int, unsigned int);
	bool should_close();
	unsigned int get_width();
	unsigned int get_height();
	GLFWwindow* get_pointer();
};
#endif /* LT_WINDOW_HPP_019e4aee_c8ab_7c2f_878c_0a6ca34791b8 */
