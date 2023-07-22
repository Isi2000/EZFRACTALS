import imageio
import os
import numpy as np

path1 = './julia_set/'
path2 = './mandelbrot_zoom/'

def gif_maker(path, gif_name):
    """
    path: string, it is the path to the data to make the gif
    gif_name: name of the gif file, it saves it in current dir
    """
    filenames_ = os.listdir(path1)
    filenames = np.sort(filenames_)
    img = []
    for fn in filenames:    
        img.append(imageio.imread(path1 + fn))
        imageio.mimsave(gif_name, img, duration = 10)

gif_maker(path1, "julia_set.gif")



