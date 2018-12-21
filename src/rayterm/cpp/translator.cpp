# include "terminal.hpp"

Vec2 window_to_pixel(float x, float y) {
    Vec2 n = Vec2();
    Vec2 sizes = get_main_size();
    n.x = x * sizes.x;
    n.y = y * sizes.y;

    return n;
}

void* sample_at(float x, float y) {
    
}

void render() {
    Vec2 sizes = get_main_size();
    for(float x = 0; x < 1; x += 1.0 / sizes.x) {
        for(float y = 0; y < 1; y += 0.5 / sizes.y) {
            Vec2 pos = window_to_pixel(x, y);
	    fprintf(stderr, "x:%d, y:%d\n", pos.x, pos.y);
	}
    }

}
