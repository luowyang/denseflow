#include "dense_flow.h"
#include "utils.h"

INITIALIZE_EASYLOGGINGPP

using namespace cv::cuda;

int main(int argc, char **argv) {
    try {
        const char *keys = {"{ v video     | video.mp4        | filename of video }"
                            "{ o outputDir | /path/to/outputs | root dir of output }"
                            "{ a algorithm | nv               | optical flow algorithm (nv/tvl1/farn/brox) }"
                            "{ s step      | 1                | right - left (0 for img, non-0 for flow) }"
                            "{ b bound     | 32               | maximum of optical flow }"
                            "{ w newWidth  | 0                | new width }"
                            "{ h newHeight | 0                | new height }"
                            "{ sh short    | 0                | short side length }"
                            "{ d deviceId  | 0                | set gpu id }"
                            "{ vv verbose  |                  | verbose }"
                            "{ help        |                  | print help message }"};

        CommandLineParser cmd(argc, argv, keys);
        string video_path = cmd.get<string>("video");
        string output_dir = cmd.get<string>("outputDir");
        string algorithm = cmd.get<string>("algorithm");
        int step = cmd.get<int>("step");
        int bound = cmd.get<int>("bound");
        int new_width = cmd.get<int>("newWidth");
        int new_height = cmd.get<int>("newHeight");
        int new_short = cmd.get<int>("short");
        int device_id = cmd.get<int>("deviceId");
        bool verbose = cmd.has("verbose");

        cmd.about("GPU optical flow extraction.");
        if (cmd.has("help") || !cmd.check()) {
            cmd.printMessage();
            cmd.printErrors();
            return 0;
        }

        calcDenseNvFlowVideoGPU(video_path, output_dir, algorithm, step, bound, new_width, new_height, new_short,
                                device_id, verbose);

    } catch (const std::exception &ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
