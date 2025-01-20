/****************************************************************************************************/
/*                                      Includes                                                    */
/****************************************************************************************************/
#include "Dio.h"
#include "Det.h"
#include "Dio_Regs.h"


static Dio_ConfigChannelType *Dio_PortChannels = NULL_PTR;
static Dio_PortType *Dio_Ports = NULL_PTR;
static Dio_ChannelGroupType *Dio_ChannelGroups  = NULL_PTR;

void Dio_Init(Dio_ConfigType *ConfigPtr){
    
    Dio_PortChannels = ConfigPtr->channels;
    Dio_Ports = ConfigPtr->ports;
    Dio_ChannelGroups = ConfigPtr->groups;

}

/****************************************************************************************************
 * Service Name: Dio_ReadChannel
 * Sws_Index : 8.3.1 [SWS_Dio_00133]
 * Service ID[hex]:0x00
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): ChannelId - ID of DIO channel
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Dio_LevelType :
 *              - STD_HIGH The physical level of the corresponding Pin is STD_HIGH
 *              - STD_LOW The physical level of the corresponding Pin is STD_LOW
 * Description: Returns the value of the specified DIO channel.
****************************************************************************************************/
Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId){

    #if(STD_ON == DIO_DEV_ERROR_DETECT)
        if(ChannelId < 0 || ChannelId >= DIO_CONFIGURED_CHANNELS)
        {
            Det_ReportError(DIO_MODULE_ID, 
                            DIO_MODULE_INSTANCE_ID, 
                            DIO_READ_CHANNEL_GROUP_SID, 
                            DIO_E_PARAM_INVALID_CHANNEL_ID);
        }
    #endif
    volatile uint32 *port_dir = NULL_PTR;

    switch (Dio_PortChannels[ChannelId].portId)
    {
    case PORT_A_ID:
        port_dir = (volatile uint32 *)GPIO_A_PDIR;
        break;
    case PORT_B_ID:
        port_dir = (volatile uint32 *)GPIO_B_PDIR;
        break;
    case PORT_C_ID:
        port_dir = (volatile uint32 *)GPIO_C_PDIR;
        break;
    case PORT_D_ID:
        port_dir = (volatile uint32 *)GPIO_D_PDIR;
        break;
    case PORT_E_ID:
        port_dir = (volatile uint32 *)GPIO_E_PDIR;
        break;
    default:
        /* Do Nothing */
        break;
    }

    if(BIT_IS_SET(*(volatile uint32 *) port_dir, Dio_PortChannels[ChannelId].channelId)){
        return STD_HIGH;
    }
    else if(BIT_IS_CLEAR(*(volatile uint32 *) port_dir, Dio_PortChannels[ChannelId].channelId)){
        return STD_LOW;
    }

}

/****************************************************************************************************
 * Service Name: Dio_WriteChannel
 * Sws_Index : 8.3.2 [SWS_Dio_00134]
 * Service ID[hex]:0x01
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): - ChannelId - ID of DIO channel
 *                  - Level - Value to be written
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Service to set a level of a channel.
 ****************************************************************************************************/
