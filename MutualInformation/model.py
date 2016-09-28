"""
Define the functions that are needed to run
a particular model.
"""

import numpy as np
import numpy.random as rng

__all__ = ["from_prior", "log_prior", "log_likelihood"]

def from_prior():
    """
    Generate a parameter vector from the prior.
    """
    return rng.rand(20)

def log_prior(params):
    """
    Evaluate the log of the prior density or mass function.
    """
    if np.any((params < 0.0) | (params > 1.0)):
        return -1E300
    return 0.0

def log_likelihood(params):
    """
    Evaluate the log likelihood.
    """
    return -0.5*np.sum((params - 0.5)/0.1)**2

