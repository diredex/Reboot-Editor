#include "InstanceManager.h"
#include "HAL/FileManager.h"
#include "Misc/Paths.h"
#include "Misc/MessageDialog.h"

#if PLATFORM_WINDOWS
#include "Windows/WindowsHWrapper.h"
#include <tlhelp32.h>
#endif

FString FInstanceManager::GetLockFilePath()
{
    return FPaths::ProjectSavedDir() / TEXT("Instance.lock");
}

bool FInstanceManager::IsPrimaryInstance()
{
    FString LockFilePath = GetLockFilePath();

    if (IFileManager::Get().FileExists(*LockFilePath))
    {
        // Check if the lock file's process is alive
        FString LockFileContent;
        if (FFileHelper::LoadFileToString(LockFileContent, *LockFilePath))
        {
            uint32 PID = FCString::Atoi(*LockFileContent);

            if (FPlatformProcess::IsApplicationRunning(PID))
            {
                return false; // Another instance is running
            }
        }
    }

    // Write the current process's PID to the lock file
    FString CurrentPID = FString::Printf(TEXT("%d"), FPlatformProcess::GetCurrentProcessId());
    FFileHelper::SaveStringToFile(CurrentPID, *LockFilePath);

    return true;
}

void FInstanceManager::ForceAcquireLock()
{
    FString LockFilePath = GetLockFilePath();

    if (IFileManager::Get().FileExists(*LockFilePath))
    {
        FString LockFileContent;
        if (FFileHelper::LoadFileToString(LockFileContent, *LockFilePath))
        {
            uint32 PID = FCString::Atoi(*LockFileContent);

            if (FPlatformProcess::IsApplicationRunning(PID))
            {
#if PLATFORM_WINDOWS
                HANDLE ProcessHandle = OpenProcess(PROCESS_TERMINATE, false, PID);
                if (ProcessHandle)
                {
                    TerminateProcess(ProcessHandle, 0);
                    CloseHandle(ProcessHandle);
                }
#endif
            }
        }
    }

    // Create a new lock file with the current process's PID
    FString CurrentPID = FString::Printf(TEXT("%d"), FPlatformProcess::GetCurrentProcessId());
    FFileHelper::SaveStringToFile(CurrentPID, *LockFilePath);
}

void FInstanceManager::ReleaseLock()
{
    FString LockFilePath = GetLockFilePath();

    if (IFileManager::Get().FileExists(*LockFilePath))
    {
        FString LockFileContent;
        if (FFileHelper::LoadFileToString(LockFileContent, *LockFilePath))
        {
            uint32 PID = FCString::Atoi(*LockFileContent);

            // Ensure only the current process can delete its lock
            if (PID == FPlatformProcess::GetCurrentProcessId())
            {
                IFileManager::Get().Delete(*LockFilePath);
            }
        }
    }
}
