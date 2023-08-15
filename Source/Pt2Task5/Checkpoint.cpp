// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"

#include "DSP/MelScale.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Cylinder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CylinderStaticMesh"));
	SetRootComponent(SM_Cylinder);
	
	SM_Button_A_Ring = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonRing"));
	SM_Button_A_Ring->SetupAttachment(RootComponent);
	
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);
	
	CheckpointText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Checkpoint"));
	CheckpointText->SetupAttachment(RootComponent);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereComponent->SetupAttachment(RootComponent);
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnBeginOverlap);
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpoint::OnConstruction(const FTransform& Transform)
{
	DynamicMaterialInstanceReference = UMaterialInstanceDynamic::Create(SM_Cylinder->GetMaterial(0), SM_Cylinder);
}

void ACheckpoint::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!bCheckpointEnabled)
	{
		bCheckpointEnabled = true;
		DynamicMaterialInstanceReference->SetVectorParameterValue(TEXT("Color"), FColor::Blue);
		SM_Cylinder->SetMaterial(0, DynamicMaterialInstanceReference);
		UpdateSpawnTransform(Arrow->GetComponentTransform());
		UGameplayStatics::SpawnSound2D(this, Sound);
	}
}
