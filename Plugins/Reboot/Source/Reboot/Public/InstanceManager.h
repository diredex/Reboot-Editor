#pragma once

#include "CoreMinimal.h"

class FInstanceManager
{
public:
	// Check if the current instance is the primary one
	static bool IsPrimaryInstance();

	// Forcefully acquire lock (terminate the other instance)
	static void ForceAcquireLock();

	// Release the lock when the process exits
	static void ReleaseLock();

private:
	static FString GetLockFilePath();
};
