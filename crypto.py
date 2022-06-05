
#%%
from collections import namedtuple
from cryptoconditions import crypto

CryptoKeypair = namedtuple('CryptoKeypair', ('private_key', 'public_key'))


def generate_keypair(seed=None) -> CryptoKeypair:
    """Generates a cryptographic key pair.
    Args:
        seed (bytes): 32-byte seed for deterministic generation.
                      Defaults to `None`.
    """
    return CryptoKeypair(
        *(k.decode() for k in crypto.ed25519_generate_key_pair(seed)))