/*
 ============================================================================
 Name        : assembler.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE  *fpr;
FILE  *fpw;
unsigned int getIstruction ();
unsigned int getothersRd ();
unsigned int getothersRs ();
unsigned int getothersshift ();
unsigned int getothersI ();
unsigned int getothersJ ();
unsigned int getothersluI ();
unsigned int getothers(unsigned int x);
int main(void) {
	unsigned int inst,code,others;
	/*pointer to the first line in the file 8*/
	fpr = fopen("test.txt","r");
	fpw = fopen("mem.txt","w");
while (!feof(fpr))
	{inst= getIstruction();
     others = getothers(inst);
	 code = inst | others;
	printf	 ("%d \n \n \n",code);
    fprintf	 (fpw,"%d \n",code);
	}
    fclose(fpr);
    fclose(fpw);

	return 0;
}


/*there are some instructions share same syntax
 *First type is instruction Rd,Rs,Rt  where d & t & s = 00 >> 31
• add Rd, Rs, Rt Rd = Rs + Rt (signed)
• addu Rd, Rs, Rt Rd = Rs + Rt (unsigned)
• sub Rd, Rs, Rt Rd = Rs - Rt (signed)
• subu Rd, Rs, Rt Rd = Rs - Rt (unsigned)
• and Rd, Rs, Rt Rd = Rs • Rt
• nor Rd, Rs, Rt Rd = (Rs + Rt)’
• or Rd, Rs, Rt Rd = Rs + Rt
• xor Rd, Rs, Rt Rd = Rs ⊕ Rt
• mfhi Rd Rd = hi
• mflo Rd Rd = lo
• slt Rd, Rs, Rt Rd = 1 if Rs < Rt, Rd = 0 if Rs ≥ Rt (signed)
• sltu Rd, Rs, Rt Rd = 1 if Rs < Rt, Rd = 0 if Rs ≥ Rt (unsigned)

 *Second type is instruction Rs,Rt  where t & s = 00 >> 31
• jr Rs
• in Rs                    Store the input value into Rs R 0x00 0x04
• out Rs                   Output the value of Rs R 0x00 0x0
• mult Rs,Rt
• multu Rs,Rt
• div Rs,Rt
• divu Rs,Rt
• push Rs,Rt
• pop Rs,Rt

 *Third type is instruction Rd,Rs,Sa  where d & s & Sa = 00 >> 31
• sll Rd, Rs, Sa Rd = Rs left shifted by Sa bits
• srl Rd, Rs, Sa Rd = Rs right shifted by Sa bits
• sra Rd, Rs, Sa Rd = Rs right arithmatic shifted by Sa bits

 *Fourth type is instruction Rt,Rs,IMM  where t & s & IMM
• addi Rt,Rs,immediate
• addiu Rt,Rs,immediate
• andi Rt,Rs,immediate
• ori Rt, Rs, Imm
• slti Rt,Rs,immediate
• sltiu Rt,Rs,immediate
• lw Rt,Rs, Offset Rt = word at M[Address + Rs]
• sw Rt,Rs, offset Word at M[Address + Rs] = Rt
• beq Rt,Rs,Offset
• bne Rt,Rs,Offset

 *Fifth type is instruction IMM
 • jal jump_target
 • j jump_target

 *Sixth type is instruction Rt,Imm
• lui Rt, Imm      Rt[31:16] = Imm, Rt[15:0] = 0



*/