void Dio_WriteChannel (Dio_ChannelType ChannelId, Dio_LevelType Level){
    
    #if(STD_ON == DIO_DEV_ERROR_DETECT)
        if(ChannelId < 0 || ChannelId >= DIO_CONFIGURED_CHANNELS)
        {
            Det_ReportError(DIO_MODULE_ID, 
                            DIO_MODULE_INSTANCE_ID, 
                            DIO_WRITE_CHANNEL_SID, 
                            DIO_E_PARAM_INVALID_CHANNEL_ID);
        }
    #endif

    volatile uint32 *port_ddr = NULL_PTR;
    volatile uint32 *port_dor = NULL_PTR;

    switch (Dio_PortChannels[ChannelId].portId)
    {
    case PORT_A_ID:
        port_ddr = (volatile uint32 *)GPIO_A_PDDR;
        port_dor = (volatile uint32 *)GPIO_A_PDOR;
        break;
    case PORT_B_ID:
        port_ddr = (volatile uint32 *)GPIO_B_PDDR;
        port_dor = (volatile uint32 *)GPIO_B_PDOR;
        break;
    case PORT_C_ID:
        port_ddr = (volatile uint32 *)GPIO_C_PDDR;
        port_dor = (volatile uint32 *)GPIO_C_PDOR;
        break;
    case PORT_D_ID:
        port_ddr = (volatile uint32 *)GPIO_D_PDDR;
        port_dor = (volatile uint32 *)GPIO_D_PDOR;
        break;
    case PORT_E_ID:
        port_ddr = (volatile uint32 *)GPIO_E_PDDR;
        port_dor = (volatile uint32 *)GPIO_E_PDOR;
        break;
    default:
        /* Do Nothing */
        break;
    }
    if(BIT_IS_SET(*(volatile uint32 *) port_ddr, Dio_PortChannels[ChannelId].channelId)){
        /* Pin is configured as an Output*/
        if(STD_HIGH == Level){
            SET_BIT(*(volatile uint32 *)port_dor, Dio_PortChannels[ChannelId].channelId);
        }
        else if(STD_LOW == Level){
            CLEAR_BIT(*(volatile uint32 *)port_dor, Dio_PortChannels[ChannelId].channelId);
        }
        else{
            /* DO Nothing */
        }
    }
    else{
        /* Do Nothing */
    }
}

/****************************************************************************************************
 * Service Name: Dio_ReadPort
 * Sws_Index : 8.3.3 [SWS_Dio_00135]
 * Service ID[hex]:0x02
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): PortId - ID of DIO Port
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Dio_PortLevelType - Level of all channels of that port
 * Description: Returns the level of all channels of that port.
****************************************************************************************************/
Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId){
    
    #if(STD_ON == DIO_DEV_ERROR_DETECT)
        if(PortId < 0 || PortId >= DIO_CONFIGURED_PORTS)
        {
            Det_ReportError(DIO_MODULE_ID, 
                            DIO_MODULE_INSTANCE_ID, 
                            DIO_READ_PORT_SID, 
                            DIO_E_PARAM_INVALID_PORT_ID);
        }
    #endif

    volatile uint32 *port_dir = NULL_PTR;
    Dio_PortLevelType ptr_level = STD_HIGH;

    switch (PortId)
    {
    case PORT_A_ID:
        port_dir = (volatile uint32 *)GPIO_A_PDIR;
        break;
    case PORT_B_ID:
        port_dir = (volatile uint32 *)GPIO_B_PDIR;
        break;
    case PORT_C_ID:
        port_dir = (volatile uint32 *)GPIO_C_PDIR;
        break;
    case PORT_D_ID:
        port_dir = (volatile uint32 *)GPIO_D_PDIR;
        break;
    case PORT_E_ID:
        port_dir = (volatile uint32 *)GPIO_E_PDIR;
        break;
    default:
        /* Do Nothing */
        break;
    }

    if(port_dir != NULL_PTR){
        ptr_level = (Dio_PortLevelType)*port_dir;
    }
    return ptr_level;
}


/****************************************************************************************************
 * Service Name: Dio_WritePort
 * Sws_Index : 8.3.4 [SWS_Dio_00136]
 * Service ID[hex]:0x03
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): - PortId - ID of DIO Port
 *                  - Level - Value to be written
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Service to set a value of the port.
 ****************************************************************************************************/
