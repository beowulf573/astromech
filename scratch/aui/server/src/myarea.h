#ifndef GTKMM_EXAMPLE_MYAREA_H
#define GTKMM_EXAMPLE_MYAREA_H

#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>

class MyArea : public Gtk::DrawingArea
{
public:
  MyArea();
  virtual ~MyArea();

protected:
  //Override default signal handler:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  bool on_timeout(int timer_number);

  Glib::RefPtr<Gdk::Pixbuf> m_image;

  int shm_fd;
  void *shm_buf;

  sigc::connection m_conn_timer;
};

#endif // GTKMM_EXAMPLE_MYAREA_H
