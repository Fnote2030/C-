#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include<fcntl.h> 
#include<stdlib.h> 
#include<malloc.h>
#include <sys/wait.h>

// ���浱ǰ������������
char line[512];
 
// ��������������ȵ����������
char *args[128]; //ָ��line
 
// �����������
int narg = 0;
int redir = 0;   //�ж��Ƿ����ض������
int gdflag = 0;  //�ж��Ƿ��йܵ�����
char *file;  //��¼�ض���Ŀ���ļ�
char *cmd[2][64] = {}; //�ܵ��������������

// �����������������ǰ������
void copy_args(char* cmd_args[]) 
{
    int i=0;
	int j=0;
	int num=0;
    for (i=0; i < narg; i++,j++) //NULL���Բ��ÿ��� 
	{
        cmd_args[i] = args[i];
		cmd[num][j] = args[i];
		//1���ж��������Ƿ�������ض���
		if( (strcmp( cmd_args[i], ">" ) == 0 ) || (strcmp( cmd_args[i], ">>") == 0) ) 
        {
            redir = 1;
			file = args[i+1]; //>������������Ϊ�ļ���
            cmd_args[i] = NULL;   //��ȥ���� > \ >>
        }
		//2���ж��������Ƿ��йܵ�����
		else if( strcmp( cmd_args[i],"|" ) == 0 ) 
        {
            gdflag++;
			cmd[num][j] = NULL;   //��ȥ���� |
			num +=1;
			j = -1;
        }
    }
}
 
