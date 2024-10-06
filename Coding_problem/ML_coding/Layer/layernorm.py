import numpy as np

class LayerNormalization:
    def __init__(self, num_features, epsilon=1e-5):
        self.gamma = np.ones((1, num_features))
        self.beta = np.zeros((1, num_features))
        self.epsilon = epsilon

    def forward(self, x):
        self.N, self.D = x.shape
        self.mean = np.mean(x, axis=1, keepdims=True)  # Shape: (N, 1)
        self.var = np.var(x, axis=1, keepdims=True)    # Shape: (N, 1)
        self.x_hat = (x - self.mean) / np.sqrt(self.var + self.epsilon)  # Shape: (N, D)
        out = self.gamma * self.x_hat + self.beta  # Shape: (N, D)
        return out

    def backward(self, dout):
        dgamma = np.sum(dout * self.x_hat, axis=0, keepdims=True)  # Shape: (1, D)
        dbeta = np.sum(dout, axis=0, keepdims=True)                # Shape: (1, D)

        dx_hat = dout * self.gamma  # Shape: (N, D)
        std_inv = 1. / np.sqrt(self.var + self.epsilon)  # Shape: (N, 1)

        dx = (1. / self.D) * std_inv * (self.D * dx_hat - np.sum(dx_hat, axis=1, keepdims=True)
                                        - self.x_hat * np.sum(dx_hat * self.x_hat, axis=1, keepdims=True))

        return dx, dgamma, dbeta