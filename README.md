# Final report branch

This is the version of the planner that I used to write the final report.

## Building

### Ubuntu 14.04
Clone this repository and checkout the `final-report` branch. Follow the build instructions from the roboticslibrary page [here](http://www.roboticslibrary.org/tutorials/build-ubuntu). The planner depends on functionality that is only implemented for the SOLID library yet, so be sure to install it as described on the roboticslibrary page. Also be sure to build in release mode for performance reasons (e.g. `cmake -DCMAKE_BUILD_TYPE=Release`).

### Windows 10
Building the roboticslibrary on Windows is painful due to several dependencies with more dependencies and so on. However it runs flawlessly on the Windows Subsystem for Linux (WSL). You can just follow the build instructions for Ubuntu from above. To run the experiments you need an X-Server for the UI. I use the free XMing Server ([download](https://sourceforge.net/projects/xming/)). In your WSL Bash run once in a session
```
export DISPLAY=:0
```
For a detailed information look at [this](https://www.howtogeek.com/261575/how-to-run-graphical-linux-desktop-applications-from-windows-10s-bash-shell/) post.


## Experiments

For the benchmarks in the report, the following experiments were run in release mode. Once the scene is loaded, hit `space` to start planning and `F12` to reset the planner.

### RRT-Connect 
```
./demos/rlPlanDemo/rlPlanDemo ../rl-examples-0.6.2/rlplan/box-2d-gripper_rrtCon.xml
```

### Connect-move-only uncertainty planner  
```
./demos/rlPlanDemo/rlPlanDemo ../rl-examples-0.6.2/rlplan/box-2d-gripper_connect-pcrrt.xml
```

### Full uncertainty planner
```
./demos/rlPlanDemo/rlPlanDemo ../rl-examples-0.6.2/rlplan/box-2d-gripper_pcrrt.xml
```

### POMDP full uncertainty planner
```
./demos/rlPlanDemo/rlPlanDemo ../rl-examples-0.6.2/rlplan/box-2d-gripper-pomdp_pcrrt.xml
```

## Architecture Overview

The main planner is implemented in `src/rl/plan/PcRrt.cpp` with some helper structures defined in `src/rl/plan/PcRrtExtensions.h`. To run the planner, we utilize the built-in demo `demos/rlPlanDemo/rlPlanDemo`. Extensions has been made to `demos/rlPlanDemo/MainWindow.cpp` to be able to select the planner and its arguments via XML tags in the scenario files. 

Furthermore, extensions needed to be made to the scene graph implementation to extract surface normals. This is just implemented for the SOLID library right now and the implementation resides in `src/rl/sg/solid/Scene.cpp`.

To simulate motion errors, a new model has been implemented in `src/rl/plan/NoisyModel.cpp`, which allows to interpolate noisy from one configuration to another. The noise parameters are also set via XML tags and are assigned to the model in `demos/rlPlanDemo/MainWindow.cpp`.
