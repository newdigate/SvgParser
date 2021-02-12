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

void
SvgOutput_ST7735::quadCurve(float delta, int p0x, int p0y, int p1x, int p1y, int p2x, int p2y, struct svgStyle_t *style) {
    if(style->stroke_color_set == UNSET) return;
    uint16_t color = convertColor(style->stroke_color);
    int x = p0x, y = p0y;
    DBG_OUT("QUAD: delta:%f \t p0.x:%d, p0.y:%d\t p1.x:%d, p1.y:%d \t p2.x:%d, p2.y:%d\n", delta, p0x, p0y, p1x, p1y, p2x, p2y);
    for( float i = 0.0f ; i < 1 ; i += delta )
    {
        // The Green Line
        int xa = getPt( p0x , p1x , i );
        int ya = getPt( p0y , p1y , i );
        int xb = getPt( p1x , p2x , i );
        int yb = getPt( p1y , p2y , i );

        // The Black Dot
        int x2 = getPt( xa , xb , i );
        int y2 = getPt( ya , yb , i );

        tft.drawLine( x, y, x2, y2, color );
        x = x2;
        y = y2;
    }
}

void SvgOutput_ST7735::quadCurve(float delta, int p0x, int p0y, int p1x, int p1y, int p2x, int p2y, int p3x, int p3y, struct svgStyle_t *style) {

    if(style->stroke_color_set == UNSET) return;
    uint16_t color = convertColor(style->stroke_color);

    int x = p0x, y = p0y;
    DBG_OUT("QUAD: delta: %f \t p0.x:%d, p0.y:%d \t p1.x:%d, p1.y:%d \t p2.x:%d, p2.y:%d \t p3.x:%d, p3.y:%d\n", delta, p0x, p0y, p1x, p1y, p2x, p2y, p3x, p3y);
    for( float i = delta ; i < 1 ; i += delta )
    {
        // The Green Lines
        int xa = getPt( p0x , p1x , i );
        int ya = getPt( p0y , p1y , i );
        int xb = getPt( p1x , p2x , i );
        int yb = getPt( p1y , p2y , i );
        int xc = getPt( p2x , p3x , i );
        int yc = getPt( p2y , p3y , i );

        // The Blue Line
        int xm = getPt( xa , xb , i );
        int ym = getPt( ya , yb , i );
        int xn = getPt( xb , xc , i );
        int yn = getPt( yb , yc , i );

        // The Black Dot
        int x2 = getPt( xm , xn , i );
        int y2 = getPt( ym , yn , i );

        tft.drawLine( x, y, x2, y2, color );
        x = x2;
        y = y2;
    }
}
