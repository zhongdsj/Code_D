# include "Structs/FactionDataStruct.h"
# include "Structs/PersonDataStruct.h"

FFactionDataStruct::FFactionDataStruct()
{
	this->faction_background = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Characters/Mannequins/Textures/Shared/T_UE_Logo_M.T_UE_Logo_M'"));
}

void FFactionDataStruct::Pack()
{
	if (this->packing)
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
