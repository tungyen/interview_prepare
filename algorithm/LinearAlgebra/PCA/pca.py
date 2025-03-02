import numpy as np
import cv2

class PCA:
    
    def __init__(self, data, K):
        
        # Input:
        #     data - N by d data, N is data number, d is dimension
        #     K - The target dimension of data projection
        
        self.data = data
        self.K = K
        
    def Projection(self):
        
        mu = np.average(self.data, axis=0)
        DN = self.data - np.expand_dims(mu, 0)
        conv = np.matmul(np.transpose(DN), DN)
        U, _, _ = np.linalg.svd(conv)
        
        self.projectionMatrix = U[:, :self.K]
        dataProjection = np.matmul(self.data, self.projectionMatrix)
        
        return dataProjection
    
    def Reconstruction(self):
        
        dataReconstruction = np.matmul(np.matmul(self.data, self.projectionMatrix), np.transpose(self.projectionMatrix))
        return dataReconstruction
    
if __name__ == '__main__':
    
    capoo = cv2.imread("capoo.png")
    capooPCA = np.zeros((capoo.shape), dtype=np.uint8)
    
    for c in range(capoo.shape[2]):
        pca = PCA(capoo[:, :, c], 150)
        Proj = pca.Projection()
        Reconstruction = pca.Reconstruction()

        capooPCA[:, :, c] = Reconstruction
        
    cv2.imshow("Capoo after PCA", capooPCA)
    cv2.waitKey()