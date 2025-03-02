import numpy as np
from layer import layer

class BatchNormalization(layer):
    def __init__(self, num_features, epsilon=1e-5, momentum=0.9):
        self.gamma = np.ones((1, num_features))
        self.beta = np.zeros((1, num_features))
        self.epsilon = epsilon
        self.momentum = momentum
        self.cache = None

        self.running_mean = np.zeros((1, num_features))
        self.running_var = np.ones((1, num_features))

    def forward(self, x, training=True):
        self.cache = x
        if training:
            batch_mean = np.mean(x, axis=0)
            batch_var = np.var(x, axis=0)

            x_hat = (x - batch_mean) / np.sqrt(batch_var + self.epsilon)
            self.running_mean = self.momentum * self.running_mean + (1 - self.momentum) * batch_mean
            self.running_var = self.momentum * self.running_var + (1 - self.momentum) * batch_var
        else:
            x_hat = (x - self.running_mean) / np.sqrt(self.running_var + self.epsilon)

        out = self.gamma * x_hat + self.beta
        return out

    def backward(self, dout):
        x = self.cache
        N, D = x.shape

        batch_mean = np.mean(x, axis=0)
        batch_var = np.var(x, axis=0)

        x_hat = (x - batch_mean) / np.sqrt(batch_var + self.epsilon)
        dgamma = np.sum(dout * x_hat, axis=0)
        dbeta = np.sum(dout, axis=0)

        dx_hat = dout * self.gamma
        dvar = np.sum(dx_hat * (x - batch_mean) * -0.5 * (batch_var + self.epsilon)**-1.5, axis=0)
        dmean = np.sum(dx_hat * -1 / np.sqrt(batch_var + self.epsilon), axis=0) + dvar * np.mean(-2 * (x - batch_mean), axis=0)
        dx = dx_hat / np.sqrt(batch_var + self.epsilon) + dvar * 2 * (x - batch_mean) / N + dmean / N

        return dx, dgamma, dbeta

