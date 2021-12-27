#ifdef ARDUINO_BOARD
    #include <Arduino.h>
    #include <pgmspace.h>
#else
    #include <stdint.h>
#endif



uint8_t get_bit(int x, int y, int w, int h, const uint8_t * image_data){
    int offset = (y * w + x);
    int data_offset = offset / 8;
    int bit_offset = offset % 8;
    int value = 1 << bit_offset;
    #ifdef ARDUINO_BOARD
        uint8_t mem_value = pgm_read_byte(image_data + data_offset);
    #else
        uint8_t mem_value = image_data[data_offset];
    #endif
    value = (mem_value & value) ? 0x0: 0XF;
    return value;
}

void load_img(int x, int y, int w, int h, const uint8_t * image_data, uint8_t * framebuffer, int screen_w, int screen_h){
    for (int xx = 0; xx < w; xx ++){
        for (int yy = 0; yy < h; yy ++){
            uint8_t val = get_bit(xx, yy, w, h, image_data);
            int byte_pos = (y + yy) * screen_w + x + xx;
            int fb_pos = byte_pos / 2;
            int fb_offs = byte_pos % 2;
            if (fb_offs){
                val = val << (fb_offs * 4);
            } 
            framebuffer[fb_pos] = framebuffer[fb_pos] ^ val;
        }
    }
}