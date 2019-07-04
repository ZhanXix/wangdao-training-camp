#include "func.h"
typedef struct fd_msg
{
    int newFd;
    char ip[16];
    char name[20];
    struct fd_msg *next, *prior;
} FdMsg_t, *pFdMsg_t;

int main()
{
    int ret;
    //初始化socketFd
    int socketFd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(socketFd, -1, "socket");
    struct sockaddr_in socketAddr;
    bzero(&socketAddr, sizeof(socketAddr));
    socketAddr.sin_family = AF_INET;
    socketAddr.sin_addr.s_addr = inet_addr("192.168.5.192");
    socketAddr.sin_port = htons(2000);
    ret = bind(socketFd, (struct sockaddr *)&socketAddr, sizeof(socketAddr));
    ERROR_CHECK(ret, -1, "bind");
    listen(socketFd, 200);
    //初始化fd_msg链表
    pFdMsg_t newNode_fdMsg, pCur, pPre;
    char newname[20] = {0};
    pFdMsg_t FdMsg[256];
    bzero(FdMsg, sizeof(FdMsg));
    pFdMsg_t timeCircle[60]; //时间轮盘，超时1min断开
    bzero(timeCircle, sizeof(timeCircle));
    //epoll
    int epFd = epoll_create(1);
    struct epoll_event event, events[256];
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;
    ret = epoll_ctl(epFd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    ERROR_CHECK(ret, -1, "epoll_ctl");
    int status;
    event.events = EPOLLIN;
    event.data.fd = socketFd;
    ret = epoll_ctl(epFd, EPOLL_CTL_ADD, socketFd, &event);
    ERROR_CHECK(ret, -1, "epoll_ctl");
    int allFd, i, j;
    char buf[128] = {0};
    char sendbuf[256] = {0};
    int newFd;
    struct sockaddr_in newAddr;
    socklen_t addrLen = sizeof(newAddr);
    time_t firstTime = time(NULL), newTime = time(NULL), LastTime = time(NULL);
    int TimePoint = (newTime - firstTime) % 60,LastTimePoint;
    //printf("TimePoint:%d\n",TimePoint);
    while (1)
    {
    startcircle:
        newTime = time(NULL);
        //printf("Lasttime:%d\n",LastTime);
        //printf("newtime:%d\n",newTime);
        if (newTime > LastTime)
        {
            LastTimePoint = (LastTime - firstTime) % 60;
            TimePoint = (newTime - firstTime) % 60;
            //printf("TimePoint:%d\n",TimePoint);
            if (LastTimePoint > TimePoint)
            {
                LastTimePoint=0;
            }
            for (j = LastTimePoint; j <= TimePoint; ++j)
            {
                if (timeCircle[TimePoint] != NULL) //断开超时连接
                {
                    pPre = timeCircle[TimePoint];
                    pCur = pPre->next;
                    while (pCur)
                    {
                        pPre->next = pCur->next;
                        printf(">>>>>>>>>%s(Fd%d)已超时<<<<<<<<<\n", pCur->name, pCur->newFd);
                        close(pCur->newFd);
                        free(pCur);
                        pCur = pPre->next;
                    }
                    printf(">>>>>>>>>%s(Fd%d)已超时<<<<<<<<<\n", pPre->name, pPre->newFd);
                    close(pPre->newFd);
                    free(pPre);
                    timeCircle[TimePoint] = NULL;
                }
            }
            LastTime = newTime;
        }
        allFd = epoll_wait(epFd, events, 256, -1);
        for (i = 0; i < allFd; ++i)
        {
            if (events[i].data.fd == socketFd)
            {
                //连接新客户端
                bzero(&newAddr, sizeof(newAddr));
                newFd = accept(socketFd, (struct sockaddr *)&newAddr, &addrLen);
                bzero(newname, sizeof(newname));
                recv(newFd, newname, sizeof(newname), 0);
                printf(">>>>>>>>>用户%s已成功连接<<<<<<<<<\n", newname);
                //将新客户端加入监听
                status = fcntl(newFd, F_GETFL);
                status = status | O_NONBLOCK;
                fcntl(newFd, F_SETFL, status);
                event.events = EPOLLIN;
                event.data.fd = newFd;
                ret = epoll_ctl(epFd, EPOLL_CTL_ADD, newFd, &event);
                ERROR_CHECK(ret, -1, "epoll_ctl");
                //建立新客户端结点
                newNode_fdMsg = NULL;
                newNode_fdMsg = (pFdMsg_t)malloc(sizeof(FdMsg_t));
                bzero(newNode_fdMsg, sizeof(FdMsg_t));
                strcpy(newNode_fdMsg->ip, inet_ntoa(newAddr.sin_addr));
                printf("ip:%s\n", newNode_fdMsg->ip);
                strcpy(newNode_fdMsg->name, newname);
                newNode_fdMsg->newFd = newFd;
                printf("fd:%d\n", newNode_fdMsg->newFd);
                printf(">>>>>>>>><<<<<<<<<\n");
                //将结点加入时间轮盘
                if (timeCircle[TimePoint] == NULL)
                {
                    timeCircle[TimePoint] = newNode_fdMsg;
                    newNode_fdMsg->next = NULL;
                    newNode_fdMsg->prior = NULL;
                    //printf(">>>>>>>>>Fd%d已成功加入时间轮盘%d<<<<<<<<<\n", timeCircle[TimePoint]->newFd, TimePoint);
                }
                else
                {
                    pCur = timeCircle[TimePoint]->next;
                    pPre = timeCircle[TimePoint];
                    while (pCur)
                    {
                        pCur = pCur->next;
                        pPre = pPre->next;
                    }
                    pPre->next = newNode_fdMsg;
                    newNode_fdMsg->prior = pPre;
                    newNode_fdMsg->next = NULL;
                }
                //将结点加入总指针链表
                FdMsg[newFd] = newNode_fdMsg;
                //printf(">>>>>>>>>Fd%d已成功加入指针链表<<<<<<<<<\n", timeCircle[TimePoint]->newFd);
            }
            if (events[i].events == EPOLLIN && events[i].data.fd == STDIN_FILENO)
            {
                bzero(buf, sizeof(buf));
                ret = read(STDIN_FILENO, buf, sizeof(buf));
                if (0 == ret)
                {
                    printf(">>>>>>>>>已主动断开<<<<<<<<<\n");
                    goto end;
                }
                bzero(sendbuf, sizeof(sendbuf));
                strcpy(sendbuf, ">>>>>server<<<<< ");
                strcat(sendbuf, buf);
                for (j = 0; j < 256; ++j)
                {
                    if (FdMsg[j])
                    {
                        send(j, sendbuf, strlen(sendbuf) - 1, 0);
                    }
                }
            }
            if (FdMsg[events[i].data.fd] != NULL)
            {
                newFd = events[i].data.fd;
                bzero(buf, sizeof(buf));
                ret = recv(newFd, buf, sizeof(buf), 0);
                if (0 == ret)
                {
                    //解除监听
                    ret = epoll_ctl(epFd, EPOLL_CTL_DEL, newFd, &event);
                    ERROR_CHECK(ret, -1, "epoll_ctl");
                    close(newFd);
                    printf(">>>>>>>>>%s(Fd%d)连接已断开<<<<<<<<<\n", FdMsg[newFd]->name, FdMsg[newFd]->newFd);
                    //删除结点
                    pCur = FdMsg[newFd];
                    FdMsg[newFd] = NULL;
                    if (pCur->prior == NULL)
                    {
                        for (j = 0; j < 60; ++j)
                        {
                            if (timeCircle[j] == pCur)
                            {
                                timeCircle[j] = pCur->next;
                                break;
                            }
                        }
                    }
                    else
                    {
                        pCur->prior->next = pCur->next;
                        pCur->next->prior = pCur->prior;
                    }
                    free(pCur);
                    pCur = NULL;
                    goto startcircle;
                }
                else
                {
                    bzero(sendbuf, sizeof(sendbuf));
                    strcpy(sendbuf, FdMsg[newFd]->name);
                    strcat(sendbuf, " >>>>> ");
                    strcat(sendbuf, buf);
                    for (j = 0; j < 256; ++j)
                    {
                        if (FdMsg[j]&&j!=FdMsg[newFd]->newFd)
                        {
                            send(j, sendbuf, strlen(sendbuf), 0);
                        }
                    }
                    printf("%s\n", sendbuf);
                    //更新结点在轮盘的位置
                    //从原来位置删除
                    pCur = FdMsg[newFd];
                    if (pCur->prior == NULL)
                    {
                        for (j = 0; j < 60; ++j)
                        {
                            if (timeCircle[j] == pCur)
                            {
                                //if(j==TimePoint)//无需更新
                                //{
                                //    goto startcircle;
                                //}
                                timeCircle[j] = pCur->next;
                                break;
                            }
                        }
                    }
                    else
                    {
                        pCur->prior->next = pCur->next;
                        if (pCur->next)
                        {
                            pCur->next->prior = pCur->prior;
                        }
                    }
                    //插入新位置中
                    if (timeCircle[TimePoint] == NULL)
                    {
                        timeCircle[TimePoint] = pCur;
                        pCur->prior = NULL;
                        pCur->next = NULL;
                    }
                    else
                    {
                        pPre = timeCircle[TimePoint];
                        while (pPre->next);
                        pPre->next = pCur;
                        pCur->prior = pPre;
                        pCur->next = NULL;
                    }
                    //printf(">>>>>>>>>%s(Fd%d)已成功更新时间轮盘%d<<<<<<<<<\n", pCur->name, pCur->newFd, TimePoint);
                }
            }
        }
    }
end:
    close(epFd);
    close(socketFd);
    return 0;
}
