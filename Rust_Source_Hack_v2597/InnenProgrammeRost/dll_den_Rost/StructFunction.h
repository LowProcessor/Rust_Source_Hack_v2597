#pragma once
#include"RW_Function.h"
#include"decryption_function.h"
#include"NeuTypeDatei.h"
#include<math.h>
#include"ESP.h"
using namespace std;

DWORD64 basenetworkable, ClientEntity, EntityList, EntityObject, EntityClass;
Matrix4x4 vMatrix;
char buffer[1024]="";
DWORD64 EAddr;
float dst = -1.0f;
bool flag = 0;
int BekammtZahlEntitat()
{
	
	int AnzahlEntitat = 0;
	

	basenetworkable = read<DWORD64>(GameAssembleyBaseAddress + basenetworkable_c);
	if ((basenetworkable <= 0) || (basenetworkable == (DWORD64)nullptr))return -1;
	printf("basenetworkable: %I64x \n", basenetworkable);
	basenetworkable = read<DWORD64>(basenetworkable + 0xB8);
	if ((basenetworkable <= 0) || (basenetworkable == (DWORD64)nullptr))return -1;
	ClientEntity = read<DWORD64>(basenetworkable + 0x10);
	if ((ClientEntity <= 0) || (ClientEntity == (DWORD64)nullptr))return -1;
	printf("ClientEntity_salanta: %I64x \n", ClientEntity);
	ClientEntity = ClientEntities(ClientEntity);
	if ((ClientEntity <= 0) || (ClientEntity == (DWORD64)nullptr))return -1;
	printf("ClientEntity_purkaa: %I64x \n", ClientEntity);
	EntityList = read<DWORD64>(ClientEntity + 0x10);
	if ((EntityList <= 0) || (EntityList == (DWORD64)nullptr))return -1;
	printf("ClientEntity_salantaa: %I64x \n", EntityList);
	EntityList = EntityList_parkaa(EntityList);
	if ((EntityList <= 0) || (EntityList == (DWORD64)nullptr))return -1;
	printf("EntityList_parkaa: %I64x \n", EntityList);
	EntityObject = read<DWORD64>(EntityList + 0x18);
	if ((EntityObject <= 0) || (EntityObject == (DWORD64)nullptr))return -1;
	AnzahlEntitat = read<int>(EntityObject + 0x18);
	if ((AnzahlEntitat <= 0) || (AnzahlEntitat == (DWORD64)nullptr))return -1;
	printf("AnzahlEntitat: %d \n", AnzahlEntitat);
	return AnzahlEntitat;
}
float HealthZahl(DWORD64 EntitatAddr)
{
	float HP  = read<float>(EntitatAddr + health);;
	return HP;
}

Vector3 ErwerbPos(DWORD64 EntitatAddr)
{
	Vector3 Position;
	EntitatAddr = read<DWORD64>(EntitatAddr + 0x10);
	EntitatAddr = read<DWORD64>(EntitatAddr + 0x30);
	EntitatAddr = read<DWORD64>(EntitatAddr + 0x30);
	EntitatAddr = read<DWORD64>(EntitatAddr + 0x8);
	EntitatAddr = read<DWORD64>(EntitatAddr + 0x38);
	Position  = read<Vector3>(EntitatAddr + 0x90);
	return Position;
}
DWORD64 Camera;
void ErwerbViewMatrx()
{
	Camera = read<DWORD64>(GameAssembleyBaseAddress + maincamera_c);
	Camera = read<DWORD64>(Camera+maincamera_chain1);
	Camera = read<DWORD64>(Camera + maincamera_chain2);
	Camera = read<DWORD64>(Camera + maincamera_chain3);
	vMatrix = read<Matrix4x4>(Camera + oMatrix);
	
	
}

Vector2 ErwerbAngle(DWORD64 EntitatAddr)
{
	Vector2 Angle;
	EntitatAddr = read<DWORD64>(EntitatAddr + PlayerInput);
	Angle = read<Vector2>(EntitatAddr + view_angle);

	return Angle;
}

