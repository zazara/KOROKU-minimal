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
#include "Canvas.h"
#include "TransparentWindow.h"
#include <gtkmm/application.h>

int main(int argc, char **argv) {
  auto app = Gtk::Application::create(argc, argv);

  KOROKU::TransparentWindow win;

  win.show_all();

  return app->run(win);
}