from layer import layer
import numpy as np

class Sigmoid(layer):
    
    def __init__(self):
        self.cache = None
        
    def forward(self, input_x):
        self.cache = input_x
        res = 1 / (1 + np.exp(input_x))
        return res
    
    def backward(self, dout):
        x = self.cache
        sigma = 1 / (1 + np.exp(x))
        ds = sigma * (1-sigma)
        return dout * ds