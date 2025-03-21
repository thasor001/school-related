from src import preprocess_image, augment_image

import tensorflow as tf

import matplotlib
matplotlib.use("TkAgg") # Since i am running this in an GNU terminal.
import matplotlib.pyplot as plt

import numpy as np

# Loading dataset:
(x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()

# Displaying a few of the sample images
fig, axes = plt.subplots(3, 3, figsize=(9, 9))

for i, ax in enumerate(axes.flat):
    ax.imshow(x_train[i], cmap="plasma", interpolation="hanning")
    ax.set_facecolor((0.15, 0.15, 0.156))
    ax.set_xticks([])
    ax.set_yticks([])
    ax.set_title(y_train[i], fontsize=12)

plt.tight_layout()
plt.show()


# Resizing all the images to match the input size of pre-trained models:

# ResNet50 and mobileNetV2 both takes in an image of (224, 224, 3)
# That is 244 x 244 pixels with 3 color channels (RGB)

# Processing all those images at once requires ALOT of ram.
# Given that the mnist dataset consists of 70000 images, and each image consists
# of 28 * 28 * 32 (float32 -> 32 bits) we are already looking at a lot of ram just
# to keep them loaded, but scaling the images up to 224 * 224 * 3 * 32 makes it into
# ~38 GB of data which is not something my computer will allow me to do.

# So we will use pipelining and lazy lists to process -> augment -> train images on the fly.

# First we create a lazy list (a list that is not loaded fully but loads on demand)
train_dataset = tf.data.Dataset.from_tensor_slices((x_train, y_train))
test_dataset = tf.data.Dataset.from_tensor_slices((x_test, y_test))

# Apply preprocessing and augmentation
train_dataset = (train_dataset
                 .map(preprocess_image, num_parallel_calls=tf.data.AUTOTUNE)
                 .shuffle(buffer_size=1000)
                 .map(augment_image, num_parallel_calls=tf.data.AUTOTUNE)
                 .batch(32)
                 .prefetch(tf.data.AUTOTUNE))

# Here we are chaning operation:

# First .map:
# We apply preprocess_image (Function in src/utils.py) on every element,
# This takes the original image and formats it into the size required by ResNet50.
# num_parallel_calls, this tells tensorflow to create X amount of threads on the 
# CPU, in out case this is tf.data.AUTOTUNE which tells tensorflow to dynamically determine
# the number of threads to create.

# .shuffle:
# Shuffle randomly shuffles the order of elements in the dataset, this ensures that the model
# wont become overfitted with the input data.

# Second .map:
# We apply augment_image (Function in src/utils.py) this augments each image, and again
# dynamically determines how many CPU threas to use.

# .batch:
# This batches the dataset into batches e.g., 32 so [32, 224, 224, 3]. We do this since the GPU
# depending on if you have CUDA & CUDNN installed abd the CPU works more efficiently when it does
# not need to create a new thread for each and every image. Instead we batch them up so that each
# thread can work on 32 images at a time.

# .prefetch
# Prefetches data even before the GPU / CPU is done with training on the current images.
# This speeds up the process as when the model is done training on 
