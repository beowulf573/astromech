#include "myarea.h"
#include <cairomm/context.h>
#include <giomm/resource.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <glibmm/fileutils.h>
#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>

#define SHARED_FB "shared_fb"

MyArea::MyArea()
{
    shm_fd = -1;
    shm_buf = NULL;
  try
  {
    int shm_fd = shm_open(SHARED_FB, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if(shm_fd > 0) {
        ftruncate(shm_fd, 320*200*3);
        shm_buf = mmap(NULL, 320*200*3, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, (off_t)0);
        if(shm_buf == MAP_FAILED) {
            fprintf(stderr, "mmap failed: %s\n", strerror(errno));
            shm_buf = NULL;
        }
    }
    else {
        fprintf(stderr, "shm_open failed: %s\n", strerror(errno));
    }
    
    if(shm_buf != NULL) {
        guint8* data = (guint8*)shm_buf;
        m_image = Gdk::Pixbuf::create_from_data(data, Gdk::COLORSPACE_RGB, false, 8, 320, 200, 320 * 3);

        for(int row = 0; row < 200; row++) {
            for(int col = 0; col < 320; col++) {
            //*data++ = row;
            *data++ = 0;
            *data++ = row;
            *data++ = row;
            }
        }
    }
    //memset(data, 128, 3 * sizeof(guint8) * 320 * 200);

  }
  catch(const Gio::ResourceError& ex)
  {
    //std::cerr << "ResourceError: " << ex.what() << std::endl;
  }
  catch(const Gdk::PixbufError& ex)
  {
    //std::cerr << "PixbufError: " << ex.what() << std::endl;
  }

  if (m_image) {
    set_size_request(m_image->get_width(), m_image->get_height());
  }
}

MyArea::~MyArea()
{
    if(shm_buf != NULL) {
        munmap(shm_buf, 320*200*3);
    }
    if(shm_fd > 0) {
        close(shm_fd);
        shm_unlink(SHARED_FB);
    }
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  if (!m_image)
    return false;

  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  // Draw the image in the middle of the drawing area, or (if the image is
  // larger than the drawing area) draw the middle part of the image.
  Gdk::Cairo::set_source_pixbuf(cr, m_image,
    (width - m_image->get_width())/2, (height - m_image->get_height())/2);
  cr->paint();

  return true;
}
