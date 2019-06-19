#include "skse64/PapyrusVM.h"
#include "skse64/PapyrusNativeFunctions.h"
#include "papyrus.h"

namespace papyrus
{
	void DebugTrace(StaticFunctionTag* base, BSFixedString s)
	{
		_MESSAGE("%s", s);
	}
}

void papyrus::RegisterFuncs(VMClassRegistry* vm)
{
	vm->RegisterFunction(
		new NativeFunction1<StaticFunctionTag, void, BSFixedString>("DebugTrace", "zzzSamplePlugin", papyrus::DebugTrace, vm));

}
