#ifndef quickMap_h
#define quickMap_h

#include <Arduino.h>

class quickMap
{
public:
  quickMap();
  bool init(float in_min, float in_max, float out_min, float out_max);
  
  // Función de mapeo ultra rápida con restricciones (constrain) automáticas
  inline float map(const float value) { 
    if (value >= _in_max_limit) return _out_max_limit;
    if (value <= _in_min_limit) return _out_min_limit;
    return _base + value * _factor;
  }

private:
  float _in_min_limit, _in_max_limit;
  float _out_min_limit, _out_max_limit;
  float _factor, _base;
};

// Constructor por defecto
inline quickMap::quickMap()
{
  init(0.0f, 1.0f, 0.0f, 1.0f);
}

// Inicialización y precalculo de factores
inline bool quickMap::init(float in_min, float in_max, float out_min, float out_max)
{
  float _inRange = in_max - in_min;
  float _outRange = out_max - out_min;
  
  if (_inRange == 0.0f) return false; // Evitar división por cero

  _factor = _outRange / _inRange;
  _base = out_min - in_min * _factor;

  // Lógica para que las restricciones funcionen aunque el rango esté invertido
  if (in_min < in_max) {
    _in_min_limit = in_min;
    _in_max_limit = in_max;
    _out_min_limit = out_min;
    _out_max_limit = out_max;
  } else {
    _in_min_limit = in_max;
    _in_max_limit = in_min;
    _out_min_limit = out_max;
    _out_max_limit = out_min;
  }

  return true;
}

#endif
