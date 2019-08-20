#include "ClientArea.h"
#include <cairomm/context.h>

#include <gtkmm.h>

namespace KOROKU {

class TransparentWindow : public Gtk::Window {
public:
  TransparentWindow();
  virtual ~TransparentWindow();
  KOROKU::ClientArea clientArea;
};

TransparentWindow::TransparentWindow() {
  this->set_default_size(800, 500);
  set_app_paintable(true);
  // Transparent Process
  Glib::RefPtr<Gdk::Visual> visual = get_screen()->get_rgba_visual();
  gtk_widget_set_visual(GTK_WIDGET(gobj()), visual->gobj());

  this->add(clientArea);
  this->show_all();
}
TransparentWindow::~TransparentWindow() {}

} // namespace KOROKU