#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <getopt.h>

#define SADDR struct sockaddr
#define SLEN sizeof(struct sockaddr_in)

int main(int argc, char **argv) {
	int SERV_PORT = -1;
	int BUFSIZE = -1;
  while (1) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"BUFSIZE", required_argument, 0, 0},
					{"SERV_PORT", required_argument, 0, 0},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "", options, &option_index);

    if (c == -1)
      break;

    switch (c) {
    case 0: {
      switch (option_index) {
      case 0:
        BUFSIZE = atoi(optarg);
	if(BUFSIZE < 1)
		BUFSIZE = -1;
        break;
      case 1:
        SERV_PORT = atoi(optarg);
	if(SERV_PORT < 0)
		SERV_PORT = -1;
        break;
      default:
        printf("Index %d is out of options\n", option_index);
      }
    } break;

    case '?':
      printf("Arguments error\n");
      break;
    default:
      fprintf(stderr, "getopt returned character code 0%o?\n", c);
    }
  }

  if (BUFSIZE == -1 || SERV_PORT == -1) {
    fprintf(stderr, "Using: %s --BUFSIZE 1024 --SERV_PORT 20001\n",
            argv[0]);
    return 1;
  }



  int sockfd, n;
  char sendline[BUFSIZE], recvline[BUFSIZE + 1];
  struct sockaddr_in servaddr;
  struct sockaddr_in cliaddr;

  /*if (argc != 2) {
    printf("usage: client <IPaddress of server>\n");
    exit(1);
  }*/

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERV_PORT);

  if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 0) {
    perror("inet_pton problem");
    exit(1);
  }
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket problem");
    exit(1);
  }

  write(1, "Enter string\n", 13);

  while ((n = read(0, sendline, BUFSIZE)) > 0) {
    if (sendto(sockfd, sendline, n, 0, (SADDR *)&servaddr, SLEN) == -1) {
      perror("sendto problem");
      exit(1);
    }

    if (recvfrom(sockfd, recvline, BUFSIZE, 0, NULL, NULL) == -1) {
      perror("recvfrom problem");
      exit(1);
    }

    printf("REPLY FROM SERVER= %s\n", recvline);
  }
  close(sockfd);
}
