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
#include <gtkmm.h>
namespace KOROKU {
class EditBox : public Gtk::Box {
public:
  EditBox();
  Gtk::Button undo;
  Gtk::Button redo;
  void onUndoClicked();
  void onRedoClicked();
};

EditBox::EditBox() : Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0) {
  this->undo = Gtk::Button("Undo");
  this->redo = Gtk::Button("Redo");
  this->pack_start(undo, true, true, 5);
  this->pack_start(redo, true, true, 5);
}

} // namespace KOROKU
