
#ifndef BUTTERFLY_WALLPAPER_H
#define BUTTERFLY_WALLPAPER_H

#include <X11/Xlib.h>

namespace butterfly
{

class Wallpaper
{

private:
    char *fore_color = NULL;
    char *back_color = NULL;
public:
    Wallpaper();
    ~Wallpaper();

    void setBackgroundToBitmap(Pixmap bitmap, unsigned int width, unsigned int height);

};

}

#endif //BUTTERFLY_WALLPAPER_H
