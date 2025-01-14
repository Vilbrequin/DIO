#ifndef COMPILER_H_
#define COMPILER_H_

/*****************************************************************************************************************************************************************************
 * Sws_Index : 8.2.1.1 [SWS_COMPILER_00046]
 * Description : This memory class shall be provided as empty definition, used for the declaration of local pointers. 
 *****************************************************************************************************************************************************************************/
#define AUTOMATIC

/*****************************************************************************************************************************************************************************
 * Sws_Index : 8.2.1.2 [SWS_COMPILER_00059]
 * Description : This memory class shall be provided as empty definition, used within type definitions, where no memory qualifier can be specified. 
 *****************************************************************************************************************************************************************************/
#define TYPEDEF

/*****************************************************************************************************************************************************************************
 * Sws_Index : 8.2.1.3 [SWS_COMPILER_00051]
 * Description : The compiler abstraction shall provide the NULL_PTR define with a void pointer to zero definition.
 *****************************************************************************************************************************************************************************/
#define NULL_PTR            ((void *)0)

/*  */
/*****************************************************************************************************************************************************************************
 * Sws_Index : 8.2.1.4 [SWS_COMPILER_00057]
 * Description : The compiler abstraction shall provide the INLINE define for abstraction of the keyword inline.
 *****************************************************************************************************************************************************************************/
#define INLINE              inline

/*  */
/*****************************************************************************************************************************************************************************
 * Sws_Index : 8.2.1.5 [SWS_COMPILER_00060]
 * Description : The compiler abstraction shall provide the LOCAL_INLINE define for abstraction of the keyword inline in functions with “static” scope.
 *****************************************************************************************************************************************************************************/
#define LOCAL_INLINE        static inline

#endif /* COMPILER_H_ */