RotorXor
========


NOTICE
------
  This is EXPERIMENTAL software, written as a proof-of-concept by a
  relative novice with both C++ and cryptography!  There may be memory
  leaks, unstable operation, errors in encryption/decryption, and other
  bugs which may render this completely useless for anything other than
  "fun".  Do NOT use RotorXor encryption for any applications which
  require secure communications.  This software has NO warranty, implied
  or otherwise.


WHAT IS ROTORXOR?
-----------------
  RotorXor is a byte stream encryption protocol which combines the
  rotary encryption techniques used in World War II rotor machines with
  modern-day pseudorandom number generators and stream encryption.


HOW IT WORKS
------------
  This explanation assumes that the reader has at least a very basic
  understanding of German rotor machines and XOR ciphering.

  As the name implies, the heart of the RotorXor is built around the
  "Rotor", along with a "Xorer".  To explain how RotorXor works, perhaps
  it would be best to explain each of the classes which makes its
  operation possible:

  CharSet: The set of characters which RotorXor is capable of handling.
  This is a holdover from an attempt to create a working Enigma, which
  handles A to Z only.  Also handles the conversion of characters to
  numerical values and vice-versa.  Seeing how RotorXor works with the
  entire ASCII character set, and character/value conversion is trivial,
  this class may be eliminated in a future update.

  Generator: This class simply utilises a deterministic PRNG to generate
  a random ASCII character within the ranged dictated by CharSet, which
  defaults to the full ASCII character set.

  Drum: The Drum is the heart of any rotor machine.  The "drum" refers
  to the portion of an enigma rotor where the actual scrambler wires are
  located.  Similarly, this class is composed of the actual substitution
  cipher tables.  The cipher table is a char vector composed of the
  characters within CharSet.  The cipher table is then scrambled by a
  deterministic PRNG.  To do the substitution, the input character is
  converted to its numerical ASCII value, and the value at that index in
  the vector is returned.

  Rotor: The rotor is the main implementation of the drum.  It adds
  several features to the drum.  First, it provides an offset which
  shifts the values of the vector by a random amount.  Second, it
  provides a means to rotate the Rotors.  Third, it provides each Rotor
  with a "notch", used by some stepping algorithms.  These are all set
  by deterministic PRNG.  In addition, though the Rotors are contained
  within a vector, each Rotor contains a pointer to the next and
  previous rotors within the RotorBank to allow encoding and decoding to
  be done recursively.

  RotorBank: Manages a vector of Rotors.  In addition to basic bank
  management functions such as appending additional rotors to the
  vector, RotorBank adds the ability to step Rotors via bool vector.

  Scrambler: The scrambler is composed of a Generator, which is
  scrambled through a RotorBank.  The Rotors are stepped by a bool
  array.

  Pulser: This is simply a specialized scrambler which is used to
  generate stepper vectors for stepping the Rotors of another Scrambler.
  The Pulser itself steps its rotors in a fashion not unlike to that of
  an odometer.

  Xorer: The Xorer handles the actual byte-by-byte encryption of a
  stream.  It is composed of a Scrambler and a Pulser, both with the
  same number of rotors.  For each character to be encrypted/decrypted,
  the Scrambler deterministically generates a character, which is then
  XORed with a byte of plaintext.  After each character of ciphertext is
  generated, the Pulser is pulsed, the resulting stepper vector is
  passed to the Scrambler, and the indicated Rotors are stepped.

  Handler: The handler simply accepts a stream of bytes as input, passes
  them, byte-by-byte, to the Xorer, and builds a new byte stream from
  the resulting ciphertext.

  The present implementation utilizes a custom-written implementation of
  the Blum Blum Shub PRNG (which itself definitely unsuitable for use in
  cryptographic functions since it has a VERY small keyspace, and was
  only written for the "fun of it"), which is utilized by Generator and
  Drum.  It accepts a Keyfile, which itself contains a data structure
  composed of two Prime (unsigned short) numbers, along with a Seed
  (unsigned int) which is a random number less than the 2 random Primes
  multiplied together.  An individual Keyfile is generated for each Drum
  and Generator contained within a given RotorXor session.

INSTALLATION
------------
  For details, please see the INSTALL file included with this
  distribution after you finish reading this file.

COMMAND LINE INTERFACE
----------------------
  The RotorXor interface comes with several command-line options
  which can be used to streamline operations.

  Usage: rotorxor [options]

  Options:

  @c -q	@c \--quiet:	Quiet mode - Forces batch mode and suppresses
			messages to stdout.  Messages to stderr will
			still be printed. [NOT YET IMPLEMENTED]

  @c -h	@c \--help:	Show help and exit.

  @c -v	@c \--version:	Show version and exit.

CONTENTS
--------

doc/
@n  IMPORTANT DOCUMENTATION about RotorXor which MUST be read.

src/
@n  RotorXor source code

AUTHORS
@n  A list of developers and contributors to the RotorXor project.

BUGS
@n  A list of bugs that need to be corrected.

CHANGELOG
@n  The GNU General Public License.

Doxyfile
@n  Configuration information for Doxygen, used for automatic
  documentation generation.

INSTALL
@n  Quick installation instructions.

NEWS
@n  Major changes since the previous version.

README.md
@n  Important information that should be reviewed before using
  RotorXor.

TODO
@n  Planned changes for future versions.