DWORD64 obj_name;
DWORD64 GetPrefabId(DWORD64 EntitatAddr)
{
	
	EntitatAddr = read<DWORD64>(EntitatAddr + 0x10);
	EntitatAddr = read<DWORD64>(EntitatAddr + 0x30);
	EntitatAddr = read<DWORD64>(EntitatAddr + 0x60);
	obj_name = read<DWORD64>(EntitatAddr + 0x14);
	return obj_name;
}
float Rechnen3DDistantion(Vector3 MeinePosition, Vector3 EntitatPosition)
{
	return sqrt((MeinePosition.x - EntitatPosition.x)*(MeinePosition.x - EntitatPosition.x) + (MeinePosition.y - EntitatPosition.y)*(MeinePosition.y - EntitatPosition.y) + (MeinePosition.z - EntitatPosition.z)*(MeinePosition.z - EntitatPosition.z));
}
float RechnenHyp(Vector3 MeinePosition, Vector3 EntitatPosition)
{
	return sqrt((MeinePosition.x - EntitatPosition.x)*(MeinePosition.x - EntitatPosition.x)  + (MeinePosition.z - EntitatPosition.z)*(MeinePosition.z - EntitatPosition.z));
}
int Nachteste_Ziel(float r_dst,int idx)
{
	int index=0;

	if (dst <= 0.0f)
	{
		dst = r_dst;
	}
	if (dst > r_dst)
	{
		dst = r_dst;
		index = idx;
	}

	return index;
}
bool compare(const std::string& left, const std::string& right)
{
	return left.length() < right.length();
}
float FOV_SUCHEN(Vector3 MeinePosition, Vector3 EntitatPosition, Vector2 vec_view)
{
	Vector3 vec;
	Vector2 ang;
	Vector2 err(0, 0);
	float hyp = RechnenHyp(MeinePosition, EntitatPosition);
	vec.x = EntitatPosition.x - MeinePosition.x;
	vec.y = EntitatPosition.y - MeinePosition.y;
	vec.z = EntitatPosition.z - MeinePosition.z;
	ang.x = 0; //atanf(((vec.z / vec.y)))* 57.295779513082f;
	ang.y = (acosf((vec.z / hyp)))* 57.295779513082f;
	bool f = 0;
	if (abs(MeinePosition.x) < abs(EntitatPosition.x))
	{
		f = 1;
	}
	if (vec_view.y < 0)
	{

		if (abs(vec_view.y) >= 180.0f)
		{
			vec_view.y += 360.0f;
		}

		if (ang.y < 0)
		{
			ang.y = -vec_view.y - ang.y;
		}
		else if (ang.y > 0)
		{
			ang.y = ang.y - abs(vec_view.y);
		}

	}
	else if (vec_view.y > 0)
	{

		if (abs(vec_view.y) >= 180.0f)
		{
			vec_view.y -= 360.0f;
		}

		if (ang.y < 0)
		{
			ang.y = -ang.y - vec_view.y;
		}
		else if (ang.y > 0)
		{
			ang.y = (ang.y - abs(vec_view.y));
		}

	}


	float FOV_RECH = abs(ang.y);
	//printf("FOV %f: \n", FOV_RECH);
	if (abs(FOV_RECH) <= 30.0f) {

		flag = 1;
		if (f == 1)
		{
			ang.y = -ang.y;
		}
		return abs(FOV_RECH);
	}

	flag = 0;
	return abs(FOV_RECH);


}

Vector2 Rechnen3DAngle(Vector3 MeinePosition, Vector3 EntitatPosition, Vector2 vec_view)
{
	Vector3 vec;
	Vector2 ang;
	Vector2 err(0, 0);
	float hyp = RechnenHyp(MeinePosition, EntitatPosition);
	vec.x = EntitatPosition.x - MeinePosition.x;
	vec.y = EntitatPosition.y - MeinePosition.y;
	vec.z = EntitatPosition.z - MeinePosition.z;
	ang.x = 0; //atanf(((vec.z / vec.y)))* 57.295779513082f;
	ang.y = (acosf((vec.z / hyp)))* 57.295779513082f;
	bool f = 0;
	if (abs(MeinePosition.x) < abs(EntitatPosition.x))
	{
		f = 1;
	}
	if (vec_view.y < 0)
	{

		if (abs(vec_view.y) >= 180.0f)
		{
			vec_view.y += 360.0f;
		}

		if (ang.y < 0)
		{
			ang.y = -vec_view.y - ang.y;
		}
		else if (ang.y > 0)
		{
			ang.y = ang.y - abs(vec_view.y);
		}

	}
	else if (vec_view.y > 0)
	{

		if (abs(vec_view.y) >= 180.0f)
		{
			vec_view.y -= 360.0f;
		}

		if (ang.y < 0)
		{
			ang.y = -ang.y - vec_view.y;
		}
		else if (ang.y > 0)
		{
			ang.y = (ang.y - abs(vec_view.y));
		}

	}


	float FOV_RECH = abs(ang.y);
	//printf("FOV %f: \n", FOV_RECH);
	if (abs(FOV_RECH) <= 30.0f) {

		flag = 1;
		if (f == 1)
		{
			ang.y = -ang.y;
		}
		return ang;
	}

	flag = 0;
	return err;


}

