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

The following experiments were run for the benchmarks in Release build mode.

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
