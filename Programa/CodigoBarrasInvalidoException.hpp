#ifndef CODIGO_BARRAS_INVALIDO_EXCEPTION
#define CODIGO_BARRAS_INVALIDO_EXCEPTION

#include <stdexcept>

namespace sistema
{

class CodigoBarrasInvalidoException : public std::runtime_error{
    public:
        CodigoBarrasInvalidoException(const std::string codigoBarras);
        virtual ~CodigoBarrasInvalidoException() = default;

        const std::string codigoBarras;
};

} // namespace sistema

#endif