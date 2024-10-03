from layer import layer
import numpy as np

class LeakyReLU(layer):
    def __init__(self, alpha=0.01, inplace=True):
        self.cache = None
        self.alpha = alpha  # Slope for negative values
        self.inplace = inplace

    def forward(self, input_x: np.ndarray):
        res = np.where(input_x > 0, input_x, input_x * self.alpha)
        if self.inplace:
            self.cache = res.copy()
        else:
            self.cache = input_x.copy()
        return res

    def backward(self, dout):
        x_temp = self.cache
        dx = np.where(x_temp > 0, dout, dout * self.alpha)
        return dx
