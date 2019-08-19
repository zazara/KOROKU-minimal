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
