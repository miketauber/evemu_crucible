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

PyCallable_Make_InnerDispatcher(CharMgrService)

CharMgrService::CharMgrService(PyServiceMgr *mgr, DBcore *dbc)
: PyService(mgr, "charmgr"),
  m_dispatch(new Dispatcher(this)),
  m_db(dbc)
{
	_SetCallDispatcher(m_dispatch);

	PyCallable_REG_CALL(CharMgrService, GetPublicInfo)
	PyCallable_REG_CALL(CharMgrService, GetPublicInfo3)
	PyCallable_REG_CALL(CharMgrService, GetTopBounties)
}

CharMgrService::~CharMgrService() {
	delete m_dispatch;
}

PyResult CharMgrService::Handle_GetPublicInfo(PyCallArgs &call) {
	//takes a single int arg: char id
	// or corp id
	Call_SingleIntegerArg args;
	if(!args.Decode(&call.tuple)) {
		codelog(CLIENT__ERROR, "%s: Failed to decode arguments.", call.client->GetName());
		return NULL;
	}

	/*if(IsAgent(args.arg)) {
		//handle agents special right now...
		PyRep *result = m_db.GetAgentPublicInfo(args.arg);
		if(result == NULL) {
			codelog(CLIENT__ERROR, "%s: Failed to find agent %u", call.client->GetName(), args.arg);
			return NULL;
		}
		return result;
	}*/

	PyRep *result = m_db.GetCharPublicInfo(args.arg);
	if(result == NULL) {
		codelog(CLIENT__ERROR, "%s: Failed to find char %u", call.client->GetName(), args.arg);
		return NULL;
	}
	
	return result;
}

PyResult CharMgrService::Handle_GetPublicInfo3(PyCallArgs &call) {
	//takes a single int arg: char id
	Call_SingleIntegerArg args;
	if(!args.Decode(&call.tuple)) {
		codelog(CLIENT__ERROR, "%s: Failed to decode arguments.", call.client->GetName());
		return NULL;
	}
	
	PyRep *result = m_db.GetCharPublicInfo3(args.arg);
	if(result == NULL) {
		codelog(CLIENT__ERROR, "%s: Failed to find char %u", call.client->GetName(), args.arg);
		return NULL;
	}
	
	return result;
}

PyResult CharMgrService::Handle_GetTopBounties(PyCallArgs &call) {
	_log(SERVICE__ERROR, "%s::GetTopBounties unimplemented.", GetName());

	util_Rowset rs;

	rs.header.push_back("characterID");
	rs.header.push_back("ownerName");
	rs.header.push_back("bounty");
	rs.header.push_back("online");

	return rs.FastEncode();
}
























