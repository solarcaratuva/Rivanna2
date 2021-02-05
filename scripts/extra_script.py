# Adapted from https://github.com/KKoovalsky/PlatformIO-Helpers

from os import path
import sys

Import("env")

root_dir = env['PROJECT_DIR']

# sys.path.append(path.join(root_dir, 'scripts'))

import mbedignore
mbedignore_path = path.join(root_dir, '.mbedignore')
mbed_os_dir = path.join(env['PROJECT_PACKAGES_DIR'], 'framework-mbed')

# Does the job related to ignoring the paths. 
mbedignore.apply(mbedignore_path, mbed_os_dir)

mbed_os_dir = path.join(env['PROJECT_PACKAGES_DIR'], 'framework-mbed-latest')
mbedignore.apply(mbedignore_path, mbed_os_dir)