#include "skse64/PluginAPI.h"
#include "skse64_common/skse_version.h"
#include "skse64/PapyrusVM.h"

#include <shlobj.h>
#include "papyrus.h"

IDebugLog	gLog;
UInt32 g_skseVersion;
PluginHandle	g_pluginHandle = kPluginHandle_Invalid;
SKSEMessagingInterface	* g_messaging = nullptr;

void SKSEMessageHandler(SKSEMessagingInterface::Message* msg)
{
	switch (msg->type)
	{
	case SKSEMessagingInterface::kMessage_DataLoaded:
		papyrus::RegisterFuncs((*g_skyrimVM)->GetClassRegistry());
		break;
	case SKSEMessagingInterface::kMessage_NewGame:
	case SKSEMessagingInterface::kMessage_PostLoadGame:
		break;
	}
}

extern "C"
{

bool SKSEPlugin_Query(const SKSEInterface * skse, PluginInfo * info)
{
	SInt32	logLevel = IDebugLog::kLevel_DebugMessage;
	gLog.SetLogLevel((IDebugLog::LogLevel)logLevel);

	gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\samplePlugin.log");

	_MESSAGE("samplePlugin.dll");

	g_skseVersion = skse->skseVersion;

	info->infoVersion = PluginInfo::kInfoVersion;
	info->name =	"samplePlugin";
	info->version = 1;

	g_pluginHandle = skse->GetPluginHandle();

	if (skse->isEditor)
	{
		return false;
	}
	else if (skse->runtimeVersion != RUNTIME_VERSION_1_5_80)
	{
		_MESSAGE("unsupported runtime version %08X", skse->runtimeVersion);
		return false;
	}

	g_messaging = (SKSEMessagingInterface *)skse->QueryInterface(kInterface_Messaging);
	if (!g_messaging)
	{
		return false;
	}
	return true;
}

bool SKSEPlugin_Load(const SKSEInterface * skse)
{
	if (g_messaging)
	{
		g_messaging->RegisterListener(g_pluginHandle, "SKSE", SKSEMessageHandler);
	}
	return true;
}

};
