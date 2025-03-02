from layer import layer
import numpy as np


class ReLU(layer):
    def __init__(self, inplace = True):
        self.cache = None
        self.inplace = inplace

    def forward(self, input_x: np.ndarray):
        res = np.maximum(input_x , 0)
        if self.inplace:
            self.cache = res.copy()
        else:
            self.cache = input_x.copy()
        return res

    def backward(self, dout):
        x_temp = self.cache
        dx = np.where(x_temp < 0, 0 , dout)
        return dx
