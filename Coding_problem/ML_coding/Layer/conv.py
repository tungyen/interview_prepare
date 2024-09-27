import numpy as np
from layer import layer

class Conv1D(layer):
    def __init__(self, in_channels, out_channels, kernel_size, stride=1, padding=0):
        self.in_channels = in_channels
        self.out_channels = out_channels
        self.kernel_size = kernel_size
        self.stride = stride
        self.padding = padding

        self.weights = np.random.randn(out_channels, in_channels, kernel_size)
        self.bias = np.random.randn(out_channels)

    def pad_input(self, x):
        if self.padding > 0:
            return np.pad(x, ((0, 0), (0, 0), (self.padding, self.padding)), mode='constant')
        return x
    
    def forward(self, x):
        batch_size, in_channels, input_length = x.shape
        output_length = int((input_length + 2 * self.padding - self.kernel_size) / self.stride + 1)
        x_padded = self.pad_input(x)
        output = np.zeros((batch_size, self.out_channels, output_length))

        for b in range(batch_size):
            for oc in range(self.out_channels):
                for i in range(0, output_length):
                    start = i * self.stride
                    end = start + self.kernel_size
                    for ic in range(in_channels):
                        output[b, oc, i] += np.sum(x_padded[b, ic, start:end] * self.weights[oc, ic, :])
                output[b, oc, :] += self.bias[oc]

        return output

    def backward(self, dout, x):
        B, in_channels, _ = x.shape
        _, _, output_length = dout.shape

        x_padded = self.pad_input(x)

        dx_padded = np.zeros_like(x_padded)
        dw = np.zeros_like(self.weights)
        db = np.zeros_like(self.bias)

        for b in range(B):
            for oc in range(self.out_channels):
                for i in range(output_length):
                    start = i * self.stride
                    end = start + self.kernel_size
                    db[oc] += np.sum(dout[b, oc, i])
                    for ic in range(in_channels):
                        dw[oc, ic, :] += dout[b, oc, i] * x_padded[b, ic, start:end]
                        dx_padded[b, ic, start:end] += dout[b, oc, i] * self.weights[oc, ic, :]

        if self.padding > 0:
            dx = dx_padded[:, :, self.padding:-self.padding]
        else:
            dx = dx_padded

        return dx, dw, db

