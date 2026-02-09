#ifndef DECODER_HEADER
#define DECODER_HEADER

#include <cstdint>
#include <stdexcept>
#include <functional>

class SPU;

template<typename... Args>
using SPUFunctionPtr = void(*)(SPU&, Args...);

using DecodedOperation = std::function<void(SPU&)>;

template<typename... Args>
DecodedOperation make_spu_operation(SPUFunctionPtr<Args...> func, Args... args) {
	return [func, ...args = std::forward<Args>(args)](SPU& spu) mutable {
		func(spu, std::forward<Args>(args)...);
	};
}

DecodedOperation decode(SPU& spu, Register insn);

#endif