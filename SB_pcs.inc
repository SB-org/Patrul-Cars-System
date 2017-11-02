/*

   Patrul Car System
	by SooBad
   02/11/17
                   
*/

//==================== MACROS:
#if !defined _samp_included 
    #error "Please include a_samp or a_npc, before this inc!"
#endif

#if defined __PawnBuild
    #if !defined streamer_included && !defined STREAMER_TYPE_OBJECT
        #warning "Please include streamer plugin for correct operation!"
    #endif
#endif

#if defined SB_pcs_inc
    #endinput
#endif
#define SB_pcs_inc

#if !defined D_PCS_NITRO
    #define D_PCS_NITRO 5777
#endif

//==================== GLOBAL VARIABLES:
static
    p_car,
    p_car_siren,
    p_car_neon_1, p_car_neon_2,
    p_car_nitro[MAX_PLAYERS char],
    p_car_fnitro,
    p_car_fsiren;

//==================== CALLBACKS:
public OnGameModeInit()
{
    p_car = AddStaticVehicleEx(470, -226.8, 992.0, 19.6, 270.0, 0, 0, 0, 1);
    SetVehicleNumberPlate(p_car, !"PATRUL");
    AddDefTune(p_car);	   

    #if defined SB_pcs_OnGameModeInit
        return SB_pcs_OnGameModeInit();
    #else
        return 1;
    #endif
}
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit SB_pcs_OnGameModeInit
#if defined SB_pcs_OnGameModeInit
forward SB_pcs_OnGameModeInit();
#endif

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    p_car_nitro{playerid} = 0;

    #if defined SB_pcs_OnPlayerEnterVehicle
    	return SB_pcs_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerEnterVehicle
    #undef OnPlayerEnterVehicle
#else
    #define _ALS_OnPlayerEnterVehicle
#endif
#define OnPlayerEnterVehicle SB_pcs_OnPlayerEnterVehicle
#if defined SB_pcs_OnPlayerEnterVehicle
forward SB_pcs_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
#endif

