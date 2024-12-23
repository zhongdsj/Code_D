# pragma once
# include "CoreMinimal.h"
# include "Engine/DataTable.h"
# include "BaseDataStruct.generated.h"

USTRUCT()
struct FBaseDataStruct : public FTableRowBase
{
	GENERATED_BODY()

	bool packing = false;
	virtual void Pack() { return; };

	template<class T>
	T* CastTo()
	{
		T* result = reinterpret_cast<T*>(this);
		return result;
	}
};