/*+==========================================================================================================================*/
/*============First Type=======================*/
unsigned int getothersRd (void)
{   unsigned int y=0; /*the ouput of the function*/
    char temp [2];/*temp array to get the string Reg number*/
    int temp2;/*temp int to get the integer Reg number*/
    unsigned char count=0;/*counter for the Reg number in the instruction line */
    char line[50];/*temp array to get the whole line after the instruction*/
    unsigned char i=0;/*line cursor*/

    fgets(line,50,fpr);/*getting the whole line after the instruction*/
 while (line [i]!= '\0') /*as i am in the same line or instruction*/
 {
   if (line[i]=='R')
	   /*when you see  a capital R it means it indicates a Reg number but which one that what the count would tell us
	    * as the instruction format is instruction Rd,Rs,Rt
	          and the binary format is OPCODE      RS RT RD   SA FUNC
	     in this type we focus on the three Regs only
       */
   { count++;
	 temp [0]= line[i+1] ;/*getting the string reg number */
     temp [1]= line[i+2] ;
     temp2 = atoi(temp);/*converting the string number to integer*/
     printf("%d \n",temp2);
	 if (count==1)
	 {/* first reg is Rd so in the code it is shifted lift by 11 */
     y|=(temp2<<11);
	 }
     else if(count==2)
     {/* second reg is Rs so in the code it is shifted lift by 21 */
    	y|=(temp2<<21); //RS
     }
     else if(count==3)
	 {/* third reg is Rt so in the code it is shifted lift by 16 */
    	 y|=(temp2<<16);//Rt
	 }
	 printf("%d \n",y);
   }
   i++;
 }
 printf("%s \n",line);

 return y;
 }

/*+==========================================================================================================================*/
/*============Second Type=======================*/
unsigned int getothersRs (void)
{   unsigned int y=0;/*the ouput of the function*/
    char temp [2];/*temp array to get the string Reg number*/
    int temp2;/*temp int to get the integer Reg number*/
    unsigned char count=0;/*counter for the Reg number in the instruction line */
    char line[50];/*temp array to get the whole line after the instruction*/
    unsigned char i=0;/*line cursor*/

    fgets(line,50,fpr);/*getting the whole line after the instruction*/
 while (line [i]!= '\0')
 {   /*when you see  a capital R it means it indicates a Reg number but which one that what the count would tell us
      * as the instruction format is instruction Rs,Rt
            and the binary format is OPCODE      RS RT RD   SA FUNC
       in this type we focus on the two Regs only Rs,Rt
     */
   if (line[i]=='R')
   { count++;
	 temp [0]= line[i+1] ;
     temp [1]= line[i+2] ;
     temp2 = atoi(temp);
     printf("%d \n",temp2);
     if(count==1)
     {/* first reg is Rs so in the code it is shifted lift by 21 */
    	y|=(temp2<<21); //RS
     }
     else if(count==2)
	 {/* second reg is Rt so in the code it is shifted lift by 16 */
    	 y|=(temp2<<16);//Rt
	 }
	 printf("%d \n",y);
   }
   i++;
 }
 printf("%s \n",line);

 return y;
 }

/*+==========================================================================================================================*/
/*============Third Type=======================*/
unsigned int getothersshift (void)
{   unsigned int y=0;/*the ouput of the function*/
    char temp [2];/*temp array to get the string Reg number*/
    int temp2;/*temp int to get the integer Reg number*/
    char SA [7];/*temp array to get the string shift amount number 5 digits in case of binary and 2 digits for the base type*/
    unsigned int SA2=0;/*temp int to get the integer shift amount number*/
    unsigned char count=0;/*counter for the Reg number in the instruction line */
    char line[50];/*temp array to get the whole line after the instruction*/
    unsigned char i=0;/*line cursor*/

    fgets(line,50,fpr);/*getting the whole line after the instruction*/
 while (line [i]!= '\0')
 {
   if (line[i]=='R')
	   /*when you see  a capital R it means it indicates a Reg number but which one that what the count would tell us
	    * as the instruction format is instruction Rd,Rs,SA
	          and the binary format is OPCODE      RS RT RD   SA FUNC
	     in this type we focus on the two Regs and SA
       */
   { count++;
	 temp [0]= line[i+1] ;
     temp [1]= line[i+2] ;
      temp2 = atoi(temp);
     printf("%d \n",temp2);
     if (count==1)
     	 {/* first reg is Rd so in the code it is shifted lift by 11 */
          y|=(temp2<<11);
     	 }
          else if(count==2)
          {/* second reg is Rs so in the code it is shifted lift by 21 */
         	y|=(temp2<<21);
         	SA[0]=line[i+4];/*getting string SA which is after the second R letter by 4 char*/
            SA[1]=line[i+5];
            if ((SA[0]=='0')&&(SA[1]=='x'))
            {
            SA2 = (int)strtol((SA+2), NULL,16);
            }
            else if ((SA[0]=='0')&&(SA[1]=='b'))
            {
            SA2 = (int)strtol((SA+2), NULL,2);
            }
            else
            {
             SA2 = (int)strtol(SA, NULL,10);
            }
            /*getting integer SA*/
            SA2 &=0b00000000000000000000000000011111;
            y|=(SA2<<6);
          }

	 printf("%d \n",y);
   }
   i++;
 }
 printf("%s \n",line);

 return y;
 }

