# Copyright (c) 2017-2018, Niklas Hauser
# Copyright (c) 2019, Linas Nikiperavicius
#
# This file is part of the modm project.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

#!/usr/bin/env python3

import os
from os.path import join, abspath

project_name = 'osshs-bootloader'

build_path = './build/' + project_name
profile = ARGUMENTS.get('profile', 'debug')

generated_paths = [
    'modm'
]

CacheDir('./build/cache')

env = DefaultEnvironment(tools=[], ENV=os.environ)

env['CONFIG_BUILD_BASE'] = abspath(build_path)
env['CONFIG_PROJECT_NAME'] = project_name
env['CONFIG_PROFILE'] = profile

env.SConscript(dirs=generated_paths, exports='env')

ignored = ['cmake-*', '.lbuild_cache', build_path] + generated_paths
sources = []

sources += env.FindSourceFiles('./src', ignorePaths=ignored)
sources += env.FindSourceFiles('./ext/osshs-protocol/src', ignorePaths=ignored)

env.Append(CPPPATH = [
    './include',
    './ext/magic_enum/include',
    './ext/osshs-protocol/include'
])

env.Append(CCFLAGS = [
    '-fno-exceptions'
])

if profile == 'debug':
    env.Append(CCFLAGS = [
        '-O0'
    ])

if profile == 'release':
    env.Append(CCFLAGS = [
        '-DDISABLE_LOGGING'
    ])

env.BuildTarget(sources)
