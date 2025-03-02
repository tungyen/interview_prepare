from layer import layer
import numpy as np


class CrossEntropyLoss(layer):
    def __init__(self):
        self.cache = None
        pass

    def forward(self, input_x: np.ndarray, target_y: np.ndarray):
        N, _ = input_x.shape
        labels = np.zeros((target_y.shape[0], np.amax(target_y)+1))
        labels[np.arange(target_y.shape[0]), target_y] = 1
        totalLoss = np.sum(-np.log(np.sum(labels * input_x, axis = 1)))
        loss = totalLoss / N
        self.cache = [loss.copy(), input_x.copy(), target_y.copy()]
        return loss

    def backward(self):
        _, x_temp, y_temp = self.cache
        N = x_temp.shape[0]
        labels = np.zeros((y_temp.shape[0], np.amax(y_temp)+1))
        labels[np.arange(y_temp.shape[0]), y_temp] = 1
        dx = x_temp - labels
        assert x_temp.shape == dx.shape, "Mismatch in shape"
        dx /= N
        return dx

    def zero_grad(self):
        pass
