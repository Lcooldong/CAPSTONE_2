#include "MCP2515.h"

extern SPI_HandleTypeDef			hspi3;
#define SPI_CAN								&hspi3;
#define SPI_TIMEOUT						10
#define MCP2515_CS_HIGH()			HAL_GPIO_WritePin(CAN_CS_GPIO_Port, CAN_CS_Pin, GPIO_PIN_SET)
#define MCP2515_CS_LOW()			HAL_GPIO_WritePin(CAN_CS_GPIO_Port, CAN_CS_Pin, GPIO_PIN_RESET)


/* Prototypes */
static void SPI_Tx(uint8_t data);
static void SPI_TxBuffer(uint8_t *buffer, uint8_t length);
static uint8_t SPI_Rx(void);
static void SPI_RxBuffer(uint8_t *bufer, uint8_t length);

/* initialization MCP2515 */
bool MCP2515_Initialize(void)
{
	MCP2515_CS_HIGH();
	
	uint8_t loop = 10;
	
	do{
		/* SPI Ready Check */
		if(HAL_SPI_GetState(SPI_CAN) == HAL_SPI_STATE_READY)
			return true;
		
		loop--;
	}while(loop >0);

	return false;
}
