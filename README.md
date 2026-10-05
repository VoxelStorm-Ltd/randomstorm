# RandomStorm

RandomStorm is a small C++ wrapper around `std::mt19937`, providing seed management and convenience functions for random numbers, angles, and ASCII characters. AdvertCity uses it for repeatable procedural generation, random placement and orientation, and gameplay choices.

Compile [randomstorm/randomstorm.cpp](randomstorm/randomstorm.cpp) into your application and include [randomstorm/randomstorm.h](randomstorm/randomstorm.h). It uses C++11 standard-library facilities with no third-party dependencies. The radians helper also relies on the non-standard `M_PI` constant being available in the build environment.

## Usage

```cpp
#include <cassert>
#include <iostream>
#include <random>
#include "randomstorm/randomstorm.h"

int main() {
  /// Generate repeatable values from an explicit seed
  randomstorm random;
  random.set_seed(42);

  auto const first_roll{random.get_random_uint(1, 6)};
  random.reset();
  assert(random.get_random_uint(1, 6) == first_roll);

  std::cout << random.get_random_float(-1.0f, 1.0f) << '\n';
  std::cout << random.get_random_bool(0.25) << '\n';
  std::cout << random.get_random_angle_degrees() << '\n';
  std::cout << random.get_random_char_alphanum_upper() << '\n';

  // use the same engine with other standard distributions
  std::normal_distribution<double> distribution{0.0, 1.0};
  std::cout << distribution(random.generator) << '\n';
}
```

**Call `set_seed()` or `reset()` before drawing values.** The current constructor records its seed argument (default `1337`) but leaves the engine default-constructed. For example, `randomstorm random{42};` requires `random.reset()` to apply that seed. `set_seed(value)` both saves and applies a seed; `set_seed()` without an argument restores `1337`. `get_seed()` returns the saved seed.

## Helpers

| Methods | Result |
| --- | --- |
| `get_random_float(from, to)`, `get_random_double(from, to)` | Uniform real values in `[from, to)`; defaults to `[0, 1)` |
| `get_random_int(from, to)` | Uniform integers, both endpoints included; defaults to `[-128, 128]` |
| `get_random_uint(from, to)` | Uniform unsigned integers, both endpoints included; defaults to `[0, 255]` |
| `get_random_bool(probability)` | A boolean with the supplied probability of `true`; defaults to `0.5` |
| `get_random_angle_degrees()`, `get_random_angle_radians()` | Angles over a full turn, starting at zero; both currently draw through the float helper despite returning `double` |
| `get_random_char_alpha_upper()`, `get_random_char_alpha_lower()` | ASCII letters `A–Z` or `a–z` |
| `get_random_char_alphanum_upper()`, `get_random_char_alphanum_lower()` | ASCII digits plus letters of the selected case |
| `get_random_char_digit()` | An ASCII digit `0–9` |

Supply ordered bounds and probabilities between zero and one. The helpers use standard distributions without additional argument validation.

## Repeatability and state

`reset()` restarts the engine from the saved seed. Repeating the same sequence of calls after a reset reproduces the results within the same implementation; standard-library distribution results are not guaranteed to match across different library implementations. Restoring a seed restarts a sequence rather than restoring its previous position. For an exact in-memory checkpoint, copy the public `generator` and restore that copy later; seeding it directly does not update `get_seed()`.

AdvertCity resets its generator around procedural generation stages and saves the seed with its game data. It also passes `randomgen.generator` directly to a distribution for corporation income. These patterns can be found in the game's `universe.cpp`, `savegame/save.cpp`, and `corporation/corporation.cpp`.

Each instance owns its engine and saved seed. There are no background threads or internal locks; use a separate instance per thread or synchronize shared access. This is a deterministic game-randomness utility, not a cryptographic random generator.
