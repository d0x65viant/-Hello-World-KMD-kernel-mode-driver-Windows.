#include <ntddk.h>
#include <wdf.h>

void SampleUnload(_In_ PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	//KdPrint(("Sample driver Unload called\n"));
	DbgPrintEx(0,0,"Sample driver Unload called\n");
}

NTSTATUS DriverEntry(
_In_ PDRIVER_OBJECT DriverObject,
_In_ PUNICODE_STRING RegistryPath) {
	//PDRIVER_OBJECT  DriverObject - указатель на объект-драйвер, соответствующий загружаемому драйверу
	//PUNICODE_STRING RegistryPath - указатель на строку в формате Unicode с именем ключа реестра, соответствующего загружаемому драйверу
	UNREFERENCED_PARAMETER(RegistryPath);
	DbgPrintEx(0, 0, "Sample driver initialized successfully\n");
	RTL_OSVERSIONINFOW info = {0};
	info.dwOSVersionInfoSize = sizeof(RTL_OSVERSIONINFOW);
	
	if (RtlGetVersion(&info) == STATUS_SUCCESS)
		DbgPrintEx(0, 0, "Version OS: %llu\nBuild number: %llu\nPlatform Id: %llu\n", 
			info.dwMajorVersion,
			info.dwBuildNumber);
	else
		DbgPrintEx(0,0, "ErrVerOS: OS version is not defined.\n");

	DriverObject->DriverUnload = SampleUnload;

	return STATUS_SUCCESS;
}
