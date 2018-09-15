#!/usr/bin/env python
import numpy as np
label=np.fromfile('label',sep=',')[5:]
points=np.fromfile('points', sep=',')[3:].reshape(len(label), -1)