/*+==========================================================================================================================*/
/*============Fourth Type=======================*/
unsigned int getothersI (void)
{   unsigned int y=0; /*the ouput of the function*/
    char temp [2];/*temp array to get the string Reg number*/
    int temp2;/*temp int to get the integer Reg number*/
    char IMM [18];/*temp array to get the string imm number as the maximum number for 16bit is 65535 five decimal digits
                  and 16 digit in case of binary and two more digits for the base type */
    int IMM2;/*temp int to get the integer imm number*/
    unsigned char count=0;/*counter for the Reg number in the instruction line */
    char line[50];/*temp array to get the whole line after the instruction*/
    unsigned char i=0;/*line cursor*/
    unsigned char j=0;/*another line cursor*/

    fgets(line,50,fpr);/*getting the whole line after the instruction*/
 while (line [i]!= '\0') /*as i am in the same line or instruction*/
 {
   if (line[i]=='R')
	   /*when you see  a capital R it means it indicates a Reg number but which one that what the count would tell us
	    * as the instruction format is instruction Rt,Rs,Imm
	          and the binary format is OPCODE      RS RT RD   SA FUNC
	     in this type we focus on the two Regs Rt,Rs and Imm
       */
   { count++;
	 temp [0]= line[i+1] ;/*getting the string reg number */
     temp [1]= line[i+2] ;
     temp2 = atoi(temp);/*converting the string number to integer*/
     printf("%d \n",temp2);
	 if (count==1)
	 {/* first reg is Rt so in the code it is shifted lift by 16 */
    	 y|=(temp2<<16);//Rt
	 }
     else if(count==2)
     {/* second reg is Rs so in the code it is shifted lift by 21 */
    	y|=(temp2<<21);
    	while (line [i+j+4]!= '\0')
    	{   IMM [j]=line [i+j+4];/*as i now on the second R of the line meaning the imm is 4 char away*/
    		j++;
    	}
    	 if ((IMM[0]=='0')&&(IMM[1]=='x'))
    	 {
    	 IMM2 = (int)strtol((IMM+2), NULL,16);
    	 }
    	 else if ((IMM[0]=='0')&&(IMM[1]=='b'))
    	 {
    	 IMM2 = (int)strtol((IMM+2), NULL,2);
    	 }
    	 else
    	 {
    	  IMM2 = (int)strtol(IMM, NULL,10);
    	 }
    	IMM2 &=0x0000ffff;/*the imm is 16bit*/
    	y|=IMM2;

     }
	 printf("%d \n",y);
   }
   i++;
 }
 printf("%s \n",line);

 return y;
 }

/*+==========================================================================================================================*/
/*============Fifth Type=======================*/
unsigned int getothersJ (void)
{   unsigned int y=0; /*the ouput of the function*/
    char IMM [28];/*temp array to get the string imm number as the maximum number for 26bit is 67108863 eight decimal digits
    				and 26 digit in case of binary and two more digits for the base type */
    int IMM2;/*temp int to get the integer imm number*/
    char line[50];/*temp array to get the whole line after the instruction*/
    unsigned char i=0;/*line cursor*/

    fgets(line,50,fpr);/*getting the whole line after the instruction*/
 while (line [i]!= '\0') /*as i am in the same line or instruction*/
 {
       IMM [i]=line [i+1];/*as i now on the second R of the line meaning the imm is 4 char away*/
    	i++;
 }
 if ((IMM[0]=='0')&&(IMM[1]=='x'))/*hex*/
 {printf("hex \n");
 IMM2 = (int)strtol((IMM+2), NULL,16);
 }
 else if ((IMM[0]=='0')&&(IMM[1]=='b'))/*binary*/
 {printf("bin \n");
 IMM2 = (int)strtol((IMM+2), NULL,2);
 }
 else/*decimal*/
 {printf("dec \n");
  IMM2 = (int)strtol(IMM, NULL,10);
 }
 IMM2 &= 0b00000011111111111111111111111111;/*as the IMM in this type is 26bit*/
 y|=IMM2;
 printf("%s \n",line);

 return y;
 }

