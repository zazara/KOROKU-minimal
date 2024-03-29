/* KOROKU-minimal
 *
 * Copyright (C) 2019 zazara
 *
 * This file is part of KOROKU-minimal.
 *
 * KOROKU-minimal is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * KOROKU-minimal is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with KOROKU-minimal.  If not, see <http://www.gnu.org/licenses/>.
 */
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