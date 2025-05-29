#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
  printf("Start of the main program\n");  
  int status;
  int fds[2];
  pipe(fds);
  int pid = fork();

  if (pid == -1)
  {
    printf("Failed to create child process");
  }
  if (pid == 0)
  {
    printf("This is child process id: %d \n", getpid());
    sleep(1);
    close(fds[0]);
    write(fds[1], "Hello world\n", 12);
    close(fds[1]);
    printf("Done writing from child");
  } else {
    close(fds[1]);
    wait(&status);
    printf("Parents process id: %d \n", getpid());
    printf("Status: %d\n", status);
    char str[13];
    read(fds[0], str, 12);
    str[12] = '\0';
    close(fds[0]);
    printf("[%s]", str);
  }
}
