#ifndef RANDOMSTORM_H_INCLUDED
#define RANDOMSTORM_H_INCLUDED

#include <random>

class randomstorm {
private:
  static uint32_t constexpr default_seed = 1337;                                // the program-wide default random seed
  uint32_t seed = default_seed;                                                 // assigned a value from lastseed on object construction

public:
  using generator_type = std::mt19937;
  generator_type generator;                                                     // the random engine (TODO: consider implementing http://stackoverflow.com/a/1227137/1678468)

public:
  randomstorm(uint32_t seed = default_seed);
  ~randomstorm();

  // seed control functions
  uint32_t get_seed() const __attribute__((__pure__));
  void set_seed(uint32_t newseed = default_seed);
  void reset();

  // basic numerical random functions
  float        get_random_float( float        from = 0.0f, float        to = 1.0f);
  double       get_random_double(double       from = 0.0,  double       to = 1.0);
  int          get_random_int(   int          from = -128, int          to = 128);
  unsigned int get_random_uint(  unsigned int from = 0u,   unsigned int to = 255u);
  bool         get_random_bool(double trueprobability = 0.5);

  // more advanced semantic random functions
  float  get_random_angle_degrees();
  float  get_random_angle_radians();
  char   get_random_char_alpha_upper();
  char   get_random_char_alpha_lower();
  char   get_random_char_alphanum_upper();
  char   get_random_char_alphanum_lower();
  char   get_random_char_digit();
};

#endif // RANDOMSTORM_H_INCLUDED
