#ifndef _SVG_OUTPUT_ST7735_H_
#define _SVG_OUTPUT_ST7735_H_

#include "SvgParser.h"
#include <ST7735_t3.h>

class SvgOutput_ST7735 : public SvgOutput
{   
public:
    SvgOutput_ST7735(ST7735_t3 &atft) : tft(atft) {};
    

    virtual void circle(int16_t x, int16_t y, int16_t radius, struct svgStyle_t * style);

    virtual void rect(int16_t x, int16_t y, int16_t width, int16_t height, struct svgStyle_t * style);
    virtual void text(int16_t x, int16_t y, char * text, struct svgStyle_t * style);
    
    virtual void path(uint16_t *data, uint16_t len, struct svgStyle_t * style);

    inline uint16_t color565(uint8_t r, uint8_t g, uint8_t b) {
        return ((b & 0xF8) << 8) | ((g & 0xFC) << 3) | (r >> 3);
    }

    virtual void quadCurve(float delta, float p0x, float p0y, float p1x, float p1y, float p2x, float p2y, struct svgStyle_t * style);

    virtual void quadCurve(float delta, float p0x, float p0y, float p1x, float p1y, float p2x, float p2y, float p3x, float p3y, struct svgStyle_t * style);
private:
    ST7735_t3 &tft;
    uint16_t convertColor(uint32_t color){
        return color565((color & 0x00FF0000) >> 16, (color & 0x0000FF00) >> 8, color & 0x000000FF);
    }

    static float getPt( float n1 , float n2 , float perc )
    {
        float diff = n2 - n1;

        return n1 + ( diff * perc );
    }

};

#endif