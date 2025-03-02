class layer:
    def __init__(self):
        pass

    def forward(self, input_x):
        print("The input is: ", input_x)
        pass

    def backward(self):
        pass

    def zero_grad(self):
        pass

    def __call__(self, input_x, **kwargs):
        return self.forward(input_x, **kwargs)

    @property
    def parameters(self):
        return []

    @property
    def grads(self):
        return []