// �ܵ���������
void gdprocess()
{
	int p1, p2;
    int fd[2];
	gdflag = 0; //�ܵ����Ŵ�����
	pipe(fd);
	p1 = fork(); // �����ӽ��� p1
	
	if (p1 == 0) 
	{
		// p1 �Ա�׼����ض���Ϊ�ܵ���д��
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execvp(cmd[0][0],cmd[0]);
		return;
	}
	p2 = fork(); // �����ӽ��� p2
	if (p2 == 0) 
	{
		// p2 �Ա�׼�����ض���Ϊ�ܵ��Ķ���
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execvp(cmd[1][0], cmd[1]);
		return;
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(p1, NULL, 0);
	waitpid(p2, NULL, 0);
	exit(0);
} 

// ִ�� ls ����
void exec_ls() 
{
    int pid = fork();
    int fd;
	char* cmd_args[64] = {};
    if (pid > 0) 
	{
        waitpid(pid, NULL, 0);
        return;
    }  
    copy_args(cmd_args);
	// printf("%s\n",cmd_args[0]);
	// printf("%s\n",file);
	
    if(redir == 1)//����������ض���
	{	
        fd = open( file,O_RDWR | O_CREAT | O_TRUNC, 0644 );
        dup2( fd,1 );    //ָ�����ļ�������Ϊ1,1Ϊ��׼�����0Ϊ��׼����
		close(fd);
		redir = 0;
    }
	
	if(gdflag > 0)//��������йܵ�
	{
		gdprocess();
	}
	else
		execv("/bin/ls", cmd_args);
}
 
// ִ�� pwd ����
void exec_pwd() 
{
    char buffer[256];
    getwd(buffer);     //��ǰ·��
    printf("%s\n", buffer);
}
 
// ִ�� cd ����
void exec_cd() 
{
    if (narg != 2) //��ʽ����
		return;
    chdir(args[1]); 
    exec_pwd();
}

//ִ��environ ����
void exec_env()
{
	execlp("env","",NULL);	
}

//echo ����Ļ����ʾ����
void exec_echo()
{
	int pid = fork();
	int fd;
	char* cmd_args[64] = {};     
	if (pid > 0) 
	{       
		waitpid(pid, NULL, 0);       
		return;
	}   
	copy_args(cmd_args);    
	if(redir == 1)//����������ض���
	{	
        fd = open( file,O_RDWR | O_CREAT | O_TRUNC, 0644 );
        dup2( fd,1 );    //ָ�����ļ�������Ϊ1,1Ϊ��׼�����0Ϊ��׼����
		close(fd);
		redir = 0;
    }
	if(gdflag > 0)//��������йܵ�
	{
		gdprocess();
	}
	else
		execv("/bin/echo", cmd_args);
}

//ִ��help
void exec_help()
{
	int pid = fork();
	if (pid > 0) 
	{
		waitpid(pid, NULL, 0);
		return;
	}  
	system("help");
}

//�����ļ�
void exec_touch() 
{  
	int pid = fork();
	char* cmd_args[64] = {};     
	if (pid > 0) 
	{       
		waitpid(pid, NULL, 0);       
		return;
	}   
	copy_args(cmd_args);    
	execv("/bin/touch", cmd_args);  
}

//�༭�ļ�
void exec_vim() 
{  
	int pid = fork();
	char* cmd_args[64] = {};     
	if (pid > 0) 
	{       
		waitpid(pid, NULL, 0);       
		return;
	}   
	copy_args(cmd_args);    
	execv("/bin/vim", cmd_args);  
}

//�����ļ���
void exec_mkdir() 
{  
	int pid = fork();   
	char* cmd_args[64] = {};   
	if (pid > 0) 
	{       
		waitpid(pid, NULL, 0);       
		return;
	}   
	copy_args(cmd_args);    
	execv("/bin/mkdir", cmd_args);  
}

//ɾ���ļ��к��ļ���
void exec_rm()
{
	int pid = fork();    
	char* cmd_args[64] = {};    
	if (pid > 0) 
	{       
		waitpid(pid, NULL, 0);       
		return;
	}   
	copy_args(cmd_args);    
	execv("/bin/rm", cmd_args); 
}

//��ʾ�ĵ�����
void exec_cat()
{
	int pid = fork();   
	char* cmd_args[64] = {};  
	int fd;
	if (pid > 0) 
	{       
		waitpid(pid, NULL, 0);       
		return;
	}   
	copy_args(cmd_args);  
	
    if(redir == 1)//����������ض���
	{	
        fd = open( file,O_RDWR | O_CREAT | O_TRUNC, 0644 );
		if (fd == -1) 
			return;
        dup2( fd,1 );    //ָ�����ļ�������Ϊ1,1Ϊ��׼�����0Ϊ��׼����
		close(fd);
		redir = 0;
    }
	if(gdflag > 0)//��������йܵ�
	{
		gdprocess();
	}
	else
		execv("/bin/cat", cmd_args); 
}

//����
void exec_copy()
{
    int pid = fork();  
	char* cmd_args[64] = {};    
    if (pid > 0) 
	{       
		waitpid(pid, NULL, 0);       
		return;
    }   
	copy_args(cmd_args);    
	execv("/bin/cp", cmd_args); 
}

//�ƶ�
void exec_move()
{
    int pid = fork();    
	char* cmd_args[64] = {};   
    if (pid > 0) {       
		waitpid(pid, NULL, 0);       
		return;
    }   
	copy_args(cmd_args);    
	execv("/bin/mv", cmd_args); 
}

//����
void exec_grep()
{
    int pid = fork();  
	int fd;	
	char* cmd_args[64] = {};   
    if (pid > 0) {       
		waitpid(pid, NULL, 0);       
		return;
    }   
	copy_args(cmd_args); 
    if(redir == 1)//����������ض���
	{	
        fd = open( file,O_RDWR | O_CREAT | O_TRUNC, 0644 );
        dup2( fd,1 );    //ָ�����ļ�������Ϊ1,1Ϊ��׼�����0Ϊ��׼����
		close(fd);
		redir = 0;
    }
	if(gdflag > 0)//��������йܵ�
	{
		gdprocess();
	}
	else
		execv("/bin/grep", cmd_args);	
}

//��ʾ��ʾ����
void show() 
{
	char *username;         //�û���
	char hostname[256] = {};//������
	char curpath[256] = {}; //��ǰ·��
	char prompt = '$';
	//��ȡ�û���
	username = getpwuid(getuid())->pw_name;
	//��ȡ������
	gethostname(hostname, sizeof(hostname));
	//��ȡ��ǰ·��
	getcwd(curpath, 256);
	
	// \033[32m ��ɫ���� \033[32;1m ����
	// \033[31m ��ɫ����
	// \033[34m ��ɫ����
	// \033[0m �ر���������
	printf("\n");
	printf("\033[32m%s@%s:~\033[34;1m%s\033[0m\n%c ",username, hostname, curpath, prompt);
}

//������
int main() 
{    
    show();
    while (gets(line)) 
	{
		narg = 0; //�����������  
		args[0] = strtok(line," ");//�ַ����ָ���������ÿ������ָ�
		//ֻ���»س�
		if(args[0] == NULL)
		{
			show();
			continue;
		}
		while(args[narg] != NULL)//���һ������ָ��ΪNULL
		{ 
			narg++; 
			args[narg] = strtok(NULL," "); //������NULL������������ָ��Ϊ��ʼλ
		} 
		
        if (strcmp(args[0], "quit") == 0) 
		{
            break;
        } 
		else if (strcmp(args[0], "ls") == 0) 
		{
            exec_ls();
        } 
		else if (strcmp(args[0], "pwd") == 0) 
		{
            exec_pwd();
        } 
		else if (strcmp(args[0], "cd") == 0) 
		{
            exec_cd();
        } 
		else if(strcmp(args[0], "env")==0)
		{
			exec_env();
		}
		else if(strcmp(args[0], "echo")==0)
		{
			exec_echo();
		}
		else if(strcmp(args[0], "help")==0)
		{
			exec_help();
		}
		else if(strcmp(args[0], "mkdir")==0)
		{
		    exec_mkdir();	
		}
		else if(strcmp(args[0], "touch")==0)
		{
			exec_touch();
		}
		else if(strcmp(args[0], "vim")==0)
		{
		    exec_vim();
		}
		else if(strcmp(args[0], "cp")==0)
		{
		    exec_copy();
		}
		else if(strcmp(args[0], "mv")==0)
		{
		    exec_move();
		}
		else if(strcmp(args[0], "rm")==0)
		{
		    exec_rm();
		}
		else if(strcmp(args[0], "cat")==0)
		{
		    exec_cat();
		}
		else if(strcmp(args[0], "grep")==0)
		{
			exec_grep();
		}
		else 
		{
			printf("command not found\n");
		}
		show();
	}//endwhile
    return 0;
}