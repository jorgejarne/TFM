
#include <stdio.h>
#include <letmecreate/letmecreate.h>

#define MAX_SIZE 512


int main(int argc, char *argv[])
{
   
    char command[2048];
    FILE *pf;
    char *data =malloc(MAX_SIZE+1);
    int  result;
    int fd[2];
    int distintos;

   


    printf("-------------------------------------------------------------------- \n");
    printf("|                 Bienvenido al cliente MQTT de Ci40               | \n");
    printf("-------------------------------------------------------------------- \n");

  sprintf(command, "mosquitto_sub -h mosquitto.org -p 1883 -t 'mqttRelay'");
  //sprintf(command, "mosquitto_sub -h 192.168.43.120 -p 1883 -t 'mqttRelay'");  
 //sprintf(command, "mosquitto_sub -h 192.168.1.91 -p 1883 -t 'mqttRelay'"); 
    pf = popen(command,"r");
    if(pf==NULL){
   	perror("read");
        exit(3);
    } 
    while(1){
	  
	  if(fgets(data, MAX_SIZE , pf)!=NULL){
	       printf("un valor ha llegado por mqtt");
	       ssize_t len = strlen(data);
	       result = write (fd[1],data,MAX_SIZE);
	       printf("\n \n valor leido:  %s y ocupa : %d  \n \n",data,len);
	       if(data[0] =='0'){
		printf("cerrando rele \n");
		relay2_click_enable_relay(MIKROBUS_1, RELAY2_CLICK_RELAY_1);
	        relay2_click_enable_relay(MIKROBUS_1, RELAY2_CLICK_RELAY_2);

		}
	       if(data[0]=='1'){
		  printf("abriendo rele \n");
		  relay2_click_disable_relay(MIKROBUS_1, RELAY2_CLICK_RELAY_1);
		  relay2_click_disable_relay(MIKROBUS_1, RELAY2_CLICK_RELAY_2);

		}
	      
	   }
     } 

  

    return 0;
}
