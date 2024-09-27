import numpy as np
from layer import layer

class NumpyAttention(layer):
    def __init__(self):
        self.cache = {}

    def forward(self, query, key, value, mask=None):
        """
        query: (batch_size, seq_len_q, dim)
        key: (batch_size, seq_len_k, dim)
        value: (batch_size, seq_len_v, dim)
        mask: (batch_size, seq_len_q, seq_len_k)
        """
        d_k = query.shape[-1]
        scores = np.dot(query, key.transpose(0, 2, 1)) / np.sqrt(d_k)

        if mask is not None:
            scores += (mask * -1e9)

        exp_scores = np.exp(scores - np.max(scores, axis=-1, keepdims=True))
        attn_weights = exp_scores / np.sum(exp_scores, axis=-1, keepdims=True)

        output = np.dot(attn_weights, value)

        self.cache['query'] = query
        self.cache['key'] = key
        self.cache['value'] = value
        self.cache['attn_weights'] = attn_weights
        return output

    def backward(self, grad_output):
        """
        grad_output: (batch_size, seq_len_q, dim)
        """
        query = self.cache['query']
        key = self.cache['key']
        value = self.cache['value']
        attn_weights = self.cache['attn_weights']

        d_k = query.shape[-1]

        grad_value = np.dot(attn_weights.transpose(0, 2, 1), grad_output)
        grad_attn_weights = np.dot(grad_output, value.transpose(0, 2, 1))
        grad_scores = grad_attn_weights * (attn_weights * (1 - attn_weights))
        grad_query = np.dot(grad_scores, key)
        grad_key = np.dot(grad_scores.transpose(0, 2, 1), query)

        return grad_query, grad_key, grad_value
