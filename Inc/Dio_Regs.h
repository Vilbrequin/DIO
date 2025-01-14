#ifndef DIO_REGS_H_
#define DIO_REGS_H_

#define GPIO_A_BASE_ADDRESS             (0x400FF000U)
#define GPIO_B_BASE_ADDRESS             (0x400FF040U)
#define GPIO_C_BASE_ADDRESS             (0x400FF080U)
#define GPIO_D_BASE_ADDRESS             (0x400FF0C0U)
#define GPIO_E_BASE_ADDRESS             (0x400FF100U)

// Port Data Output Register (PDOR)
#define PDOR_OFFSET                     0x00

#define GPIO_A_PDOR                     (GPIO_A_BASE_ADDRESS + PDOR_OFFSET)
#define GPIO_B_PDOR                     (GPIO_B_BASE_ADDRESS + PDOR_OFFSET)
#define GPIO_C_PDOR                     (GPIO_C_BASE_ADDRESS + PDOR_OFFSET)
#define GPIO_D_PDOR                     (GPIO_D_BASE_ADDRESS + PDOR_OFFSET)
#define GPIO_E_PDOR                     (GPIO_E_BASE_ADDRESS + PDOR_OFFSET)

// Port Data Input Register (PDIR)
#define PDIR_OFFSET                     (0x10U)
#define GPIO_A_PDIR                     (GPIO_A_BASE_ADDRESS + PDIR_OFFSET)
#define GPIO_B_PDIR                     (GPIO_B_BASE_ADDRESS + PDIR_OFFSET)
#define GPIO_C_PDIR                     (GPIO_C_BASE_ADDRESS + PDIR_OFFSET)
#define GPIO_D_PDIR                     (GPIO_D_BASE_ADDRESS + PDIR_OFFSET)
#define GPIO_E_PDIR                     (GPIO_E_BASE_ADDRESS + PDIR_OFFSET)

// Port Data Direction Register (PDDR)
#define PDDR_OFFSET                     (0x14U)
#define GPIO_A_PDDR                     (GPIO_A_BASE_ADDRESS + PDDR_OFFSET)
#define GPIO_B_PDDR                     (GPIO_B_BASE_ADDRESS + PDDR_OFFSET)
#define GPIO_C_PDDR                     (GPIO_C_BASE_ADDRESS + PDDR_OFFSET)
#define GPIO_D_PDDR                     (GPIO_D_BASE_ADDRESS + PDDR_OFFSET)
#define GPIO_E_PDDR                     (GPIO_E_BASE_ADDRESS + PDDR_OFFSET)


#endif /* DIO_REGS_H_ */
