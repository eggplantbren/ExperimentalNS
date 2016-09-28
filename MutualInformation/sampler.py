"""
Define the Sampler class.
For now, this is just standard NS.
"""

__all__ = ["Sampler"]

# Import the model
from model import from_prior, log_prior, log_likelihood

class Sampler:
    """
    An object of this class is a sampler.
    """
    def __init__(self, num_particles=10):
        """
        Constructor: specify number of particles.
        """
        self.ready = False

    def initialise(self):
        """
        Generate particles from the prior.
        """
        self.particles = [from_prior() for i in range(0, self.num_particles)]
        self.ready = True

