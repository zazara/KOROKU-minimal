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
class BrushBox : public Gtk::Box {
private:
  Gtk::Box primaryBox, switchBox;

public:
  Gtk::ColorButton primaryBrush;
  Gtk::Scale brushWidthScale;
  Gtk::RadioButton primaryButton, eraserButton;
  BrushBox();
  virtual ~BrushBox();
};

BrushBox::BrushBox()
    : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0), primaryButton("Brush"),
      eraserButton("Eraser") {

  // box
  this->switchBox = Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0);

  // color button
  this->primaryBrush.set_color(Gdk::Color("black"));
  // group
  Gtk::RadioButton::Group selector = primaryButton.get_group();
  eraserButton.set_group(selector);

  // scale
  this->brushWidthScale.set_range(1, 30);
  this->brushWidthScale.set_increments(1, 1);
  this->brushWidthScale.set_value(1);
  this->brushWidthScale.set_round_digits(0.1);
  this->pack_start(brushWidthScale, false, false);
  this->pack_start(primaryBrush);
  this->switchBox.pack_start(primaryButton);
  this->switchBox.pack_start(eraserButton);
  this->pack_start(this->switchBox);
}

BrushBox::~BrushBox() {}

} // namespace KOROKU
