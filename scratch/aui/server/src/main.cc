#include "myarea.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

int main(int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv, "org.heorot.org.aui_test");

  Gtk::Window win;
  win.set_title("Astromech GUI");
  win.set_default_size(300, 200);

  MyArea area;
  win.add(area);
  area.show();

  return app->run(win);
}