/*+==========================================================================================================================*/
/*============Sixth Type=======================*/
unsigned int getothersluI (void)
{   unsigned int y=0; /*the ouput of the function*/
    char temp [2];/*temp array to get the string Reg number*/
    int temp2;/*temp int to get the integer Reg number*/
    char IMM [18];/*temp array to get the string imm number as the maximum number for 16bit is 65535 five decimal digits
					and 16 digit in case of binary and two more digits for the base type */
    int IMM2;/*temp int to get the integer imm number*/
    unsigned char count=0;/*counter for the Reg number in the instruction line */
    char line[50];/*temp array to get the whole line after the instruction*/
    unsigned char i=0;/*line cursor*/
    unsigned char j=0;/*another line cursor*/

    fgets(line,50,fpr);/*getting the whole line after the instruction*/
 while (line [i]!= '\0') /*as i am in the same line or instruction*/
 {
   if (line[i]=='R')
	   /*when you see  a capital R it means it indicates a Reg number but which one that what the count would tell us
	    * as the instruction format is instruction Rt,Imm
	          and the binary format is OPCODE      RS RT RD   SA FUNC
	     in this type we focus on the a Reg Rt and Imm
       */
   { count++;
	 temp [0]= line[i+1] ;/*getting the string reg number */
     temp [1]= line[i+2] ;
     temp2 = atoi(temp);/*converting the string number to integer*/
     printf("%d \n",temp2);
	 /* first reg is Rt so in the code it is shifted lift by 16 */
    	 y|=(temp2<<16);//Rt
    	 while (line [i+j+4]!= '\0') /*as i am in the same line or instruction*/
    	  {
    	        IMM [j]=line [i+j+4];/*as i now on the second R of the line meaning the imm is 4 char away*/
    	     	j++;
    	  }
    	 if ((IMM[0]=='0')&&(IMM[1]=='x'))
    	 {
    	 IMM2 = (int)strtol((IMM+2), NULL,16);
    	 }
    	 else if ((IMM[0]=='0')&&(IMM[1]=='b'))
    	 {
    	 IMM2 = (int)strtol((IMM+2), NULL,2);
    	 }
    	 else
    	 {
    	  IMM2 = (int)strtol(IMM, NULL,10);
    	 }
    	 IMM2 &=0x0000ffff;/*the imm is 16 bit*/
    	 y|=IMM2;
    	 printf("%d \n",y);
   }
   i++;
 }
 printf("%s \n",line);

 return y;
 }


/*+==========================================================================================================================*/
/*this function determine the instruction layout type*/
unsigned int getothers(unsigned int x)
{  unsigned int y;
	if ( (x==32)||(x==33)||(x==34)||(x==35)||(x==36)||(x==37)||\
	     (x==38)||(x==39)||(x==16)||(x==18)||(x==42)|| (x==43))
		{  /*first type*/
		    printf("first type \n");
			y= getothersRd();
		}
	else if ((x==8)||(x==4)||(x==5)||(x==24)||(x==25)||(x==26)||\
			 (x==27)||(x==10)||(x==11))
			{ /*second type*/
		     printf("second type \n");
			 y= getothersRs();
			}
	else if ((x==0)||(x==2)||(x==3))
			{/*third type*/
		      printf("third type \n");
				y= getothersshift();
			}
	else if( (x==536870912)||(x==603979776)||(x==805306368)||(x==872415232)||(x==671088640)||(x==738197504)||\
			 (x==2348810240)||(x==2885681152)||(x==989680)||(x==335544320))
    		{/*fourth type*/
		       printf("fourth type \n");
		   	   y= getothersI();
    		}
	else if((x==134217728)||(x==201326592))
			{/*fifth type*/
		        printf("fifth type \n");
				y= getothersJ();
			}
	else if(x==1006632960)
			{/*sixth type*/
		       printf("sixth type \n");
				y= getothersluI();
			}
	else if ((x==6)||(x=7))
			{/*hlt and nop*/
		        printf("hlt or nop \n");
				y=0x00000000;
			}
	return y;
}



