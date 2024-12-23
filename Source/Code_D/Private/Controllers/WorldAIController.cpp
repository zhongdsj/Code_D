// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/WorldAIController.h"

#include "DetourCrowdAIController.h"
#include "Navigation/PathFollowingComponent.h"

void AWorldAIController::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);
	if(!m_useAvoid)
	{
		return;
	}

	auto path = this->GetPathFollowingComponent()->GetPath();
	
	if (path != nullptr)
	{
		// path.bObservingGoalActor;
		auto goal_actor = path->GetGoalActor();
		FHitResult out_hit;
		auto forward = this->GetPawn()->GetActorForwardVector();
		auto line_start = this->GetPawn()->GetActorLocation() + forward * 40;
		FCollisionQueryParams params;
		bool hit = this->GetWorld()->LineTraceSingleByChannel(out_hit, line_start , line_start + forward * this->m_voLength, ECollisionChannel::ECC_Visibility, FCollisionQueryParams::DefaultQueryParam);
		// DrawDebugLine(GetWorld(), line_start, out_hit.GetActor() ? out_hit.Location : line_start + forward * this->m_voLength, FColor::Red, false, 0);
		auto hit_actor = out_hit.GetActor();
		// GEngine->AddOnScreenDebugMessage(static_cast<uint64>(this->GetUniqueID()) + 1, 2, FColor::Red, FString::Printf(TEXT("begin: (%f, %f, %f), end: (%f, %f, %f)"), points.Num(), index, point_location.X, point_location.Y, point_location.Z));
		if (hit && hit_actor != this->GetPawn() && hit_actor != goal_actor)
		{
			this->m_endLocation = path->GetEndLocation();
			FVector focal = this->GetPawn()->GetActorLocation() + this->GetPawn()->GetActorRightVector() * -200;
			this->MoveToLocation(focal);
			this->m_avoid = true;
		}
	}
}

void AWorldAIController::OnMoveCompleted(FAIRequestID _requestID, const FPathFollowingResult& _result)
{
	Super::OnMoveCompleted(_requestID, _result);
	if(this->m_avoid)
	{
		this->MoveToLocation(this->m_endLocation);
		this->m_avoid = false;
	}
}