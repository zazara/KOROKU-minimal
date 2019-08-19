#include "SideMenu.h"
#include <gtkmm.h>

namespace KOROKU {
class ClientArea : public Gtk::Box {
public:
  ClientArea();
  KOROKU::Canvas canvas;
  Gtk::Box *vbox;
  Gtk::Button button;
  KOROKU::SideMenu sideMenu;

private:
  void undo();
  void redo();
  void setPrimaryColor();
  bool setBrushWidth(Gtk::ScrollType, double);
  void setBrushSelect();
  void eraseAll();
};

ClientArea::ClientArea() {
  this->button = Gtk::Button("Test");
  this->pack_start(canvas);
  this->pack_start(sideMenu, false, false);
  this->sideMenu.editBox.undo.signal_clicked().connect(
      sigc::mem_fun(*this, &ClientArea::undo));
  this->sideMenu.editBox.redo.signal_clicked().connect(
      sigc::mem_fun(*this, &ClientArea::redo));
  this->sideMenu.brushBox.primaryBrush.signal_color_set().connect(
      sigc::mem_fun(*this, &ClientArea::setPrimaryColor));
  this->sideMenu.brushBox.brushWidthScale.signal_change_value().connect(
      sigc::mem_fun(*this, &ClientArea::setBrushWidth));
  this->sideMenu.brushBox.primaryButton.signal_clicked().connect(
      sigc::mem_fun(*this, &ClientArea::setBrushSelect));
  this->sideMenu.eraseAll->signal_clicked().connect(
      sigc::mem_fun(*this, &ClientArea::eraseAll));
}

void ClientArea::undo() { this->canvas.undo(); }
void ClientArea::redo() { this->canvas.redo(); }
void ClientArea::setPrimaryColor() {
  this->canvas.setPrimaryBrushRGB(
      // Magic number is temporary fix
      this->sideMenu.brushBox.primaryBrush.get_color().get_red() / 65535.0,
      this->sideMenu.brushBox.primaryBrush.get_color().get_green() / 65535.0,
      this->sideMenu.brushBox.primaryBrush.get_color().get_blue() / 65535.0);
}

// Temporary code
bool ClientArea::setBrushWidth(Gtk::ScrollType scroll, double value) {
  if (this->sideMenu.brushBox.primaryButton.get_active()) {
    this->canvas.setPrimaryBrushWidth(value);
  } else {
    this->canvas.setEraserBrushWidth(value);
  }
  return true;
}

void ClientArea::setBrushSelect() {
  if (this->sideMenu.brushBox.primaryButton.get_active()) {
    this->canvas.setBrushSelect(PRIMARY_BRUSH);
    this->sideMenu.brushBox.brushWidthScale.set_value(
        (int)this->canvas.primaryBrushParam.width);
  } else {
    this->canvas.setBrushSelect(ERASER_BRUSH);
    this->sideMenu.brushBox.brushWidthScale.set_value(
        (int)this->canvas.eraserBrushParam.width);
  }
}

void ClientArea::eraseAll() { this->canvas.eraseAll(); }

} // namespace KOROKU
