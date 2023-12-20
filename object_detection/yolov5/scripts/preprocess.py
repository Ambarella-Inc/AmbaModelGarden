import argparse
import os
import sys
import numpy as np
import time
from pathlib import Path

FILE = Path(__file__).resolve()
ROOT = FILE.parents[0]  # YOLOv5 root directory
if str(ROOT) not in sys.path:
    sys.path.append(str(ROOT))  # add ROOT to PATH
ROOT = Path(os.path.relpath(ROOT, Path.cwd()))  # relative

from utils.general import LOGGER, print_args, RGB2YUV420, increment_path
from utils.dataloaders import IMG_FORMATS, LoadImages, letterbox

def run(
        source=ROOT / 'data/images',  # file/dir/URL/glob, 0 for webcam
        imgsz=(640, 640),  # inference size (height, width)
        project=ROOT / 'runs/preprocess',  # save results to project/name
        name='exp',  # save results to project/name
        exist_ok=False,  # existing project/name ok, do not increment        
):    

    if type(source) == np.ndarray:
        LOGGER.info("Received ndarry of shape {}".format(source.shape))
        img = letterbox(source, imgsz, auto=False)[0] # Preprocess ndarr
        img = img[:,:,::-1] # Convert to RGB
        y, uv = RGB2YUV420(img)
        uv = uv.reshape((1,2,imgsz[0]//2,imgsz[1]//2))
        LOGGER.info("Generate Y and UV ndarrays of shape {} and {}".format(y.shape, uv.shape))
        return y, uv
    else:
        source = str(source)    
        # Directories
        save_dir = increment_path(Path(project) / name, exist_ok=exist_ok)  # increment run
        (save_dir).mkdir(parents=True, exist_ok=True)  # make dir

        # Create dataset object
        dataset = LoadImages(source, img_size=imgsz, auto=False)
        
        # For every image in the source, convert image to RGB, run the letterbox preprocess, convert to Y and UV and finally save as .bin

        y_fname = save_dir / 'images_y.txt'
        uv_fname = save_dir / 'images_uv.txt'

        with y_fname.open('a') as yf:
            with uv_fname.open('a') as uvf:
                for p, im, _, _, _ in dataset:     
                    p = Path(p)
                    LOGGER.info("Applying preprocessing to {}".format(p))

                    # Transpose to HWC
                    im = np.transpose(im, (1,2,0))
                    
                    # Convert to Y (YYYY) and UV (UVUVUVUV)  interleave. 
                    y, uv = RGB2YUV420(im)
                    uv = uv.reshape((1,2,imgsz[0]//2,imgsz[1]//2))
                    
                    # Bin file names
                    y_bin_fname = save_dir / (p.name.split(".")[0] + '_y.bin')
                    uv_bin_fname = save_dir / (p.name.split(".")[0] + '_uv.bin')

                    # Save binaries
                    y.tofile(y_bin_fname)
                    uv.tofile(uv_bin_fname)
                    
                    # Write to .txt file
                    yf.write(str(y_bin_fname.name))
                    uvf.write(str(uv_bin_fname.name))
        
        LOGGER.info("\n** Preprocessing done. Please find the files under {}**".format(save_dir))
        return str(y_fname), str(uv_fname)


def parse_opt():
    parser = argparse.ArgumentParser()
    parser.add_argument('--source', type=str, default=ROOT / 'data/images', help='file/dir/URL/glob, 0 for webcam')
    parser.add_argument('--imgsz', '--img', '--img-size', nargs='+', type=int, default=[640], help='inference size h,w')
    parser.add_argument('--project', default=ROOT / 'runs/preprocess', help='save results to project/name')
    parser.add_argument('--name', default='exp', help='save results to project/name')
    parser.add_argument('--exist-ok', action='store_true', help='existing project/name ok, do not increment')
    opt = parser.parse_args()
    opt.imgsz *= 2 if len(opt.imgsz) == 1 else 1  # expand
    print_args(vars(opt))
    return opt


def main(opt):
    run(**vars(opt))


if __name__ == "__main__":
    opt = parse_opt()
    main(opt)
