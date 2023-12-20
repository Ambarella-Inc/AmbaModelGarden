## Data Preparation

Users are expected to only provide the dataset to run the training service. Users are advised to prepare the dataset in the format required by Ultralytics. [Train Custom Data](https://github.com/ultralytics/yolov5/wiki/Train-Custom-Data/81e78210c068140f06cf46127404efee770424b2) 

Here is a sample dataset.yaml file: 

    path: coco128
    train: images/train2017 # train images (relative to 'path')
    val: images/val2017 # val images (relative to 'path')

    # Classes
    nc: 80
    names:
    0: person
    1: bicycle
    2: car
    ...
    77: teddy bear
    78: hair drier
    79: toothbrush

The `names` can be a represented as a list of classes as well. 

    path: coco128
    train: images/train2017 # train images (relative to 'path')
    val: images/val2017 # val images (relative to 'path')

    # Classes
    nc: 80
    names: [ 'person', 'bicycle', 'car', .... ,'teddy bear', 'hair drier', 'toothbrush' ]


The dataset.yaml must be placed at the same root level as the dataset folder. The name of the dataset folder must be the same name as the value of the path. For example:

* Example 1 <br> 
    `VOC.yaml` <br> 
    `VOC/`

* Example 2 <br> 
    `coco128.yaml` <br> 
    `coco128/`

* Example 3 <br> 
    `VisDrone.yaml` <br> 
    `VisDrone/`