# include "Structs/CityDataStruct.h"
# include "Structs/PersonDataStruct.h"

void FCityDataStruct::Pack()
{
	if(this->packing)
	{
		return;
	}
	this->packing = true;

	if (!this->owner_handle.IsNull())
	{
		this->owner_data = this->owner_handle.GetRow<FPersonDataStruct>(nullptr);
	}
	if (this->owner_data != nullptr)
	{
		this->owner_data->Pack();
	}
	this->packing = false;
}
