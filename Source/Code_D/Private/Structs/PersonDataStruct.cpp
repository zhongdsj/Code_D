# include "Structs/PersonDataStruct.h"
# include "Structs/FactionDataStruct.h"

void FPersonDataStruct::Pack()
{
	if(this->packing)
	{
		return;
	}
	this->packing = true;
	if (!this->faction_handle.IsNull())
	{
		this->faction_data = this->faction_handle.GetRow<FFactionDataStruct>(nullptr);
	}
	if (this->faction_data != nullptr)
	{
		this->faction_data->Pack();
	}
	this->packing = false;
}
