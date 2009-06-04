/*
	------------------------------------------------------------------------------------
	LICENSE:
	------------------------------------------------------------------------------------
	This file is part of EVEmu: EVE Online Server Emulator
	Copyright 2006 - 2008 The EVEmu Team
	For the latest information visit http://evemu.mmoforge.org
	------------------------------------------------------------------------------------
	This program is free software; you can redistribute it and/or modify it under
	the terms of the GNU Lesser General Public License as published by the Free Software
	Foundation; either version 2 of the License, or (at your option) any later
	version.

	This program is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
	FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License along with
	this program; if not, write to the Free Software Foundation, Inc., 59 Temple
	Place - Suite 330, Boston, MA 02111-1307, USA, or go to
	http://www.gnu.org/copyleft/lesser.txt.
	------------------------------------------------------------------------------------
	Author:		Zhur
*/



#include "EvemuPCH.h"

PyCallable_Make_InnerDispatcher(NetService)

NetService::NetService(PyServiceMgr *mgr)
: PyService(mgr, "machoNet"),
m_dispatch(new Dispatcher(this))
{
	_SetCallDispatcher(m_dispatch);

	PyCallable_REG_CALL(NetService, GetInitVals)
	PyCallable_REG_CALL(NetService, GetTime)
}

NetService::~NetService() {
	delete m_dispatch;
}

PyResult NetService::Handle_GetInitVals(PyCallArgs &call) {
	PyRepTuple *result = new PyRepTuple(2);
	PyRepString str("machoNet.serviceInfo");

	PyRep *serverinfo;
	if(!m_manager->cache_service->IsCacheLoaded(&str)) {
		//not cached yet, we have to generate it
		PyRepDict *dict = new PyRepDict;

		dict->add("trademgr", new PyRepString("station"));
		dict->add("stationSvc", new PyRepNone());
		dict->add("zsystem", new PyRepNone());
		dict->add("invbroker", new PyRepNone());
		dict->add("droneMgr", new PyRepNone());
		dict->add("userSvc", new PyRepNone());
		dict->add("map", new PyRepNone());
		dict->add("beyonce", new PyRepNone());
		dict->add("standing2", new PyRepNone());
		dict->add("ram", new PyRepNone());
		dict->add("DB", new PyRepNone());
		dict->add("posMgr", new PyRepNone());
		dict->add("voucher", new PyRepNone());
		dict->add("entity", new PyRepNone());
		dict->add("damageTracker", new PyRepNone());
		dict->add("agentMgr", new PyRepNone());
		dict->add("dogmaIM", new PyRepNone());
		dict->add("machoNet", new PyRepNone());
		dict->add("dungeonExplorationMgr", new PyRepNone());
		dict->add("watchdog", new PyRepNone());
		dict->add("ship", new PyRepNone());
		dict->add("DB2", new PyRepNone());
		dict->add("market", new PyRepNone());
		dict->add("dungeon", new PyRepNone());
		dict->add("npcSvc", new PyRepNone());
		dict->add("sessionMgr", new PyRepNone());
		dict->add("LSC", new PyRepString("location"));
		dict->add("allianceRegistry", new PyRepNone());
		dict->add("tutorialSvc", new PyRepString("station"));
		dict->add("bookmark", new PyRepString("station"));
		dict->add("cache", new PyRepNone());
		dict->add("character", new PyRepNone());
		dict->add("factory", new PyRepNone());
		dict->add("facWarMgr", new PyRepNone());
		dict->add("corpStationMgr", new PyRepNone());
		dict->add("authentication", new PyRepNone());
		dict->add("station", new PyRepString("location"));
		dict->add("effectCompiler", new PyRepNone());
		dict->add("slash", new PyRepString("station"));
		dict->add("charmgr", new PyRepNone());
		dict->add("BSD", new PyRepNone());
		dict->add("reprocessingSvc", new PyRepNone());
		dict->add("config", new PyRepString("locationPreferred"));
		dict->add("billingMgr", new PyRepNone());
		dict->add("billMgr", new PyRepNone());
		dict->add("lookupSvc", new PyRepNone());
		dict->add("emailreader", new PyRepNone());
		dict->add("lootSvc", new PyRepNone());
		dict->add("http", new PyRepNone());
		dict->add("repairSvc", new PyRepNone());
		dict->add("gagger", new PyRepNone());
		dict->add("dataconfig", new PyRepNone());
		dict->add("lien", new PyRepNone());
		dict->add("i2", new PyRepNone());
		dict->add("wormholeMgr", new PyRepString("station"));
		dict->add("pathfinder", new PyRepNone());
		dict->add("alert", new PyRepNone());
		dict->add("director", new PyRepNone());
		dict->add("dogma", new PyRepNone());
		dict->add("aggressionMgr", new PyRepNone());
		dict->add("corporationSvc", new PyRepNone());
		dict->add("certificateMgr", new PyRepNone());
		dict->add("clones", new PyRepNone());
		dict->add("jumpCloneSvc", new PyRepNone());
		dict->add("insuranceSvc", new PyRepNone());
		dict->add("corpmgr", new PyRepNone());
		dict->add("warRegistry", new PyRepNone());
		dict->add("corpRegistry", new PyRepNone());
		dict->add("account", new PyRepString("station"));
		dict->add("gangSvc", new PyRepString("station"));
		dict->add("objectCaching", new PyRepNone());
		dict->add("counter", new PyRepNone());
		dict->add("petitioner", new PyRepNone());
		dict->add("keeper", new PyRepString("solarsystem"));
		dict->add("LPSvc", new PyRepNone());
		dict->add("clientStatsMgr", new PyRepNone());
		dict->add("jumpbeaconsvc", new PyRepNone());
		dict->add("scanMgr", new PyRepString("solarsystem"));
		dict->add("contractMgr", new PyRepString("station"));
		dict->add("debug", new PyRepNone());
		dict->add("languageSvc", new PyRepNone());
		dict->add("skillMgr", new PyRepNone());
		dict->add("voiceMgr", new PyRepNone());
		dict->add("onlineStatus", new PyRepNone());
		dict->add("gangSvcObjectHandler", new PyRepNone());

		//register it
		m_manager->cache_service->GiveCache(&str, (PyRep **)&dict);
	}
	serverinfo = m_manager->cache_service->GetCacheHint(str.value.c_str());

	PyRepDict *initvals = new PyRepDict();
    //send all the cache hints needed for server info.
	m_manager->cache_service->InsertCacheHints(ObjCacheService::hLoginCachables, initvals);

	result->items[0] = serverinfo;
	result->items[1] = initvals;

	return result;
}

PyResult NetService::Handle_GetTime(PyCallArgs &call) {
	return(new PyRepInteger(Win32TimeNow()));
}




















