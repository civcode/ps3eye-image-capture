/** Small C++ wrapper around V4L example code to access the webcam
**/

#include <string>
#include <memory> // unique_ptr

struct buffer {
      void   *data;
      size_t  size;
};

struct RGBImage {
      unsigned char   *data; // RGB888 <=> RGB24
      size_t          width;
      size_t          height;
      size_t          size; // width * height * 3
};


class Webcam {

public:
    Webcam(const std::string& device = "/dev/video0", 
           int width = 320, 
           int height = 240,
           int fps = 30);

    ~Webcam();

    /** Captures and returns a frame from the webcam.
     *
     * The returned object contains a field 'data' with the image data in RGB888
     * format (ie, RGB24), as well as 'width', 'height' and 'size' (equal to
     * width * height * 3)
     *
     * This call blocks until a frame is available or until the provided
     * timeout (in seconds). 
     *
     * Throws a runtime_error if the timeout is reached.
     */
    const RGBImage& frame(int timeout = 5);

    const buffer& get_buffer(int timeout = 5);


private:
    void init_mmap();

    void open_device();
    void close_device();

    void init_device();
    void uninit_device();

    void start_capturing();
    void stop_capturing();

    bool read_frame();
    bool read_buffer(int &idx);

    void set_fps(int fps);

    std::string device;
    int fd;

    RGBImage rgb_frame;
    struct buffer          *buffers;
    unsigned int     n_buffers;

    size_t xres, yres;
    size_t stride;
    size_t fps;

    bool force_format = true;
};




