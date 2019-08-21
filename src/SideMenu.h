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
  Gtk::Button about;

  Glib::RefPtr<Gdk::Pixbuf> logo;
  void runAbout();
};

SideMenu::SideMenu()
    : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0), about("About KOROKU") {
  Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
  css_provider->load_from_data("box {background-image: image(white);}");
  this->get_style_context()->add_provider(css_provider,
                                          GTK_STYLE_PROVIDER_PRIORITY_USER);
  this->eraseAll = new Gtk::Button("Erase All");
  this->about.signal_clicked().connect(
      sigc::mem_fun(*this, &SideMenu::runAbout));

  logo = Gdk::Pixbuf::create_from_file("./src/images/s_icon.png");

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
}

void SideMenu::runAbout() {
  Gtk::AboutDialog aboutDialog;
  aboutDialog.set_program_name("KOROKU");
  aboutDialog.set_version("0.1.0");
  aboutDialog.set_comments("Painting software to trace images.");
  aboutDialog.set_website("https://github.com/zazara/KOROKU-minimal");
  aboutDialog.set_website_label("GitHub Repository");
  aboutDialog.set_license_type(Gtk::LICENSE_GPL_3_0);
  aboutDialog.set_copyright("© 2019 zazara");
  aboutDialog.set_modal(true);
  aboutDialog.set_logo(logo);
  aboutDialog.run();
}
} // namespace KOROKU
