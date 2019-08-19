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
