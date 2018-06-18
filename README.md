# Focus-stacking algorithm implementation

This is implementation of focus-stacking algorithm, which the main purpose is to merge multiply photos, taken with different focus, into color and sharp image.
This project creates also estimated depth map, based on the same images.

### Prerequisites

* OpenCV3 only for image reading, showing and writing.
* cmake

### Installing

Download and compile the code:
```
git clone https://github.com/wojtasso/focus-stacking.git
cd focus-stacking
cmake .
make
```

To launch the program execute:
```
./focus
```

The application takes photos from folder `images`.
In this example, photos are taken from [here](http://grail.cs.washington.edu/projects/photomontage/data/bug.zip)

### Results

* sharp image in `focused.png`
* depth map in `depth.png`
* gif produced by [depthy.me](http://depthy.me) in `focused.gif`

