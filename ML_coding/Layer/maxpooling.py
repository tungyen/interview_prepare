from layer import layer
import numpy as np

class MaxPooling1d(layer):
    
    def __init__(self, kernel_size=2, stride=2, padding=None):
        self.kernel_size = kernel_size
        self.stride = stride
        self.padding = padding
        
    def forward(self, input_x):
        (n, c, l) = input_x.shape
        self.input = input_x
        
        # Handle the padding argument
        if self.padding is not None:
            input_x = np.pad(input, ((0, 0), (0, 0), (self.padding, self.padding)), mode='constant', constant_values=(float('-inf'),))
        self.padded_input = input_x
        pool_length = (l + 2 * self.padding - self.kernel_size) // self.stride + 1
        
        
        shape = (n, c, pool_length, self.kernel_size)
        strides = (input.strides[0], input.strides[1], input.strides[2] * self.stride, input.strides[2])
        windows = np.lib.stride_tricks.as_strided(input, shape=shape, strides=strides)
        self.argmax_indices = np.argmax(windows, axis=3)
        output = np.max(windows, axis=3)
        return output
        
    def backward(self, dout):
        d_input_padded = np.zeros_like(self.padded_input)
        batch_size, channels, input_length = self.padded_input.shape
        output_length = dout.shape[2]

        shape = (batch_size, channels, output_length, self.kernel_size)
        strides = (self.padded_input.strides[0], self.padded_input.strides[1], self.padded_input.strides[2] * self.stride, self.padded_input.strides[2])
        windows = np.lib.stride_tricks.as_strided(self.padded_input, shape=shape, strides=strides)

        window_indices = np.arange(self.kernel_size)
        max_indices = (window_indices == self.argmax_indices[..., None])

        d_input_windowed = np.zeros_like(windows)
        d_input_windowed[max_indices] = dout[..., None]

        for i in range(self.kernel_size):
            d_input_padded[:, :, i::self.stride] += d_input_windowed[:, :, :, i]

        if self.padding > 0:
            d_input = d_input_padded[:, :, self.padding:-self.padding]
        else:
            d_input = d_input_padded

        return d_input
    
class MaxPool2d(layer):
    
    def __init__(self, kernel_size, stride=2, padding=None):
        self.kernel_size = kernel_size if isinstance(kernel_size, tuple) else (kernel_size, kernel_size)
        self.stride = stride if isinstance(stride, tuple) else (stride, stride)
        self.padding = padding if isinstance(padding, tuple) else (padding, padding)

    def forward(self, input):

        B, C, H, W = input.shape
        if self.padding != (0, 0):
            input = np.pad(input, ((0, 0), (0, 0), (self.padding[0], self.padding[0]), (self.padding[1], self.padding[1])), mode='constant', constant_values=(float('-inf'),))
        self.padded_input = input

        output_height = (H + 2 * self.padding[0] - self.kernel_size[0]) // self.stride[0] + 1
        output_width = (W + 2 * self.padding[1] - self.kernel_size[1]) // self.stride[1] + 1

        shape = (B, C, output_height, output_width, self.kernel_size[0], self.kernel_size[1])
        strides = (input.strides[0], input.strides[1], input.strides[2] * self.stride[0], input.strides[3] * self.stride[1], input.strides[2], input.strides[3])
        windows = np.lib.stride_tricks.as_strided(input, shape=shape, strides=strides)

        self.argmax_indices = np.argmax(windows.reshape(B, C, output_height, output_width, -1), axis=-1)
        output = np.max(windows, axis=(4, 5))
        return output

    def backward(self, d_output):

        d_input_padded = np.zeros_like(self.padded_input)
        B, C, _, _ = self.padded_input.shape
        output_height, output_width = d_output.shape[2], d_output.shape[3]

        shape = (B, C, output_height, output_width, self.kernel_size[0], self.kernel_size[1])
        strides = (self.padded_input.strides[0], self.padded_input.strides[1], self.padded_input.strides[2] * self.stride[0], self.padded_input.strides[3] * self.stride[1], self.padded_input.strides[2], self.padded_input.strides[3])
        windows = np.lib.stride_tricks.as_strided(self.padded_input, shape=shape, strides=strides)

        window_indices = np.arange(self.kernel_size[0] * self.kernel_size[1])
        max_indices = (window_indices == self.argmax_indices[..., None])

        d_input_windowed = np.zeros_like(windows)
        d_input_windowed[max_indices] = d_output[..., None]

        for i in range(self.kernel_size[0]):
            for j in range(self.kernel_size[1]):
                d_input_padded[:, :, i::self.stride[0], j::self.stride[1]] += d_input_windowed[:, :, :, :, i, j]

        if self.padding != (0, 0):
            d_input = d_input_padded[:, :, self.padding[0]:-self.padding[0], self.padding[1]:-self.padding[1]]
        else:
            d_input = d_input_padded

        return d_input
