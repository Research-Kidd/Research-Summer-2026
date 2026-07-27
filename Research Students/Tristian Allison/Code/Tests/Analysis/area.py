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

stack = []

#for i in range(10):

# Aquire filename and open it with uproot
#file = uproot.open(f"./data/10runs_Am241_{i}.root")
file = uproot.open("./data/14C-10K-Runs.root")

# Get tree with photon info
tree = file["Photons"]
arrays = tree.arrays(["iEvent", "x", "y", "energy"], library="np")

event_ids = np.unique(arrays["iEvent"])

# Create Image Stacks from ROOT file
for j, event_id in enumerate(event_ids):
    # create mask for event ID
    mask = arrays["iEvent"] == event_id

    # get components belonging to that event
    x = arrays["x"][mask]
    y = arrays["y"][mask]
    energies = arrays["energy"][mask]

    # Make picture and add it to tiff stack
    hist, x_edges, y_edges = np.histogram2d(x, y, weights=energies, bins=resolution, range=[[-1.25,1.25], [-1.25,1.25]])

    stack.append(hist.astype(np.float32))


min_area = 15
area_arr = []

for img in stack:
    # Image adjustment
    adjusted_img = cv2.normalize(img, None, alpha=0, beta=255, norm_type=cv2.NORM_MINMAX).astype(np.uint8)

    curr_img = cv2.GaussianBlur(adjusted_img, (0,0), sigmaX=2)

    # Apply Threshold
    _, threshold = cv2.threshold(curr_img, 60, 255, cv2.THRESH_BINARY)

    # Counts Blobs and makes a mask for each blob
    num_labels, labels, stats, centroids = cv2.connectedComponentsWithStats(threshold, connectivity=8)

    # Skip label 0 (background)
    areas = stats[1:, cv2.CC_STAT_AREA]
    areas = areas[areas >= min_area]
    
    area_arr.extend(areas)


plt.hist(area_arr, bins=25)

plt.ylabel("Count")
plt.xlabel("Area (pixels)")

plt.show()