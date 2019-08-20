#include "BrushBox.h"
#include "EditBox.h"
#include <gtkmm.h>
namespace KOROKU {
class SideMenu : public Gtk::Box {
public:
  SideMenu();
  KOROKU::EditBox editBox;
  KOROKU::BrushBox brushBox;
  Gtk::Button *eraseAll;

private:
  Gtk::Frame editFrame, brushFrame;
  Gtk::Box mainBox;
  Gtk::LinkButton about;
};

SideMenu::SideMenu()
    : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0),
      about("https://github.com/zazara/KOROKU-minimal", "About KOROKU") {
  Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
  css_provider->load_from_data("box {background-image: image(white);}");
  this->get_style_context()->add_provider(css_provider,
                                          GTK_STYLE_PROVIDER_PRIORITY_USER);
  this->eraseAll = new Gtk::Button("Erase All");

  editFrame.set_label("Edit");
  editFrame.add(this->editBox);
  brushFrame.set_label("Draw");
  brushFrame.add(this->brushBox);
  this->mainBox = Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0);
  this->mainBox.pack_start(editFrame, false, false);
  this->mainBox.pack_start(brushFrame, false, false, 20);
  this->pack_start(mainBox, false, false);
  eraseAll->get_style_context()->add_class("suggested-action");
  this->pack_start(*eraseAll, false, false, 20);
  this->pack_start(about, false, false);
} // namespace KOROKU
} // namespace KOROKU
