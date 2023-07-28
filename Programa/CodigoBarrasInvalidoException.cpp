#include "CodigoBarrasInvalidoException.hpp"

using namespace sistema; //namespace

CodigoBarrasInvalidoException::CodigoBarrasInvalidoException(const std::string codigoBarras)
    :std::runtime_error{"Código de barras inválido"}, codigoBarras{codigoBarras}{}