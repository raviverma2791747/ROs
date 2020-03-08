#ifndef __IMAGE_H
#define __IMAGE_H

#include <gui/widget.h>
#include <drivers/mouse.h>

namespace myos
{
    namespace gui
    {
class Image : public CompositeWidget
{
	 protected: 
	 common::uint8_t  *img;
	public:
	Image(Widget* parent,
                   common::int32_t x, common::int32_t y, common::int32_t w, common::int32_t h,
                   common::uint8_t r, common::uint8_t g, common::uint8_t b,common::uint8_t  *_img);
	~Image();	
	 void Draw(common::GraphicsContext* gc);
};
	}
}
#endif
