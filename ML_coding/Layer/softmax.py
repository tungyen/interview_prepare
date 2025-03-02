from layer import layer
import numpy as np


class Softmax(layer):
    def __init__(self):
        pass

    def forward(self, input_x: np.ndarray):
        v = input_x - np.max(input_x, axis=-1, keepdims=True)
        v = np.exp(v) / np.sum(np.exp(v), axis= 1, keepdims=True)
        assert v.shape == input_x.shape, "Scores must be NxC"
        self.v = v
        return v

    def backward(self, dout):
        res = []
        for i in range(dout.shape[0]):
            softmax_grad = np.diag(self.v[i]) - np.outer(self.v[i], self.v[i])
            res.append(np.dot(softmax_grad, dout[i].T))
        res = np.array(res)
        return res
