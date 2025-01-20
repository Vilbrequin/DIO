#ifndef DIO_H_
#define DIO_H_


/****************************************************************************************************/
/*                                      Includes                                                    */
/****************************************************************************************************/
#include "Dio_Types.h"
#include "Compiler.h"
#include "Common_Macros.h"

/****************************************************************************************************/
/*                   MACROS: used in error detection & get version Api                              */
/****************************************************************************************************/
#define DIO_MODULE_ID                              (120U)
#define DIO_MODULE_INSTANCE_ID                     (0U)
#define DIO_MODULE_VENDOR_ID                       (0xD0) /* My own vendor id (company dependent): highest vid is 0xC7(Real-Time Innovations)*/

/* Module version 1.0.0 */
#define DIO_MODULE_MAJOR_VERSION                   (1U)
#define DIO_MODULE_MINOR_VERSION                   (0U)
#define DIO_MODULE_PATCH_VERSION                   (0U)

/*********************************************************************************************************
 *                                              API Service Id Macros                                    *
 *********************************************************************************************************/
#define DIO_READ_CHANNEL_SID                        (uint8)0x00

#define DIO_WRITE_CHANNEL_SID                       (uint8)0x01

#define DIO_READ_PORT_SID                            (uint8)0x02

#define DIO_WRITE_PORT_SID                          (uint8)0x03

#define DIO_READ_CHANNEL_GROUP_SID                  (uint8)0x04

#define DIO_WRITE_CHANNEL_GROUP_SID                 (uint8)0x05

#define DIO_GET_VERSION_INFO_SID                    (uint8)0x12

#define DIO_FLIP_CHANNEL_SID                        (uint8)0x11

#define DIO_MASKED_WRITE_PORT_SID                   (uint8)0x13

/****************************************************************************************************/
/*                                      DioGeneral                                                  */
/****************************************************************************************************/

/****************************************************************************************************
 * SWS Item: [ECUC_Dio_00142]
 * Parameter Name: DioDevErrorDetect
 * Parent Container: DioGeneral
 * Description: Switches the development error detection and notification on or off:
 *              - true: detection and notification is enabled.
 *              - false: detection and notification is disabled.
 * Multiplicity: 1
 * Default value: false
 * scope: local
 ****************************************************************************************************/
#define DIO_DEV_ERROR_DETECT            (STD_OFF)

/****************************************************************************************************
 * SWS Item: [ECUC_Dio_00153]
 * Parameter Name: DioFlipChannelApi
 * Parent Container: DioGeneral
 * Description: Adds / removes the service Dio_FlipChannel() from the code.
 * Multiplicity: 1
 * Default value: --
 * scope: local
 ****************************************************************************************************/
#define DIO_FLIP_CHANNEL_API            (STD_OFF)           

/****************************************************************************************************
 * SWS Item: [ECUC_Dio_00155]
 * Parameter Name: DioMaskedWritePortApi
 * Parent Container: DioGeneral
 * Description: Adds / removes the service Dio_MaskedWritePort() from the code.
 * Multiplicity: 1
 * Default value: false
 * scope: local
 ****************************************************************************************************/
#define DIO_MASKED_WRITE_PORT_API       (STD_OFF)

/****************************************************************************************************
 * SWS Item: [ECUC_Dio_00143]
 * Parameter Name: DioVersionInfoApi
 * Parent Container: DioGeneral
 * Description: Adds / removes the service Dio_GetVersionInfo() from the code.
 * Multiplicity: 1
 * Default value: false
 * scope: local
 ****************************************************************************************************/
#define DIO_VERSION_INFO_API            (STD_OFF)

/****************************************************************************************************/
/*                                 Function definitions                                             */
/****************************************************************************************************/

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
Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId);

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
void Dio_WriteChannel (Dio_ChannelType ChannelId, Dio_LevelType Level);

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
Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId);

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
void Dio_WritePort (Dio_PortType PortId, Dio_PortLevelType Level);

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
Dio_PortLevelType Dio_ReadChannelGroup (const Dio_ChannelGroupType* ChannelGroupIdPtr);

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
void Dio_WriteChannelGroup (const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level);

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
void Dio_GetVersionInfo (Std_VersionInfoType* VersionInfo);

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
Dio_LevelType Dio_FlipChannel (Dio_ChannelType ChannelId);


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
void Dio_MaskedWritePort (Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask);


#endif /* DIO_H_ */