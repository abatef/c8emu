#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <SDL2/SDL.h>

#include <array>

class Audio {
 public:
  ~Audio();

  bool Init();

  void Beep(int length);

 private:
  static constexpr double kFrequency = 48000;
  static constexpr double kTone = 440;
  static constexpr int kAmplitude = 7;
  static constexpr int kBias = 127;
  static constexpr int kSamplesPerFrame = (kFrequency / 60) * 3;

  std::array<unsigned char, kSamplesPerFrame * 30> audio_buffer;

  double WavePosition = 0;
  double WaveIncrement = (kTone * (2.0 * M_PI)) / kFrequency;

  SDL_AudioDeviceID device;

  void SineWave(int length);
};

#endif  // AUDIO_HPP
