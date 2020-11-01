// webserver.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<WinSock2.h> 
#include<minwindef.h>
#include<stdio.h>
#include<sys/stat.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
/*
WSAStartup进行初始化--> socket创建套接字---->bind绑定
--->listrn监听---->connect连接----->accept接收请求
send/recv发送或接收数据 --->WSACleanup最终关闭
*/
/*
int WSAStartup(
	WORD wVersionRequired,
	LPWSADATA lpWSAData
);
该函数的参数wVersionRequired表示WinSock2的版本号
 lpWSAData参数为指向WSADATA的指针，WSADATA结构用于
 WSAStartup初始化返回的信息。

	wVersionRequired可以使用MAKEWORD生成，在这里可以使用
	版本1.1或版本2.2，1.1只支持tcp/ip
	版本2.1则会支持更多/我们选1.1

	// 初始化完毕后创建套接字，套接字创建使用函数，函数原型:
	SOCKET WSAAPI socket(int af,int type, int protocol);	
	在函数原型中 af表示IP地址类型，使用PF_INET表示ipv4,type表示使用哪种通信
	类型，例如SOCK_STREAM表示TCP，protocol表示传输协议，使用0会根据前2个参数使用默认值。

	 //绑定服务器
	 创建完socket后需要对服务器进行绑定，配置端口信息。IP地址等。
	 首先查看bind函数需要哪一些参数，函数原型如下
	 int bind(socket socket, const sockaddr *addr, int addlen);
	 参数socket表示绑定的socket,传入socket即可，addr为 sockaddr_in的结构体变量指针
	 ，在sockaddr_in结构体变量中配置一些服务器信息，addrlen为addr的大小值
	 通过bind函数原型得知了我们所需要的数据，接下来创建一个sockaddr_in结构体变量
	 用于配置服务器信息；

	 // 4 进行监听
	 int listen(int socked, int backlog);
	 函数原型中，参数socked表示监听的套接字，backlog为设置内核中的某一些处理（此处不进行深入讲解）
	 直接设置为10即可，最大上限为128.使用监听并且判断是否成功代码为:

	 // 5获取请求
	 监听完成后开始获取请求。受限需要使用accept对套接字进行连接，accept函数原型如下：
	 int accept(int sockfd,struct sockaddr *addr, socklen_t *addrlen);
	 参数sockfd为指定的套接字，addr为指向struct sockaddr的指针，一般为客户端地址；
	 addrlen一般设置为sizeof(struct sockaddr_in)即可。

	 接下来开始接收客户端的请求， 使用recv函数，函数原型为:
	 ssize_t recv(int sockfd,void *buf,size_t len,int flags);
	 参数sockfd为accept建立的通信；buf为缓存的位置；len为缓存大小；
	 flags一般设置为0即可，

	 // 6 请求处理层编写
	 得到请求后开始编写处理层。继续接着代码往下写没有层级，编写一个函数名为
	 req.该函数接收请求信息与一个建立好的连接为参数：
	 void req(char *buf,int access_socket)

	 // 接着编写一个发送函数send_;
	 send函数功能并不难，不赘述，就是一个遍历发送的逻辑。
	 随后发送http响应与文件类型
 */
int send_(int s, char* buf, int* len)
{
	int total;
	int bytesleft;
	int n;
	total = 0;
	bytesleft = *len;
	while (total < *len)
	{
		n = send(s, buf + total, bytesleft, 0);
		if (-1 == n) {
			break;
		}
		total += n;
		bytesleft -= n;
	}
	*len = total;
	return n == -1 ? -1 : 0;
}
void req(char* request, int client_sock) {
	char arguments[BUFSIZ];
	strcpy(arguments, "./");
	// 随后分离请求与参数
	char command[BUFSIZ];
	sscanf(request, "%s%s", command, arguments + 2);
	//printf(" -----------%s %s", command, arguments);
	// 接着我们标记一些头元素
	char* extension = "text/html";
	char* content_type = "text/plain";
	char* body_length = "Content-Length: ";
	// 接着获取请求参数，若获取index.html.就获取当前路径下的该文件:
	printf("參數: %s", arguments);
	FILE* rfile = fopen(arguments, "rb");
	// 获取文件后表示请求ok,我们先返回一个200状态
	char* head = "HTTP/1.1 200 OK\r\n";
	int len;
	char ctype[30] = "Content-type:text/html\r\n";
	len = strlen(head);

	send_(client_sock, head, &len);
	len = strlen(ctype);
	send_(client_sock, ctype, &len);

	struct stat statbuf;

	char length_buf[20];
	fstat(fileno(rfile), &statbuf);
	itoa(statbuf.st_size, length_buf, 10);
	send(client_sock, body_length, strlen(body_length), 0);
	send(client_sock, length_buf, strlen(length_buf), 0);

	send(client_sock, "\n", 1, 0);
	send(client_sock, "\r\n", 2, 0);
	
	char read_buf[1024];
	len = fread(read_buf, 1, statbuf.st_size, rfile);
	if (send_(client_sock, read_buf, &len) == -1) {
		printf("error!");
	}
	return 0;
}
int main()
{
	// 声明一个WSADATA结构体 
	WSADATA wsaData;
	/* 1 WSDStartup 若初始化失败则会返回非0值 */
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
		exit(1);
	}
	int skt = socket(PF_INET, SOCK_STREAM, 0);
	//2  创建完socket后，若为-1表示创建失败，进程判断如下
	if (-1 == skt) {
		return -1;
	}
	// 3 绑定服务器
	/* 通过bind函数原型得知了我们所需要的数据，接下来创建一个sockaddr_in结构体变量
	用于配置服务器信息；*/
	struct sockaddr_in server_addr;
	// 随后配置地址家族为AF_INET对应TCP/IP
	server_addr.sin_family = AF_INET;
	// 接着配置端口信息：
	server_addr.sin_port = htons(8080);
	// 在指定IP地址
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// ip地址若不确定可以手动输入，最后使用神器memset初始化内存。
	memset(&(server_addr.sin_zero), '\0', 8);
	// 随后使用bind函数进行绑定且进行判断是否绑定成功；
	if (bind(skt, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1) {
		return -1;
	}
	//4 listen进行监听
	if (listen(skt, 10) == -1) {
		return -1;
	}
	
	
	// 5 获取请求
	while (1) {

		printf("listening ... ...\n");
		struct sockaddr_in c_skt;
		int s_size = sizeof(struct sockaddr_in);
		int access_skt = accept(skt, (struct sockaddr*) & c_skt, &s_size);
		// 接下来开始接收客户端的请求，使用recv函数，函数原型为:
		char buf[1024];
		if (recv(access_skt, buf, 1024, 0) == -1) {
			exit(1);
		}

		printf("%s", buf);
		req(buf, access_skt);
		//此时我们在到accept和recv外层添加一下循环，使之流程重复；
	}
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