void Dio_WritePort (Dio_PortType PortId, Dio_PortLevelType Level){

    #if(STD_ON == DIO_DEV_ERROR_DETECT)
        if(PortId < 0 || PortId >= DIO_CONFIGURED_PORTS)
        {
            Det_ReportError(DIO_MODULE_ID, 
                            DIO_MODULE_INSTANCE_ID, 
                            DIO_WRITE_PORT_SID, 
                            DIO_E_PARAM_INVALID_PORT_ID);
        }
    #endif

    volatile uint32 *port_dor = NULL_PTR;

    switch (PortId)
    {
    case PORT_A_ID:
        port_dor = (volatile uint32 *)GPIO_A_PDOR;
        break;
    case PORT_B_ID:
        port_dor = (volatile uint32 *)GPIO_B_PDOR;
        break;
    case PORT_C_ID:
        port_dor = (volatile uint32 *)GPIO_C_PDOR;
        break;
    case PORT_D_ID:
        port_dor = (volatile uint32 *)GPIO_D_PDOR;
        break;
    case PORT_E_ID:
        port_dor = (volatile uint32 *)GPIO_E_PDOR;
        break;
    default:
        /* Do Nothing */
        break;
    }

    if(port_dor != NULL_PTR){
        *port_dor = Level;
    }
}

/****************************************************************************************************
 * Service Name: Dio_ReadChannelGroup
 * Sws_Index : 8.3.5 [SWS_Dio_00137]
 * Service ID[hex]:0x04
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): ChannelGroupIdPtr - Pointer to ChannelGroup
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Dio_PortLevelType Level of a subset of the adjoining bits of a port
 * Description: This Service reads a subset of the adjoining bits of a port.
****************************************************************************************************/
Dio_PortLevelType Dio_ReadChannelGroup (const Dio_ChannelGroupType* ChannelGroupIdPtr){

    #if(STD_ON == DIO_DEV_ERROR_DETECT)
        if(NULL_PTR == ChannelGroupIdPtr){
            Det_ReportError(DIO_MODULE_ID, 
                            DIO_MODULE_INSTANCE_ID, 
                            DIO_READ_CHANNEL_GROUP_SID, 
                            DIO_E_PARAM_POINTER);
        }
        /* TODO: add the case when Invalid channel group requested */
    #endif

    volatile uint32 *port_dir = NULL_PTR;
    Dio_PortLevelType channel_level = STD_HIGH;

    switch (ChannelGroupIdPtr->port)
    {
    case PORT_A_ID:
        port_dir = (volatile uint32 *)GPIO_A_PDIR;
        break;
    case PORT_B_ID:
        port_dir = (volatile uint32 *)GPIO_B_PDIR;
        break;
    case PORT_C_ID:
        port_dir = (volatile uint32 *)GPIO_C_PDIR;
        break;
    case PORT_D_ID:
        port_dir = (volatile uint32 *)GPIO_D_PDIR;
        break;
    case PORT_E_ID:
        port_dir = (volatile uint32 *)GPIO_E_PDIR;
        break;
    default:
        /* Do Nothing */
        break;
    }

    if(port_dir != NULL_PTR){
        channel_level = (Dio_PortLevelType)((*port_dir) & ChannelGroupIdPtr->mask) >> ChannelGroupIdPtr->offset;
    }
    return channel_level;
}

/****************************************************************************************************
 * Service Name: Dio_WriteChannelGroup
 * Sws_Index : 8.3.6 [SWS_Dio_00138]
 * Service ID[hex]:0x05
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): - ChannelGroupIdPtr - Pointer to ChannelGroup
 *                  - Level - Value to be written
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Service to set a subset of the adjoining bits of a port to a specified level
 ****************************************************************************************************/
void Dio_WriteChannelGroup (const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level){
    
    #if(STD_ON == DIO_DEV_ERROR_DETECT)
        if(NULL_PTR == ChannelGroupIdPtr){
            Det_ReportError(DIO_MODULE_ID, 
                            DIO_MODULE_INSTANCE_ID, 
                            DIO_WRITE_CHANNEL_GROUP_SID, 
                            DIO_E_PARAM_POINTER);
        }
        /* TODO: add the case when Invalid channel group requested */
    #endif

    volatile uint32 *port_dor = NULL_PTR;

    switch (ChannelGroupIdPtr->port)
    {
    case PORT_A_ID:
        port_dor = (volatile uint32 *)GPIO_A_PDOR;
        break;
    case PORT_B_ID:
        port_dor = (volatile uint32 *)GPIO_B_PDOR;
        break;
    case PORT_C_ID:
        port_dor = (volatile uint32 *)GPIO_C_PDOR;
        break;
    case PORT_D_ID:
        port_dor = (volatile uint32 *)GPIO_D_PDOR;
        break;
    case PORT_E_ID:
        port_dor = (volatile uint32 *)GPIO_E_PDOR;
        break;
    default:
        /* Do Nothing */
        break;
    }

    *port_dor = ((*port_dor) & (~(ChannelGroupIdPtr->mask))) | (Level >> ChannelGroupIdPtr->offset);  
}

