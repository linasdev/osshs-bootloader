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

project_name = "osshs-bootloader"

SConscript('../SCons-common.py', src_dir = './', exports = [
    'project_name'
])
