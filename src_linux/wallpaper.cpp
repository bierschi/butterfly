
#include "wallpaper.h"

namespace butterfly
{

Wallpaper::Wallpaper()
{

}

void Wallpaper::setBackgroundToBitmap(Pixmap bitmap, unsigned int width, unsigned int height)
{
    Pixmap pix;
    GC gc;
    XGCValues gc_init;

    gc_init.foreground = NameToPixel(fore_color, BlackPixel(dpy, screen));
    gc_init.background = NameToPixel(back_color, WhitePixel(dpy, screen));
    if (reverse) {
        unsigned long temp=gc_init.foreground;
        gc_init.foreground=gc_init.background;
        gc_init.background=temp;
    }
    gc = XCreateGC(dpy, root, GCForeground|GCBackground, &gc_init);
    pix = XCreatePixmap(dpy, root, width, height,
                        (unsigned int)DefaultDepth(dpy, screen));
    XCopyPlane(dpy, bitmap, pix, gc, 0, 0, width, height, 0, 0, (unsigned long)1);
    XSetWindowBackgroundPixmap(dpy, root, pix);
    XFreeGC(dpy, gc);
    XFreePixmap(dpy, bitmap);
    if (save_colors)
        save_pixmap = pix;
    else
        XFreePixmap(dpy, pix);
    XClearWindow(dpy, root);
    unsave_past = 1;
}

} // namespace butterfly