/****************************************************************************************************
 * Service Name: Dio_GetVersionInfo
 * Sws_Index : 8.3.7 [SWS_Dio_00139]
 * Service ID[hex]:0x12
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): VersionInfo - Pointer to where to store the version information of this module
 * Return value: None
 * Description: Service to get the version information of this module.
 ****************************************************************************************************/
void Dio_GetVersionInfo (Std_VersionInfoType* VersionInfo){
    
    VersionInfo->sw_major_version = (uint8)DIO_MODULE_MAJOR_VERSION;
    VersionInfo->sw_minor_version = (uint8)DIO_MODULE_MINOR_VERSION;
    VersionInfo->sw_patch_version = (uint8)DIO_MODULE_PATCH_VERSION;
    VersionInfo->moduleID = (uint8)DIO_MODULE_ID;
    VersionInfo->vendorID = (uint8)DIO_MODULE_VENDOR_ID;
}

/****************************************************************************************************
 * Service Name: Dio_FlipChannel
 * Sws_Index : 8.3.8 [SWS_Dio_00190]
 * Service ID[hex]:0x11
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): ChannelId - ID of DIO channel
 * Parameters (inout): None
 * Parameters (out):None
 * Return value: Dio_LevelType :
 *              - STD_HIGH The physical level of the corresponding Pin is STD_HIGH
 *              - STD_LOW The physical level of the corresponding Pin is STD_LOW
 * Description: Service to flip (change from 1 to 0 or from 0 to 1) the level of a channel and 
 *              return the level of the channel after flip.
 ****************************************************************************************************/
