#include "Canvas.h"
#include "TransparentWindow.h"
#include <gtkmm/application.h>

int main(int argc, char **argv) {
  auto app = Gtk::Application::create(argc, argv);

  KOROKU::TransparentWindow win;

  try {
    Gtk::Window::set_default_icon_from_file("src/images/s_icon.png");
  } catch (...) {
    Glib::exception_handlers_invoke();
    exit(1);
  }
  win.show_all();

  return app->run(win);
}