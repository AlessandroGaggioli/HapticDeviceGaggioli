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

echo_and_run cd "/home/student/HapticDeviceGaggioli/haptic_ws/src/panda_simulator/panda_sim_custom_action_server"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/student/HapticDeviceGaggioli/haptic_ws/install/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/student/HapticDeviceGaggioli/haptic_ws/install/lib/python3/dist-packages:/home/student/HapticDeviceGaggioli/haptic_ws/build/panda_sim_custom_action_server/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/student/HapticDeviceGaggioli/haptic_ws/build/panda_sim_custom_action_server" \
    "/usr/bin/python3" \
    "/home/student/HapticDeviceGaggioli/haptic_ws/src/panda_simulator/panda_sim_custom_action_server/setup.py" \
     \
    build --build-base "/home/student/HapticDeviceGaggioli/haptic_ws/build/panda_sim_custom_action_server" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/student/HapticDeviceGaggioli/haptic_ws/install" --install-scripts="/home/student/HapticDeviceGaggioli/haptic_ws/install/bin"
