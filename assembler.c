
#include<stdio.h>
#include<string.h>
#include<conio.h>

int substring(char a[10],char b[10]);
void binary(int num,char []);
void hexa(char num[10],char code[17]);
void concat(char s1[17],char s2[5]);

int main()
{
	FILE *f1=fopen("inst_set.txt","r");
	FILE *fpass=fopen("inst_set.txt","r");
	FILE *f2=fopen("machine.txt","w");

	FILE *fetch1=fopen("a.txt","r");
	FILE *fcount=fopen("a.txt","r");
	FILE *fetch2=fopen("b.txt","r");
	int fetch=0,number=0;
	char lab[10][10],labline[10], w,h,ins[10],curr[10],code[17];
	int count=0,i,j=0,len=0,mid=0,l=0,u=0,found=0,flag=0,line=1,index=0,call;
	char fetchins,addins[20];
	while((fetchins=fgetc(fcount))!= EOF)
	{
		if(fetchins=='\n')
			number++;
	}
	fclose(fcount);
	printf("PASS 1\n");
	line=0;
	while((fetchins=fgetc(fpass))!= EOF)
	{	
		if(fetchins=='\n')
		{
			line++;
		 	count=0;
		}
		else if(fetchins==' ')
		{
			ins[count]='\0';
			if(substring(ins,"CALL")==0)
			{
				call=line;
				printf("%s %d\n",ins,line+1);
			}
		}
		else
			ins[count++]=fetchins;
		if(fetchins==':')
		{
			ins[count-1]='\0';
			strcpy(lab[index],ins);
			labline[index++]=line;
			printf("%s %d\n",lab[index-1],labline[index-1]);
			getch();
		}
	}
	number++;
	char **a=(char**)malloc(number*sizeof(char *));
	char **b=(char**)malloc(number*sizeof(char *));
	for(fetch=0;fetch<number;fetch++)
	{
 		a[fetch]=(char *)malloc(10*(sizeof(char )));
		a[fetch][0]='\0';
		b[fetch]=(char *)malloc(10*(sizeof(char )));
		b[fetch][0]='\0';
	}
	fetch=0;
	number=0;
	printf("INSTRUCTIONS\n");
	while((fetchins=fgetc(fetch1))!= EOF)
	{
	    addins[fetch++]=fetchins;
		if(fetchins=='\n')
		{
			addins[fetch-1]='\0';
			strcpy(a[number++],addins);
			fetch=0;
		}
	}
	addins[fetch]='\0';
	strcpy(a[number++],addins);
	fetch=0;
	number=0;
	while((fetchins=fgetc(fetch2))!= EOF)
	{
		addins[fetch++]=fetchins;
		if(fetchins=='\n')
		{
			addins[fetch-1]='\0';
			strcpy(b[number++],addins);
			fetch=0;
		}
	}
	addins[fetch]='\0';
	strcpy(b[number++],addins);
	fetch=0;
	while(fetch++<number)
	{
		printf("\n %d %s %s",fetch-1,a[fetch-1],b[fetch-1]);
	}
	printf("\n\nPASS 2\n");
	printf("Assembly Language code-> Machine Language\n");
	ins[0]='\0';
	while((w=fgetc(f1))!= EOF)
	{	
		if(w=='@')
		{
			printf("Code breaked ins=%s line=%d",ins,line);
			exit(0);
		}
		if(flag>0)
		flag--;	
		if(w!='\n'&&w!=' '&&w!=',')
		{
				ins[count++]=w;
		}
		else if(w==' '||w=='\n'||w==',')
		{
			ins[count]='\0';
			count=0;
			if(w==' ')
			{
				strcpy(curr,ins);
			}
		}
	    if(w==':')
		 {
		  flag=2;
	     }
		if(count==0&&flag==0)
		{
			if(len==16)
			{
				len=0;
				fputc('\n',f2);
				printf("\n");
			}
			l=0;
			found=0;
			u=number-1;
			while(1)
			{
				mid=(u+l)/2;
				if(strcmp(ins,a[mid])>0)
					l=mid;
				else if(strcmp(ins,a[mid])<0)
					u=mid;
				else if(strcmp(ins,a[mid])==0)
				{
				break;
				}
				if(l>=76)
				break;
				if(u-l==1)
				break;
		}
		if((strcmp(a[mid],ins)!=0&&(ins[0]<'0'||ins[0]>'9'))||l==76)
		{
			found=0;
			for(j=0;j<index;j++)
			{
				if(strcmp(lab[j],ins)==0)	
				{
					found++;
				}
			}
			if(found==0)
			{
			 	printf("ERROR : instruction '%s' not found",ins);
				printf("\nPress h for help-");
				scanf("%c",&h);
				if(h=='h')
				{
					printf("\nKindly use the following instruction-");	
					for(j=0;j<number;j++)
					{
						if(ins[0]==a[j][0])
							printf("\n%s",a[j]);
					}
				}
				exit(0);
			}
		}
		if((substring(curr,"CALL")==0&&substring(ins,"CALL")!=0)||(substring(curr,"RET")==0&&substring(ins,"RET")!=0)||(substring(curr,"JMP")==0&&substring(ins,"JMP")!=0))
		 {
			for(j=0;j<index;j++)
			{
				if(strcmp(lab[j],ins)==0)
				{
					if(substring(curr,"RET")==0)
					binary(call,code);
					else
					binary(labline[j],code);
					printf("%s %s\n",lab[j],code);
				fputs(code,f2);	
				break;	
				}
			}
			if(index==j)
			{
			 	printf("Label %s not found",ins);
				exit(0);
			}
			getch();
			len=16;
		 }
		else if(strcmp(curr,"MVI")==0&&substring(ins,"R")!=0&&substring(ins,"M")!=0)
		{
			int num=0;
			for(j=0;ins[j]!='\0';j++)
				num=num*10+(ins[j]-48);
			binary(num,code);	
			printf("%s- %s\n\n",ins,code);
			fputs(code,f2);	
			fputc('\n',f2);
			len=0;
			getch();
		}
		else if((strcmp(curr,"LOAD")==0&&(substring(ins,"R")!=0)&&(substring(ins,"L")!=0)))
		{
			hexa(ins,code);	
			printf("%s- %s\n\n",ins,code);
			getch();
			fputs(code,f2);	
			fputc('\n',f2);
			getch();
			len=0;
		}
		else if((strcmp(curr,"STR")==0&&(substring(ins,"R")!=0)&&(substring(ins,"S")!=0)))
		{
			hexa(ins,code);	
			printf("%s- %s\n\n",ins,code);
			getch();
			fputs(code,f2);	
			fputc('\n',f2);
			getch();
			len=0;
		}
		else
		 {
			for(j=0;b[mid][j]!='\0';j++)
			{
			len++;
			}
			printf("%s- %s \n ",a[mid],b[mid]);
			fputs(b[mid],f2);
		 }
		}
		if(strcmp(ins,"HLT")==0)
		{
			fputc('\n',f2);	
			printf("HLT - 1111111111110000");
			fputs("1111111111110000",f2);
		}
	 if(w=='\n')
	 	{
	 	curr[0]='\0';
	 	line++;
		}
	}
	return 0;
}
void binary(int num,char code[17])
{
	int i=0;
	while(num>0)
	{
		if(num%2==1)
		code[i++]='1';
	 	else 
	 	code[i++]='0';
		num/=2;
	}
	for(;i<16;i++)
	{
		code[i]='0';
	}	
	code[16]='\0';
	strrev(code);
	return code;
}
void hexa(char num[5],char code[17])
{
	code[0]='\0';
	int i=0,len;
	len=strlen(num);
	for(i=4;i>len;i--)
	    concat(code,"0000");
        
	for(i=0;num[i]!='\0';num++)
	{
		switch(num[i])
		{
        case '0':
            concat(code,"0000"); break;
        case '1':
            concat(code,"0001"); break;
        case '2':
            concat(code,"0010"); break;
        case '3':
            concat(code,"0011"); break;
        case '4':
            concat(code,"0100"); break;
        case '5':
            concat(code,"0101"); break;
        case '6':
            concat(code,"0110"); break;
        case '7':
            concat(code,"0111"); break;
        case '8':
            concat(code,"1000"); break;
        case '9':
            concat(code,"1001"); break;
        case 'A':
            concat(code,"1010"); break;
        case 'B':
            concat(code,"1011"); break;
        case 'C':
            concat(code,"1100"); break;
        case 'D':
            concat(code,"1101"); break;
        case 'E':
            concat(code,"1110"); break;
        case 'F':
            concat(code,"1111");
        }
	}
	code[17]='\0';
}
void concat(char s1[17],char s2[5])
{
	int i=0,len;
	for(len=0;s1[len]!='\0';len++);
	for(i=0;s2[i]!='\0';i++)
	{
		s1[len++]=s2[i];
	}
	s1[len]='\0';
}
int substring(char a[10],char b[10])
{
	int i=0;
	for(i=0;b[i]!='\0';i++)
	{
		if(a[i]!=b[i])
		return -1;
	}
	return 0;
}
