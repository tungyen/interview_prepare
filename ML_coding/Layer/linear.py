from layer import layer
import numpy as np

class Linear(layer):
    """Linear Neural Network layers"""

    def __init__(self, input_dims: int, output_dims: int):
        self.w = np.random.rand(input_dims, output_dims) * 0.0001
        self.b = np.random.rand(output_dims) * 0.0001
        self.dw = None
        self.db = None
        self.cache = None

    def forward(self, input_x: np.ndarray):
        res = input_x @ self.w + self.b
        self.cache = [input_x.copy(), self.w.copy(), self.b.copy()]
        return res

    def backward(self, dout):
        temp_x, temp_w, _ = self.cache
        dx = dout @ temp_w.T
        self.dw = temp_x.T @ dout 
        self.db = np.sum(dout, axis = 0) # Summation along the first axis
        return dx

    def zero_grad(self):
        self.dw = None
        self.db = None

    @property
    def parameters(self):
        return [self.w, self.b]

    @property
    def grads(self):
        return [self.dw, self.db]
