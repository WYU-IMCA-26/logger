python3 src/log1/adminpy/adminpy.py src/log1/admin/admin.yaml src/log1/include/log1/admin.h
source install/setup.bash
# python3 src/log1/adminpy/adminpy.py src/log1/admin/admin.yaml src/log1/src/admin.h
colcon build --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=Release
ros2 run log1 main