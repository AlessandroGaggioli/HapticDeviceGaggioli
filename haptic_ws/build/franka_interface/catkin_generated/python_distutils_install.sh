#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/student/HapticDeviceGaggioli/haptic_ws/src/franka_ros_interface/franka_interface"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/student/HapticDeviceGaggioli/haptic_ws/install/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/student/HapticDeviceGaggioli/haptic_ws/install/lib/python3/dist-packages:/home/student/HapticDeviceGaggioli/haptic_ws/build/franka_interface/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/student/HapticDeviceGaggioli/haptic_ws/build/franka_interface" \
    "/usr/bin/python3" \
    "/home/student/HapticDeviceGaggioli/haptic_ws/src/franka_ros_interface/franka_interface/setup.py" \
     \
    build --build-base "/home/student/HapticDeviceGaggioli/haptic_ws/build/franka_interface" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/student/HapticDeviceGaggioli/haptic_ws/install" --install-scripts="/home/student/HapticDeviceGaggioli/haptic_ws/install/bin"
