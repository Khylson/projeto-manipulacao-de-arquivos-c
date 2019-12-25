#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
 
   struct sockaddr_in LO_EndPOP;
   struct sockaddr_in LO_EndSMTP;
   
   time_t t = time(NULL);
   struct tm *tm = localtime(&t);
    //printf("%s", asctime(tm));
    
   int LO_TamEndPOP;
   int LO_TamEndSMTP;

   WORD LO_Versao;
   WSADATA LO_wsaData;

   int LO_CanalPOP;
   int LO_CanalSMTP;

   char LO_vbcrlf[2];
   LO_vbcrlf[0] = 13;
   LO_vbcrlf[1] = 10;
   LO_vbcrlf[2] = 0;

   //-----> Verificação da versão da winsock

   
   LO_Versao = MAKEWORD( 2, 2 );
   
   int LO_Erro = WSAStartup( LO_Versao, &LO_wsaData );
   if( LO_Erro != 0 )
   {
      printf( "Não foi possível encontrar a dll winsock!\n" );
      
      return(-1);
   }
   if( LOBYTE( LO_wsaData.wVersion) < 2 || HIBYTE( LO_wsaData.wVersion) < 2)
   {
      printf( "A dll winsock é muito antiga!\n" );
      
      return(-1);
   }
   
   //-----> Inicia a autenticação POP3 - Necessário para SMTP também !
   
 
   // Inicializa estrutura para o canal de escuta
   
   LO_EndPOP.sin_family = AF_INET;
   LO_EndPOP.sin_addr.s_addr = inet_addr("200.199.201.238") ; // IP da brasil telecom
   LO_EndPOP.sin_port = htons(110);                           // Porta POP
   int LO_Con;
   for( LO_Con = 0; LO_Con < 8; LO_Con++ )
   {
      LO_EndPOP.sin_zero[LO_Con] = 0;
   }
   LO_TamEndPOP = sizeof(LO_EndPOP);
 
   //-----> Cria canal de conexão socket
   
   if(( LO_CanalPOP = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP )) <= 0 )
   {
      printf( "Erro ao criar o canal!\n" );
      
      return(-1);
   }

   //-----> Conecta ao servidor
 
   if( connect( LO_CanalPOP, (struct sockaddr*)&LO_EndPOP, LO_TamEndPOP ) == -1 )
   {
      printf( "Erro ao se conectar!\n" );
      
      return(-1);
   }  
   
   char LO_Retorno[512];


  const char *LO_Usuario = "USER MX Khylson";

   printf( "Mensagem: %s\n", LO_Usuario );
   send( LO_CanalPOP, LO_Usuario, strlen(LO_Usuario), 0);
   send( LO_CanalPOP, LO_vbcrlf, 2, 0);

   memset( LO_Retorno, '\0', 512 );
   recv( LO_CanalPOP, LO_Retorno, 512, 0 );
   printf( "Retorno: %s\n", LO_Retorno );


  const char *LO_Senha = "PASS Muxito@2230";

  // printf( "Mensagem: %s\n", LO_Senha );
   send( LO_CanalPOP, LO_Senha, strlen(LO_Senha), 0);
   send( LO_CanalPOP, LO_vbcrlf, 2, 0);

   memset( LO_Retorno, '\0', 512 );
   recv( LO_CanalPOP, LO_Retorno, 512, 0 );
  // printf( "Retorno: %s\n", LO_Retorno );


   //-----> Inicia a autenticação POP3 - Necessário para SMTP também !
   
   
   // Inicializa estrutura para o canal de escuta
   
   LO_EndSMTP.sin_family = AF_INET;
   LO_EndSMTP.sin_addr.s_addr = inet_addr("200.199.201.235"); // IP da brasil telecom
   LO_EndSMTP.sin_port = htons(25);                           // Porta SMTP
   for( LO_Con = 0; LO_Con < 8; LO_Con++ )
   {
      LO_EndSMTP.sin_zero[LO_Con] = 0;
   }
   LO_TamEndSMTP = sizeof(LO_EndSMTP);
 
   //-----> Cria canal de conexão socket
   
   if(( LO_CanalSMTP = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP )) <= 0 )
   {
      printf( "Erro ao criar o canal!\n" );
    
      return(-1);
   }

   //-----> Conecta ao servidor
 
   if( connect( LO_CanalSMTP, (struct sockaddr*)&LO_EndSMTP, LO_TamEndSMTP ) == -1 )
   {
      printf( "Erro ao se conectar!\n" );
      
      return(-1);
   }  

   printf( "Conectado ao servidor!\n\n" );

   printf( "Enviando mensagem...\n\n" );

   memset( LO_Retorno, '\0', 512 );
   recv( LO_CanalSMTP, LO_Retorno, 512, 0 );
   printf( "Retorno: %s\n", LO_Retorno );

  const char *LO_Helo = "HELO www.accounts.google.com";

   printf( "Mensagem: %s\n", LO_Helo );
   send( LO_CanalSMTP, LO_Helo, strlen(LO_Helo), 0);
   send( LO_CanalSMTP, LO_vbcrlf, 2, 0);

   memset( LO_Retorno, '\0', 512 );
   recv( LO_CanalSMTP, LO_Retorno, 512, 0 );
   printf( "Retorno: %s\n", LO_Retorno );

   const char *LO_De = "MAIL De: <mkhylson@gmail.com>";
   printf( "%Mensagem: %s\n", LO_De );
   send( LO_CanalSMTP, LO_De, strlen(LO_De), 0);
   send( LO_CanalSMTP, LO_vbcrlf, 2, 0);

   memset( LO_Retorno, '\0', 512 );
   recv( LO_CanalSMTP, LO_Retorno, 512, 0 );
   printf( "Retorno: %s\n", LO_Retorno );

   const char *LO_Para = "RCPT Para: <mkhylson@gmail.com>";
   printf( "%Mensagem: %s\n", LO_Para );
   send( LO_CanalSMTP, LO_Para, strlen(LO_Para), 0);
   send( LO_CanalSMTP, LO_vbcrlf, 2, 0);

   memset( LO_Retorno, '\0', 512 );
   recv( LO_CanalSMTP, LO_Retorno, 512, 0 );
   printf( "Retorno: %s\n", LO_Retorno );


   // Início da mensagem
   
   const char *LO_Data = asctime(tm);
   printf( "%Mensagem: %s\n", LO_Data );
   send( LO_CanalSMTP, LO_Data, strlen(LO_Data), 0);
   send( LO_CanalSMTP, LO_vbcrlf, 2, 0);

   memset( LO_Retorno, '\0', 512 );
   recv( LO_CanalSMTP, LO_Retorno, 512, 0 );
   printf( "Retorno: %s\n", LO_Retorno );

   const char *LO_Subject = "Assunto: Mensagem de teste!";
   printf( "Mensagem: %s\n", LO_Subject );
   send( LO_CanalSMTP, LO_Subject, strlen(LO_Subject), 0);
   send( LO_CanalSMTP, LO_vbcrlf, 2, 0);

   const char *LO_From = "De: mkhylson@gmail.com";
   printf( "Mensagem: %s\n", LO_From );
   send( LO_CanalSMTP, LO_From, strlen(LO_From), 0);
   send( LO_CanalSMTP, LO_vbcrlf, 2, 0);

   const char *LO_To = "Para: mkhylson@gmail.com";
   printf( "Mensagem: %s\n", LO_To );
   send( LO_CanalSMTP, LO_To, strlen(LO_To), 0);
   send( LO_CanalSMTP, LO_vbcrlf, 2, 0);

   const char *LO_Msg = "Texto: Ola, uma mensagem foi enviada na sua casa de correio!";
   printf( "Mensagem: %s\n", LO_Msg );
   send( LO_CanalSMTP, LO_Msg, strlen(LO_Msg), 0);
   send( LO_CanalSMTP, LO_vbcrlf, 2, 0);

   // Fim da mensagem

   send( LO_CanalSMTP, ".", 1, 0);
   send( LO_CanalSMTP, LO_vbcrlf, 2, 0);  

   memset( LO_Retorno, '\0', 512 );
   recv( LO_CanalSMTP, LO_Retorno, 512, 0 );
   printf( "Retorno: %s\n", LO_Retorno );

   // Envia comando de encerramento

   printf( "%Mensagem: QUIT\n" );
   send( LO_CanalSMTP, "QUIT", 4, 0);
   send( LO_CanalSMTP, LO_vbcrlf, 2, 0);  

   memset( LO_Retorno, '\0', 512 );
   recv( LO_CanalSMTP, LO_Retorno, 512, 0 );
   printf( "Retorno: %s\n", LO_Retorno );
 
   printf( "Fim do envio!\n" );

   closesocket( LO_CanalPOP );  
   closesocket( LO_CanalSMTP );  
 
 
   return 0;
}
