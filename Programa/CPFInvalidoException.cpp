#include "CPFInvalidoException.hpp"

using namespace sistema; //namespace

CPFInvalidoException::CPFInvalidoException(const long cpf)
    :std::runtime_error{"CPF inválido"}, cpf{cpf}{}