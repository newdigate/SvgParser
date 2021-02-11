#include "SvgOutput_st7735_t3.h"

void SvgOutput_ST7735::circle(short x, short y, short radius, struct svgStyle_t *style) {
    DBG_OUT("CIRCLE: x %i y %i radiuss %i stroke width: %i\n",x,y,radius,style->stroke_width);
    tft.drawCircle(x, y, radius, style->stroke_color);
    int16_t start=0, end; // radius is in middle of stroke

    if(style->stroke_color_set != UNSET && style->stroke_width) {
        uint16_t stroke_color = convertColor(style->stroke_color);

        start = style->stroke_width*style->x_scale/2;
        end = start;
        end += (style->stroke_width*style->x_scale -start -end);

        // check if this can be done by printing to filled circles
        if(style->fill_color_set == SET){
            start = style->stroke_width*style->x_scale;
            tft.fillCircle(x, y, radius+end, stroke_color);
        } else {

            DBG_OUT("start: %i end: %i\n",start,end);
            for(uint16_t i=radius-start; i<radius+end; i++)
                tft.drawCircle(x, y, i, stroke_color);
        }
    }

    // filled circle?
    if(style->fill_color_set == SET) {
        tft.fillCircle(x, y, radius-start, convertColor(style->fill_color));
    }
}

void SvgOutput_ST7735::rect(short x, short y, short width, short height, struct svgStyle_t *style) {
    DBG_OUT("RECT: x %i y %i width %i height %i\n",x,y,width, height);

    // filled rect?
    if(style->fill_color_set == SET) {
        tft.fillRect(x, y, width, height, convertColor(style->fill_color));
    }

    if(style->stroke_color_set != UNSET && style->stroke_width) {
        uint16_t stroke_color = convertColor(style->stroke_color);
        tft.drawRect(x, y, width, height, stroke_color);
    }
}

void SvgOutput_ST7735::text(short x, short y, char *text, struct svgStyle_t *style) {
    DBG_OUT("TEXT: x %i y %i size %i text \"%s\"\n", x, y, style->font_size, text);
    if(style->stroke_color_set == UNSET && style->fill_color_set == UNSET) return;

    tft.setTextColor(convertColor(style->stroke_color));
    tft.setTextSize(1);

    DBG_OUT("cur font height: %i\n",tft.getTextSizeY());
    uint8_t newHeight = round(style->font_size*style->y_scale/ tft.getTextSizeY());
    if(!newHeight) newHeight++;
    DBG_OUT("height factor: %i\n",newHeight);

    tft.setTextSize(newHeight);

    tft.setTextDatum(BL_DATUM);
    tft.drawString(text, x, y + (style->font_size*style->y_scale - tft.getTextSizeY())/2);

}

void SvgOutput_ST7735::path(unsigned short *data, unsigned short len, struct svgStyle_t *style) {
    if(len<2) return;
    if(style->stroke_color_set == UNSET) return;
    uint16_t color = convertColor(style->stroke_color);

    for(uint16_t i = 1; i<len; i++)
        tft.drawLine(data[(i-1)*2], data[(i-1)*2+1], data[i*2], data[i*2 + 1], color);

    DBG_OUT("PATH: len: %i \n",len);
}
