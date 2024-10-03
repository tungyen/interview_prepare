from layer import layer
import numpy as np

class GELU(layer):
    def __init__(self, inplace=True):
        self.cache = None
        self.inplace = inplace

    def forward(self, input_x: np.ndarray):
        # GELU approximation
        res = 0.5 * input_x * (1 + np.tanh(np.sqrt(2 / np.pi) * (input_x + 0.044715 * input_x ** 3)))
        if self.inplace:
            self.cache = res.copy()
        else:
            self.cache = input_x.copy()
        return res

    def backward(self, dout):
        x_temp = self.cache
        cdf = 0.5 * (1 + np.tanh(np.sqrt(2 / np.pi) * (x_temp + 0.044715 * x_temp ** 3)))
        pdf = np.exp(-0.5 * x_temp ** 2) / np.sqrt(2 * np.pi)
        dgelu_dx = cdf + x_temp * pdf
        dx = dgelu_dx * dout
        return dx
