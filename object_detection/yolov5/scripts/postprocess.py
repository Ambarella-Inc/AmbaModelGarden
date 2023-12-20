import argparse
import numpy as np
import cv2
import yaml
import os,sys
from pathlib import Path
from utils.plots import Annotator, colors
from utils.general import scale_coords, print_args, increment_path, non_max_suppression, prepare_predictions, LOGGER
from utils.dataloaders import LoadImages

FILE = Path(__file__).resolve()
ROOT = FILE.parents[0]  # YOLOv5 root directory
if str(ROOT) not in sys.path:
    sys.path.append(str(ROOT))  # add ROOT to PATH
ROOT = Path(os.path.relpath(ROOT, Path.cwd()))  # relative

def run(
        source,  # Image .jpg source to draw detected boxes on.
        detection_output, # Path to .npy or .bin after running forward pass on the model.
        imgsz=(640, 640),  # inference size (height, width)
        data=ROOT / 'data/coco128.yaml',  # dataset.yaml path
        project=ROOT / 'runs/postprocess',  # save results to project/name
        name='exp',  # save results to project/name
        exist_ok=False,  # existing project/name ok, do not increment
        max_det=300, # Maximum number of detection boxes
        line_thickness=3,  # bounding box thickness (pixels)
        hide_labels=False,  # hide labels
        hide_conf=False,  # hide confidences
        conf_thres=0.25,  # confidence threshold
        iou_thres=0.45,  # NMS IOU threshold
        run_nms=False, # Run NMS algo on the model predictions
):

    save_dir = increment_path(Path(project) / name, exist_ok=exist_ok)  # increment run
    (save_dir).mkdir(parents=True, exist_ok=True)  # make dir

    # Read .npy or .bin file or .json file
    if run_nms:
        pred = prepare_predictions(detection_output, dtype='float16')
    else:
        pred = prepare_predictions(detection_output, dtype='float32', max_boxes=max_det)

    # Read the dataset yaml
    with open(data, errors='ignore') as f:
        d = yaml.safe_load(f)
        names, nc = d['names'], d['nc']
    
    # Create a dataset object
    dataset = LoadImages(source, img_size=imgsz, auto=False)

    for path, img, img0, _, _ in dataset:

        LOGGER.info("\nWorking on image {}".format(path))

        img = np.expand_dims(img, 0)

        
        if run_nms:
            pred = non_max_suppression(pred, conf_thres, iou_thres, max_det=max_det, nc=nc)
            pred = pred[0]
        
        # Prepare the prediction output
        pred = np.squeeze(pred)
        if len(pred.shape) == 1:
            pred = np.expand_dims(pred, 0)
        else:
            pred = pred[np.where(pred.any(axis=1))[0]]

        # Create annotator object
        annotator = Annotator(img0, line_width=line_thickness, example=str(names))

        # Rescale boxes from img_size to im0 size
        pred[:, :4] = scale_coords(img.shape[2:], pred[:, :4], img0.shape).round()
        
        # Write results
        for *xyxy, conf, cls in reversed(pred):
            c = int(cls)  # integer class
            label = None if hide_labels else (names[c] if hide_conf else f'{names[c]} {conf:.2f}')
            annotator.box_label(xyxy, label, color=colors(c, True))
        im0 = annotator.result()

        # Save to disk
        p = Path(source)
        save_path = str(save_dir / p.name)  # im.jpg    
        cv2.imwrite(save_path, im0)

    LOGGER.info("\n** Postprocessing done. Please find the files under {}**".format(save_dir))
    return save_path

def parse_opt():
    parser = argparse.ArgumentParser()
    parser.add_argument('--detection-output', type=str, help='Path to model output file')
    parser.add_argument('--source', type=str, help='Input image file')
    parser.add_argument('--data', type=str, help='dataset.yaml path')
    parser.add_argument('--project', default=ROOT / 'runs/postprocess', help='save results to project/name')
    parser.add_argument('--name', default='exp', help='save results to project/name')
    parser.add_argument('--exist-ok', action='store_true', help='existing project/name ok, do not increment')
    parser.add_argument('--imgsz', '--img', '--img-size', type=int, default=640, help='inference size h,w')
    parser.add_argument('--max-det', default=300, type=int, help='maximum number of boxes to be detected. For .bin input, this is required to reshape to [B,6]')
    parser.add_argument('--line-thickness', default=3, type=int, help='bounding box thickness (pixels)')
    parser.add_argument('--hide-labels', default=False, action='store_true', help='hide labels')
    parser.add_argument('--hide-conf', default=False, action='store_true', help='hide confidences')
    parser.add_argument('--conf-thres', type=float, default=0.25, help='confidence threshold')
    parser.add_argument('--iou-thres', type=float, default=0.45, help='NMS IoU threshold') 
    parser.add_argument('--run-nms', action='store_true', help='Run NMS algorithm on the model predictions.')
    opt = parser.parse_args()
    print_args(vars(opt))
    return opt
    
def main(opt):    
    run(**vars(opt))

if __name__ == "__main__":
    opt = parse_opt()
    main(opt)        