Vector2 WorldToScreen(Vector3 EntityPos)
{
	float pViewMatrix[4][4] = { {vMatrix._11,vMatrix._12,vMatrix._13,vMatrix._14},
								{vMatrix._21,vMatrix._22,vMatrix._23,vMatrix._24},
								{vMatrix._31,vMatrix._32,vMatrix._33,vMatrix._34},
								{vMatrix._41,vMatrix._42,vMatrix._43,vMatrix._44}, };
	Vector2 BildSchirmPos,fehlr(-1,-1);
	Vector3 TransVec = Vector3(pViewMatrix[0][3], pViewMatrix[1][3], pViewMatrix[2][3]);
	Vector3 RightVec = Vector3(pViewMatrix[0][0], pViewMatrix[1][0], pViewMatrix[2][0]);
	Vector3 UpVec = Vector3(pViewMatrix[0][1], pViewMatrix[1][1], pViewMatrix[2][1]);
	float w = Dot(TransVec, EntityPos) + pViewMatrix[3][3];
	if (w < 0.098f)
		return fehlr;

	float y = Dot(UpVec, EntityPos) + pViewMatrix[3][1];
	float x = Dot(RightVec, EntityPos) + pViewMatrix[3][0];
	BildSchirmPos = Vector2((WIDTH / 2) * (1.f + x / w), (HEIGHT / 2) * (1.f - y / w));
	BildSchirmPos.x = BildSchirmPos.x;
	BildSchirmPos.y = BildSchirmPos.y;

	return BildSchirmPos;
}



/*
DWORD64 GetPrefabId(DWORD64 EntitatAddr)
{
	EntitatAddr = read<DWORD64>(EntitatAddr + 0x10);
	EntitatAddr = read<DWORD64>(EntitatAddr + 0x30);
	EntitatAddr = read<DWORD64>(EntitatAddr + 0x30);
	EntitatAddr = read<DWORD64>(EntitatAddr + 0x8);
	EntitatAddr = read<DWORD64>(EntitatAddr + 0x38);
	EntitatAddr = read<DWORD64>(EntitatAddr + 0x30);
	return EntitatAddr;
}
*/
/*
DWORD64 GetTransform(DWORD64 EntitatAddr, int bone)
{
	DWORD64 player_model;
	player_model = read<DWORD64>(EntitatAddr + PlayerModel);
	DWORD64 boneTransforms;
	boneTransforms = read<DWORD64>(player_model +bonetransform);
	DWORD64 BoneValue;
	BoneValue =read<DWORD64>((boneTransforms + (0x20 + (bone * 0x8))));
	DWORD64 ret;
	ret = read<DWORD64>(BoneValue + 0x10);
	return ret;
}

Vector3 GetPosition(DWORD64 transform)
{
	__m128 result;
	int x = 0, y = 0;
	const __m128 mulVec0 = { -2.000, 2.000, -2.000, 0.000 };
	const __m128 mulVec1 = { 2.000, -2.000, -2.000, 0.000 };
	const __m128 mulVec2 = { -2.000, -2.000, 2.000, 0.000 };

	TransformAccessReadOnly pTransformAccessReadOnly;
	pTransformAccessReadOnly = read<TransformAccessReadOnly>(transform + 0x38);
	unsigned int index;
	index = read<unsigned int>(transform + 0x40);
	TransformData transformData;
	transformData = read<TransformData>(pTransformAccessReadOnly.pTransformData + 0x18);

	if (transformData.pTransformArray && transformData.pTransformIndices)
	{

		
		result = read<__m128>(transformData.pTransformArray + 0x30 * index);
		int transformIndex;
		transformIndex = read<int>(transformData.pTransformIndices + 0x4 * index);
		int pSafe = 0;
		while (transformIndex >= 0 && pSafe++ < 200)
		{
			Matrix34 matrix34;
			matrix34 = read<Matrix34>(transformData.pTransformArray + 0x30 * transformIndex);

			__m128 xxxx = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x00));	// xxxx
			__m128 yyyy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x55));	// yyyy
			__m128 zwxy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x8E));	// zwxy
			__m128 wzyw = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0xDB));	// wzyw
			__m128 zzzz = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0xAA));	// zzzz
			__m128 yxwy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x71));	// yxwy
			__m128 tmp7 = _mm_mul_ps(*(__m128*)(&matrix34.vec2), result);

			result = _mm_add_ps(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(xxxx, mulVec1), zwxy),
								_mm_mul_ps(_mm_mul_ps(yyyy, mulVec2), wzyw)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0xAA))),
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(zzzz, mulVec2), wzyw),
								_mm_mul_ps(_mm_mul_ps(xxxx, mulVec0), yxwy)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x55)))),
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(yyyy, mulVec0), yxwy),
								_mm_mul_ps(_mm_mul_ps(zzzz, mulVec1), zwxy)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x00))),
						tmp7)), *(__m128*)(&matrix34.vec0));

			transformIndex;
			transformIndex = read<int>(transformData.pTransformIndices + 0x4 * transformIndex);

		}
	}
	Vector3 pos;
	pos.x = result.m128_f32[0];
	pos.y = result.m128_f32[1] - 1;
	pos.z = result.m128_f32[2];

	

	return pos;
}


*/
