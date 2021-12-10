
/***************************** Include Files *********************************/

#include "xparameters.h"
#include "xuartns550.h"
#include "xil_printf.h"
#include <unistd.h>

/************************** Constant Definitions *****************************/

#define UART_DEVICE_ID_1 XPAR_UARTNS550_1_DEVICE_ID
#define BAUD_RATE 921600

/**************************** Type Definitions *******************************/
#define TEST_BUFFER_SIZE 64
u8 cmd_buf[TEST_BUFFER_SIZE];
u8 id_buf[TEST_BUFFER_SIZE];
u8 data_buf[TEST_BUFFER_SIZE];
int cmdCount, idCount, dataCount;
/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/
int start_uart();

/************************** Variable Definitions *****************************/

XUartNs550 UartNs550;		/* The instance of the UART Driver */
XUartNs550_Config *ConfigPtr;
XUartNs550Format FormatPtr;

/*****************************************************************************/

int main(void)
{
	int Status;
	u8 ReplyAck[] = { '<', 'a', 'c', 'k','>' };
	int f_cmd = 0, f_new = 0, f_c=0, f_i=0, f_d=0;
	u8 R[1];

	xil_printf("\t\t\t [RPU] start app \r\n");

	/* ******************************* */
	/* Initialize the UartNs550 device */
	/* ******************************* */
	Status = XUartNs550_Initialize(&UartNs550, UART_DEVICE_ID_1);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	// Get ConfigPtr
	ConfigPtr = XUartNs550_LookupConfig(UART_DEVICE_ID_1);
	if (ConfigPtr == (XUartNs550_Config *)NULL) {
		return XST_FAILURE;
	}

	// Get 	DataFormatPtr
	XUartNs550_GetDataFormat(&UartNs550, &FormatPtr);

	// Set parameters
	FormatPtr.DataBits = XUN_FORMAT_8_BITS;
	FormatPtr.Parity = XUN_FORMAT_NO_PARITY;
	FormatPtr.StopBits = XUN_FORMAT_1_STOP_BIT;

	// Sets the data format for the specified UART
	Status = XUartNs550_SetDataFormat(&UartNs550, &FormatPtr);
	if (Status != XST_SUCCESS) {
			return XST_FAILURE;
	}

	// Set baud rate
	ConfigPtr->DefaultBaudRate = BAUD_RATE;
	Status = XUartNs550_CfgInitialize(&UartNs550, ConfigPtr, ConfigPtr->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	// Check parameters
	XUartNs550_GetDataFormat(&UartNs550, &FormatPtr);

	xil_printf("\t\t\t [RPU] PortStat = [%d]\r\n", UartNs550.Stats);
	xil_printf("\t\t\t [RPU] BaudRate = [%d]\r\n", FormatPtr.BaudRate);
	xil_printf("\t\t\t [RPU] data bit = [%d]\r\n", FormatPtr.DataBits);
	xil_printf("\t\t\t [RPU] parity = [%d]\r\n", FormatPtr.Parity);
	xil_printf("\t\t\t [RPU] stop = [%d]\r\n", FormatPtr.StopBits);


	/* ********* */
	/* main loop */
	/* ********* */

	while(1){

		// read new command and parsing
		while (XUartNs550_Recv(&UartNs550, R, 1) > 0){
			if (R[0] =='<'){
				cmdCount = 0;
				idCount = 0;
				dataCount = 0;
				f_new = 1;
				f_c=1;
				f_i=0;
				f_d=0;
			}
			else if (R[0] == '>'){
				if (f_new == 1){
					f_cmd = 1;
					f_new = 0;
					f_c = 0;
					f_i = 0;
					f_d = 0;
					break;
				}
			}
			else if (R[0] == ':'){
				f_c = 0;
				f_i = 1;
				f_d = 0;
			}
			else if (R[0] == '/'){
				f_c = 0;
				f_i = 0;
				f_d = 1;
			}
			else {
				if (f_c == 1){
					cmd_buf[cmdCount] = R[0];
					cmdCount++;
				}
				else if (f_i == 1){
					id_buf[idCount] = R[0];
					idCount++;
				}
				if (f_d == 1){
					data_buf[dataCount] = R[0];
					dataCount++;
				}
				else {
					//
				}

			}
		}

		// daemon command
		if (f_cmd ==1){
			f_cmd = 0;
			 // print cmd
			xil_printf("\t\t\t [RPU] hew CMD size [%d] = ", cmdCount);
			for (int j=0; j < cmdCount; j++){
				xil_printf("[%c]", cmd_buf[j]);
			}
			xil_printf("\r\n");
			// print id
			xil_printf("\t\t\t [RPU] hew ID size [%d] = ", idCount);
			for (int j=0; j < idCount; j++){
				xil_printf("[%c]", id_buf[j]);
			}
			xil_printf("\r\n");
			// print data
			xil_printf("\t\t\t [RPU] hew DATA size [%d] = ", dataCount);
			for (int j=0; j < dataCount; j++){
				xil_printf("[%c]", data_buf[j]);
			}
			xil_printf("\r\n");

			cmdCount = 0;
			idCount = 0;
			dataCount = 0;

			//send
			int SentCount = 0;
			xil_printf("\t\t\t [RPU] send >> ");
			while (SentCount < sizeof(ReplyAck)) {
				xil_printf("[%c]", ReplyAck[SentCount]);
				SentCount += XUartNs550_Send(&UartNs550, &ReplyAck[SentCount], 1);
			}
			xil_printf("\t\t\t [RPU] send answer [%d]\r\n", SentCount);

		}


		sleep(0.1);

	}

	return Status;
}




/*     */
int start_uart(){
	int Status;


	return XST_SUCCESS;
}

