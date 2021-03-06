/*
=============================================================================
     Header Name: dal_port.h

     General Description:
===============================================================================
                         Opulan Confidential Proprietary                     
                  ID and version: xxxxxxxxxxxxxx  Version 1.00
                  (c) Copyright Opulan XXXX - XXXX, All Rights Reserved
     

Revision History:
Author                Date              Description of Changes
----------------   ------------  ----------------------------------------------
 zzhu 				   2007/11/13		Initial Version	
----------------   ------------  ----------------------------------------------
*/
#ifndef DAL_PORT_H
#define DAL_PORT_H

#include <opl_driver.h>
#include <opconn_api.h>

#define DAL_PORT_ADMIN_ENABLE   (1)
#define DAL_PORT_ADMIN_DISABLE  (0)

#define PHY_PORT_ADMIN_ENABLE	  (1)
#define PHY_PORT_ADMIN_DISABLE (0)


#define DAL_NUM_OF_PORTS 		4
#define DAL_MIN_PORT_NUM 		1
#define DAL_MAX_PORT_NUM		4
#define DAL_SWITCH_UP_LINK_PORT 6

#define PORT_IS_OUT_OF_RANTE(portNum) 0


/*******************************************************************************
* dalPortStateGet
*
* DESCRIPTION:
*  		this function is used to get the ethernet port status down or up.
*
*	INPUTS:
*			portId:0x0
*
*	OUTPUTS:
*			status:0x01:up,0x00:down		     
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortStateGet(UINT8 portId,UINT8 *status);


/*******************************************************************************
* dalPortSpeedSet
*
* DESCRIPTION:
*  		this function is used to set port speed 
*
*	INPUTS:
*			portId:0x01-0x04
*			speed:10 100 1000.
*	OUTPUTS:
*			 
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortSpeedSet(UINT8 portId,UINT32 portSpeed);


/*******************************************************************************
* dalPortSpeedGet
* DESCRIPTION:
*  		this function is used to get the port speed
*
*	INPUTS:
*			portId:0x01-0x04
*			speed:10 100 1000.
*	OUTPUTS:
*			 
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortSpeedGet(UINT8 portId,UINT32 *portSpeed);

	
/*******************************************************************************
* dalPortDuplexSet
*
* DESCRIPTION:
*  		this function is used to set port speed 
*
*	INPUTS:
*			portId:0x01-0x04
*			speed:10 100 1000.
*	OUTPUTS:
*			 
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortDuplexSet(UINT8 portId,UINT32 duplex);


/*******************************************************************************
* dalPortDuplexGet
*
* DESCRIPTION:
*  		this function is used to get the port speed
*
*	INPUTS:
*			portId:0x01-0x04
*			speed:10 100 1000.
*	OUTPUTS:
*			 
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortDuplexGet(UINT8 portId,UINT32 *duplex);

OPL_STATUS dalPortPvidSet(UINT8 portId,UINT16 pvid);

OPL_STATUS dalPortPvidGet(UINT8 portId,UINT16 *pvid);

OPL_STATUS dalPortDefaultPriSet(UINT8 portId,UINT8 defaultPri);

OPL_STATUS dalPortDefaultPriGet(UINT8 portId,UINT8 *defaultPri);


/*******************************************************************************
* dalPortFlowcontrolSet
*
* DESCRIPTION:
*  		this function is used to dsiable or enable the flow control
*
*	INPUTS:
*			portId:0x0
*			enable:0x00:disable,0x01:enable.
*	OUTPUTS:
*			 
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortFlowcontrolSet(UINT8 portId,UINT8 enable);
/*******************************************************************************
* dalPortLoopbackSet
*
* DESCRIPTION:
*  		this function is used to dsiable or enable the externel loop back
*
*	INPUTS:
*			portId:0x0
*			enable:0x00:disable,0x01:enable.
*	OUTPUTS:
*			 
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortLoopbackSet(UINT8 portId,UINT8 enable);

/*******************************************************************************
* dalPortFlowcontrolGet
*
* DESCRIPTION:
*  			this function is used to get flowcontrol config info.
*
*	INPUTS:
*			portId:0x0
*	OUTPUTS:
*			enable:0x00:disable,0x01:enable. 
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortFlowcontrolGet(UINT8 portId,UINT8 *enable);

/*******************************************************************************
* dalPortUsPolicingEnableSet
*
* DESCRIPTION:
*  			this function is used to set the upstream policing parameter.
*
*	INPUTS:
*			portId:0x0
*			enable:0x00:disable,0x01:enable
*	OUTPUTS:
*			
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortUsPolicingEnableSet(UINT8 portId,UINT8 enable);


/*******************************************************************************
* dalPortUsPolicingEnableGet
*
* DESCRIPTION:
*  			this function is used to set the upstream policing parameter.
*
*	INPUTS:
*			portId:0x0
*	OUTPUTS:
*			
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortUsPolicingEnableGet(UINT8 portId,UINT8 *enable);


/*******************************************************************************
* dalPortUsPolicingCirSet
*
* DESCRIPTION:
*  			this function is used to set the upstream policing parameter.
*
*	INPUTS:
*			portId:0x0
*			cir:
*	OUTPUTS:
*			
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortUsPolicingCirSet(UINT8 portId,UINT32 cir);


/*******************************************************************************
* dalPortUsPolicingCirGet
*
* DESCRIPTION:
*  			this function is used to set the upstream policing parameter.
*
*	INPUTS:
*			portId:0x0
*			cir:
*	OUTPUTS:
*			
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortUsPolicingCirGet(UINT8 portId,UINT32 *cir);


/*******************************************************************************
* dalPortUsPolicingCbsSet
*
* DESCRIPTION:
*  			this function is used to set the upstream policing parameter.
*
*	INPUTS:
*			portId:0x0
*			ebs:
*	OUTPUTS:
*			
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortUsPolicingCbsSet(UINT8 portId,UINT32 cbs);


/*******************************************************************************
* dalPortUsPolicingCbsGet
*
* DESCRIPTION:
*  			this function is used to set the upstream policing parameter.
*
*	INPUTS:
*			portId:0x0
*			cbs:
*	OUTPUTS:
*			
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortUsPolicingCbsGet(UINT8 portId,UINT32 *cbs);


/*******************************************************************************
* dalPortUsPolicingEbsSet
*
* DESCRIPTION:
*  			this function is used to set the upstream policing parameter.
*
*	INPUTS:
*			portId:0x0
*			ebs:
*	OUTPUTS:
*			
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortUsPolicingEbsSet(UINT8 portId,UINT32 ebs);


/*******************************************************************************
* dalPortUsPolicingEbsGet
*
* DESCRIPTION:
*  			this function is used to set the upstream policing parameter.
*
*	INPUTS:
*			portId:0x0
*			ebs:
*	OUTPUTS:
*			
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortUsPolicingEbsGet(UINT8 portId,UINT32 *ebs);

/*******************************************************************************
* dalPortUsPolicingSet
*
* DESCRIPTION:
*  			this function is used to set the upstream policing parameter.
*
*	INPUTS:
*			portId:0x0
*			enable:0x00:disable,0x01:enable
*			cir:  0x000000-0xffffff
*			cbs:
*			ebs:
*	OUTPUTS:
*			
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortUsPolicingSet(UINT8 portId,UINT8 enable,UINT32 cir,UINT32 cbs,UINT32 ebs);

/*******************************************************************************
* dalPortUsPolicingGet
*
* DESCRIPTION:
*  			this function is used to get the shaper parameter
*
*	INPUTS:
*			portId:0x0
*			
*	OUTPUTS:
*			enable:0x00:disable,0x01:enable
*			cir:
*			cbs:
*			ebs:	
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortUsPolicingGet(UINT8 portId,UINT8 *enable,UINT32 *cir,UINT32 *cbs,UINT32 *ebs);

/*******************************************************************************
* dalPortDsPolicingEnableSet
*
* DESCRIPTION:
*  			this function is used to set the shaper parameter
*
*	INPUTS:
*			portId:0x0
*			enable:0x00:disable,0x01:enable
*	OUTPUTS:
*			
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortDsPolicingEnableSet(UINT8 portId,UINT8 enable);

/*******************************************************************************
* dalPortDsPolicingEnableGet
*
* DESCRIPTION:
*  			this function is used to get the shaper parameter
*
*	INPUTS:
*			portId:0x0
*			
*	OUTPUTS:
*			enable:0x00:disable,0x01:enable
*			cir:
*			cbs:
*			ebs:	
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortDsPolicingEnableGet(UINT8 portId,UINT8 *enable);

/*******************************************************************************
* dalPortDsPolicingCirSet
*
* DESCRIPTION:
*  			this function is used to set the shaper parameter
*
*	INPUTS:
*			portId:0x0
*           cir:
*	OUTPUTS:
*			
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortDsPolicingCirSet(UINT8 portId,UINT32 cir);

/*******************************************************************************
* dalPortDsPolicingCirGet
*
* DESCRIPTION:
*  			this function is used to get the shaper parameter
*
*	INPUTS:
*			portId:0x0
*			cir
*	OUTPUTS:
*			enable:0x00:disable,0x01:enable
*			cir:
*			cbs:
*			ebs:	
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortDsPolicingCirGet(UINT8 portId,UINT32 *cir);
/*******************************************************************************
* dalPortDsPolicingPirSet
*
* DESCRIPTION:
*  			this function is used to set the shaper parameter
*
*	INPUTS:
*			portId:0x0
*			enable:0x00:disable,0x01:enable
*           pir
*	OUTPUTS:
*			
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortDsPolicingPirSet(UINT8 portId,UINT32 cbs);


/*******************************************************************************
* dalPortDsPolicingPirGet
*
* DESCRIPTION:
*  			this function is used to set the shaper parameter
*
*	INPUTS:
*			portId:0x0
*			enable:0x00:disable,0x01:enable
*           pir
*	OUTPUTS:
*			
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortDsPolicingPirGet(UINT8 portId,UINT32 *cbs);

/*******************************************************************************
* dalPortDsPolicingSet
*
* DESCRIPTION:
*  			this function is used to set the shaper parameter
*
*	INPUTS:
*			portId:0x0
*			enable:0x00:disable,0x01:enable
*			cir:
*			cbs:
*			ebs:
*	OUTPUTS:
*			
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortDsPolicingSet(UINT8 portId,UINT8 enable,UINT32 cir,UINT32 cbs);

/*******************************************************************************
* dalPortDsPolicingGet
*
* DESCRIPTION:
*  			this function is used to get the shaper parameter
*
*	INPUTS:
*			portId:0x0
*			
*	OUTPUTS:
*			enable:0x00:disable,0x01:enable
*			cir:
*			cbs:
*			ebs:	
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortDsPolicingGet(UINT8 portId,UINT8 *enable,UINT32 *cir,UINT32 *cbs);


/*******************************************************************************
* dalPhyAdminStateGet
*
* DESCRIPTION:
*  		this function is used to get the port's phy admin status.0x01 for disable,0x02 for enable.
*
*	INPUTS:
*		portId: 		portId
*		state:		enable:0x02,disable:0x01
*	OUTPUTS:
*		
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPhyAdminStateGet(UINT8 portId,UINT32 *state);

/*******************************************************************************
* dalPhyAdminControlSet
*
* DESCRIPTION:
*  		this function is used to set the port'phy admin status,0x01 for disable,0x02 for enable
*
*	INPUTS:
*		portId: 		portId
*		state:		disable:0x01,enable:0x02
*	OUTPUTS:
*		
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPhyAdminControlSet(UINT8 portId,UINT32 state);

/*******************************************************************************
* dalPhyAutonegAdminStateGet
*
* DESCRIPTION:
*  		this function is used to get autonegocitation config info for the port.0x01 for disable,0x02 for enable
*
*	INPUTS:
*		portId: 		portId
*		
*	OUTPUTS:
*		state:		disable:0x01,enable:0x02
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPhyAutonegAdminStateGet(UINT8 portId,UINT32 *state);

/*******************************************************************************
* dalPhyAutonegEnableSet
*
* DESCRIPTION:
*  		this function is used to set autonegocitation enable. 0x01 for dsiable,0x02 for enable
*
*	INPUTS:
*		portId: 		portId
*		enable:		disable:0x01;eanble:0x02
*	OUTPUTS:
*		
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPhyAutonegEnableSet(UINT8 portId,UINT32 enable);

/*******************************************************************************
* dalPhyAutonegRestart
*
* DESCRIPTION:
*  		this function is used to force the port restart autonegocitation.
*
*	INPUTS:
*		portId: 		portId
*		
*	OUTPUTS:
*		
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPhyAutonegRestart(UINT8 portId);


/*******************************************************************************
* dalPortVlanModeSet
*
* DESCRIPTION:
*  		this function is used to set port vlan for the specifies port
*
*	INPUTS:
*		portId: 		portId
*		
*	OUTPUTS:
*		
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortVlanModeSet(UINT8 portId,UINT32 vlanMode);

/*******************************************************************************
* dalPortVlanModeGet
*
* DESCRIPTION:
*  		this function is used to set port vlan for the specifies port
*
*	INPUTS:
*		portId: 		portId
*		
*	OUTPUTS:
*		
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortVlanModeGet(UINT8 portId,UINT32 *vlanMode);

/*******************************************************************************
* dalPortLearnEnableSet
*
* DESCRIPTION:
*  		this function is used to set per port learning enable
*
*	INPUTS:
*		portId: 		portId
*		
*	OUTPUTS:
*		
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortLearnEnableSet(UINT8 portId,UINT32 enable);

/*******************************************************************************
* dalPortInit
*
* DESCRIPTION:
*  		this function is used to init the port parameter.
*
*	INPUTS:
*		portId: 		portId
*		
*	OUTPUTS:
*		mode:		0x01:unknown,0x02:enable,0x03:disable
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortInit(void);

/*******************************************************************************
* dalPortSpecificSpeedRead
* DESCRIPTION:
*  		this function is used to get the port speed
*
*	INPUTS:
*			portId:0x01-0x04
*			speed:10 100 1000.
*	OUTPUTS:
*			 
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortSpecificSpeedRead(UINT8 portId,UINT32 *portSpeed);

/*******************************************************************************
* dalPortSpecificDuplexRead
*
* DESCRIPTION:
*  		this function is used to get the port specific duplex
*
*	INPUTS:
*			portId:0x01-0x04
*			duplex: Full-duplex or half-duplex.
*	OUTPUTS:
*			 
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPortSpecificDuplexRead(UINT8 portId,UINT32 *duplex);

/*******************************************************************************
* dalPhySpecificAutonegRead
*
* DESCRIPTION:
*  		this function is used to get autonegocitation status info for the port.0x01 for completed,0x02 for failed
*
*	INPUTS:
*		portId: 		portId
*		
*	OUTPUTS:
*		state:		completed:0x01,failed:0x02
* 	RETURNS:
* 			OPL_OK if the access is success.
* 			OPL_ERROR if the access is failed.
* 	SEE ALSO: 
*/
OPL_STATUS dalPhySpecificAutonegRead(UINT8 portId, UINT32  *state);

#endif