public OnPlayerExitVehicle(playerid, vehicleid)
{
    new pcs_vehid = GetPlayerVehicleID(playerid);

    p_car_nitro{playerid} = 0;

    if(pcs_vehid == p_car)
    {
	#if defined streamer_included || defined STREAMER_TYPE_OBJECT
	    if(IsValidDynamicObject(p_car_fnitro)) 
		DestroyDynamicObject(p_car_fnitro);
	    if(IsValidDynamicObject(p_car_neon_1))
		DestroyDynamicObject(p_car_neon_1);
	    if(IsValidDynamicObject(p_car_neon_2))
		DestroyDynamicObject(p_car_neon_2);
	#else
	    if(IsValidObject(p_car_fnitro))
		DestroyObject(p_car_fnitro);
	    if(IsValidObject(p_car_neon_1)) 
		DestroyObject(p_car_neon_1);
	    if(IsValidObject(p_car_neon_2)) 
		DestroyObject(p_car_neon_2);	
	#endif    
    }
    #if defined SB_pcs_OnPlayerExitVehicle
    	return SB_pcs_OnPlayerExitVehicle(playerid, vehicleid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerExitVehicle
    #undef OnPlayerExitVehicle
#else
    #define _ALS_OnPlayerExitVehicle
#endif
#define OnPlayerExitVehicle SB_pcs_OnPlayerExitVehicle
#if defined SB_pcs_OnPlayerExitVehicle
forward SB_pcs_OnPlayerExitVehicle(playerid, vehicleid);
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    new pcs_vehid = GetPlayerVehicleID(playerid);

    if(IsPlayerInAnyVehicle(playerid) && pcs_vehid == p_car)
    {
	switch(newkeys)
	{
	    case 320, 512:
	    {
		CarAngle(pcs_vehid);
	    }
	    case 2:
	    {
		AddVehicleComponent(pcs_vehid, 1087);
	    }
	    case 4:
	    {
		ShowPlayerDialog(
                    playerid, D_PCS_NITRO, DIALOG_STYLE_LIST,
			!"{00FFFF}Какое нитро?",
			    !"{00FF00}110км/ч\n{FFFF00}130км/ч\n{FF0000}200км/ч", !"Выбрать", !"Закрыть");

		if(p_car_nitro{playerid} == 0)
		{	
		    #if defined streamer_included || defined STREAMER_TYPE_OBJECT
		        if(IsValidDynamicObject(p_car_fnitro) 
			    DestroyDynamicObject(p_car_fnitro);
			else 
			{
			    p_car_fnitro = CreateDynamicObject(18694, 0, 0, 0, 0, 0, 0);
			    AttachDynamicObjectToVehicle(p_car_fnitro, pcs_vehid, -1.2, -2.0, 2.80, 180.0, 0.0, 0.0);
			}
			if(IsValidDynamicObject(p_car_neon_1))
			    DestroyDynamicObject(p_car_neon_1);
			else
			{
			    p_car_neon_1 = CreateDynamicObject(18648, 0, 0, 0, 0, 0, 0);
			    AttachDynamicObjectToVehicle(p_car_neon_1, pcs_vehid, -1.0, -0.3, -0.36, 0.0, 0.0, 0.0);
			}
			if(IsValidDynamicObject(p_car_neon_2))
			    DestroyDynamicObject(p_car_neon_2);
			else
			{
			    p_car_neon_2 = CreateDynamicObject(18648, 0, 0, 0, 0, 0, 0);
			    AttachDynamicObjectToVehicle(p_car_neon_2, pcs_vehid, 1.0, -0.3, -0.36, 0.0, 0.0, 0.0);
			}
			if(IsValidDynamicObject(p_car_fsiren))
			    DestroyDynamicObject(p_car_fsiren);
			else
			{
			    p_car_fsiren = CreateDynamicObject(19419, 0, 0, 0, 0, 0, 0);
			    AttachDynamicObjectToVehicle(p_car_fsiren, pcs_vehid, 0.0, 0.0, 1.1, 0.0, 0.0, 0.0);
			}
		    #else
			if(IsValidObject(p_car_fnitro))
			    DestroyObject(p_car_fnitro);
			else
			{
			    p_car_fnitro = CreateObject(18694, 0, 0, 0, 0, 0, 0);
			    AttachObjectToVehicle(p_car_fnitro, pcs_vehid, -1.2, -2.0, 2.80, 180.0, 0.0, 0.0);
			}
			if(IsValidObject(p_car_neon_1))
			    DestroyObject(p_car_neon_1);
			else
			{
			    p_car_neon_1 = CreateObject(18648, 0, 0, 0, 0, 0, 0);
			    AttachObjectToVehicle(p_car_neon_1, pcs_vehid, -1.0, -0.3, -0.36, 0.0, 0.0, 0.0);
			}
			if(IsValidObject(p_car_neon_2)) 
			    DestroyObject(p_car_neon_2);
			else
			{
			    p_car_neon_2 = CreateObject(18648, 0, 0, 0, 0, 0, 0);
			    AttachObjectToVehicle(p_car_neon_2, pcs_vehid, 1.0, -0.3, -0.36, 0.0, 0.0, 0.0);
			}
			if(IsValidObject(p_car_fsiren))
			    DestroyObject(p_car_fsiren);
			else
			{
			    p_car_fsiren = CreateObject(19419, 0, 0, 0, 0, 0, 0);
			    AttachObjectToVehicle(p_car_fsiren, pcs_vehid, 0.0, 0.0, 1.1, 0.0, 0.0, 0.0);
			}	
		    #endif   
	            }
	    }
	    case 12:
	    {
	        switch(p_car_nitro{playerid})
		{
		    case 1:
		    {
		        SetVehicleSpeed(pcs_vehid, 110);
			p_car_nitro{playerid} = 1;
		    }
		    case 2:
		    {
		        SetVehicleSpeed(pcs_vehid, 130);
			p_car_nitro{playerid} = 2;
		    }
		    case 3:
		    {
			SetVehicleSpeed(pcs_vehid, 200);
			p_car_nitro{playerid} = 3;
		    }
		}
	    }
        }
    }
    #if defined SB_pcs_OnPlayerKeyStateChange
    	return SB_pcs_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerKeyStateChange
    #undef OnPlayerKeyStateChange
#else
    #define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange SB_pcs_OnPlayerKeyStateChange
#if defined SB_pcs_OnPlayerKeyStateChange
forward SB_pcs_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnVehicleDeath(vehicleid, killerid)
{
    new pcs_vehid = GetPlayerVehicleID(killerid);

    if(pcs_vehid == p_car)
    {
	#if defined streamer_included || defined STREAMER_TYPE_OBJECT
	    if(IsValidDynamicObject(p_car_fnitro))
		DestroyDynamicObject(p_car_fnitro);
	    if(IsValidDynamicObject(p_car_neon_1))
		DestroyDynamicObject(p_car_neon_1);
	    if(IsValidDynamicObject(p_car_neon_2))
		DestroyDynamicObject(p_car_neon_2);
        #else
	    if(IsValidObject(p_car_fnitro))
		DestroyObject(p_car_fnitro);
	    if(IsValidObject(p_car_neon_1))
		DestroyObject(p_car_neon_1);
	    if(IsValidObject(p_car_neon_2))
		DestroyObject(p_car_neon_2);	
	#endif    
    }
    #if defined SB_pcs_OnVehicleDeath
    	return SB_pcs_OnVehicleDeath(vehicleid, killerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnVehicleDeath
    #undef OnVehicleDeath
#else
    #define _ALS_OnVehicleDeath
#endif
#define OnVehicleDeath SB_pcs_OnVehicleDeath
#if defined SB_pcs_OnVehicleDeath
forward SB_pcs_OnVehicleDeath(vehicleid, killerid);
#endif

public OnVehicleSpawn(vehicleid)
{
    AddVehicleComponent(p_car, 1085);	

    #if defined SB_pcs_OnVehicleSpawn
        return SB_pcs_OnVehicleSpawn(vehicleid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnVehicleSpawn
    #undef OnVehicleSpawn
#else
    #define _ALS_OnVehicleSpawn
#endif
#define OnVehicleSpawn SB_pcs_OnVehicleSpawn
#if defined SB_pcs_OnVehicleSpawn
forward SB_pcs_OnVehicleSpawn(vehicleid);
#endif

public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
    if(vehicleid == p_car)
    {
	new Float:pcs_vhealth;

	GetVehicleHealth(vehicleid, pcs_vhealth);

        if(pcs_vhealth < 1000.0)
	    SetVehicleHealth(vehicleid, 1000.0);
    }
    #if defined SB_pcs_OnVehicleDamageStatusUpd
        return SB_pcs_OnVehicleDamageStatusUpd(vehicleid, playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnVehicleDamageStatusUpdat
    #undef OnVehicleDamageStatusUpdate
#else
    #define _ALS_OnVehicleDamageStatusUpdat
#endif
#define OnVehicleDamageStatusUpdate SB_pcs_OnVehicleDamageStatusUpd
#if defined SB_pcs_OnVehicleDamageStatusUpd
forward SB_pcs_OnVehicleDamageStatusUpd(vehicleid, playerid);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
	case D_PCS_NITRO:
	{
	    if(response)
	    {
	        switch(listitem)
		{
		    case 0:
		    {
			p_car_nitro{playerid} = 1;
			SendClientMessage(playerid, 0xFF000000, !"Нитро 110км/ч активировано!");
		    }	
		    case 1:
		    {
		        p_car_nitro{playerid} = 2;
			SendClientMessage(playerid, 0xFF000000, !"Нитро 130км/ч активировано!");
		    }
		    case 2:
		    {
			p_car_nitro{playerid} = 3;
			SendClientMessage(playerid, 0xFF000000, !"Нитро 200км/ч активировано!");
		    }
		}
	    }
        }
    }
    #if defined SB_pcs_OnDialogResponse
        return SB_pcs_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnDialogResponse
    #undef OnDialogResponse
#else
    #define _ALS_OnDialogResponse
#endif
#define OnDialogResponse SB_pcs_OnDialogResponse
#if defined SB_pcs_OnDialogResponse
forward SB_pcs_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

//==================== STOCKS:
static stock 
    AddDefTune(p_carid)
{
    AddVehicleComponent(p_carid, 1085);
    
    #if defined streamer_included || defined STREAMER_TYPE_OBJECT
        p_car_siren = CreateDynamicObject(19420, 0, 0, 0, 0, 0, 0);
        AttachDynamicObjectToVehicle(p_car_siren, p_carid, 0.0, 0.0, 1.1, 0.0, 0.0, 0.0);
    #else
	p_car_siren = CreateObject(19420, 0, 0, 0, 0, 0, 0);
        AttachObjectToVehicle(p_car_siren, p_carid, 0.0, 0.0, 1.1, 0.0, 0.0, 0.0);
    #endif

    return 1;
}

static stock 
    CarAngle(p_carid)
{   
    new 
        Float:pcs_x,
        Float:pcs_y,
        Float:pcs_z,
        Float:pcs_angle;

    GetVehiclePos(p_carid, pcs_x, pcs_y, pcs_z);
    GetVehicleZAngle(p_carid, pcs_angle);
    SetVehiclePos(p_carid, pcs_x, pcs_y, pcs_z);
    SetVehicleZAngle(p_carid, pcs_angle);
    SetVehicleSpeed(p_carid, 0);

    return 1;
}

static stock 
    SetVehicleSpeed(p_carid, Float:speed)
{
    new
        Float:pcs_x1, 
	Float:pcs_y1, 
	Float:pcs_z1, 
	Float:pcs_x2, 
	Float:pcs_y2, 
	Float:pcs_z2, 
	Float:pcs_a;
		
    GetVehicleVelocity(p_carid, pcs_x1, pcs_y1, pcs_z1);
    GetVehiclePos(p_carid, pcs_x2, pcs_y2, pcs_z2);
    GetVehicleZAngle(p_carid, pcs_a); 
    pcs_a = 360 - pcs_a;
    
    pcs_x1 = (floatsin(pcs_a, degrees) * (speed/100) + floatcos(pcs_a, degrees) * 0 + pcs_x2) - pcs_x2;
    pcs_y1 = (floatcos(pcs_a, degrees) * (speed/100) + floatsin(pcs_a, degrees) * 0 + pcs_y2) - pcs_y2;
    
    SetVehicleVelocity(p_carid, pcs_x1, pcs_y1, pcs_z1);

    return 1;
}

stock
    SB_pcs_ShowPlayerDialog(playerid, dialogid, style, caption[], info[], button1[], button2[])
        return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);

#if defined _ALS_ShowPlayerDialog
    #undef ShowPlayerDialog
#else
    #define _ALS_ShowPlayerDialog
#endif
#define ShowPlayerDialog SB_pcs_ShowPlayerDialog

stock
    SB_pcs_GetVehicleHealth(vehicleid, &Float:health)
        return GetVehicleHealth(vehicleid, health);

#if defined _ALS_GetVehicleHealth
    #undef GetVehicleHealth
#else
    #define _ALS_GetVehicleHealth
#endif
#define GetVehicleHealth SB_pcs_GetVehicleHealth

stock
    SB_pcs_SetVehicleHealth(vehicleid, Float:health)
        return SetVehicleHealth(vehicleid, health);

#if defined _ALS_SetVehicleHealth
    #undef SetVehicleHealth
#else
    #define _ALS_SetVehicleHealth
#endif
#define SetVehicleHealth SB_pcs_SetVehicleHealth

stock
    SB_pcs_GetVehiclePos(vehicleid, &Float:X, &Float:Y, &Float:Z)
	return GetVehiclePos(vehicleid, X, Y, Z);

#if defined _ALS_GetVehiclePos
    #undef GetVehiclePos
#else
    #define _ALS_GetVehiclePos
#endif
#define GetVehiclePos SB_pcs_GetVehiclePos


stock 
    SB_pcs_SetVehiclePos(vehicleid, Float:x, Float:y, Float:z)
	return SetVehiclePos(vehicleid, x, y, z);

#if defined _ALS_SetVehiclePos
    #undef SetVehiclePos
#else
    #define _ALS_SetVehiclePos
#endif
#define SetVehiclePos SB_pcs_SetVehiclePos


stock
    SB_pcs_GetVehicleZAngle(vehicleid, &Float:z_angle)
	return GetVehicleZAngle(vehicleid, z_angle);

#if defined _ALS_GetVehicleZAngle
    #undef GetVehicleZAngle
#else
    #define _ALS_GetVehicleZAngle
#endif
#define GetVehicleZAngle SB_pcs_GetVehicleZAngle


stock
    SB_pcs_SetVehicleZAngle(vehicleid, &Float:z_angle)
	return SetVehicleZAngle(vehicleid, z_angle);

#if defined _ALS_SetVehicleZAngle
    #undef SetVehicleZAngle
#else
    #define _ALS_SetVehicleZAngle
#endif
#define SetVehicleZAngle SB_pcs_SetVehicleZAngle


stock
    SB_pcs_GetVehicleVelocity(vehicleid, &Float:x, &Float:y, &Float:z)
	return GetVehicleVelocity(vehicleid, x, y, z);

#if defined _ALS_GetVehicleVelocity
    #undef GetVehicleVelocity
#else
    #define _ALS_GetVehicleVelocity
#endif
#define GetVehicleVelocity SB_pcs_GetVehicleVelocity


stock
    SB_pcs_SetVehicleVelocity(vehicleid, Float:x, Float:y, Float:z)
	return SetVehicleVelocity(vehicleid, x, y, z);

#if defined _ALS_SetVehicleVelocity
    #undef SetVehicleVelocity
#else
    #define _ALS_SetVehicleVelocity
#endif
#define SetVehicleVelocity SB_pcs_SetVehicleVelocity
