import matplotlib.pyplot as plt
import numpy as np

plt.ion()
x = np.linspace(0, 4*np.pi, 100)
fig, axes = plt.subplots(nrows=3)

fig.canvas.draw()
background = fig.canvas.copy_from_bbox(axes[0].bbox)

lines = [ax.plot(x, np.cos(x))[0] for ax in axes]
fig.canvas.draw()

for phase in range(1000):
    fig.canvas.restore_region(background)
    lines[0].set_ydata(np.cos(x + phase / 5.0))
    axes[0].draw_artist(lines[0])
    fig.canvas.blit(axes[0].bbox)
