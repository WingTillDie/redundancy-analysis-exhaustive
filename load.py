#!/usr/bin/env python
import numpy as np
label=np.fromfile('label',sep=',')
points=np.fromfile('points', sep=',').reshape(len(label), -1)
