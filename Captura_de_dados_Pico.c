#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "pico/time.h"
#include <string.h>
#include "hardware/adc.h"
#include "hardware/dma.h"
#include "hardware/gpio.h"

#define FSAMP 500000  // 500kHz
#define NSAMP 1500
#define ADC_BASE_FREQ 48000000  // 48MHz
#define CLKDIV ((ADC_BASE_FREQ / FSAMP) - 1)
//#define CLKDIV 0
#define CAPTURE_CHANNEL 0
#define LED_PIN 25
#define TX1_PIN 2
#define TX2_PIN 3
#define TX3_PIN 4
#define TX4_PIN 5
#define PIN_S0 6
#define PIN_S1 7
#define PIN_S2 8
#define PIN_S3 9
#define PIN_ACK 10
//#define PIN_tst 11


uint16_t cap_buf[NSAMP];
dma_channel_config cfg;
uint dma_chan;

void setup_adc();
void setup_dma();
void sample(uint16_t *capture_buf);
void send_serial_data(uint16_t *buf, size_t len);

int main() {
    stdio_init_all();
    setup_adc();
    setup_dma();
    // Initialise GPIO (Blue LED connected to pin 25)
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    gpio_init(TX1_PIN);
    gpio_set_dir(TX1_PIN, GPIO_OUT);

    gpio_init(TX2_PIN);
    gpio_set_dir(TX2_PIN, GPIO_OUT);

    gpio_init(TX3_PIN);
    gpio_set_dir(TX3_PIN, GPIO_OUT);
    
    gpio_init(TX4_PIN);
    gpio_set_dir(TX4_PIN, GPIO_OUT);

    gpio_init(PIN_S0);
    gpio_set_dir(PIN_S0, GPIO_OUT);

    gpio_init(PIN_S1);
    gpio_set_dir(PIN_S1, GPIO_OUT);

    gpio_init(PIN_S2);
    gpio_set_dir(PIN_S2, GPIO_OUT);
    
    gpio_init(PIN_S3);
    gpio_set_dir(PIN_S3, GPIO_OUT);

    gpio_init(PIN_ACK);
    gpio_set_dir(PIN_ACK, GPIO_IN);

    //gpio_init(PIN_tst);
    //gpio_set_dir(PIN_tst, GPIO_OUT);

    char userInput;
    bool pin_state;

    while (1) {
        
        gpio_put(PIN_S0, 0); 
        gpio_put(PIN_S1, 0); 
        gpio_put(PIN_S2, 0); 
        gpio_put(PIN_S3, 0); 
        gpio_put(TX1_PIN, 0);
        gpio_put(TX2_PIN, 0);
        gpio_put(TX3_PIN, 0);
        gpio_put(TX4_PIN, 0);
        

        userInput = getchar();

            if(userInput == '1'){
            
        gpio_put(PIN_S0, 1); // Set pin 9 to HIGH
        gpio_put(PIN_S1, 0); // Set pin 10 to low
        gpio_put(PIN_S2, 0); // Set pin 11 to low
        gpio_put(PIN_S3, 0); // Set pin 12 to low

            gpio_put(TX1_PIN, 1);

            while(true){
                pin_state=gpio_get(PIN_ACK);
                if(pin_state){
                    break;
                }
            }

   //         gpio_put(PIN_tst, 1);    
            sample(cap_buf);
   //         gpio_put(PIN_tst, 0);  
            gpio_put(TX1_PIN, 0);  //Deliga o pino de transmiss'ao durante a escrita da serial
        gpio_put(PIN_S0, 0); 
        gpio_put(PIN_S1, 0); 
        gpio_put(PIN_S2, 0); 
        gpio_put(PIN_S3, 0); 

            send_serial_data(cap_buf, NSAMP);
        }
//--------------------------------------------------------------------------------------------
        else if(userInput == '2'){
            //T1R2
            
            gpio_put(PIN_S0, 0); // Set pin 9 to HIGH
            gpio_put(PIN_S1, 1); // Set pin 10 to low
        gpio_put(PIN_S2, 0); // Set pin 11 to low
        gpio_put(PIN_S3, 0); // Set pin 12 to low
            
            gpio_put(TX1_PIN, 1);


            while(true){
                pin_state=gpio_get(PIN_ACK);
                if(pin_state){
                    break;
                }
            }

   //         gpio_put(PIN_tst, 1);    
            sample(cap_buf);
   //         gpio_put(PIN_tst, 0);  
            gpio_put(TX1_PIN, 0);  //Deliga o pino de transmiss'ao durante a escrita da serial
        gpio_put(PIN_S0, 0); 
        gpio_put(PIN_S1, 0); 
        gpio_put(PIN_S2, 0); 
        gpio_put(PIN_S3, 0); 

            send_serial_data(cap_buf, NSAMP);
        }

//-----------------------------------------------------------------------------------
        
        else if(userInput == '3'){
            //T1R3
            
            gpio_put(PIN_S0, 0); // Set pin 9 to HIGH
            gpio_put(PIN_S1, 0); // Set pin 10 to low
        gpio_put(PIN_S2, 1); // Set pin 11 to low
        gpio_put(PIN_S3, 0); // Set pin 12 to low
            
            gpio_put(TX1_PIN, 1);


            while(true){
                pin_state=gpio_get(PIN_ACK);
                if(pin_state){
                    break;
                }
            }

   //         gpio_put(PIN_tst, 1);    
            sample(cap_buf);
   //         gpio_put(PIN_tst, 0);  
            gpio_put(TX1_PIN, 0);  //Deliga o pino de transmiss'ao durante a escrita da serial
        gpio_put(PIN_S0, 0); 
        gpio_put(PIN_S1, 0); 
        gpio_put(PIN_S2, 0); 
        gpio_put(PIN_S3, 0); 

            send_serial_data(cap_buf, NSAMP);
        }

//------------------------------------------------------------------------------------
else if(userInput == '4'){
            //T1R4
            
            gpio_put(PIN_S0, 0); // Set pin 9 to HIGH
            gpio_put(PIN_S1, 0); // Set pin 10 to low
        gpio_put(PIN_S2, 0); // Set pin 11 to low
        gpio_put(PIN_S3, 1); // Set pin 12 to low
            
            gpio_put(TX1_PIN, 1);


            while(true){
                pin_state=gpio_get(PIN_ACK);
                if(pin_state){
                    break;
                }
            }

   //         gpio_put(PIN_tst, 1);    
            sample(cap_buf);
   //         gpio_put(PIN_tst, 0);  
            gpio_put(TX1_PIN, 0);  //Deliga o pino de transmiss'ao durante a escrita da serial
        gpio_put(PIN_S0, 0); 
        gpio_put(PIN_S1, 0); 
        gpio_put(PIN_S2, 0); 
        gpio_put(PIN_S3, 0); 

            send_serial_data(cap_buf, NSAMP);
        }

//----------------------------------------------------------------------------------------------------
else if(userInput == '5'){
            //T2R1
            
            gpio_put(PIN_S0, 1); // Set pin 9 to HIGH
            gpio_put(PIN_S1, 0); // Set pin 10 to low
        gpio_put(PIN_S2, 0); // Set pin 11 to low
        gpio_put(PIN_S3, 0); // Set pin 12 to low
            
            gpio_put(TX2_PIN, 1);
 

            while(true){
                pin_state=gpio_get(PIN_ACK);
                if(pin_state){
                    break;
                }
            }

   //         gpio_put(PIN_tst, 1);    
            sample(cap_buf);
   //         gpio_put(PIN_tst, 0);  
            gpio_put(TX2_PIN, 0);  //Deliga o pino de transmiss'ao durante a escrita da serial
        gpio_put(PIN_S0, 0); 
        gpio_put(PIN_S1, 0); 
        gpio_put(PIN_S2, 0); 
        gpio_put(PIN_S3, 0); 

            send_serial_data(cap_buf, NSAMP);
        }
//----------------------------------------------------------------------------------------------------
    
    else if(userInput == '6'){
            //T2R2
            
            gpio_put(PIN_S0, 0); // Set pin 9 to HIGH
            gpio_put(PIN_S1, 1); // Set pin 10 to low
        gpio_put(PIN_S2, 0); // Set pin 11 to low
        gpio_put(PIN_S3, 0); // Set pin 12 to low
            
            gpio_put(TX2_PIN, 1);
 

            while(true){
                pin_state=gpio_get(PIN_ACK);
                if(pin_state){
                    break;
                }
            }

   //         gpio_put(PIN_tst, 1);    
            sample(cap_buf);
   //         gpio_put(PIN_tst, 0);  
            gpio_put(TX2_PIN, 0);  //Deliga o pino de transmiss'ao durante a escrita da serial
        gpio_put(PIN_S0, 0); 
        gpio_put(PIN_S1, 0); 
        gpio_put(PIN_S2, 0); 
        gpio_put(PIN_S3, 0); 

            send_serial_data(cap_buf, NSAMP);
        }
//----------------------------------------------------------------------------------------------------
else if(userInput == '7'){
            //T2R3
            
            gpio_put(PIN_S0, 0); // Set pin 9 to HIGH
            gpio_put(PIN_S1, 0); // Set pin 10 to low
        gpio_put(PIN_S2, 1); // Set pin 11 to low
        gpio_put(PIN_S3, 0); // Set pin 12 to low
            
            gpio_put(TX2_PIN, 1);
 

            while(true){
                pin_state=gpio_get(PIN_ACK);
                if(pin_state){
                    break;
                }
            }

   //         gpio_put(PIN_tst, 1);    
            sample(cap_buf);
   //         gpio_put(PIN_tst, 0);  
            gpio_put(TX2_PIN, 0);  //Deliga o pino de transmiss'ao durante a escrita da serial
        gpio_put(PIN_S0, 0); 
        gpio_put(PIN_S1, 0); 
        gpio_put(PIN_S2, 0); 
        gpio_put(PIN_S3, 0); 

            send_serial_data(cap_buf, NSAMP);
        }  

 //-----------------------------------------------------------------------------------------------------

 else if(userInput == '8'){
            //T2R4
            
            gpio_put(PIN_S0, 0); // Set pin 9 to HIGH
            gpio_put(PIN_S1, 0); // Set pin 10 to low
        gpio_put(PIN_S2, 0); // Set pin 11 to low
        gpio_put(PIN_S3, 1); // Set pin 12 to low
            
            gpio_put(TX2_PIN, 1);
 

            while(true){
                pin_state=gpio_get(PIN_ACK);
                if(pin_state){
                    break;
                }
            }

   //         gpio_put(PIN_tst, 1);    
            sample(cap_buf);
   //         gpio_put(PIN_tst, 0);  
            gpio_put(TX2_PIN, 0);  //Deliga o pino de transmiss'ao durante a escrita da serial
        gpio_put(PIN_S0, 0); 
        gpio_put(PIN_S1, 0); 
        gpio_put(PIN_S2, 0); 
        gpio_put(PIN_S3, 0); 

            send_serial_data(cap_buf, NSAMP);
        }

//-----------------------------------------------------------------------------------------


else if(userInput == '9'){
            //T3R1
            
            gpio_put(PIN_S0, 1); // Set pin 9 to HIGH
            gpio_put(PIN_S1, 0); // Set pin 10 to low
        gpio_put(PIN_S2, 0); // Set pin 11 to low
        gpio_put(PIN_S3, 0); // Set pin 12 to low
            
            gpio_put(TX3_PIN, 1);
 

            while(true){
                pin_state=gpio_get(PIN_ACK);
                if(pin_state){
                    break;
                }
            }

   //         gpio_put(PIN_tst, 1);    
            sample(cap_buf);
   //         gpio_put(PIN_tst, 0);  
            gpio_put(TX3_PIN, 0);  //Deliga o pino de transmiss'ao durante a escrita da serial
        gpio_put(PIN_S0, 0); 
        gpio_put(PIN_S1, 0); 
        gpio_put(PIN_S2, 0); 
        gpio_put(PIN_S3, 0); 

            send_serial_data(cap_buf, NSAMP);
        }

//----------------------------------------------------------------------------------------------------------

else if(userInput == 'A'){
            //T3R2
            
            gpio_put(PIN_S0, 0); // Set pin 9 to HIGH
            gpio_put(PIN_S1, 1); // Set pin 10 to low
        gpio_put(PIN_S2, 0); // Set pin 11 to low
        gpio_put(PIN_S3, 0); // Set pin 12 to low
            
            gpio_put(TX3_PIN, 1);
 

            while(true){
                pin_state=gpio_get(PIN_ACK);
                if(pin_state){
                    break;
                }
            }

   //         gpio_put(PIN_tst, 1);    
            sample(cap_buf);
   //         gpio_put(PIN_tst, 0);  
            gpio_put(TX3_PIN, 0);  //Deliga o pino de transmiss'ao durante a escrita da serial
        gpio_put(PIN_S0, 0); 
        gpio_put(PIN_S1, 0); 
        gpio_put(PIN_S2, 0); 
        gpio_put(PIN_S3, 0); 

            send_serial_data(cap_buf, NSAMP);
        }

//----------------------------------------------------------------------------------------------------------


else if(userInput == 'B'){
            //T3R3
            
            gpio_put(PIN_S0, 0); // Set pin 9 to HIGH
            gpio_put(PIN_S1, 0); // Set pin 10 to low
        gpio_put(PIN_S2, 1); // Set pin 11 to low
        gpio_put(PIN_S3, 0); // Set pin 12 to low
            
            gpio_put(TX3_PIN, 1);
 

            while(true){
                pin_state=gpio_get(PIN_ACK);
                if(pin_state){
                    break;
                }
            }

   //         gpio_put(PIN_tst, 1);    
            sample(cap_buf);
   //         gpio_put(PIN_tst, 0);  
            gpio_put(TX3_PIN, 0);  //Deliga o pino de transmiss'ao durante a escrita da serial
        gpio_put(PIN_S0, 0); 
        gpio_put(PIN_S1, 0); 
        gpio_put(PIN_S2, 0); 
        gpio_put(PIN_S3, 0); 

            send_serial_data(cap_buf, NSAMP);
        }

//------------------------------------------------------------------------------------------------------------

else if(userInput == 'C'){
            //T3R4
            
            gpio_put(PIN_S0, 0); // Set pin 9 to HIGH
            gpio_put(PIN_S1, 0); // Set pin 10 to low
        gpio_put(PIN_S2, 0); // Set pin 11 to low
        gpio_put(PIN_S3, 1); // Set pin 12 to low
            
            gpio_put(TX3_PIN, 1);
 

            while(true){
                pin_state=gpio_get(PIN_ACK);
                if(pin_state){
                    break;
                }
            }

   //         gpio_put(PIN_tst, 1);    
            sample(cap_buf);
   //         gpio_put(PIN_tst, 0);  
            gpio_put(TX3_PIN, 0);  //Deliga o pino de transmiss'ao durante a escrita da serial
        gpio_put(PIN_S0, 0); 
        gpio_put(PIN_S1, 0); 
        gpio_put(PIN_S2, 0); 
        gpio_put(PIN_S3, 0); 

            send_serial_data(cap_buf, NSAMP);
        }
//----------------------------------------------------------------------------------------------------

else if(userInput == 'D'){
            //T4R1
            
            gpio_put(PIN_S0, 1); // Set pin 9 to HIGH
            gpio_put(PIN_S1, 0); // Set pin 10 to low
        gpio_put(PIN_S2, 0); // Set pin 11 to low
        gpio_put(PIN_S3, 0); // Set pin 12 to low
            
            gpio_put(TX4_PIN, 1);
 

            while(true){
                pin_state=gpio_get(PIN_ACK);
                if(pin_state){
                    break;
                }
            }

   //         gpio_put(PIN_tst, 1);    
            sample(cap_buf);
   //         gpio_put(PIN_tst, 0);  
            gpio_put(TX4_PIN, 0);  //Deliga o pino de transmiss'ao durante a escrita da serial
        gpio_put(PIN_S0, 0); 
        gpio_put(PIN_S1, 0); 
        gpio_put(PIN_S2, 0); 
        gpio_put(PIN_S3, 0); 

            send_serial_data(cap_buf, NSAMP);
        }

  //-------------------------------------------------------------------------------------------------

  else if(userInput == 'E'){
            //T4R2
            
            gpio_put(PIN_S0, 0); // Set pin 9 to HIGH
            gpio_put(PIN_S1, 1); // Set pin 10 to low
        gpio_put(PIN_S2, 0); // Set pin 11 to low
        gpio_put(PIN_S3, 0); // Set pin 12 to low
            
            gpio_put(TX4_PIN, 1);
 

            while(true){
                pin_state=gpio_get(PIN_ACK);
                if(pin_state){
                    break;
                }
            }

   //         gpio_put(PIN_tst, 1);    
            sample(cap_buf);
   //         gpio_put(PIN_tst, 0);  
            gpio_put(TX4_PIN, 0);  //Deliga o pino de transmiss'ao durante a escrita da serial
        gpio_put(PIN_S0, 0); 
        gpio_put(PIN_S1, 0); 
        gpio_put(PIN_S2, 0); 
        gpio_put(PIN_S3, 0); 

            send_serial_data(cap_buf, NSAMP);
        }      

//-------------------------------------------------------------------------------------------------------

  else if(userInput == 'F'){
            //T4R3
            
            gpio_put(PIN_S0, 0); // Set pin 9 to HIGH
            gpio_put(PIN_S1, 0); // Set pin 10 to low
        gpio_put(PIN_S2, 1); // Set pin 11 to low
        gpio_put(PIN_S3, 0); // Set pin 12 to low
            
            gpio_put(TX4_PIN, 1);
 

            while(true){
                pin_state=gpio_get(PIN_ACK);
                if(pin_state){
                    break;
                }
            }

   //         gpio_put(PIN_tst, 1);    
            sample(cap_buf);
   //         gpio_put(PIN_tst, 0);  
            gpio_put(TX4_PIN, 0);  //Deliga o pino de transmiss'ao durante a escrita da serial
        gpio_put(PIN_S0, 0); 
        gpio_put(PIN_S1, 0); 
        gpio_put(PIN_S2, 0); 
        gpio_put(PIN_S3, 0); 

            send_serial_data(cap_buf, NSAMP);
        }      

//-------------------------------------------------------------------------------------------

  else if(userInput == 'G'){
            //T4R4
            
            gpio_put(PIN_S0, 0); // Set pin 9 to HIGH
            gpio_put(PIN_S1, 0); // Set pin 10 to low
        gpio_put(PIN_S2, 0); // Set pin 11 to low
        gpio_put(PIN_S3, 1); // Set pin 12 to low
            
            gpio_put(TX4_PIN, 1);
 

            while(true){
                pin_state=gpio_get(PIN_ACK);
                if(pin_state){
                    break;
                }
            }

   //         gpio_put(PIN_tst, 1);    
            sample(cap_buf);
   //         gpio_put(PIN_tst, 0);  
            gpio_put(TX4_PIN, 0);  //Deliga o pino de transmiss'ao durante a escrita da serial
        gpio_put(PIN_S0, 0); 
        gpio_put(PIN_S1, 0); 
        gpio_put(PIN_S2, 0); 
        gpio_put(PIN_S3, 0); 

            send_serial_data(cap_buf, NSAMP);
        } 
//--------------------------------------------------------------------------------------------
        else{
            // printf("Invalid Input!\n");
        }
        
	}
}

void setup_adc() {
    adc_init();
    adc_select_input(CAPTURE_CHANNEL);
    adc_set_clkdiv(1);
    adc_fifo_setup(true, true, 1, false, true);
}

void setup_dma() {
    dma_chan = dma_claim_unused_channel(true);
    cfg = dma_channel_get_default_config(dma_chan);
    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_16);
    channel_config_set_read_increment(&cfg, false);
    channel_config_set_write_increment(&cfg, true);
    channel_config_set_dreq(&cfg, DREQ_ADC);
}

void sample(uint16_t *capture_buf) {
    adc_fifo_drain();
    adc_run(false);
      
    dma_channel_configure(dma_chan, &cfg, capture_buf, &adc_hw->fifo, NSAMP, true);

    gpio_put(LED_PIN, 1);
    adc_run(true);
    dma_channel_wait_for_finish_blocking(dma_chan);
    gpio_put(LED_PIN, 0);
}

void send_serial_data(uint16_t *buf, size_t len) {
    

    for (size_t i = 0; i < len; i++) {
        printf("%d,", buf[i]);
    }
    printf("\n");
}