/*+==========================================================================================================================*/
/*this function get the opcode and func of the instruction line*/
unsigned int getIstruction (void)
{ char instruction_name[4];/*maximum 4*/
unsigned int x;
	fscanf(fpr,"%s",instruction_name);
     if (! strcmp(instruction_name,"sll"))
	x=0x00000000;
else if (! strcmp(instruction_name,"srl"))
	 x=0x00000002;
else if (! strcmp(instruction_name,"sra"))
	 x=0x00000003;
else if (! strcmp(instruction_name,"in"))
	 x=0x00000004;
else if (! strcmp(instruction_name,"out"))
	 x=0x00000005;
else if (! strcmp(instruction_name,"hlt"))
	 x=0x00000006;
else if (! strcmp(instruction_name,"nop"))
	 x=0x00000007;
else if (! strcmp(instruction_name,"jr"))
	 x=0x00000008;
else if (! strcmp(instruction_name,"push"))
	 x=0x0000000A;
else if (! strcmp(instruction_name,"pop"))
	 x=0x0000000B;
else if (! strcmp(instruction_name,"mfhi"))
	 x=0x00000010;
else if (! strcmp(instruction_name,"mflo"))
	 x=0x00000012;
else if (! strcmp(instruction_name,"mult"))
	 x=0x00000018;
else if (! strcmp(instruction_name,"multu"))
	 x=0x00000019;
else if (! strcmp(instruction_name,"div"))
	 x=0x0000001A;
else if (! strcmp(instruction_name,"divu"))
	 x=0x0000001B;
else if (! strcmp(instruction_name,"add"))
	 x=0x00000020;
else if (! strcmp(instruction_name,"addu"))
	 x=0x00000021;
else if (! strcmp(instruction_name,"sub"))
	 x=0x00000022;
else if (! strcmp(instruction_name,"subu"))
	 x=0x00000023;
else if (! strcmp(instruction_name,"and"))
	 x=0x00000024;
else if (! strcmp(instruction_name,"or"))
	 x=0x00000025;
else if (! strcmp(instruction_name,"xor"))
	 x=0x00000026;
else if (! strcmp(instruction_name,"nor"))
	 x=0x00000027;
else if (! strcmp(instruction_name,"slt"))
	 x=0x0000002A;
else if (! strcmp(instruction_name,"sltu"))
	 x=0x0000002B;
else if (! strcmp(instruction_name,"j"))
	 x=0x08000000;
else if (! strcmp(instruction_name,"jal"))
	 x=0x0C000000;
else if (! strcmp(instruction_name,"beq"))
	 x=0x10000000;
else if (! strcmp(instruction_name,"bne"))
	 x=0x14000000;
else if (! strcmp(instruction_name,"addi"))
	 x=0x20000000;
else if (! strcmp(instruction_name,"addiu"))
	 x=0x24000000;
else if (! strcmp(instruction_name,"slti"))
	 x=0x28000000;
else if (! strcmp(instruction_name,"sltiu"))
	 x=0x2C000000;
else if (! strcmp(instruction_name,"andi"))
	 x=0x30000000;
else if (! strcmp(instruction_name,"ori"))
	 x=0x34000000;
else if (! strcmp(instruction_name,"lui"))
	 x=0x3C000000;
else if (! strcmp(instruction_name,"lw"))
	 x=0x8C000000;
else if (! strcmp(instruction_name,"sw"))
	 x=0xAC000000;
printf("%d \n",x);
return x;
}






