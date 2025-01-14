#ifndef DIO_TYPES_H_
#define DIO_TYPES_H_

/****************************************************************************************************/
/*                                      Includes                                                    */
/****************************************************************************************************/
#include "Std_Types.h"

/****************************************************************************************************/
/*                                      Macros Definitions                                          */
/****************************************************************************************************/
#define DIO_CONFIGURED_CHANNELS     (89U)
#define DIO_CONFIGURED_PORTS        (5U) /* Port A to Port E*/
#define DIO_CONFIGURED_GROUPS       (3U) /* eg of configured groups (3 groups)*/

#define ChANNELS_PER_PORT           (18U)

/****************************************************************************************************/
/*                                  [SWS_Dio_91001] Development Errors                              */
/****************************************************************************************************/

#define DIO_E_PARAM_INVALID_CHANNEL_ID          0x0A

#define DIO_E_PARAM_INVALID_PORT_ID             0x14

#define DIO_E_PARAM_INVALID_GROUP               0x1F

#define DIO_E_PARAM_POINTER                     0x20
/****************************************************************************************************/
/*                                      Types Definitions                                           */
/****************************************************************************************************/

/*
 * Index : 8.2.1 [SWS_Dio_00182]
 * Description : Numeric ID of a DIO channel.
 */
typedef uint8 Dio_ChannelType;

/*
 * Index : 8.2.2 [SWS_Dio_00183]
 * Description : Numeric ID of a DIO port.
 */
typedef uint8 Dio_PortType;
#define PORT_A_ID           (Dio_PortType)0x00
#define PORT_B_ID           (Dio_PortType)0x01
#define PORT_C_ID           (Dio_PortType)0x02
#define PORT_D_ID           (Dio_PortType)0x03
#define PORT_E_ID           (Dio_PortType)0x04

/*
 * Index : 8.2.5 [SWS_Dio_00186]
 * Description : If the μC owns ports of different port widths (e.g. 4, 8,16...Bit) Dio_PortLevelType 
 *              inherits the size of the largest port.
 */
typedef uint8 Dio_PortLevelType;

/*
 * Index : 8.2.4 [SWS_Dio_00185]
 * Description : These are the possible levels a DIO channel can have (input or output).
 */
typedef uint8 Dio_LevelType;
#define STD_LOW                 (Dio_LevelType)0x00
#define STD_HIGH                (Dio_LevelType)0x01

/*
 * Index : 8.2.3 [SWS_Dio_00184]
 * Description : Channel group, which consists of several adjoining channels within a port.
 */
typedef struct {
    uint8 mask;
    uint8 offset;
    Dio_PortType port;
}Dio_ChannelGroupType;

typedef struct{
    Dio_PortType portId;
    Dio_ChannelType channelId;
}Dio_ConfigChannelType;

typedef struct{
    Dio_ConfigChannelType channels[DIO_CONFIGURED_CHANNELS];
    Dio_PortType ports[DIO_CONFIGURED_PORTS];
    Dio_ChannelGroupType groups[DIO_CONFIGURED_GROUPS];
}Dio_ConfigType;

#endif /* DIO_TYPES_H_ */