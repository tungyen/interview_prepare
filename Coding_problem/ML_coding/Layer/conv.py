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
    

class Conv2D_Numpy:
    def __init__(self, in_channels, out_channels, kernel_size, stride=1, padding=0):
        """
        Initialize the Conv2D layer.
        :param in_channels: Number of input channels
        :param out_channels: Number of output channels
        :param kernel_size: Size of the convolution kernel (tuple or int)
        :param stride: Stride of the convolution
        :param padding: Padding around the input image
        """
        self.in_channels = in_channels
        self.out_channels = out_channels
        self.kernel_size = kernel_size if isinstance(kernel_size, tuple) else (kernel_size, kernel_size)
        self.stride = stride
        self.padding = padding
        
        # Initialize weights and bias
        self.weight = np.random.randn(out_channels, in_channels, *self.kernel_size) * 0.01
        self.bias = np.zeros(out_channels)

    def im2col(self, input_data, filter_height, filter_width, stride=1, padding=0):
        """
        Transform input image into column matrix for matrix multiplication.
        """
        batch_size, in_channels, input_height, input_width = input_data.shape

        # Compute output dimensions
        out_height = (input_height + 2 * padding - filter_height) // stride + 1
        out_width = (input_width + 2 * padding - filter_width) // stride + 1

        # Pad input image
        padded_data = np.pad(input_data, ((0, 0), (0, 0), (padding, padding), (padding, padding)), mode='constant')

        # Create a column matrix
        col = np.zeros((batch_size, in_channels, filter_height, filter_width, out_height, out_width))

        for y in range(filter_height):
            y_max = y + stride * out_height
            for x in range(filter_width):
                x_max = x + stride * out_width
                col[:, :, y, x, :, :] = padded_data[:, :, y:y_max:stride, x:x_max:stride]

        # Reshape to (batch_size * out_height * out_width, in_channels * filter_height * filter_width)
        col = col.transpose(0, 4, 5, 1, 2, 3).reshape(batch_size * out_height * out_width, -1)
        
        return col

    def forward(self, x):
        """
        Forward pass using im2col and matrix multiplication.
        :param x: Input array (batch_size, in_channels, height, width)
        :return: Output array after convolution
        """
        batch_size, in_channels, input_height, input_width = x.shape
        filter_height, filter_width = self.kernel_size

        # Apply im2col to get the image matrix
        col = self.im2col(x, filter_height, filter_width, self.stride, self.padding)

        # Flatten the filters (out_channels, in_channels, filter_height, filter_width) to (out_channels, in_channels * filter_height * filter_width)
        filters_flat = self.weight.reshape(self.out_channels, -1)

        # Matrix multiplication (im2col matrix @ filters_flat.T + bias)
        out = col @ filters_flat.T + self.bias

        # Compute output dimensions
        out_height = (input_height + 2 * self.padding - filter_height) // self.stride + 1
        out_width = (input_width + 2 * self.padding - filter_width) // self.stride + 1

        # Reshape output to (batch_size, out_channels, out_height, out_width)
        out = out.reshape(batch_size, out_height, out_width, self.out_channels).transpose(0, 3, 1, 2)

        self.cache = (x, col)  # Store values for backward pass
        return out

    def backward(self, dout, learning_rate=1e-3):
        """
        Backward pass for 2D convolution.
        :param dout: Gradient of the loss with respect to the output
        :return: Gradient with respect to the input, weight, and bias
        """
        x, col = self.cache
        batch_size, in_channels, input_height, input_width = x.shape
        filter_height, filter_width = self.kernel_size
        _, out_channels, out_height, out_width = dout.shape

        # Reshape dout for matrix multiplication with columns (backprop)
        dout_reshaped = dout.transpose(0, 2, 3, 1).reshape(-1, out_channels)

        # Gradient with respect to filters
        dw = dout_reshaped.T @ col
        dw = dw.reshape(out_channels, in_channels, filter_height, filter_width)

        # Gradient with respect to bias
        db = np.sum(dout_reshaped, axis=0)

        # Gradient with respect to input (dx)
        filters_flat = self.weight.reshape(out_channels, -1)
        dcol = dout_reshaped @ filters_flat
        dx = self.col2im(dcol, x.shape, filter_height, filter_width, self.stride, self.padding)

        # Update weights and bias
        self.weight -= learning_rate * dw
        self.bias -= learning_rate * db

        return dx

    def col2im(self, col, input_shape, filter_height, filter_width, stride=1, padding=0):
        """
        Transform column matrix back to the image (inverse of im2col).
        """
        batch_size, in_channels, input_height, input_width = input_shape
        out_height = (input_height + 2 * padding - filter_height) // stride + 1
        out_width = (input_width + 2 * padding - filter_width) // stride + 1

        col = col.reshape(batch_size, out_height, out_width, in_channels, filter_height, filter_width).transpose(0, 3, 4, 5, 1, 2)
        
        padded_input = np.zeros((batch_size, in_channels, input_height + 2 * padding, input_width + 2 * padding))

        for y in range(filter_height):
            y_max = y + stride * out_height
            for x in range(filter_width):
                x_max = x + stride * out_width
                padded_input[:, :, y:y_max:stride, x:x_max:stride] += col[:, :, y, x, :, :]

        if padding == 0:
            return padded_input
        return padded_input[:, :, padding:-padding, padding:-padding]



