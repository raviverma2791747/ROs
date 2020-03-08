#include<gui/image.h>

using namespace myos::common;
using namespace myos::gui;

Image::Image(Widget* parent,
            common::int32_t x, common::int32_t y, common::int32_t w, common::int32_t h,
            common::uint8_t r, common::uint8_t g, common::uint8_t b,common::uint8_t  *_img)
: CompositeWidget(parent, x,y,w,h, r,g,b)
{
	img = _img;
}

Image::~Image()
{
}

void Image::Draw(common::GraphicsContext* gc)
{
	//CompositeWidget::Draw(gc); //we don't need to draw the base classes window 
	for(int i=0;i<x;i++)
	{
		for(int j=0;j<y;j++)
		{
		gc->PutPixel(x+ i,y + j,*(img+ i + j));
		}
	}
}