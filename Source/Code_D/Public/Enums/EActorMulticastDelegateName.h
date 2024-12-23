// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM()
enum class EActorMulticastDelegateName : uint8
{
	Begin_Cursor_Over = 0,
	End_Cursor_Over,
	On_Click,
	On_Release,
	Begin_Check,
	End_Check,
	Begin_Space,
	End_Space
};