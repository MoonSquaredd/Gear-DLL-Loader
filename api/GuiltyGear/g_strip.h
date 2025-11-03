#ifndef g_strip
#define g_strip

typedef struct {
    int sprno;
    float x;
    float y;
    float z;
    float zm_x; //horizontal scale
    float zm_y; //vertical scale
    float u0;
    float v0;
    float u1;
    float v1;
    int ang;
    float trnsl;
    short listType;
    short attr;
    int base_color;
    int offset_color;
    int sizex;
    int sizey;
    long tex;
} NL_SPR_ARG;

void gSpriteDraw_NaomiLibVersion(NL_SPR_ARG *,int);

#endif
