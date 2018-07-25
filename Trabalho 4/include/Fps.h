#ifndef FPS_H
#define FPS_H

#include <time.h>

class Fps {
    public:
        clock_t t1, t2;
        long    cont_frames;
        float   fps, fps_old;
        Fps();
        float getFrames();
        virtual ~Fps();
    protected:
    private:
};

#endif // FPS_H
