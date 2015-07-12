#include "randomstorm.h"
#include <random>
#include "vmath.h"

randomstorm::randomstorm(uint32_t seed)
  : seed(seed) {
  /// Default constructor
}

randomstorm::~randomstorm() {
  /// Default destructor
}

uint32_t randomstorm::get_seed() const {
  /// Return the current generator seed
  return seed;
}
void randomstorm::set_seed(uint32_t newseed) {
  /// Update the generator seed
  seed = newseed;
  reset();
}

void randomstorm::reset() {
  /// Re-seed the generator with its saved seed
  generator.seed(seed);
}

float randomstorm::get_random_float(float from, float to) {
  std::uniform_real_distribution<float> distribution(from, to);
  return distribution(generator);
}
double randomstorm::get_random_double(double from, double to) {
  std::uniform_real_distribution<double> distribution(from, to);
  return distribution(generator);
}
int randomstorm::get_random_int(int from, int to) {
  std::uniform_int_distribution<int> distribution(from, to);
  return distribution(generator);
}
unsigned int randomstorm::get_random_uint(unsigned int from, unsigned int to) {
  std::uniform_int_distribution<unsigned int> distribution(from, to);
  return distribution(generator);
}
bool randomstorm::get_random_bool(double trueprobability) {
  std::bernoulli_distribution distribution(trueprobability);
  return distribution(generator);
}

double randomstorm::get_random_angle_degrees() {
  return get_random_float(0.0, 360.0);
}
double randomstorm::get_random_angle_radians() {
  return get_random_float(0.0, 2.0 * M_PI);
}

char randomstorm::get_random_char_alpha_upper() {
  /// Return random ascii value for A-Z
  return get_random_uint('A', 'Z');
}
char randomstorm::get_random_char_alpha_lower() {
  /// Return random ascii value for a-z
  return get_random_uint('a', 'z');
}
char randomstorm::get_random_char_alphanum_upper() {
  /// Return random ascii value for 0-9 A-Z
  // include the entire range from 0 to Z, see http://www.asciitable.com/
  unsigned int constexpr gap('A' - '9' - 1);
  char result(get_random_uint('0', 'Z' - gap));
  if(result > '9') {                    // bridge the gap between 9 and A
    result += gap;
  }
  return result;
}
char randomstorm::get_random_char_alphanum_lower() {
  /// Return random ascii value for 0-9 a-z
  // include the entire range from 0 to z, see http://www.asciitable.com/
  unsigned int constexpr gap('a' - '9' - 1);
  char result(get_random_uint('0', 'z' - gap));
  if(result > '9') {                    // bridge the gap between 9 and a
    result += gap;
  }
  return result;
}
char randomstorm::get_random_char_digit() {
  /// Return random ascii value for 0-9
  return get_random_uint('0', '9');
}
