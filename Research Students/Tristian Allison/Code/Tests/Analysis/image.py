# Import Libraries
import io
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

import cv2
from skimage import measure
import tifffile as tiff

import uproot

# EMCCD Camera resolution is 512x512 pixels
resolution = 128

# Aquire filename and open it with uproot
file = uproot.open("./data/10runs_Am241_1.root")
print(file["Photons"].keys())

# Get tree with photon info
tree = file["Photons"]
arrays = tree.arrays(["iEvent", "x", "y", "energy"], library="np")

event_ids = np.unique(arrays["iEvent"])

stack = np.zeros((len(event_ids), resolution, resolution), dtype=np.float32)

# Create Image Stacks from ROOT file
for i, event_id in enumerate(event_ids):
  # create mask for event ID
  mask = arrays["iEvent"] == event_id

  # get components belonging to that event
  x = arrays["x"][mask]
  y = arrays["y"][mask]
  energies = arrays["energy"][mask]

  # Make picture and add it to tiff stack
  hist, x_edges, y_edges = np.histogram2d(x, y, weights=energies, bins=resolution, range=[[-1.25,1.25], [-1.25,1.25]])

  stack[i] = hist.astype(np.float32)

# Process image stacks
for img in stack:
    
    height = img.shape[0]
    width = img.shape[1]

    if (np.count_nonzero(img) >= 1000):
    
        # Image adjustment
        adjusted_img = cv2.normalize(
            img,
            None,
            alpha=0,
            beta=255,
            norm_type=cv2.NORM_MINMAX
        ).astype(np.uint8)

        curr_img = cv2.GaussianBlur(adjusted_img, (0,0), sigmaX=2)

        # Apply Threshold
        _, threshold = cv2.threshold(curr_img, 60, 255, cv2.THRESH_BINARY)

        # Counts Blobs and makes a mask for each blob
        num_labels, labels, center, _ = cv2.connectedComponentsWithStats(threshold, connectivity=8)

        masks = []

        for label in range (1, num_labels):
            mask = np.uint8(labels == label) * 255
            masks.append(mask)

        for i, mask in enumerate(masks):
            masked_image = cv2.bitwise_and(curr_img, curr_img, mask=mask)
            masked_image = cv2.normalize(
                masked_image,
                None,
                alpha=0,
                beta=255,
                norm_type=cv2.NORM_MINMAX
            ).astype(np.uint8)

            combined_image = np.hstack((adjusted_img,curr_img, masked_image))

            if np.count_nonzero(masked_image) > 50:
                cv2.imshow('Original Image vs. Masked Image', combined_image)
            
                cv2.waitKey(0)
                cv2.destroyAllWindows()

                # Make mesh grid for this mask
                x = np.linspace(-1.25, 1.25, width)
                y = np.linspace(-1.25, 1.25, height)
            
                x, y = np.meshgrid(x, y)

                z = masked_image.astype(float)
                z = z / np.max(z)
            
                fig = plt.figure()
            
                ax = fig.add_subplot(111, projection='3d')
                ax.plot_surface(x, y, z, cmap="viridis")

                ax.set_xlabel("x (mm)")
                ax.set_ylabel("y (mm)")
                ax.set_zlabel("Intensity")
            
                plt.show()