import tensorflow as tf
import tensorflow.keras as ks

import numpy as np

# Function for preprocessing a single image at a time:
def preprocess_image(image, label):
    # Normalizing the image
    image = tf.cast(image, tf.float32) / 255.0

    # Resizing the image to 224 x 224
    image = tf.image.resize(image[..., tf.newaxis], [224, 224])

    # Converting the 1 channel (Grey) into 3 channel (RGB) by just repeating
    # The greyscale 3 times.
    image = tf.repeat(image, 3, axis=-1) # Shape: (224, 224, 3)

    return image, label


# Function to augment the picture:
# I avoid flipping/ rotating the images since this might confuse digits
# e.g., 9 turning into 6.
def augment_image(image, label):
    image = tf.image.random_brightness(image, max_delta=0.2)
    image = tf.image.random_contrast(image, lower=0.8, upper=1.2)

    return image, label

