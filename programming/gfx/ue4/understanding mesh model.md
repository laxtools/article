# understanding mesh model 

UE4의 매시 모델의 매시, 애님, 재질 (+쉐이더), 피직스(?)에 대해 살펴본다. 양이 방대하므로 매시와 애님에 집중하고 이후 재질과 피직스를 본다. 



# 목표 

- FBX import / export 코드 이해 
- 매시 / 애님 스펙 
- 관련 쉐이더의 동작 



# 진행 

프로젝트 생성 FBX import 호출. 매시와 애님 임포트 코드 보기. 

D:\Epic Games\Launcher\Engine\Binaries\Win64

EpicGamesLaucher로 시작. 

현재 설치 버전으 4.14.0. 

C++ 프로젝트 생성 



## 시작 단초 

`FFbxImportAssetsAutomationTest::RunTest` of FbxAutomationTests.cpp 

- UFbxFactory
- UStaticMesh
- USkeletalMesh



## UFbxFactory 

`UnFbx::FFbxImporter`

- ImportStaticMeshAsSingle



Engine\Source\Editor\UnrealEd\Private\Fbx

- 여기에 Fbx 관련 처리가 다 들어있다. 



# 정적 매시 

UStaticMesh 

```c++
TScopedPointer<class FStaticMeshRenderData> RenderData;
TArray<FStaticMaterial> StaticMaterials;
float LightmapUVDensity;
int32 LightMapResolution;
int32 LightMapCoordinateIndex;
class UBodySetup* BodySetup;
uint32 bHasNavigationData:1;
float LpvBiasMultiplier;
bool bAllowCPUAccess;
FRenderCommandFence ReleaseResourcesFence;
FString HighResSourceMeshName;
uint32 HighResSourceMeshCRC;
FGuid LightingGuid;
TArray<class UStaticMeshSocket*> Sockets;
TSharedPtr<class FSpeedTreeWind> SpeedTreeWind;
FVector PositiveBoundsExtension;
FVector NegativeBoundsExtension;
FBoxSphereBounds ExtendedBounds;
```

FStaticMeshLODResources
```c++
FStaticMeshVertexBuffer VertexBuffer;
FPositionVertexBuffer PositionVertexBuffer;
FColorVertexBuffer ColorVertexBuffer;

FRawStaticIndexBuffer IndexBuffer;
FRawStaticIndexBuffer DepthOnlyIndexBuffer;
FRawStaticIndexBuffer ReversedDepthOnlyIndexBuffer;
FRawStaticIndexBuffer WireframeIndexBuffer;
FRawStaticIndexBuffer AdjacencyIndexBuffer;
FLocalVertexFactory VertexFactory;
FLocalVertexFactory VertexFactoryOverrideColorVertexBuffer;
TArray<FStaticMeshSection> Sections;
class FDistanceFieldVolumeData* DistanceFieldData; 

float MaxDeviation;
uint32 bHasAdjacencyInfo : 1;
uint32 bHasDepthOnlyIndices : 1;
uint32 bHasReversedIndices : 1;
uint32 bHasReversedDepthOnlyIndices: 1;

uint32 DepthOnlyNumTriangles;

struct FSplineMeshVertexFactory* SplineVertexFactory;
struct FSplineMeshVertexFactory* SplineVertexFactoryOverrideColorVertexBuffer;
```



FStaticMeshSection

- 같은 재질로 그려지는 부분이기 때문에 재질 측면에서 중요할 듯 

RHI (Rendering Hardware Interface 일 듯)

매시의 의미는 사용에서 드러난다. Fbx import 과정에서 Fbx의 의미와 매핑된다. 렌더링 할 때 렌더링 의미로 결정된다. 위와 같이 두 가지 방향에서 의미를 결정할 수 있다. 



# Skeletal Mesh 

https://docs.unrealengine.com/en-us/Engine/Content/FBX/







# 자료 



## shader

.usf 파일들. 자체 언어. transpiler로 타겟 RHI의 쉐이더로 빌드.  정확한 구조는 더 복잡할 듯. 



## FBX 이해 

http://docs.autodesk.com/FBX/2014/ENU/FBX-SDK-Documentation/

### Your First FBX SDK Program 

The following FBX SDK program provides an overview about how to:

1. Instantiate an FBX SDK memory management object. ([FbxManager](javascript:void(0)))
2. Import the contents of an FBX file into a scene. ([FbxIOSettings](javascript:void(0)), [FbxImporter](javascript:void(0)), [FbxScene](javascript:void(0)))
3. Traverse the element hierarchy of a scene. ([FbxScene](javascript:void(0)), [FbxNode](javascript:void(0)), [FbxNodeAttribute](javascript:void(0)))
4. Access and print basic information about the elements of a scene. ([FbxNode](javascript:void(0)), [FbxNodeAttribute](javascript:void(0)), [FbxString](javascript:void(0)))



### Animation 

- animation stacks ([FbxAnimStack](javascript:void(0))), 
- animation layers ([FbxAnimLayer](javascript:void(0))), 
- animation curve nodes ([FbxAnimCurveNode](javascript:void(0))), 
- animation curves ([FbxAnimCurve](javascript:void(0))), 
- animation curve keys ([FbxAnimCurveKey](javascript:void(0))) 



Bone 정보는 어떻게 얻는가? Joint로 불리고 애니메이션을 export할 때 선택한다. FBX 파일에 해당 정보가 들어있어야 한다. 어디에 들어있는 지는 확인해야 한다. 



직접 해보지 않으면 다 이해하기가 어려운 면이 있다. 이번 주 풀로 시간을 투자 한다. 


















