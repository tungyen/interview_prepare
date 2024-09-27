from layer import layer
import numpy as np


class Softmax(layer):
    def __init__(self):
        pass

    def forward(self, input_x: np.ndarray):
        v = input_x - np.max(input_x, axis=-1, keepdims=True)
        v = np.exp(v) / np.sum(np.exp(v), axis= 1, keepdims=True)
        assert v.shape == input_x.shape, "Scores must be NxC"
        return v

    def backward(self, dout):
        return dout
