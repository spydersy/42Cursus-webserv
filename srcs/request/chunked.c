#define MAX_SIZE 1024

char *RecvChunked(SOCKET s)
{
    int chunk_length;
    char result[MAX_SIZE];
    char *result_ptr;

    memset(result,0,sizeof(result));

    for (chunk_length=0, result_ptr=result;;)
    {
        int recv_size;
        int size;

        if (chunk_length == 0) // get chunk length
        {
            char str[MAX_SIZE];
            char *ptr;

            // RecvLn
            for (ptr=str; ptr-str+sizeof(char) < sizeof(str);)
            {
                int ret = recv(s, ptr, sizeof(char), 0);
                if (ret <= 0)
                {
                    break;
                }

                if (*ptr != '\n')
                {
                    ptr += ret;
                    continue;
                }

                if (ptr-str <= 1)
                {
                    break;
                }

                if (*(ptr-1) == '\r')
                {
                    ptr --;
                }
                break;
            }

            *ptr = '\0';

            chunk_length = (int)strtol(str, NULL, 16); // HexToInt
        }
        recv_size = MIN(sizeof(result)-(result_ptr-result)-sizeof(char), chunk_length);

        if (recv_size == 0)
        {
            break; // nothing to receive
        }

        size = recv(s, result_ptr, recv_size, 0);

        if (chunk_length >= size)
        {
            chunk_length -= size;
        }
        else
        {
            chunk_length = 0;
        }

        result_ptr += size;

        if (size == 0)
        {
            // Disconnected ?
            break;
        }

        if (chunk_length == 0) // recv '\r\n' at the end of every chunk
        {
            char str[2];
            if (recv(s, str, sizeof(str), 0) < 2)
            {
                break; // Disconnect ?
            }
        }
    }
    return strdup(result);
}