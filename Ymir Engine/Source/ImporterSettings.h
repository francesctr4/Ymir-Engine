#pragma once

#include "Globals.h"

#include "Settings.h"

namespace ImporterSettings {

	uint Save(const Settings& ourSettings, char** fileBuffer); // Save Settings as .yset on Library
	void Load(const char* fileBuffer, Settings& ourSettings); // Load Settings from Library
	 
}