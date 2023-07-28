#include "CNPJInvalidoException.hpp"

using namespace sistema; //namespace

CNPJInvalidoException::CNPJInvalidoException(const std::string cnpj)
    :std::runtime_error{"CNPJ inválido"}, cnpj{cnpj}{}