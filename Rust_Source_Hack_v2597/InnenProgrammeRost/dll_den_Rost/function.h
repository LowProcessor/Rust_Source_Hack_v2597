#pragma once
#include"RW_Function.h"
#include"StructFunction.h"
DWORD64 BASE_PLAYER;
float HP;
int Zahl;
Vector3 LocalPlayer_pos,Entitat_Pos_bein, Entitat_Pos_Kopf;
Vector2 BildSchirmPos_bein,BildSchirmPos_Kopf, ViewAngel, delta_Angle;
float min_FOV=-1.0f, FOV_;
float distantion = 0;

bool AIM_EINSCHALTEN = 1;
bool suchen_ziel = 0;
void AIM_BOT(DWORD64 LocalPlayerAddress, Vector2 ViewAngle, Vector2 d_Angle)
{

	Vector2 neu_Angle;
	neu_Angle.x = ViewAngle.x + d_Angle.x;
	neu_Angle.y = ViewAngle.y + d_Angle.y;
	LocalPlayerAddress = read<DWORD64>(LocalPlayerAddress + PlayerInput);
	if (flag == 1) {
		write(LocalPlayerAddress + view_angle, neu_Angle);
	}
}

int min_idx = -1;

void ErwerbEntitat()
{
	
	dst = -1.0f;
	min_FOV = -1.0f;
	
	 Zahl = BekammtZahlEntitat();
	 int zahl_ent_aim = 0;
	 if (Zahl <= 0) return;
	EntityClass = read<DWORD64>(EntityObject + 0x10);
	if ((EntityClass <= 0) || (EntityClass == (DWORD64)nullptr)) return;
	DWORD64 *Entitaten = new DWORD64[Zahl];
	
//	d3d_device->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 0, 0, 0), 1, 0);
	
//	d3d_device->BeginScene();
	//DrawBox(111, 222, 111,111, 1, D3DCOLOR_ARGB(255, 255, 0, 0, 0));
	
	
	if (GetAsyncKeyState(0x4C))AIM_EINSCHALTEN = !AIM_EINSCHALTEN;
	//InvalidateRect(TargetWnd, 0, true);
	//InvalidateRect(TargetWnd, 0, 1);
	//int *idx_z = new int[Zahl];
	for (int i = 0; i < Zahl; i++)
	{
		
		
		//InvalidateRect(TargetWnd, 0, true);
		Entitaten[i] = read<DWORD64>(EntityClass + 0x20 + (i * 0x8));
		
		if ((Entitaten[i] <= 0) || (Entitaten[i] == (DWORD64)nullptr)) return;
		//int ID = GetPrefabId(Entitaten[i]);
		//if (HP != 0)
		//{
		//DWORD64 ID = GetPrefabId(Entitaten[i]);
		HP = HealthZahl(Entitaten[i]);
		if (i == 0)
		{
			ErwerbViewMatrx();
			LocalPlayer_pos = ErwerbPos(Entitaten[i]);
			ViewAngel = ErwerbAngle(Entitaten[0]);
			//printf("%f %f %f \n", vMatrix._11, vMatrix._12, vMatrix._13);
		}
		else if ((HP <= 100.0f) && (HP >1) && HP!=35 && HP!=50 && HP!=25)
		{
			
			Entitat_Pos_bein = ErwerbPos(Entitaten[i]);
			Entitat_Pos_Kopf.x = Entitat_Pos_bein.x;
			Entitat_Pos_Kopf.y = Entitat_Pos_bein.y + 1.25f;
			Entitat_Pos_Kopf.z = Entitat_Pos_bein.z;

			distantion = Rechnen3DDistantion(LocalPlayer_pos, Entitat_Pos_bein);
		//	min_idx = Nachteste_Ziel(distantion, i);
		//	if ((AIM_EINSCHALTEN==1)) {
				
		//	}
			
			if ((distantion <= 90))
			{
				
				FOV_ = FOV_SUCHEN(LocalPlayer_pos, ErwerbPos(Entitaten[i]), ViewAngel);
				if (min_FOV == -1.0f)
				{
					min_FOV = FOV_;
					min_idx = i;
				}
				else
				{
					if (min_FOV > FOV_)
					{
						min_FOV = FOV_;
						min_idx = i;
					}
				}
				/*
					if (dst <= 0.0f)
					{
						dst = distantion;
						min_idx = i;
					}
					else
					{
						if (dst > distantion) {
							dst = distantion;
							min_idx = i;
						}
					}
					*/
					
					//zahl_ent_aim++;
				
				//printf("Entitaten[ %d ] ID: %I64d\n", i, ID);
				//printf("Entitaten[ %d ]\n", i);

				//get_name_object(Entitaten[i]);
				//printf("HP: %f \n", HP);

				BildSchirmPos_bein = WorldToScreen(Entitat_Pos_bein);
				BildSchirmPos_Kopf = WorldToScreen(Entitat_Pos_Kopf);
				BOX_ESP(BildSchirmPos_bein.x, BildSchirmPos_bein.y, abs(BildSchirmPos_Kopf.y - BildSchirmPos_bein.y)/2, abs(BildSchirmPos_Kopf.y - BildSchirmPos_bein.y), 3);
				ESP_HP_oder_Distantion(BildSchirmPos_bein.x, BildSchirmPos_bein.y , distantion);
				ESP_HP_oder_Distantion(BildSchirmPos_Kopf.x, BildSchirmPos_Kopf.y, HP);
				//IDX_PRINT(BildSchirmPos_Kopf.x, BildSchirmPos_Kopf.y, i);
				//printf("min_idx %d \n", min_idx);
				//printf("Position: %f %f %f\n", Entitat_Pos.x, Entitat_Pos.y, Entitat_Pos.z);
				//printf("Distantion: %f\n", distantion);
				//printf("Position Bild: %f %f\n", BildSchirmPos.x, BildSchirmPos.y);
			}
			//}
			//}
			
		}
	}
	if (AIM_EINSCHALTEN) {
		if (GetAsyncKeyState(VK_RBUTTON)) {
			suchen_ziel = 1;
			//printf("min_idx: %d\n", min_idx);
			//if (i >= min_idx)
			AIM_BOT(Entitaten[0], ViewAngel, Rechnen3DAngle(LocalPlayer_pos, ErwerbPos(Entitaten[min_idx]), ViewAngel)); //исправить функцию Nachteste_Ziel(distantion, i);
		}
	}
	
//	d3d_device->EndScene();
//	d3d_device->Present(0, 0, 0, 0);
	
	//min_idx = 0;
	delete[] Entitaten;
}