#if(STD_ON == DIO_FLIP_CHANNEL_API)
Dio_LevelType Dio_FlipChannel (Dio_ChannelType ChannelId){
    
    #if(STD_ON == DIO_DEV_ERROR_DETECT)
        if(ChannelId < 0 || ChannelId >= DIO_CONFIGURED_CHANNELS)
        {
            Det_ReportError(DIO_MODULE_ID, 
                            DIO_MODULE_INSTANCE_ID, 
                            DIO_FLIP_CHANNEL_SID, 
                            DIO_E_PARAM_INVALID_CHANNEL_ID);
        }
    #endif
 
    volatile uint32 *port_ddr = NULL_PTR;
    volatile uint32 *port_dor = NULL_PTR;
    volatile uint32 *port_dir = NULL_PTR;
    

    switch (Dio_PortChannels[ChannelId].portId)
    {
    case PORT_A_ID:
        port_ddr = (volatile uint32 *)GPIO_A_PDDR;
        port_dor = (volatile uint32 *)GPIO_A_PDOR;
        port_dir = (volatile uint32 *)GPIO_A_PDIR;
        break;
    case PORT_B_ID:
        port_ddr = (volatile uint32 *)GPIO_B_PDDR;
        port_dor = (volatile uint32 *)GPIO_B_PDOR;
        port_dir = (volatile uint32 *)GPIO_B_PDIR;
        break;
    case PORT_C_ID:
        port_ddr = (volatile uint32 *)GPIO_C_PDDR;
        port_dor = (volatile uint32 *)GPIO_C_PDOR;
        port_dir = (volatile uint32 *)GPIO_C_PDIR;
        break;
    case PORT_D_ID:
        port_ddr = (volatile uint32 *)GPIO_D_PDDR;
        port_dor = (volatile uint32 *)GPIO_D_PDOR;
        port_dir = (volatile uint32 *)GPIO_D_PDIR;
        break;
    case PORT_E_ID:
        port_ddr = (volatile uint32 *)GPIO_E_PDDR;
        port_dor = (volatile uint32 *)GPIO_E_PDOR;
        port_dir = (volatile uint32 *)GPIO_E_PDIR;
        break;
    default:
        /* Do Nothing */
        break;
    }
    if(BIT_IS_SET(*(volatile uint32 *) port_ddr, Dio_PortChannels[ChannelId].channelId)){
        
        /* Pin is configured as an Output*/
         if(BIT_IS_SET(*(volatile uint32 *)port_dor, Dio_PortChannels[ChannelId].channelId))
        {
            CLEAR_BIT(*(volatile uint32 *)port_dor, Dio_PortChannels[ChannelId].channelId);
            return STD_LOW;
        }
        else if(BIT_IS_CLEAR(*(volatile uint32 *)port_dor, Dio_PortChannels[ChannelId].channelId)){
            SET_BIT(*(volatile uint32 *)port_dor, Dio_PortChannels[ChannelId].channelId);
            return STD_HIGH;
        }
        else{
            /* DO Nothing */
        }
    }
    else if(BIT_IS_CLEAR(*(volatile uint32 *) port_ddr, Dio_PortChannels[ChannelId].channelId))
    {
        /* Pin is configured as an Input: the function shall have no influence on the physical output.
           The return value shall be the level of the specified channel.*/
           
         if(BIT_IS_SET(*(volatile uint32 *)port_dir, Dio_PortChannels[ChannelId].channelId))
        {
            return STD_HIGH;
        }
        else if(BIT_IS_CLEAR(*(volatile uint32 *)port_dir, Dio_PortChannels[ChannelId].channelId)){
            
            return STD_LOW;
        }
        else{
            /* DO Nothing */
        }
    }
    else{
        /* Do Nothing */
    }
}
#endif
/****************************************************************************************************
 * Service Name: Dio_MaskedWritePort
 * Sws_Index : 8.3.9 [SWS_Dio_00300]
 * Service ID[hex]:0x13
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): - PortId - ID of DIO Port
 *                  - Level - Value to be written
 *                  - Mask - Channels to be masked in the port
 * Parameters (inout): None
 * Parameters (out):None
 * Return value: None
 * Description: Service to set the value of a given port with required mask.
 ****************************************************************************************************/
#if(STD_ON == DIO_MASKED_WRITE_PORT_API)
void Dio_MaskedWritePort (Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask){
        
    #if(STD_ON == DIO_DEV_ERROR_DETECT)
        if(ChannelId < 0 || ChannelId >= DIO_CONFIGURED_CHANNELS)
        {
            Det_ReportError(DIO_MODULE_ID, 
                            DIO_MODULE_INSTANCE_ID, 
                            DIO_MASKED_WRITE_PORT_SID, 
                            DIO_E_PARAM_INVALID_CHANNEL_ID);
        }
    #endif
 
    volatile uint32 *port_dor = NULL_PTR;

    switch (PortId)
    {
    case PORT_A_ID:
        port_dor = (volatile uint32 *)GPIO_A_PDOR;
        break;
    case PORT_B_ID:
        port_dor = (volatile uint32 *)GPIO_B_PDOR;
        break;
    case PORT_C_ID:
        port_dor = (volatile uint32 *)GPIO_C_PDOR;
        break;
    case PORT_D_ID:
        port_dor = (volatile uint32 *)GPIO_D_PDOR;
        break;
    case PORT_E_ID:
        port_dor = (volatile uint32 *)GPIO_E_PDOR;
        break;
    default:
        /* Do Nothing */
        break;
    }

    *port_dor = ((*port_dor) & (~ Mask)) | (Level & Mask);
}
#endif