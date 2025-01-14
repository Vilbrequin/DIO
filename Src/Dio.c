/****************************************************************************************************/
/*                                      Includes                                                    */
/****************************************************************************************************/
#include "Dio.h"
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

    volatile uint32 *port_ddr = NULL_PTR;
    volatile uint32 *port_dir = NULL_PTR;
    volatile uint32 *port_dor = NULL_PTR;

    switch (Dio_PortChannels[ChannelId].portId)
    {
    case PORT_A_ID:
        port_ddr = (volatile uint32 *)GPIO_A_PDDR;
        port_dir = (volatile uint32 *)GPIO_A_PDIR;
        port_dor = (volatile uint32 *)GPIO_A_PDOR;
        break;
    case PORT_B_ID:
        port_ddr = (volatile uint32 *)GPIO_B_PDDR;
        port_dir = (volatile uint32 *)GPIO_B_PDIR;
        port_dor = (volatile uint32 *)GPIO_B_PDOR;
        break;
    case PORT_C_ID:
        port_ddr = (volatile uint32 *)GPIO_C_PDDR;
        port_dir = (volatile uint32 *)GPIO_C_PDIR;
        port_dor = (volatile uint32 *)GPIO_C_PDOR;
        break;
    case PORT_D_ID:
        port_ddr = (volatile uint32 *)GPIO_D_PDDR;
        port_dir = (volatile uint32 *)GPIO_D_PDIR;
        port_dor = (volatile uint32 *)GPIO_D_PDOR;
        break;
    case PORT_E_ID:
        port_ddr = (volatile uint32 *)GPIO_E_PDDR;
        port_dir = (volatile uint32 *)GPIO_E_PDIR;
        port_dor = (volatile uint32 *)GPIO_E_PDOR;
        break;
    default:
        /* Do Nothing */
        break;
    }

    if(BIT_IS_SET(*(volatile uint32 *) port_ddr, Dio_PortChannels[ChannelId].channelId)){
        /* Pin is configured as an Output*/
        if(BIT_IS_SET(*(volatile uint32 *) port_dor, Dio_PortChannels[ChannelId].channelId)){
            return STD_HIGH;
        }
        else if(BIT_IS_CLEAR(*(volatile uint32 *) port_dor, Dio_PortChannels[ChannelId].channelId)){
            return STD_LOW;
        }
        else {
            /* Do Nothing*/
        }
    }
    else if(BIT_IS_CLEAR(*(volatile uint32 *) port_ddr, Dio_PortChannels[ChannelId].channelId)){
        /* Pin is configured as an Input*/
        if(BIT_IS_SET(*(volatile uint32 *) port_dir, Dio_PortChannels[ChannelId].channelId)){
            return STD_HIGH;
        }
        else if(BIT_IS_CLEAR(*(volatile uint32 *) port_dir, Dio_PortChannels[ChannelId].channelId)){
            return STD_LOW;
        }
        else {
            /* Do Nothing*/
        }
    }
    else {
        /* Do Nothing*/
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