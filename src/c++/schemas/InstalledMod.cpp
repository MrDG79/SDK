#include "c++/schemas/InstalledMod.h"
#include "c/ModioC.h"                      // for ModioInstalledMod
#include "dependencies/nlohmann/json.hpp"  // for json

namespace modio
{
void InstalledMod::initialize(ModioInstalledMod modio_installed_mod)
{
	mod_id = modio_installed_mod.mod_id;
	modfile_id = modio_installed_mod.modfile_id;
	date_updated = modio_installed_mod.date_updated;
	if (modio_installed_mod.path)
		path = modio_installed_mod.path;
	mod.initialize(modio_installed_mod.mod);
}

nlohmann::json toJson(InstalledMod &installed_mod)
{
	nlohmann::json installed_mod_json;

	installed_mod_json["mod_id"] = installed_mod.mod_id;
	installed_mod_json["modfile_id"] = installed_mod.modfile_id;
	installed_mod_json["date_updated"] = installed_mod.date_updated;
	installed_mod_json["path"] = installed_mod.path;

	return installed_mod_json;
}
} // namespace modio
