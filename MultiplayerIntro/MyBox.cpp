// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBox.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyBox::AMyBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ReplicatedVar = 100.f;
	//bReplicates = true;
}

// Called when the game starts or when spawned
void AMyBox::BeginPlay()
{
	Super::BeginPlay();
	
	SetReplicates(true);
	SetReplicateMovement(true);

	if (HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimer(TestTimer, this, &AMyBox::NetMulticastRPCExplode, 2.f, false);
	}
}

// Called every frame
void AMyBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{

	}
	else
	{

	}
	//if (GetLocalRole() == ROLE_Authority)
}

//function needed for successful replication
void AMyBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//makes sure this variable is replicated (needs #include Net/UnrealNetwork.h)
	DOREPLIFETIME(AMyBox, ReplicatedVar);
}

//called on all clients whenever its assigned variable is changed, must call manually to run a replicated function on a server
void AMyBox::OnRep_ReplicatedVar()
{
	if (HasAuthority())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Green, TEXT("Server: OnRep_ReplicatedVar"));
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Yellow, 
			//FString::Printf(TEXT("Client %d: OnRep_ReplicatedVar"), GPlayInEditorID));
	}
}

void AMyBox::DecreaseReplicatedVar()
{
	//Check for authority so only the server can manipulate the replicated variable, clients should not be manipulating replicated variables.
	if (HasAuthority())
	{
		--ReplicatedVar;
		OnRep_ReplicatedVar(); //must be called manually to run function on server
		if (ReplicatedVar > 0)
		{
			GetWorld()->GetTimerManager().SetTimer(TestTimer, this, &AMyBox::DecreaseReplicatedVar, 2.f, false);
		}
	}
}

void AMyBox::NetMulticastRPCExplode_Implementation()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Server: NetMulticastRPCExplode_Implementation"));
		GetWorld()->GetTimerManager().SetTimer(TestTimer, this, &AMyBox::NetMulticastRPCExplode, 2.f, false);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Client: NetMulticastRPCExplode_Implementation"));
	}

	//there are no graphics being displayed on a dedicated server, therefore it makes no sense to spawn particles on a dedicated server
	if (!IsRunningDedicatedServer())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation(), FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);
	}
}