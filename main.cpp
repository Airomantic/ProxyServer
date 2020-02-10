#include <iostream>
#include <cstring>

int solvent(char proxy[1000][16], int n_proxy, char server[1000][16], int m_server);
/**
 * 使用代理服务器能够在一定程度上隐藏客户端信息，从而保护用户在互联网上的隐私。我们知道n个代理服务器的IP地址，现在要用它们去访问m个服务器。
 * 这 m 个服务器的 IP 地址和访问顺序也已经给出。
 * 系统在同一时刻只能使用一个代理服务器，并要求不能用代理服务器去访问和它 IP地址相同的服务器（不然客户端信息很有可能就会被泄露）。
 * 在这样的条件下，找到一种使用代理服务器的方案，使得代理服务器切换的次数尽可能得少。
 * @return
 */
int main() {
    int n_proxy, m_server, i;
    while (scanf("%d", &n_proxy) != EOF) {
        char proxy[n_proxy][16];
        for (i = 0; i <n_proxy ; i++)
            scanf("%s",proxy[i]);

        scanf("%d", &m_server);
        char server[m_server][16];
        for (i = 0; i <m_server ; i++)
            scanf("%s", server[i]);

        printf("%d\n", solvent(proxy, n_proxy, server, m_server));
    }
    return 0;
}

int solvent(char proxy[1000][16], int n_proxy, char server[1000][16], int m_server) {
    //每次调用，在目标串中找最长可以访问到的结点，从该结点开始再往后找最长
    int i, j, max;
    max = -1;
    for (i = 0; i < n_proxy; i++) {
        for (int j = 0; j < m_server; j++) {
            if (!strcmp(proxy[i], server[j])) {//匹配则返回0,代理服务器只在目标服务器中出现多次也可以
                if (j > max)
                    max = j;
                break;
            }
        }
        if (j==m_server)
            return 0;
    }
    if (n_proxy==1&&max!=-1) //只有一台代理且出现在待访问队列中，无法完成
        return -1;
    return 1+solvent(proxy,n_proxy,server+max,m_server-max);
}
