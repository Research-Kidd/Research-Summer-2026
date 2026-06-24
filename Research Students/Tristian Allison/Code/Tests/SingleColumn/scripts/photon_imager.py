# Import Libraries
import io
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import uproot


# Aquire filename and open it with uproot
file = uproot.open("output0.root")
print(file.keys())

# Get tree with photon info
tree = file["Photons"]
x = tree["fX"].array(library="np")
y = tree["fY"].array(library="np")

# EMCCD Camera resolution is 512x512 pixels
resolution = 512

plt.hist2d(x, y, bins=resolution, range=[[-5,5], [-5,5]], cmap="gray")
plt.colorbar(label="Hit count")

ax = plt.gca()              # get current axes
ax.set_box_aspect(1)        # make plot square

plt.xlabel("x (mm)")
plt.ylabel("y (mm)")

plt.show()